#ifndef LOGGING_H
#define LOGGING_H

#ifndef LOGGING_ENABLED
#define LOGGING_ENABLED 0
#endif // LOGGING_ENABLED

#if LOGGING_ENABLED == 1
  #include "stdio.h"

  #define LOG(level, component, message) printf("[%5s] %5s: %s\n", (level), (component), (message))
#else
  #define LOG(level, component, message)
#endif // LOGGING_ENABLED == 1

#define REGISTER_COMPONENT(c) static char component[] = (c) 

#define DEBUG(message) LOG("DEBUG", (component), (message))
#define WARN(message) LOG("WARN", (component), (message))
#define ERR( message) LOG("ERR", (component), (message))

#endif // LOGGING_H
