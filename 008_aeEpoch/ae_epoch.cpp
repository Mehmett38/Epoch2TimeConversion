#include "ae_epoch.h"
using namespace std;


uint16_t month[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
uint16_t monthLeap[12] = { 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};
RTC_Time rtc;
uint8_t utcVal = 0;


/**
*@brief convert epoch value to year,month,hour....
*@param[in] epoch time
*@return RTC_Time this structure store the all time information
*/
RTC_Time epoch2time(uint64_t epochTim)
{
#if UTC == 1
	epochTim += (int)((float)utcVal * 3600.0);
#endif

	uint16_t i = 0;

	rtc.totalDay = epochTim / EPOCH_IN_A_DAY;
	rtc.year = 1970 + rtc.totalDay / DAY_IN_A_YEAR;			/// not fully correct year
	uint32_t totalDay = rtc.totalDay;

	// year calculation 
	for (i = 1972; i <= rtc.year; i += 4)					/// fully correct year
	{
		rtc.leakDay++;
		totalDay--;
		rtc.year = 1970 + totalDay / DAY_IN_A_YEAR;
	}

	// month and day calculation
	if (rtc.year % 4 != 0)
	{
		rtc.day = (rtc.totalDay - rtc.leakDay) % DAY_IN_A_YEAR;

		for (i = 0; i < 12; i++)
		{
			if (rtc.day < month[i])
			{
				rtc.month = i + OFFSET;

				(i != 0) ? (rtc.day = rtc.day - month[i - 1] + OFFSET) : rtc.day;
				break;
			}
		}
	}
	else
	{
		rtc.day = (rtc.totalDay - rtc.leakDay) % DAY_IN_A_YEAR + OFFSET; // 365 + 1 day

		for (i = 0; i < 12; i++)
		{
			if (rtc.day < monthLeap[i])
			{
				rtc.month = i + OFFSET;

				(i != 0) ? (rtc.day = rtc.day - monthLeap[i - 1] + OFFSET) : rtc.day;
				break;
			}
		}
	}

	// weadkday calcuation
	rtc.weekDay = ((rtc.totalDay % 7) + 3) % 7 + OFFSET;	/// the first day is thursday +3 comes

	//hour calculation 
	uint32_t currentDaySec = epochTim % EPOCH_IN_A_DAY;
	rtc.hour = currentDaySec / EPOCH_IN_A_HOUR;

	//minute calculation
	currentDaySec %= EPOCH_IN_A_HOUR;
	rtc.minute = currentDaySec / 60;

	//second calculation
	currentDaySec %= EPOCH_IN_A_MINUTE;
	rtc.second = currentDaySec;

	return rtc;
}

/**
* @brief convert year, hour... information to epoch
*@param[in] RTC_Time this structure store the all time information
*@return epoch time
*/
uint64_t time2epoch(RTC_Time rtc)
{
	uint64_t epoch = 0;

	uint8_t leapDays = 0;

	for (int i = 1972; i < rtc.year; i += 4)
		leapDays++;

	// add the days of year
	if (rtc.year % 4 != 0)
	{
		(rtc.month == 1) ? rtc.day : rtc.day += month[rtc.month - 2];
	}
	else
	{
		(rtc.month == 1) ? rtc.day : rtc.day += monthLeap[rtc.month - 2];
	}
	
	rtc.day += leapDays - 1;	/// the current day is not finished

	epoch += (rtc.year - 1970) * (EPOCH_IN_A_YEAR);
	epoch += rtc.day * (EPOCH_IN_A_DAY);
	epoch += rtc.hour * (EPOCH_IN_A_HOUR);
	epoch += rtc.minute * (EPOCH_IN_A_MINUTE);
	epoch += rtc.second;

	return epoch;
}


#if UTC == 1
/**
* @brief if UTC_CONTROL enabled can set the utc
*/
void setUtc(uint8_t utc)
{
	utcVal = utc;
}

/**
* @brief if UTC_CONTROL enabled can get the utc
*/
uint8_t getUtc()
{
	return utcVal;
}
#endif






