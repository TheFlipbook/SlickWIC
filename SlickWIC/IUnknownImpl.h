#pragma once

#include "stdafx.h"

namespace Slick
{

    class SLICKWIC_API IUnknownImpl : public IUnknown
    {
    public:
        IUnknownImpl()
            : m_refs(0)
        {
        }

        virtual ~IUnknownImpl(){}

        virtual ULONG STDMETHODCALLTYPE AddRef()
        {
            return InterlockedIncrement(&m_refs);
        }

        virtual ULONG STDMETHODCALLTYPE Release()
        {
            ULONG result = InterlockedDecrement(&m_refs);
            if( 0 == result )
            {
                // FIXME
                delete this;
            }
            
            return result;
        }

        virtual HRESULT STDMETHODCALLTYPE QueryInterface ( REFIID riid, void **ppvObject )
        {
            if( ppvObject )
            {
                if( riid == IID_IUnknown )
                {
                    *ppvObject = this;
                    AddRef();
                    return S_OK;
                }

                return E_NOINTERFACE;
            }

            return E_POINTER;
        }

    protected:
        ULONG m_refs;
    };
}