#pragma once

#if defined(_WIN32)

#if defined(LITE_API_EXPORT)
#define LITE_API __declspec(dllexport)
#else
#define LITE_API __declspec(dllimport)
#endif

#else

#define LITE_API __attribute__((__visibility__("default")))

#endif
