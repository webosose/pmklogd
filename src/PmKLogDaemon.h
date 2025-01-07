// Copyright (c) 2008-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

/**
 ********************************************************************
 * @file PmKLogDaemon.h
 *
 * @brief This file contains implementation definitions used by
 * PmKLogDaemon.
 *
 ********************************************************************
 */


#ifndef PMKLOGDAEMON_H
#define PMKLOGDAEMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include <glib.h>


/* helper for suppressing gcc 'unused function parameter' warnings */
#define UNUSED(x) x __attribute__((unused))

/* Debugging / error reporting utilities */

/* don't check in with this on! */
//#define DEBUG_LOGGING

#define COMPONENT_PREFIX    "pmklogd: "

typedef enum
{
    kPrvPrintDebug,
    kPrvPrintInfo,
    kPrvPrintError
}
PrvPrintType;


/**
 * @brief PrvPrint
 *
 * Bottleneck for status output.
 */
void PrvPrint(PrvPrintType printType, const char *fmt, ...)
__attribute__((format(printf, 2, 3)));


#ifdef DEBUG_LOGGING
#define DbgPrint(...) \
     {                                               \
         PrvPrint(kPrvPrintDebug, __VA_ARGS__);      \
     }
#else
#define DbgPrint(...)
#endif


#define InfoPrint(...) \
    {                                               \
        PrvPrint(kPrvPrintInfo, __VA_ARGS__);       \
    }


#define ErrPrint(...) \
    {                                               \
        PrvPrint(kPrvPrintError, __VA_ARGS__);      \
    }


/*
 * 'safe' string manipulation functions. Each function guarantees
 * the output buffer is not overflowed, and that it is null terminated
 * properly after (assuming it was beforehand).
 */


/**
 * @brief mystrcpy
 *
 * Easy to use wrapper for strcpy to make it safe against buffer
 * overflows and to report any truncations.
 */
void mystrcpy(char *dst, size_t dstSize, const char *src);


/**
 * @brief mystrcat
 *
 * Easy to use wrapper for strcat to make it safe against buffer
 * overflows and to report any truncations.
 */
void mystrcat(char *dst, size_t dstSize, const char *src);


/**
 * @brief mysprintf
 *
 * Easy to use wrapper for sprintf to make it safe against buffer
 * overflows and to report any truncations.
 */
void mysprintf(char *dst, size_t dstSize, const char *fmt, ...)
__attribute__((format(printf, 3, 4)));


/**
 * @brief ParseInt
 */
bool ParseInt(const char *valStr, int *nP);


/**
 * @brief LockProcess
 *
 * Acquire the process lock (by getting a file lock on our pid file).
 * @return true on success, false if failed.
 */
bool LockProcess(const char *component);


/**
 * @brief UnlockProcess
 *
 * Release the lock on the pid file as previously acquired by
 * LockProcess.
 */
void UnlockProcess(void);


#endif /* PMKLOGDAEMON_H */
