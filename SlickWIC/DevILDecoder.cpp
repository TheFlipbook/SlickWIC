#include "stdafx.h"
#include "DevILDecoder.h"

#include "DevILFrame.h"
#include "SlickWICGUIDs.h"

#include <limits.h>
namespace Slick
{
    void DevILDecoder::ReleaseMembers()
    {
        if( m_pComponentFactory )
            m_pComponentFactory->Release();
        
        if( m_pImagingFactory )
            m_pImagingFactory->Release();

        for( size_t i = 0; i < m_frames.size(); ++i )
        {
            (m_frames[i])->Release();
            m_frames[i] = NULL;
        }

        m_frames.clear();
    }

    HRESULT DevILDecoder::QueryInterface ( REFIID riid, void **ppvObject )
    {
        if( ppvObject )
        {
            if( riid == IID_IWICBitmapDecoder )
            {
                *ppvObject = this;
                AddRef();
                return S_OK;
            }

            return IUnknownImpl::QueryInterface( riid, ppvObject );
        }

        return E_INVALIDARG;
    }

	// Required methods
	HRESULT DevILDecoder::QueryCapability ( IStream *pIStream, DWORD *pdwCapabilities )
	{
		if( pIStream && pdwCapabilities) 
		{
			*pdwCapabilities  = 0;
            *pdwCapabilities |= WICBitmapDecoderCapabilityCanDecodeThumbnail;
			*pdwCapabilities |= WICBitmapDecoderCapabilityCanDecodeSomeImages;

			return S_OK;
		}

		return E_INVALIDARG;
	}

	HRESULT DevILDecoder::Initialize ( IStream *pIStream, WICDecodeOptions cacheOptions )
	{
		if( pIStream )
		{
			HRESULT result;

			// Windows Factory
			result = CoInitialize( NULL );
			result = CoCreateInstance( CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&m_pImagingFactory );
            result = m_pImagingFactory->QueryInterface( IID_IWICComponentFactory, (void**)&m_pComponentFactory );

			// Image Data
			STATSTG stats;
			result = pIStream->Stat( &stats, STATFLAG_NONAME ); //! Name not allocated.

			if( S_OK == result )
			{
				// DevIL
				ilInit();
                iluInit();

                ilEnable(IL_ORIGIN_SET);
                ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

				// Verify image is small enough
				if( 0 == stats.cbSize.HighPart )
				{
					// ALLOCATE imageData
					ILubyte *imageData = (ILubyte*)malloc(stats.cbSize.LowPart);

					// Read Data
					ULONG amountRead;
					result = pIStream->Read( imageData, stats.cbSize.LowPart, &amountRead);
					if( S_OK == result && 0 < amountRead )
					{
                        DevILFrame *frame = NULL;

						result = DevILFrame::Create( m_pImagingFactory, IL_TGA, imageData, amountRead, &frame);
                        
                        if( frame )
                        {
                            m_frames.push_back( frame );
                        }
					}

                    // FREE imageData
                    free( imageData );

                    return result;
				}
                else
                {
                    return WINCODEC_ERR_IMAGESIZEOUTOFRANGE;
                }
			}

            return result;
		}

		return E_INVALIDARG;
	}

	HRESULT DevILDecoder::GetContainerFormat ( GUID *pguidContainerFormat )
	{
		if( pguidContainerFormat )
		{
			*pguidContainerFormat = WICGUID::ID::File_TGA;
			return S_OK;
		}

		return E_POINTER;
	}

	HRESULT DevILDecoder::GetDecoderInfo ( IWICBitmapDecoderInfo **pIDecoderInfo )
	{
		if( pIDecoderInfo )
		{
			HRESULT result;
			IWICComponentInfo* pComponentInfo = NULL;
			result = m_pComponentFactory->CreateComponentInfo( WICGUID::ID::Decoder, &pComponentInfo );
			if (pComponentInfo)
			{
				result = pComponentInfo->QueryInterface( IID_IWICBitmapDecoderInfo, (void**)pIDecoderInfo );
				pComponentInfo->Release();
			}

			return result;
		}

		return E_INVALIDARG;
	}

	HRESULT DevILDecoder::GetFrameCount ( UINT *pCount )
	{
		if( pCount )
		{
            *pCount = static_cast<UINT>( m_frames.size() );
			return S_OK;
		}

		return E_INVALIDARG;
	}

	HRESULT DevILDecoder::GetFrame( UINT index, IWICBitmapFrameDecode **ppIBitmapFrame )
	{
		if( ppIBitmapFrame )
		{
            if( index < m_frames.size() && m_frames[index]  )
            {
                *ppIBitmapFrame = m_frames[index];
                (*ppIBitmapFrame)->AddRef();
			    return S_OK;
            }
            else
            {
                return WINCODEC_ERR_FRAMEMISSING;
            }
		}

		return E_INVALIDARG;
	}

	// Optional methods
	HRESULT DevILDecoder::GetPreview( IWICBitmapSource **ppIPreview )
	{
        if( ppIPreview )
        {
            if( 0 < m_frames.size() )
            {
                if( m_frames[0] )
                {
                    *ppIPreview = m_frames[0]->m_image;
                    (*ppIPreview)->AddRef();
                    return S_OK;
                }

                return E_POINTER;
            }
            
            return WINCODEC_ERR_CODECNOTHUMBNAIL;
        }

        return E_INVALIDARG;
	}
	
	HRESULT DevILDecoder::GetThumbnail( IWICBitmapSource **ppIThumbnail )
	{
        if( ppIThumbnail )
        {
            if( 0 < m_frames.size() )
            {
                if( m_frames[0] )
                {
                    return m_frames[0]->GetThumbnail(ppIThumbnail);
                }

                return E_POINTER;
            }
            
            return WINCODEC_ERR_CODECNOTHUMBNAIL;
        }

        return E_INVALIDARG;
	}

	HRESULT DevILDecoder::GetColorContexts( UINT cCount, IWICColorContext **ppIColorContexts, UINT *pcActualCount )
	{
        if( ppIColorContexts && pcActualCount )
        {
            if( 0 < m_frames.size() )
            {
                if( m_frames[0] )
                {
                    return m_frames[0]->GetColorContexts(cCount, ppIColorContexts, pcActualCount);
                }

                return E_POINTER;
            }

            return WINCODEC_ERR_UNSUPPORTEDOPERATION;
        }

        return E_INVALIDARG;
	}

	HRESULT DevILDecoder::GetMetadataQueryReader( IWICMetadataQueryReader **ppIMetadataQueryReader )
	{
        if( ppIMetadataQueryReader )
        {
            if( 0 < m_frames.size() )
            {
                if( m_frames[0] )
                {
                    return m_frames[0]->GetMetadataQueryReader(ppIMetadataQueryReader);
                }

                return E_POINTER;
            }

            return WINCODEC_ERR_UNSUPPORTEDOPERATION;
        }

        return E_INVALIDARG;
	}

	HRESULT DevILDecoder::CopyPalette( IWICPalette *pIPalette )
	{
        if( pIPalette )
        {
            if( 0 < m_frames.size() )
            {
                if( m_frames[0] )
                {
                    return m_frames[0]->CopyPalette(pIPalette);
                }

                return E_POINTER;
            }

            return WINCODEC_ERR_UNSUPPORTEDOPERATION;
        }

        return E_INVALIDARG;
	}
}