#pragma once

#include "stdafx.h"

namespace Slick
{
    HRESULT ILErrorToWICError( ILenum errorcode )
    {
        switch (errorcode)
        {
        case IL_ILLEGAL_OPERATION:
            return WINCODEC_ERR_WRONGSTATE;

        case IL_COULD_NOT_OPEN_FILE:
            WINCODEC_ERR_ACCESSDENIED;

        case IL_INVALID_ENUM:
            WINCODEC_ERR_UNKNOWNIMAGEFORMAT;

        case IL_INVALID_PARAM:
            return E_INVALIDARG;

        case IL_INVALID_FILE_HEADER:
            return WINCODEC_ERR_BADHEADER;

        case IL_ILLEGAL_FILE_VALUE:
            return WINCODEC_ERR_BADIMAGE;

        case IL_INVALID_CONVERSION:
            return WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT;

        case IL_OUT_OF_MEMORY:
            return E_OUTOFMEMORY;
            
        case IL_LIB_JPEG_ERROR:
        case IL_LIB_PNG_ERROR:
        default:
            return E_FAIL;
        }
    }

    HRESULT CheckILError()
    {
        ILenum errorcode = ilGetError();
        if( IL_NO_ERROR != errorcode )
        {
            std::clog << iluErrorString(errorcode) << std::endl;
            return ILErrorToWICError( errorcode );
        }

        return S_OK;
    }
}