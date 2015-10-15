#include "stdafx.h"
#include "DevILDecoderFactory.h"

#include "DevILDecoder.h"

namespace Slick
{
    HRESULT DevILDecoderFactory::QueryInterface ( REFIID riid, void **ppvObject )
    {
        
        if( ppvObject )
        {
            if( riid == IID_IClassFactory )
            {
                *ppvObject = this;
                AddRef();
                return S_OK;
            }

            return IUnknownImpl::QueryInterface( riid, ppvObject );
        }

        return E_INVALIDARG;
    }

    // IClassFactory
    HRESULT DevILDecoderFactory:: CreateInstance( IUnknown *pUnkOuter, REFIID riid, void **ppvObject )
    {
        if( ppvObject )
        {
            DevILDecoder *decoder = new DevILDecoder();
            if(!decoder)
                return E_OUTOFMEMORY;

            return decoder->QueryInterface( riid, ppvObject );
        }

        return E_INVALIDARG;
    }

    HRESULT DevILDecoderFactory::LockServer( BOOL fLock )
    {
        return CoLockObjectExternal( static_cast<IUnknownImpl*>(this), fLock, FALSE );
    }
}