// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include <sstream>
#include <Shlobj.h>

#include "DevILDecoder.h"
#include "DevILDecoderFactory.h"

#include "Registrar.h"
#include "SlickWICGUIDs.h"

static HINSTANCE s_hInstance = NULL;

namespace Slick
{
    static void RegisterThumbnail( Slick::IRegistrar &reg, wchar_t const *ext )
    {
        // Thumbnail Provider
        std::wstringstream thumbKey;
        thumbKey << "." << ext << L"\\ShellEx\\" << CommonGUID::Str::Explorer;
        reg.SetString( thumbKey.str().c_str(), L"", CommonGUID::Str::Thumbnail );

        // System Thumbnailer
        std::wstringstream sysKey;
        sysKey << "SystemFileAssociations\\." << ext << L"\\ShellEx\\" << CommonGUID::Str::Explorer;
        reg.SetString( thumbKey.str().c_str(), L"", CommonGUID::Str::Thumbnail );
        
        // Content Search
        std::wstringstream signalKey;
        signalKey << "." << ext;
        reg.SetString( signalKey.str().c_str(), L"Content Type", L"image/x-tga" );
        reg.SetString( signalKey.str().c_str(), L"PerceivedType", L"image" );

        // Photo Gallery
        std::wstringstream extKey;
        extKey << "." << ext;
        reg.SetString( extKey.str().c_str(), L"", L"tgafile" );

        std::wstring sysPrefix( L"SystemFileAssociations\\" );
        
        
        std::wstringstream openWithKey;
        openWithKey << "." << ext << "\\OpenWithProgids";
        reg.SetString( openWithKey.str().c_str(), L"tgafile", L"" );

        std::wstringstream openListKey;
        openListKey << "." << ext << "\\OpenWithList\\PhotoViewer.dll";
        reg.SetString( openListKey.str().c_str(), L"", L"" );
        std::wstringstream sysOpenListKey;
        sysOpenListKey << sysPrefix << openListKey.str();
        reg.SetString( sysOpenListKey.str().c_str(), L"", L"" );

        std::wstringstream contextKey;
        contextKey << "." << ext << "\\ShellEx\\ContextMenuHandlers\\ShellImagePreview";
        reg.SetString( contextKey.str().c_str(), L"", CommonGUID::Str::Gallery );
        std::wstringstream sysContextKey;
        sysContextKey << sysPrefix << contextKey.str();
        reg.SetString( sysContextKey.str().c_str(), L"", L"" );

        std::wstringstream progidKey;
        progidKey << "tgafile";
        reg.SetString( progidKey.str().c_str(), L"", L"TGA File" );
        
        std::wstringstream shellKey;
        shellKey << progidKey.str() << "\\shell";

        std::wstringstream openKey;
        openKey << shellKey.str() << "\\open";
        reg.SetExpand( openKey.str().c_str(), L"MuiVerb", L"@%ProgramFiles%\\Windows Photo Viewer\\photoviewer.dll,-3043" );
        
        std::wstringstream commandKey;
        commandKey << openKey.str() << "\\command";
        reg.SetExpand( commandKey.str().c_str(), L"", L"%SystemRoot%\\System32\\rundll32.exe \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen %1" );
        
        std::wstringstream dropKey;
        dropKey << openKey.str() << "\\DropTarget";
        reg.SetString( dropKey.str().c_str(), L"Clsid", CommonGUID::Str::Gallery );
        
        std::wstringstream printKey;
        printKey << shellKey.str() << "\\printto\\command";
        reg.SetExpand( printKey.str().c_str(), L"", L"\"%SystemRoot%\\System32\\rundll32.exe\" \"%SystemRoot%\\System32\\shimgvw.dll\",ImageView_PrintTo /pt \"%1\" \"%2\" \"%3\" \"%4\"");
        

    }

    // TODO:  This needs to be per codec.
    static void RegistryKeys( Slick::IRegistrar &reg )
    {
        std::wstring pre( L"CLSID\\" );

        // Tells WIC that this decoder exists
        std::wstringstream wicKey;
        wicKey << pre << CommonGUID::Str::WIC << L"\\Instance\\" << WICGUID::Str::Decoder; 
        reg.SetString( wicKey.str().c_str(), L"", L"" );
        reg.SetString( wicKey.str().c_str(), L"CLSID", WICGUID::Str::Decoder );
        reg.SetString( wicKey.str().c_str(), L"FriendlyName", L"SlickWIC" );

        // Information about decoder
        std::wstringstream decoderKey;
        decoderKey << pre << WICGUID::Str::Decoder;
        reg.SetString( decoderKey.str().c_str(), L"Date", _T(__DATE__) );
        reg.SetString( decoderKey.str().c_str(), L"FriendlyName", L"SlickWIC" );    // Required by Specification
        reg.SetString( decoderKey.str().c_str(), L"VendorGUID", WICGUID::Str::Vendor ); // Required by Specification

        // Information about the File
        reg.SetString( decoderKey.str().c_str(), L"ContainerFormat", WICGUID::Str::File_TGA );
        reg.SetString( decoderKey.str().c_str(), L"MimeTypes", L"image/x-tga" );    // Required by Specification
        reg.SetString( decoderKey.str().c_str(), L"FileExtensions", L".tga" );      // Required by Specification
        
        // Formats Folder
        std::wstringstream formatKey;
        formatKey << decoderKey.str() << L"\\Formats";
        reg.SetString( formatKey.str().c_str(), L"", L"" );

        // Individual pixel formats supported.
        std::wstringstream formatItem;
        formatItem << formatKey.str() << "\\" << CommonGUID::Str::WICID_32BitRGBAlpha;
        reg.SetString( formatItem.str().c_str(), L"Formats", CommonGUID::Str::WICID_24BitRGB ); // Required by Specification

        // Pattern Match to get WIC to send a file this way
        std::wstringstream patternsKey;
        patternsKey << decoderKey.str() << L"\\Patterns";
        reg.SetString( patternsKey.str().c_str(), L"", L"" );

        std::wstringstream patternsItem;
        patternsItem << patternsKey.str() << "\\0";
        reg.SetDWord( patternsItem.str().c_str(), L"EndOfStream", 1 );
        reg.SetDWord( patternsItem.str().c_str(), L"Position", 18 );

        
        const char * pattern = "TRUEVISION-XFILE";
        const unsigned int length = 16;
        BYTE mask[length];
        std::fill_n( mask, length, 0xFF );

        reg.SetDWord( patternsItem.str().c_str(), L"Length", length );
        reg.SetBytes( patternsItem.str().c_str(), L"Pattern", pattern, length );
        reg.SetBytes( patternsItem.str().c_str(), L"Mask", mask, length );

        // Tell Explorer to use this decoder for Thumbnails
        RegisterThumbnail( reg, L"tga" );
        //RegisterThumbnail( reg, L"dds" );
        //RegisterThumbnail( reg, L"psd" );

        // How to run us
        HMODULE curModule = GetModuleHandle( L"SlickWIC.dll" );
        wchar_t tempFileName[MAX_PATH];
        if( s_hInstance != NULL )
        {
            GetModuleFileName( s_hInstance, tempFileName, MAX_PATH );
            std::wstringstream inprocKey;
            inprocKey << decoderKey.str() << "\\InprocServer32";
            reg.SetString( inprocKey.str().c_str(), L"", tempFileName );
            reg.SetString( inprocKey.str().c_str(), L"ThreadingModel", L"Apartment" );
        }
        

        // Tell Explorer to invalidate the Thumbnail cache
        SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
    }
}

STDAPI DllRegisterServer()
{    
    Slick::Registrar reg;
    Slick::RegistryKeys( reg );

    return S_OK;
}

STDAPI DllUnregisterServer()
{    
    Slick::Deregistrar dereg;
    Slick::RegistryKeys( dereg );

    return S_OK;
}

STDAPI DllGetClassObject( REFCLSID rclsid, REFIID riid, void **ppvObject )
{

    if( ppvObject )
    {
        if( Slick::WICGUID::ID::Decoder == rclsid )
        {
            IClassFactory *classFactory = new Slick::DevILDecoderFactory();
            if (!classFactory)
                return E_OUTOFMEMORY;
            
            classFactory->AddRef();
            HRESULT result = classFactory->QueryInterface( riid, ppvObject );
            classFactory->Release();  // Maybe destruct.  Depends on QueryInterface
            return result;
        }
        else
        {
            return CLASS_E_CLASSNOTAVAILABLE;
        }
    }

    return E_INVALIDARG;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        s_hInstance = hModule;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}