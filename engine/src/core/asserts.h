#pragma once

#include "defines.h"

// Disable assertions by commenting out the below line.
#define KASSERTIONS_ENABLED

#ifdef KASSERTIONS_ENABLED

#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

KAPI void report_assertion_failure(const char *expression, const char *message,
                                   const char *file, i32 line);

#define KASSERT(expr)                                                          \
  do {                                                                         \
    if (!(expr)) {                                                             \
      report_assertion_failure(#expr, "", __FILE__, __LINE__);                 \
      debugBreak();                                                            \
    }                                                                          \
  } while (0)

#define KASSERT_MSG(expr, message)                                             \
  do {                                                                         \
    if (!(expr)) {                                                             \
      report_assertion_failure(#expr, message, __FILE__, __LINE__);            \
      debugBreak();                                                            \
    }                                                                          \
  } while (0)

#ifdef _DEBUG
#define KASSERT_DEBUG(expr)                                                    \
  do {                                                                         \
    if (!(expr)) {                                                             \
      report_assertion_failure(#expr, "", __FILE__, __LINE__);                 \
      debugBreak();                                                            \
    }                                                                          \
  } while (0)
#else
#define KASSERT_DEBUG(expr) ((void)0)
#endif

#else

#define KASSERT(expr) ((void)0)
#define KASSERT_MSG(expr, message) ((void)0)
#define KASSERT_DEBUG(expr) ((void)0)

#endif
