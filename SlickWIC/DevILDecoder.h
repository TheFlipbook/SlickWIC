#pragma once

#include "stdafx.h"

#include <sstream>
#include <vector>

#include "DevILFrame.h"
#include "SlickWICGUIDs.h"
#include "Registrar.h"

namespace Slick
{

    // --------------------------------------------------------------------------------------------
    class DecoderFormat_TGA
    {
    public:
        static const wchar_t* Extension() { return L"tga"; }
        static const wchar_t* DotExtension() { return L".tga"; }
        static const wchar_t* TypeName() { return L"tgafile"; }
        static const wchar_t* FriendlyName() { return L"TGA File"; }
        static const wchar_t* ContentType() { return L"image/x-tga"; }
        
        
        static const GUID DecoderKey() { return WICGUID::ID::Decoder_TGA; }
        static const wchar_t* DecoderKeyStr() { return WICGUID::Str::Decoder_TGA; }

        static const GUID FileKey() { return WICGUID::ID::File_TGA; }
        static const wchar_t* FileKeyStr() { return WICGUID::Str::File_TGA; }

        static const ILuint ILType() { return IL_TGA; }

        static void RegisterPattern( Slick::IRegistrar &reg, const std::wstring &patternsKey )
        {
            std::wstringstream patternsItem;
            patternsItem << patternsKey << "\\0";
            reg.SetDWord( patternsItem.str().c_str(), L"EndOfStream", 1 );
            reg.SetDWord( patternsItem.str().c_str(), L"Position", 18 );

        
            const char * pattern = "TRUEVISION-XFILE";
            const unsigned int length = 16;
            BYTE mask[length];
            std::fill_n( mask, length, 0xFF );

            reg.SetDWord( patternsItem.str().c_str(), L"Length", length );
            reg.SetBytes( patternsItem.str().c_str(), L"Pattern", pattern, length );
            reg.SetBytes( patternsItem.str().c_str(), L"Mask", mask, length );
        }
    };

    // --------------------------------------------------------------------------------------------
    class DecoderFormat_PSD
    {
    public:
        static const wchar_t* Extension() { return L"psd"; }
        static const wchar_t* DotExtension() { return L".psd"; }
        static const wchar_t* TypeName() { return L"psdfile"; }
        static const wchar_t* FriendlyName() { return L"PSD File"; }
        static const wchar_t* ContentType() { return L"image/x-psd"; }
        
        
        static const GUID DecoderKey() { return WICGUID::ID::Decoder_PSD; }
        static const wchar_t* DecoderKeyStr() { return WICGUID::Str::Decoder_PSD; }

        static const GUID FileKey() { return WICGUID::ID::File_PSD; }
        static const wchar_t* FileKeyStr() { return WICGUID::Str::File_PSD; }

        static const ILuint ILType() { return IL_PSD; }

        static void RegisterPattern( Slick::IRegistrar &reg, const std::wstring &patternsKey )
        {
            std::wstringstream patternsItem;
            patternsItem << patternsKey << "\\0";
            reg.SetDWord( patternsItem.str().c_str(), L"Position", 0 );

        
            const char * pattern = "8BPS";
            const unsigned int length = 4;
            BYTE mask[length];
            std::fill_n( mask, length, 0xFF );

            reg.SetDWord( patternsItem.str().c_str(), L"Length", length );
            reg.SetBytes( patternsItem.str().c_str(), L"Pattern", pattern, length );
            reg.SetBytes( patternsItem.str().c_str(), L"Mask", mask, length );
        }
    };

    // --------------------------------------------------------------------------------------------
    class DecoderFormat_DDS
    {
    public:
        static const wchar_t* Extension() { return L"dds"; }
        static const wchar_t* DotExtension() { return L".dds"; }
        static const wchar_t* TypeName() { return L"ddsfile"; }
        static const wchar_t* FriendlyName() { return L"Direct Draw Surface"; }
        static const wchar_t* ContentType() { return L"image/x-dds"; }
        
        
        static const GUID DecoderKey() { return WICGUID::ID::Decoder_DDS; }
        static const wchar_t* DecoderKeyStr() { return WICGUID::Str::Decoder_DDS; }

        static const GUID FileKey() { return WICGUID::ID::File_DDS; }
        static const wchar_t* FileKeyStr() { return WICGUID::Str::File_DDS; }

        static const ILuint ILType() { return IL_DDS; }

        static void RegisterPattern( Slick::IRegistrar &reg, const std::wstring &patternsKey )
        {
            std::wstringstream patternsItem;
            patternsItem << patternsKey << "\\0";
            reg.SetDWord( patternsItem.str().c_str(), L"Position", 0 );

        
            const char * pattern = "DDS";
            const unsigned int length = 3;
            BYTE mask[length];
            std::fill_n( mask, length, 0xFF );

            reg.SetDWord( patternsItem.str().c_str(), L"Length", length );
            reg.SetBytes( patternsItem.str().c_str(), L"Pattern", pattern, length );
            reg.SetBytes( patternsItem.str().c_str(), L"Mask", mask, length );
        }
    };

    // --------------------------------------------------------------------------------------------
    template< class T >
    class SlickDecoderFactory : public IClassFactory, public IUnknownImpl
    {
    public:
        virtual ~SlickDecoderFactory(){};

        // IUnknown
        virtual ULONG STDMETHODCALLTYPE AddRef ()
        {
            return IUnknownImpl::AddRef();
        }
        
        virtual ULONG STDMETHODCALLTYPE Release()
        {
            return IUnknownImpl::Release();
        }

        virtual HRESULT STDMETHODCALLTYPE QueryInterface ( REFIID riid, void **ppvObject )
        {
            if( ppvObject )
            {
                if( riid == IID_IClassFactory )
                {
                    *ppvObject = this;
                    AddRef();
                    return S_OK;
                }

                return IUnknownImpl::QueryInterface( riid, ppvObject );
            }
                
            return E_INVALIDARG;
        }

        // IClassFactory
        virtual HRESULT STDMETHODCALLTYPE CreateInstance( IUnknown *pUnkOuter, REFIID riid, void **ppvObject )
        {
            if( ppvObject )
            {
                T *decoder = new T();
                if(!decoder)
                    return E_OUTOFMEMORY;

                return decoder->QueryInterface( riid, ppvObject );
            }

            return E_INVALIDARG;
        }

        virtual HRESULT STDMETHODCALLTYPE LockServer( BOOL fLock )
        {
            return CoLockObjectExternal( static_cast<IUnknownImpl*>(this), fLock, FALSE );
        };

    };


    // --------------------------------------------------------------------------------------------
    template< class T >
    class SlickDecoder : public IWICBitmapDecoder, public IUnknownImpl
    {
    public:
        typedef std::vector<DevILFrame*> FrameCollection;
        typedef SlickDecoderFactory< SlickDecoder<T> > Factory;
        typedef T Format;

		SlickDecoder()
		    : m_pImagingFactory( 0 )
		    , m_pComponentFactory( 0 )
            , m_frames()
		{
		}

        virtual ~SlickDecoder(){};

        virtual void STDMETHODCALLTYPE ReleaseMembers();

        // IUnknown
        virtual ULONG STDMETHODCALLTYPE AddRef (){ return IUnknownImpl::AddRef(); }
        virtual ULONG STDMETHODCALLTYPE Release(){ return IUnknownImpl::Release(); }
        virtual HRESULT STDMETHODCALLTYPE QueryInterface ( REFIID riid, void **ppvObject );

		// Required methods
		virtual HRESULT STDMETHODCALLTYPE QueryCapability ( IStream *pIStream, DWORD *pdwCapabilities );
		virtual HRESULT STDMETHODCALLTYPE Initialize ( IStream *pIStream, WICDecodeOptions cacheOptions );
		virtual HRESULT STDMETHODCALLTYPE GetContainerFormat ( GUID *pguidContainerFormat );
		virtual HRESULT STDMETHODCALLTYPE GetDecoderInfo ( IWICBitmapDecoderInfo **pIDecoderInfo );
		virtual HRESULT STDMETHODCALLTYPE GetFrameCount ( UINT *pCount );
		virtual HRESULT STDMETHODCALLTYPE GetFrame( UINT index, IWICBitmapFrameDecode **ppIBitmapFrame );

		// Optional methods
		virtual HRESULT STDMETHODCALLTYPE GetPreview ( IWICBitmapSource **ppIPreview );
		virtual HRESULT STDMETHODCALLTYPE GetThumbnail ( IWICBitmapSource **ppIThumbnail );
		virtual HRESULT STDMETHODCALLTYPE GetColorContexts ( UINT cCount, IWICColorContext **ppIColorContexts, UINT *pcActualCount );
		virtual HRESULT STDMETHODCALLTYPE GetMetadataQueryReader ( IWICMetadataQueryReader **ppIMetadataQueryReader);
		virtual HRESULT STDMETHODCALLTYPE CopyPalette ( IWICPalette *pIPalette );

        // Codec Registration
        static void STDMETHODCALLTYPE Register( Slick::IRegistrar &reg );

	private:
		IWICImagingFactory *m_pImagingFactory;
		IWICComponentFactory *m_pComponentFactory;

        FrameCollection m_frames;
    };

    // --------------------------------------------------------------------------------------------
    template<class T>
    void SlickDecoder<T>::ReleaseMembers()
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

    // --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::QueryInterface( REFIID riid, void **ppvObject )
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

    // --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::QueryCapability ( IStream *pIStream, DWORD *pdwCapabilities )
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

    // --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::Initialize ( IStream *pIStream, WICDecodeOptions cacheOptions )
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

						result = DevILFrame::Create( m_pImagingFactory, T::ILType(), imageData, amountRead, &frame);
                        
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

    // --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::GetContainerFormat ( GUID *pguidContainerFormat )
	{
		if( pguidContainerFormat )
		{
			*pguidContainerFormat = T::FileKey();
			return S_OK;
		}

		return E_POINTER;
	}


    // --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::GetDecoderInfo ( IWICBitmapDecoderInfo **pIDecoderInfo )
	{
		if( pIDecoderInfo )
		{
			HRESULT result;
			IWICComponentInfo* pComponentInfo = NULL;
			result = m_pComponentFactory->CreateComponentInfo( T::DecoderKey(), &pComponentInfo );
			if (pComponentInfo)
			{
				result = pComponentInfo->QueryInterface( IID_IWICBitmapDecoderInfo, (void**)pIDecoderInfo );
				pComponentInfo->Release();
			}

			return result;
		}

		return E_INVALIDARG;
	}

	// --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::GetFrameCount ( UINT *pCount )
	{
		if( pCount )
		{
            *pCount = static_cast<UINT>( m_frames.size() );
			return S_OK;
		}

		return E_INVALIDARG;
	}

	// --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::GetFrame( UINT index, IWICBitmapFrameDecode **ppIBitmapFrame )
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

    // --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::GetPreview( IWICBitmapSource **ppIPreview )
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
	
	// --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::GetThumbnail( IWICBitmapSource **ppIThumbnail )
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

	// --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::GetColorContexts( UINT cCount, IWICColorContext **ppIColorContexts, UINT *pcActualCount )
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

	// --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::GetMetadataQueryReader( IWICMetadataQueryReader **ppIMetadataQueryReader )
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

	// --------------------------------------------------------------------------------------------
    template< class T >
    HRESULT SlickDecoder<T>::CopyPalette( IWICPalette *pIPalette )
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

    // --------------------------------------------------------------------------------------------
    template< class T >
    void SlickDecoder<T>::Register( Slick::IRegistrar &reg )
	{
        std::wstring pre( L"CLSID\\" );
        
        // Filettype subsection
        // --------------------

        // Tells WIC that this decoder exists
        std::wstringstream wicKey;
        wicKey << pre << CommonGUID::Str::WIC << L"\\Instance\\" << Format::DecoderKeyStr(); 
        reg.SetString( wicKey.str().c_str(), L"", L"" );
        reg.SetString( wicKey.str().c_str(), L"CLSID", Format::DecoderKeyStr() );
        reg.SetString( wicKey.str().c_str(), L"FriendlyName", L"SlickWIC" );

        // Information about decoder
        std::wstringstream decoderKey;
        decoderKey << pre << Format::DecoderKeyStr();
        reg.SetString( decoderKey.str().c_str(), L"Date", _T(__DATE__) );
        reg.SetString( decoderKey.str().c_str(), L"FriendlyName", L"SlickWIC" );                // Required by Specification
        reg.SetString( decoderKey.str().c_str(), L"VendorGUID", WICGUID::Str::Vendor );         // Required by Specification

        // Information about the File type
        reg.SetString( decoderKey.str().c_str(), L"ContainerFormat", Format::FileKeyStr() );
        reg.SetString( decoderKey.str().c_str(), L"MimeTypes", Format::ContentType() );         // Required by Specification
        reg.SetString( decoderKey.str().c_str(), L"FileExtensions", Format::DotExtension() );   // Required by Specification
        
        // Formats Folder
        std::wstringstream formatKey;
        formatKey << decoderKey.str() << L"\\Formats";
        reg.SetString( formatKey.str().c_str(), L"", L"" );

        // Individual pixel formats supported.
        std::wstringstream formatItem;
        formatItem << formatKey.str() << "\\" << CommonGUID::Str::WICID_32BitRGBAlpha;
        reg.SetString( formatItem.str().c_str(), L"Formats", CommonGUID::Str::WICID_24BitRGB ); // Required by Specification

        // Pattern Match to get WIC to send a file this way
        std::wstringstream patternsKey;
        patternsKey << decoderKey.str() << L"\\Patterns";
        reg.SetString( patternsKey.str().c_str(), L"", L"" );
        Format::RegisterPattern( reg, patternsKey.str() );


        // Explorer Subsection
        // -------------------

        // Thumbnail Provider
        std::wstringstream thumbKey;
        thumbKey << Format::DotExtension() << L"\\ShellEx\\" << CommonGUID::Str::Explorer;
        reg.SetString( thumbKey.str().c_str(), L"", CommonGUID::Str::Thumbnail );

        // System Thumbnailer
        std::wstringstream sysKey;
        sysKey << "SystemFileAssociations\\" << Format::DotExtension() << L"\\ShellEx\\" << CommonGUID::Str::Explorer;
        reg.SetString( sysKey.str().c_str(), L"", CommonGUID::Str::Thumbnail );
        
        // Content Search
        std::wstringstream signalKey;
        signalKey << Format::DotExtension();
        reg.SetString( signalKey.str().c_str(), L"Content Type", Format::ContentType() );
        reg.SetString( signalKey.str().c_str(), L"PerceivedType", L"image" );

        // Photo Gallery
        std::wstringstream extKey;
        extKey << Format::DotExtension();
        reg.SetString( extKey.str().c_str(), L"", Format::TypeName() );

        std::wstring sysPrefix( L"SystemFileAssociations\\" );
        
        std::wstringstream openWithKey;
        openWithKey << Format::DotExtension() << "\\OpenWithProgids";
        reg.SetString( openWithKey.str().c_str(), Format::TypeName(), L"" );

        std::wstringstream openListKey;
        openListKey << Format::DotExtension() << "\\OpenWithList\\PhotoViewer.dll";
        reg.SetString( openListKey.str().c_str(), L"", L"" );
        std::wstringstream sysOpenListKey;
        sysOpenListKey << sysPrefix << openListKey.str();
        reg.SetString( sysOpenListKey.str().c_str(), L"", L"" );

        std::wstringstream contextKey;
        contextKey << Format::DotExtension() << "\\ShellEx\\ContextMenuHandlers\\ShellImagePreview";
        reg.SetString( contextKey.str().c_str(), L"", CommonGUID::Str::Gallery );
        std::wstringstream sysContextKey;
        sysContextKey << sysPrefix << contextKey.str();
        reg.SetString( sysContextKey.str().c_str(), L"", L"" );

        std::wstringstream progidKey;
        progidKey << Format::TypeName() ;
        reg.SetString( progidKey.str().c_str(), L"", Format::FriendlyName() );
        
        std::wstringstream shellKey;
        shellKey << progidKey.str() << "\\shell";

        std::wstringstream openKey;
        openKey << shellKey.str() << "\\open";
        reg.SetExpand( openKey.str().c_str(), L"MuiVerb", L"@%ProgramFiles%\\Windows Photo Viewer\\photoviewer.dll,-3043" );
        
        std::wstringstream commandKey;
        commandKey << openKey.str() << "\\command";
        reg.SetExpand( commandKey.str().c_str(), L"", L"%SystemRoot%\\System32\\rundll32.exe \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen %1" );
        
        std::wstringstream dropKey;
        dropKey << openKey.str() << "\\DropTarget";
        reg.SetString( dropKey.str().c_str(), L"Clsid", CommonGUID::Str::Gallery );
        
        std::wstringstream printKey;
        printKey << shellKey.str() << "\\printto\\command";
        reg.SetExpand( printKey.str().c_str(), L"", L"\"%SystemRoot%\\System32\\rundll32.exe\" \"%SystemRoot%\\System32\\shimgvw.dll\",ImageView_PrintTo /pt \"%1\" \"%2\" \"%3\" \"%4\"");


        // Codec DLL Binding
        // -----------------
        HMODULE curModule = GetModuleHandle( L"SlickWIC.dll" );
        wchar_t tempFileName[MAX_PATH];
        if( s_hInstance != NULL )
        {
            GetModuleFileName( s_hInstance, tempFileName, MAX_PATH );
            std::wstringstream inprocKey;
            inprocKey << decoderKey.str() << "\\InprocServer32";
            reg.SetString( inprocKey.str().c_str(), L"", tempFileName );
            reg.SetString( inprocKey.str().c_str(), L"ThreadingModel", L"Apartment" );
        }
	}


    typedef SlickDecoder<DecoderFormat_TGA> SlickDecoder_TGA;
    typedef SlickDecoder<DecoderFormat_PSD> SlickDecoder_PSD;
    typedef SlickDecoder<DecoderFormat_DDS> SlickDecoder_DDS;
};