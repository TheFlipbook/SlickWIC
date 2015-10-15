#include "stdafx.h"

namespace Slick
{
    class DevILDecoderFactory : public IClassFactory, public IUnknownImpl
    {
        virtual ~DevILDecoderFactory(){};

        // IUnknown
        virtual ULONG STDMETHODCALLTYPE AddRef (){ return IUnknownImpl::AddRef(); }
        virtual ULONG STDMETHODCALLTYPE Release(){ return IUnknownImpl::Release(); }
        virtual HRESULT STDMETHODCALLTYPE QueryInterface ( REFIID riid, void **ppvObject );

        // IClassFactory
        virtual HRESULT STDMETHODCALLTYPE CreateInstance( IUnknown *pUnkOuter, REFIID riid, void **ppvObject );
        virtual HRESULT STDMETHODCALLTYPE LockServer( BOOL fLock );

    };
}