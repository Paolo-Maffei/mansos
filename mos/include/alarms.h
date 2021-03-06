/*
 * Copyright (c) 2008-2013 the MansOS team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of  conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MANSOS_ALARMS_H
#define MANSOS_ALARMS_H

/// \file
/// Alarm (software timer) implementation
///

#include <defines.h>
#include <lib/list.h>

//! Timer callback function signature
typedef void (*AlarmCallback)(void *);

//! MansOS alarm (software timer) structure.
typedef struct Alarm_s {
    //! list interface
    SLIST_ENTRY(Alarm_s) chain;
    //! callback function pointer
    AlarmCallback callback;
    //! parameter passed to the callback function
    void *data;
    //! time when the alarm should be fired (absolute value)
    uint32_t jiffies;
} Alarm_t;

// -----------------------------------------------
// User API functions
// -----------------------------------------------

///
/// Initialize an alarm timer
/// @param cb     callback function called when the alarm fires
/// @param param  user-defined parameter passed to the callback function
///
static inline void alarmInit(Alarm_t *alarm, AlarmCallback cb, void *param)
{
    SLIST_NEXT(alarm, chain) = NULL;
    alarm->callback = cb;
    alarm->data = param;
    alarm->jiffies = 0;
}

///
/// Schedule an alarm timer
/// @param milliseconds    milliseconds after which the timer will fire (relative value)
///
/// If the alarm is already scheduled, the function removes it first.
///
void alarmSchedule(Alarm_t *alarm, uint32_t milliseconds);

///
/// Remove an alarm timer
///
void alarmRemove(Alarm_t *alarm);

///
/// Get the milliseconds (relative value) after which the alarm is going to fire
///
/// Valid only when the alarm is active (i.e. scheduled)
///
uint32_t getAlarmTime(Alarm_t *);

#endif
