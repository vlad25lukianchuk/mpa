#ifndef MPA_MPABASE_CORE_INCLUDE_MPACOREGLOBAL_H_
#define MPA_MPABASE_CORE_INCLUDE_MPACOREGLOBAL_H_

#ifdef _WIN32

// TODO: FIX
// class 'std::string' needs to have dll-interface to be used by
// clients of class 'mpa::core::Number'
#pragma warning(disable : 4251)

#ifdef MPA_BUILD_CORE_LIB
#define MPA_CORE_EXPORT __declspec(dllexport)
#else
#define MPA_CORE_EXPORT __declspec(dllimport)
#endif
#else
#define MPA_CORE_EXPORT
#endif

// Avoid "unused parameter" warnings
#define MPA_UNUSED(x) (void)x;

#endif  // MPA_MPABASE_CORE_INCLUDE_MPACOREGLOBAL_H_
