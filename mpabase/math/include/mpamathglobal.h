#ifndef MPA_MPABASE_MATH_INCLUDE_MPAMATHGLOBAL_H_
#define MPA_MPABASE_MATH_INCLUDE_MPAMATHGLOBAL_H_

#ifdef _WIN32
#ifdef MPA_BUILD_MATH_LIB
#define MPA_MATH_EXPORT __declspec(dllexport)
#else
#define MPA_MATH_EXPORT __declspec(dllimport)
#endif
#else
#define MPA_MATH_EXPORT
#endif

#endif  // MPA_MPABASE_MATH_INCLUDE_MPAMATHGLOBAL_H_
