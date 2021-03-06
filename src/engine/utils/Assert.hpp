#pragma once

#ifndef BBD15B48_D134_3B08_114E_60D614CCA16E
#define BBD15B48_D134_3B08_114E_60D614CCA16E

#ifdef DEBUG
#define ENABLE_ASSERTS
#define OPENGL_DEBUG
#endif

#ifdef ENABLE_ASSERTS

#include "Logger.hpp"

#define ASSERT(x, ...)                                                                                                 \
  {                                                                                                                    \
    if (!(x)) {                                                                                                        \
      LOG_CRITICAL("[assert failure @ {}:{}] {}", __FILE__, __LINE__, __VA_ARGS__);                                    \
    }                                                                                                                  \
  }

#define REFUTE(x, ...)                                                                                                 \
  {                                                                                                                    \
    if (x) {                                                                                                           \
      LOG_CRITICAL("[refute failure @ {}:{}] {}", __FILE__, __LINE__, __VA_ARGS__);                                    \
    }                                                                                                                  \
  }

#else

#define ASSERT(x, ...)
#define REFUTE(x, ...)

#endif

#endif /* BBD15B48_D134_3B08_114E_60D614CCA16E */
