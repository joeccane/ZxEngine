#include "core.hpp"

//logging
#if defined(ZX_DEBUG) || defined(ZX_DEBUG_TRACE)
		#define zxTrace(...) __VA_ARGS__
	#else
		#define zxTrace(...)
#endif
#if defined(ZX_DEBUG) || defined(ZX_RELEASE) || defined(ZX_DEBUG_WARN)
		#define zxWarn(...) __VA_ARGS__
	#else
		#define zxWarn(...)
#endif
#if !defined(ZX_SUPPRESS_ERRORS)
		#define zxError(...) __VA_ARGS__
	#else
		#define zxError(...)
#endif


//asserts
#if defined(ZX_DEBUG) || defined(ZX_ASSERT)
	#define zxAssert(condition, message)\
		{ if(!condition)\
			__debugbreak(); }
	#else 
		zxAssert(condition, message)
#endif

#if !defined(ZX_SUPPRESS_FATAL_ASSERTS)
	#define zxFatalAssert(condition, message)\
		{ if(!condition)\
			__debugbreak(); }
	#else
		#define zxFatalAssert(condition, message)
#endif