#pragma once

#include <iostream>
#include <stdint.h>


#define EPOCH_IN_A_DAY					(86400ul)
#define DAY_IN_A_YEAR					(365)
#define EPOCH_IN_A_HOUR					(3600)
#define EPOCH_IN_A_MINUTE				(60)
#define EPOCH_IN_A_YEAR					(EPOCH_IN_A_DAY * 365)
#define OFFSET							(1)

#define UTC_CONTROL						(1)
#define UTC								(UTC_CONTROL)	// if utc control == 1 add utc


typedef struct {
	uint8_t second;
	uint8_t hour;
	uint8_t minute;
	uint8_t weekDay;
	uint16_t day;
	uint16_t month;
	uint16_t year;
	uint16_t totalDay;
	uint8_t totalYear;
	uint8_t leakDay;
}RTC_Time;


RTC_Time epoch2time(uint64_t epochTim);
uint64_t time2epoch(RTC_Time rtc);

#if UTC == 1
void setUtc(uint8_t utc);
uint8_t getUtc();
#endif


