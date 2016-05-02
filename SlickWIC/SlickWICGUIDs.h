#pragma once
#include "stdafx.h"

namespace Slick
{
    static void GUIDToStr( GUID id, std::wstring &str );

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
        };
    };

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