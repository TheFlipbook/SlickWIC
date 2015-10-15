#pragma once

#include "stdafx.h"

#include <vector>

#include "DevILFrame.h"

namespace Slick
{
	// Interface with WIC

	class DevILDecoder : public IWICBitmapDecoder, public IUnknownImpl
	{
        typedef std::vector<DevILFrame*> FrameCollection;

    public:

		DevILDecoder()
		: m_pImagingFactory( 0 )
		, m_pComponentFactory( 0 )
        , m_frames()
		{
		}

        virtual ~DevILDecoder(){};

        void STDMETHODCALLTYPE ReleaseMembers();

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

	private:
		IWICImagingFactory *m_pImagingFactory;
		IWICComponentFactory *m_pComponentFactory;

        FrameCollection m_frames;
	};
};