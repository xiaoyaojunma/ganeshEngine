#ifndef GANESHENGINE_GHHEADERS_H
#define GANESHENGINE_GHHEADERS_H

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <type_traits>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <list>
#include <array>
#include <chrono>
#include <memory>

#include <glm/glm.hpp>

#include "ghCore.h"
#include "ghILogger.h"

using Compote::Logger::LOG_LEVEL;

#ifdef _DEBUGGING
#define _LOG(LOG_LEVEL, MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        Compote::Logger::callLogMgr(LOG_LEVEL, __FILE__, __LINE__, message);\
    }
#define _TRACE(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        Compote::Logger::callLogMgr(LOG_LEVEL::TRACE, __FILE__, __LINE__, message);\
    }
#define _INFO(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        Compote::Logger::callLogMgr(LOG_LEVEL::INFO, __FILE__, __LINE__, message);\
    }
#define _DEBUG(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        Compote::Logger::callLogMgr(LOG_LEVEL::DEBUG, __FILE__, __LINE__, message);\
    }
#define _WARNING(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        Compote::Logger::callLogMgr(LOG_LEVEL::WARNING, __FILE__, __LINE__, message);\
    }
#define _ERROR(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        Compote::Logger::callLogMgr(LOG_LEVEL::ERROR, __FILE__, __LINE__, message);\
    }
#define _FATAL(MESSAGE) {\
        std::ostringstream internalLogStream;\
        internalLogStream << MESSAGE;\
        std::string message = internalLogStream.str(); \
        Compote::Logger::callLogMgr(LOG_LEVEL::FATAL, __FILE__, __LINE__, message);\
    }
#else
#define _LOG(LOG_LEVEL, MESSAGE)
#define _TRACE(MESSAGE)
#define _INFO(MESSAGE)
#define _DEBUG(MESSAGE)
#define _WARNING(MESSAGE)
#define _ERROR(MESSAGE)
#define _FATAL(MESSAGE)
#endif

#endif //GANESHENGINE_GHHEADERS_H
