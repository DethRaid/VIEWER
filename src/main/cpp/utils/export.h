/*!
 * \author ddubois 
 * \date 16-Feb-18.
 */

#ifndef VIEWER_EXPORT_H
#define VIEWER_EXPORT_H

#if defined(_WIN32)
    #if defined(DLL_EXPORT)
        #define VIEWER_API __declspec(dllexport)
    #else
        #if defined(STATIC_LINKAGE)
            #define VIEWER_API
        #else
            #define VIEWER_API __declspec(dllimport)
        #endif
    #endif
#else
    #if defined(__GNUC__)
        #define VIEWER_API __attribute__((visibility("default")))
    #endif
#endif

#endif //VIEWER_EXPORT_H
