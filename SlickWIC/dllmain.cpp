// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include <sstream>
#include <Shlobj.h>

#include "DevILDecoder.h"
#include "DevILDecoderFactory.h"

#include "Registrar.h"
#include "SlickWICGUIDs.h"

static HINSTANCE s_hInstance = NULL;
static bool s_initialized = false;

namespace Slick
{
    static void RequestInitIL( ILuint origin )
    {
        if( !s_initialized )
        {
	        ilInit();
            iluInit();

            ilEnable(IL_ORIGIN_SET);

            s_initialized = true;
        }
        
        ilOriginFunc(origin);
    }

    static void RegistryKeys( Slick::IRegistrar &reg )
    {
        SlickDecoder_PSD::Register( reg );
        SlickDecoder_TGA::Register( reg );
        SlickDecoder_DDS::Register( reg );
        

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
        IClassFactory *classFactory = nullptr;
        if( Slick::SlickDecoder_PSD::Format::DecoderKey() == rclsid )
        {
            Slick::RequestInitIL(IL_ORIGIN_UPPER_LEFT);

            classFactory = new Slick::SlickDecoder_PSD::Factory();
            if( !classFactory )
                return E_OUTOFMEMORY;
        }
        else if( Slick::SlickDecoder_TGA::Format::DecoderKey() == rclsid )
        {
            Slick::RequestInitIL(IL_ORIGIN_UPPER_LEFT);

            classFactory = new Slick::SlickDecoder_TGA::Factory();
            if( !classFactory )
                return E_OUTOFMEMORY;
        }
        else if( Slick::SlickDecoder_DDS::Format::DecoderKey() == rclsid )
        {
            Slick::RequestInitIL(IL_ORIGIN_LOWER_LEFT);

            classFactory = new Slick::SlickDecoder_DDS::Factory();
            if( !classFactory )
                return E_OUTOFMEMORY;
        }


        if( classFactory )
        {
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