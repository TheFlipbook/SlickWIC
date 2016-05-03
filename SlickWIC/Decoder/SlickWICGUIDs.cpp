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

#include "precompiled.h"
#include "SlickWICGUIDs.h"

namespace Slick
{
    // --------------------------------------------------------------------------------------------
    void GUIDToString( GUID id, std::wstring &str )
    {
        OLECHAR* chars;
        ::StringFromCLSID( id, &chars );
        
        std::wstringstream stream;
        stream << chars;
        ::CoTaskMemFree( chars );

        str = stream.str();
    }

    // --------------------------------------------------------------------------------------------
    // Vendor
    // --------------------------------------------------------------------------------------------
    const wchar_t * WICGUID::Str::Vendor
        = L"{B27648CC-7DBD-4632-B5F1-C3CFBC05E753}";
    const GUID WICGUID::ID::Vendor
        = { 0xb27648cc, 0x7dbd, 0x4632, { 0xb5, 0xf1, 0xc3, 0xcf, 0xbc, 0x5, 0xe7, 0x53 } };

    // --------------------------------------------------------------------------------------------
    // Decoder
    // --------------------------------------------------------------------------------------------
    const wchar_t * WICGUID::Str::Decoder
        = L"{6C7FB17C-A1B0-4919-98D7-95271ACE5260}";
    const GUID WICGUID::ID::Decoder
        = { 0x6c7fb17c, 0xa1b0, 0x4919, { 0x98, 0xd7, 0x95, 0x27, 0x1a, 0xce, 0x52, 0x60 } };

    // --------------------------------------------------------------------------------------------
    // Decoder_TGA
    // --------------------------------------------------------------------------------------------
    const wchar_t * WICGUID::Str::Decoder_TGA
        = L"{8710BE66-B01A-4025-8FC2-36027496B887}";
    const GUID WICGUID::ID::Decoder_TGA
        = { 0x8710be66, 0xb01a, 0x4025, { 0x8f, 0xc2, 0x36, 0x2, 0x74, 0x96, 0xb8, 0x87 } };

    // --------------------------------------------------------------------------------------------
    // File_TGA
    // --------------------------------------------------------------------------------------------
    const wchar_t * WICGUID::Str::File_TGA
        = L"{C750FDD0-F191-4903-A1BE-87B80471440B}";
    const GUID WICGUID::ID::File_TGA
        = { 0xc750fdd0, 0xf191, 0x4903, { 0xa1, 0xbe, 0x87, 0xb8, 0x4, 0x71, 0x44, 0xb } };

    // --------------------------------------------------------------------------------------------
    // Decoder_PSD
    // --------------------------------------------------------------------------------------------
    const wchar_t * WICGUID::Str::Decoder_PSD
        = L"{646F563B-4F45-4EB0-AB29-D261BAD55818}";
    const GUID WICGUID::ID::Decoder_PSD
        = { 0x646f563b, 0x4f45, 0x4eb0, { 0xab, 0x29, 0xd2, 0x61, 0xba, 0xd5, 0x58, 0x18 } };

    // --------------------------------------------------------------------------------------------
    // File_PSD
    // --------------------------------------------------------------------------------------------
    const wchar_t * WICGUID::Str::File_PSD
        = L"{E0958E58-50F5-45BD-99CA-8B5DC05770D8}";
    const GUID WICGUID::ID::File_PSD
        = { 0xe0958e58, 0x50f5, 0x45bd, { 0x99, 0xca, 0x8b, 0x5d, 0xc0, 0x57, 0x70, 0xd8 } };

    // --------------------------------------------------------------------------------------------
    // Decoder_DDS
    // --------------------------------------------------------------------------------------------
    const wchar_t * WICGUID::Str::Decoder_DDS
        = L"{58CBFCB6-0645-48D8-8912-E2F5A9F7C060}";
    const GUID WICGUID::ID::Decoder_DDS
        = { 0x58cbfcb6, 0x645, 0x48d8, { 0x89, 0x12, 0xe2, 0xf5, 0xa9, 0xf7, 0xc0, 0x60 } };

    // --------------------------------------------------------------------------------------------
    // File_DDS
    // --------------------------------------------------------------------------------------------
    const wchar_t * WICGUID::Str::File_DDS
        = L"{F7C9AB44-C00E-4321-A1CC-D35DFBC12E9A}";
    const GUID WICGUID::ID::File_DDS
        = { 0xf7c9ab44, 0xc00e, 0x4321, { 0xa1, 0xcc, 0xd3, 0x5d, 0xfb, 0xc1, 0x2e, 0x9a } };

    // --------------------------------------------------------------------------------------------
    // Explorer
    // --------------------------------------------------------------------------------------------
    const wchar_t * CommonGUID::Str::Explorer
        = L"{e357fccd-a995-4576-b01f-234630154e96}";
    const wchar_t * CommonGUID::Str::WIC
        = L"{7ED96837-96F0-4812-B211-F13C24117ED3}";
    const wchar_t * CommonGUID::Str::Thumbnail
        = L"{C7657C4A-9F68-40fa-A4DF-96BC08EB3551}";\
    const wchar_t * CommonGUID::Str::Gallery
        = L"{FFE2A43C-56B9-4bf5-9A79-CC6D4285608A}";
    const wchar_t * CommonGUID::Str::WICID_32BitRGBAlpha
        = L"{6fddc324-4e03-4bfe-b185-3d77768dc92e}";
    const wchar_t * CommonGUID::Str::WICID_24BitRGB
        = L"{6fddc324-4e03-4bfe-b185-3d77768dc920}";
}
