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
    HRESULT ILErrorToWICError( ILenum errorcode )
    {
        switch (errorcode)
        {
        case IL_ILLEGAL_OPERATION:
            return WINCODEC_ERR_WRONGSTATE;

        case IL_COULD_NOT_OPEN_FILE:
            WINCODEC_ERR_ACCESSDENIED;

        case IL_INVALID_ENUM:
            WINCODEC_ERR_UNKNOWNIMAGEFORMAT;

        case IL_INVALID_PARAM:
            return E_INVALIDARG;

        case IL_INVALID_FILE_HEADER:
            return WINCODEC_ERR_BADHEADER;

        case IL_ILLEGAL_FILE_VALUE:
            return WINCODEC_ERR_BADIMAGE;

        case IL_INVALID_CONVERSION:
            return WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT;

        case IL_OUT_OF_MEMORY:
            return E_OUTOFMEMORY;
            
        case IL_LIB_JPEG_ERROR:
        case IL_LIB_PNG_ERROR:
        default:
            return E_FAIL;
        }
    }

    // --------------------------------------------------------------------------------------------
    HRESULT CheckILError()
    {
        ILenum errorcode = ilGetError();
        if( IL_NO_ERROR != errorcode )
        {
            std::clog << iluErrorString(errorcode) << std::endl;
            return ILErrorToWICError( errorcode );
        }

        return S_OK;
    }
}