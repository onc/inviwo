#ifndef HALFEXPORT_H
#define HALFEXPORT_H

//
//  Copyright (c) 2008 Lucasfilm Entertainment Company Ltd.
//  All rights reserved.   Used under authorization.
//  This material contains the confidential and proprietary
//  information of Lucasfilm Entertainment Company and
//  may not be copied in whole or in part without the express
//  written permission of Lucasfilm Entertainment Company.
//  This copyright notice does not imply publication.
//

#if defined(OPENEXR_DLL)
    #if defined(HALF_EXPORTS)
        #ifdef _WIN32
            #define HALF_EXPORT __declspec(dllexport)
            #define HALF_EXPORT_CONST const __declspec(dllexport)
        #else
            #define HALF_EXPORT __attribute__ ((visibility ("default")))
            #define HALF_EXPORT_CONST const __attribute__ ((visibility ("default")))
        #endif
    #else
        #ifdef _WIN32
	        #define HALF_EXPORT __declspec(dllimport)
	        #define HALF_EXPORT_CONST const __declspec(dllimport)
        #else
            #define HALF_EXPORT
            #define HALF_EXPORT_CONST const
        #endif
    #endif
#else
    #define HALF_EXPORT
    #define HALF_EXPORT_CONST const
#endif

#endif // #ifndef HALFEXPORT_H

