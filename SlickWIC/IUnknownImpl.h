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
#include "stdafx.h"

namespace Slick
{
    // --------------------------------------------------------------------------------------------
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