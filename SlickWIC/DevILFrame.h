#pragma once

#include "stdafx.h"


namespace Slick
{
	// Actual Image Display Data
	class DevILFrame : public IWICBitmapFrameDecode, public IUnknownImpl
	{
	public:
        static HRESULT Create ( IWICImagingFactory *pImagingFactory, ILuint type, ILubyte *data, ILuint size, DevILFrame **frame );

        DevILFrame( IWICBitmap *image );
        virtual ~DevILFrame();

        // IUnknown
        virtual ULONG STDMETHODCALLTYPE AddRef (){ return IUnknownImpl::AddRef(); }
        virtual ULONG STDMETHODCALLTYPE Release(){ return IUnknownImpl::Release(); }
        virtual HRESULT STDMETHODCALLTYPE QueryInterface ( REFIID riid, void **ppvObject );

		// Required IWICBitmapFrameDecode
		virtual HRESULT STDMETHODCALLTYPE GetThumbnail ( IWICBitmapSource **ppIThumbnail );
		virtual HRESULT STDMETHODCALLTYPE GetColorContexts ( UINT cCount, IWICColorContext **ppIColorContexts, UINT *pcActualCount );
		virtual HRESULT STDMETHODCALLTYPE GetMetadataQueryReader ( IWICMetadataQueryReader **ppIMetadataQueryReader);
		
		// IWICBitmapSource
		virtual HRESULT STDMETHODCALLTYPE GetSize ( UINT *puiWidth, UINT *puiHeight );
		virtual HRESULT STDMETHODCALLTYPE GetPixelFormat ( WICPixelFormatGUID *pPixelFormat );
		virtual HRESULT STDMETHODCALLTYPE GetResolution ( double *pDpiX, double *pDpiY );
		virtual HRESULT STDMETHODCALLTYPE CopyPixels ( const WICRect *prc, UINT cbStride, UINT cbBufferSize, BYTE *pbBuffer );

		// IWICBitmapSource [Optional]
		virtual HRESULT STDMETHODCALLTYPE CopyPalette ( IWICPalette *pIPalette );

        //IUnknownImpl m_unknown;
        IWICBitmap *m_image;
	};

};