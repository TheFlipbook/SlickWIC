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

#include "stdafx.h"
#include "Registrar.h"

namespace Slick
{
    // --------------------------------------------------------------------------------------------
    static void Set( wchar_t const *keyName, wchar_t const *valueName, unsigned type, void const *value, size_t valueSize)
    {
        HKEY hKey;
        LSTATUS status = RegCreateKey( HKEY_CLASSES_ROOT, keyName, &hKey );
        if ( status == ERROR_SUCCESS )
        {
            status = RegSetValueEx(
                        hKey, valueName, 0, type,
                        reinterpret_cast<BYTE const *>(value),
                        static_cast<DWORD>(valueSize)
                     );
        }
    }

    // --------------------------------------------------------------------------------------------
    void Registrar::SetString( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value )
    {
        Set( keyName, valueName, REG_SZ, value, sizeof(wchar_t)*(wcslen(value)) ); 
    }

    // --------------------------------------------------------------------------------------------
    void Registrar::SetDWord( wchar_t const *keyName, wchar_t const *valueName, DWORD value )
    {
        Set( keyName, valueName, REG_DWORD, &value, sizeof(value) );
    }

    // --------------------------------------------------------------------------------------------
    void Registrar::SetBytes( wchar_t const *keyName, wchar_t const *valueName, const void *value, size_t count )
    {
        Set( keyName, valueName, REG_BINARY, value, count );
    }

    // --------------------------------------------------------------------------------------------
    void Registrar::SetExpand( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value )
    {
        Set( keyName, valueName, REG_EXPAND_SZ, value, sizeof(wchar_t)*(wcslen(value)) ); 
    }

    // --------------------------------------------------------------------------------------------
    void Deregistrar::SetString( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value )
    {
        RegDeleteKey( HKEY_CLASSES_ROOT, keyName );
    }

    // --------------------------------------------------------------------------------------------
    void Deregistrar::SetDWord( wchar_t const *keyName, wchar_t const *valueName, DWORD value )
    {
        RegDeleteKey( HKEY_CLASSES_ROOT, keyName );
    }

    // --------------------------------------------------------------------------------------------
    void Deregistrar::SetBytes( wchar_t const *keyName, wchar_t const *valueName, const void *value, size_t count )
    {
        RegDeleteKey( HKEY_CLASSES_ROOT, keyName );
    }

    // --------------------------------------------------------------------------------------------
    void Deregistrar::SetExpand( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value )
    {
        RegDeleteKey( HKEY_CLASSES_ROOT, keyName );
    }
}