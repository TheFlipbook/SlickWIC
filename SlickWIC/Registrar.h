#include "stdafx.h"

#include <string>

namespace Slick
{
    class IRegistrar
    {
    public:
        virtual void SetString( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value ) = 0;
        virtual void SetDWord( wchar_t const *keyName, wchar_t const *valueName, DWORD value ) = 0;
        virtual void SetBytes( wchar_t const *keyName, wchar_t const *valueName, const void *value, size_t count ) = 0;
        virtual void SetExpand( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value ) = 0;
    };

    class Registrar : public IRegistrar
    {
    public:
        virtual void SetString( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value );
        virtual void SetDWord( wchar_t const *keyName, wchar_t const *valueName, DWORD value );
        virtual void SetBytes( wchar_t const *keyName, wchar_t const *valueName, const void *value, size_t count );
        virtual void SetExpand( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value );
    };

    class Deregistrar : public IRegistrar
    {
    public:
        virtual void SetString( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value );
        virtual void SetDWord( wchar_t const *keyName, wchar_t const *valueName, DWORD value );
        virtual void SetBytes( wchar_t const *keyName, wchar_t const *valueName, const void *value, size_t count );
        virtual void SetExpand( wchar_t const *keyName, wchar_t const *valueName, LPCWSTR value );
    };
}