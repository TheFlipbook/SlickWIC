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

#include "Util/Registrar.h"
#include "Decoder/DevILDecoder.h"
#include "Decoder/SlickWICGUIDs.h"

namespace Slick
{
    // --------------------------------------------------------------------------------------------
    class DecoderFormat_TGA
    {
    public:
        static const wchar_t* Extension() { return L".tga"; }
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
        static const wchar_t* Extension() { return L".psd"; }
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
        static const wchar_t* Extension() { return L".dds"; }
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
    
    typedef SlickDecoder<DecoderFormat_TGA> SlickDecoder_TGA;
    typedef SlickDecoder<DecoderFormat_PSD> SlickDecoder_PSD;
    typedef SlickDecoder<DecoderFormat_DDS> SlickDecoder_DDS;
}
