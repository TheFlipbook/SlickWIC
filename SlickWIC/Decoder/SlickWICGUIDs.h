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
    static void GUIDToStr( GUID id, std::wstring &str );

    // --------------------------------------------------------------------------------------------
    class WICGUID
    {
    public:
        class ID
        {
        public:
            static const GUID Vendor;
            static const GUID Decoder;
            static const GUID Decoder_TGA;
            static const GUID File_TGA;
            static const GUID Decoder_PSD;
            static const GUID File_PSD;
            static const GUID Decoder_DDS;
            static const GUID File_DDS;
        };

        class Str
        {
        public:
            static const wchar_t * Vendor;
            static const wchar_t * Decoder;
            static const wchar_t * Decoder_TGA;
            static const wchar_t * File_TGA;
            static const wchar_t * Decoder_PSD;
            static const wchar_t * File_PSD;
            static const wchar_t * Decoder_DDS;
            static const wchar_t * File_DDS;
        };
    };

    // --------------------------------------------------------------------------------------------
    class CommonGUID
    {
    public:
        class Str
        {
        public:
            static const wchar_t * Explorer;
            static const wchar_t * WIC;
            static const wchar_t * Thumbnail;
            static const wchar_t * Gallery;
            static const wchar_t * WICID_32BitRGBAlpha;
            static const wchar_t * WICID_24BitRGB;
        };
    };
}