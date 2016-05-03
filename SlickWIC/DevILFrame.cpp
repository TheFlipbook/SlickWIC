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

#include "stdafx.h"
#include "DevILFrame.h"

#include "ILWICBridge.h"

namespace Slick
{
    // --------------------------------------------------------------------------------------------
    DevILFrame::DevILFrame( IWICBitmap *image )
        : m_image(image)
    {
        if( m_image )
            m_image->AddRef();
    }

    // --------------------------------------------------------------------------------------------
    DevILFrame::~DevILFrame()
    {
        if( m_image )
            m_image->Release();
    }

    // --------------------------------------------------------------------------------------------
    HRESULT DevILFrame::QueryInterface ( REFIID riid, void **ppvObject )
    {
        if( ppvObject )
        {
            if( riid == IID_IWICBitmapFrameDecode )
            {
                *ppvObject = this;
                AddRef();
                return S_OK;
            }
            else if ( riid == IID_IWICBitmapSource )
            {
                if( m_image )
                {
                    *ppvObject = m_image;
                    m_image->AddRef();
                    return S_OK;
                }
            }

            return IUnknownImpl::QueryInterface( riid, ppvObject );
        }

        return E_INVALIDARG;
    }

    // --------------------------------------------------------------------------------------------
    HRESULT DevILFrame::GetThumbnail ( IWICBitmapSource **ppIThumbnail )
    {
        return WINCODEC_ERR_CODECNOTHUMBNAIL;
    }

    // --------------------------------------------------------------------------------------------
    HRESULT DevILFrame::GetColorContexts ( UINT cCount, IWICColorContext **ppIColorContexts, UINT *pcActualCount )
    {
        pcActualCount = 0;
        return S_OK;
    }

    // --------------------------------------------------------------------------------------------
    HRESULT DevILFrame::GetMetadataQueryReader ( IWICMetadataQueryReader **ppIMetadataQueryReader)
    {
        return WINCODEC_ERR_UNSUPPORTEDOPERATION;
    }
	

    // --------------------------------------------------------------------------------------------
    // IWICBitmapSource
    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------
    HRESULT DevILFrame::GetSize ( UINT *puiWidth, UINT *puiHeight )
    {
        if( m_image )
            return m_image->GetSize( puiWidth, puiHeight );

        return E_POINTER;
    }

    // --------------------------------------------------------------------------------------------
    HRESULT DevILFrame::GetPixelFormat ( WICPixelFormatGUID *pPixelFormat )
    {
        if( m_image )
            return m_image->GetPixelFormat( pPixelFormat );

        return E_POINTER;
    }

    // --------------------------------------------------------------------------------------------
    HRESULT DevILFrame::GetResolution ( double *pDpiX, double *pDpiY )
    {
        if( m_image )
            return m_image->GetResolution( pDpiX, pDpiY );

        return E_POINTER;
    }

    // --------------------------------------------------------------------------------------------
    HRESULT DevILFrame::CopyPixels ( const WICRect *prc, UINT cbStride, UINT cbBufferSize, BYTE *pbBuffer )
    {
        if( m_image )
            return m_image->CopyPixels( prc, cbStride, cbBufferSize, pbBuffer );

        return E_POINTER;
    }

    // --------------------------------------------------------------------------------------------
    HRESULT DevILFrame::CopyPalette ( IWICPalette *pIPalette )
    {
        if( m_image )
            return m_image->CopyPalette( pIPalette );

        return E_POINTER;
    }

    // --------------------------------------------------------------------------------------------
    HRESULT DevILFrame::Create ( IWICImagingFactory *pImagingFactory, ILuint type, ILubyte *data, ILuint size, DevILFrame **frame)
    {
        HRESULT result = S_OK;
        ILboolean success = true;

        // ALLOCATE imageID;
        ILuint imageID;
		ilGenImages( 1, &imageID );
		
        // Bind DevIL state machine
        ilBindImage( imageID );

        // Read data
        success = ilLoadL( type, data, size );
        if( success )
        {
            // Normalize on generic type
            ilConvertImage( IL_RGB, IL_UNSIGNED_BYTE );

            // Gather data
            ILuint width = ilGetInteger( IL_IMAGE_WIDTH );
            ILuint height = ilGetInteger( IL_IMAGE_HEIGHT );
            ILuint bytesPerPixel = ilGetInteger( IL_IMAGE_BYTES_PER_PIXEL );
            ILuint bytesPerRow = width * bytesPerPixel;
            ILuint bytesPerImage = height * bytesPerRow;
						
            // Copy to Windows format
            IWICBitmap *image = NULL;
            result = pImagingFactory->CreateBitmapFromMemory( width, height, GUID_WICPixelFormat24bpp3Channels, bytesPerRow, bytesPerImage, ilGetData(), &image );

            if( image )
            {
                *frame = new DevILFrame( image );
                (*frame)->AddRef();
            }
        }
        else
        {
            result = CheckILError();
        }

        // FREE imageID;
        ilDeleteImages( 1, &imageID );

        return result;
    }
}