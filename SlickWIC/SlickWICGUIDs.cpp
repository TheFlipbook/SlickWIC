#include "stdafx.h"
#include "SlickWICGUIDs.h"

#include <sstream>

namespace Slick
{
    void GUIDToString( GUID id, std::wstring &str )
    {
        OLECHAR* chars;
        ::StringFromCLSID( id, &chars );
        
        std::wstringstream stream;
        stream << chars;
        ::CoTaskMemFree( chars );

        str = stream.str();
    }

    // Vendor
    const wchar_t * WICGUID::Str::Vendor
        = L"{B27648CC-7DBD-4632-B5F1-C3CFBC05E753}";
    const GUID WICGUID::ID::Vendor
        = { 0xb27648cc, 0x7dbd, 0x4632, { 0xb5, 0xf1, 0xc3, 0xcf, 0xbc, 0x5, 0xe7, 0x53 } };

    // Decoder
    const wchar_t * WICGUID::Str::Decoder
        = L"{6C7FB17C-A1B0-4919-98D7-95271ACE5260}";
    const GUID WICGUID::ID::Decoder
        = { 0x6c7fb17c, 0xa1b0, 0x4919, { 0x98, 0xd7, 0x95, 0x27, 0x1a, 0xce, 0x52, 0x60 } };

    // File_TGA
    const wchar_t * WICGUID::Str::File_TGA
        = L"{C750FDD0-F191-4903-A1BE-87B80471440B}";
    const GUID WICGUID::ID::File_TGA
        = { 0xc750fdd0, 0xf191, 0x4903, { 0xa1, 0xbe, 0x87, 0xb8, 0x4, 0x71, 0x44, 0xb } };

    // Explorer
    const wchar_t * CommonGUID::Str::Explorer
        = L"{e357fccd-a995-4576-b01f-234630154e96}";

    const wchar_t * CommonGUID::Str::WIC
        = L"{7ED96837-96F0-4812-B211-F13C24117ED3}";

    const wchar_t * CommonGUID::Str::Thumbnail
        = L"{C7657C4A-9F68-40fa-A4DF-96BC08EB3551}";
    
    const wchar_t * CommonGUID::Str::Gallery
        = L"{FFE2A43C-56B9-4bf5-9A79-CC6D4285608A}";

    const wchar_t * CommonGUID::Str::WICID_32BitRGBAlpha
        = L"{6fddc324-4e03-4bfe-b185-3d77768dc92e}";

    const wchar_t * CommonGUID::Str::WICID_24BitRGB
        = L"{6fddc324-4e03-4bfe-b185-3d77768dc920}";

}