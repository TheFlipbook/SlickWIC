#include "stdafx.h"
#include "Registrar.h"

namespace Slick
{
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

    void Registrar::SetString( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value )
    {
        Set( keyName, valueName, REG_SZ, value, sizeof(wchar_t)*(wcslen(value)) ); 
    }

    void Registrar::SetDWord( wchar_t const *keyName, wchar_t const *valueName, DWORD value )
    {
        Set( keyName, valueName, REG_DWORD, &value, sizeof(value) );
    }

    void Registrar::SetBytes( wchar_t const *keyName, wchar_t const *valueName, const void *value, size_t count )
    {
        Set( keyName, valueName, REG_BINARY, value, count );
    }

    void Registrar::SetExpand( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value )
    {
        Set( keyName, valueName, REG_EXPAND_SZ, value, sizeof(wchar_t)*(wcslen(value)) ); 
    }

    void Deregistrar::SetString( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value )
    {
        RegDeleteKey( HKEY_CLASSES_ROOT, keyName );
    }

    void Deregistrar::SetDWord( wchar_t const *keyName, wchar_t const *valueName, DWORD value )
    {
        RegDeleteKey( HKEY_CLASSES_ROOT, keyName );
    }

    void Deregistrar::SetBytes( wchar_t const *keyName, wchar_t const *valueName, const void *value, size_t count )
    {
        RegDeleteKey( HKEY_CLASSES_ROOT, keyName );
    }

    void Deregistrar::SetExpand( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value )
    {
        RegDeleteKey( HKEY_CLASSES_ROOT, keyName );
    }
}