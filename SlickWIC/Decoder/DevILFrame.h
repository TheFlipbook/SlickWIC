// ------------------------------------------------------------------------------------------------
// Copyright (c) 2016 Patrick "Rick" Gilliland
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// This license shall be perpetual and irrevocable.
// ------------------------------------------------------------------------------------------------

#pragma once
#include "precompiled.h"

namespace Slick
{
    // --------------------------------------------------------------------------------------------
	// Actual Image Display Data
    // --------------------------------------------------------------------------------------------
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