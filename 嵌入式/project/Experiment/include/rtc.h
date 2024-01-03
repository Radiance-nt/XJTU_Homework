#ifndef __INCLUDE_RTC_H
#define __INCLUDE_RTC_H

#include "types.h"

void rtc_init(void);

uint32_t rtc_read_time(void);

uint32_t rtc_read_date(void);

#endif