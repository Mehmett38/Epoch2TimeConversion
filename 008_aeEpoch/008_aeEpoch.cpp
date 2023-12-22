#include <iostream>
#include "ae_epoch.h"

using namespace std;

const char* ptr[] = {"Monday", "Tuesday", "Wednesday", "Thursday",
					 "Friday", "Saturday", "Sunday"};

int main()
{
	RTC_Time rtc;
	uint64_t epoch = 0;

	uint64_t epochVal = 1703284790;

	rtc = epoch2time(1703284790);
	epoch = time2epoch(rtc);

	cout << (int)rtc.day	     << "/" << (int)rtc.month  << "/" << (int)rtc.year << endl;
	cout << (int)rtc.hour		 << ":" << (int)rtc.minute << ":" << (int)rtc.second << endl;
	cout << ptr[rtc.weekDay - 1] << endl;
	cout << "User epoch value = " << epochVal << endl;
	cout << "Calculated epoch = " << epoch << endl;
	if (epochVal == epoch)
		cout << "\n\nTest Succesfully Completed\n__________________________" << endl;
}




/*
#include <iostream>
using namespace std;

#include "epoch.h"

uint64_t epochTim = 1703275805 + 10800;
uint32_t epochInDay = 24 * 60 * 60;
uint16_t dayNumber;

uint16_t month[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
uint16_t month4[12] = { 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

typedef struct {
	uint8_t second;
	uint8_t hour;
	uint8_t minute;
	uint8_t weekDay;
	uint16_t day;
	uint8_t month;
	uint16_t year;
	uint16_t totDay;
	uint8_t totYear;
}Epoch;

int main()
{
	Epoch epoch_s;
	uint32_t daySecond;
	uint16_t leakDay = 0;

	epoch_s.second = 0;
	epoch_s.hour = 0;
	epoch_s.weekDay = 0;  // first day is wednesday
	epoch_s.day = 0;
	epoch_s.month = 1;
	epoch_s.year = 1970;
	epoch_s.totDay = 0;
	epoch_s.totYear = 0;

	epoch_s.totDay = epochTim / epochInDay;
	epoch_s.year = 1970 + epoch_s.totDay / 365;
	epoch_s.weekDay = ((epoch_s.totDay % 7) + 4) % 7;

	for (int i = 1970; i <= epoch_s.year; i++)
	{
		if (i % 4 == 0)
		{
			leakDay++;
			epoch_s.totDay--;
			epoch_s.year = 1970 + epoch_s.totDay / 365;	//because of leak day, year can be more
		}
	}

	if (epoch_s.year % 4 != 0)
	{
		epoch_s.day = (epoch_s.totDay) % 365;

		for (int i = 0; i < 12; i++)
		{
			if (epoch_s.day <= month[i])
			{
				epoch_s.month = i + 1;

				if (i != 0)
				{
					epoch_s.day = epoch_s.day - month[i - 1];
				}
				break;
			}
		}

	}
	else
	{
		epoch_s.day = (epoch_s.totDay + 1) % 365;

		for (int i = 0; i < 12; i++)
		{
			if (epoch_s.day < month4[i])
			{
				epoch_s.month = i + 1;

				if (i != 0)
				{
					epoch_s.day = epoch_s.day - month[i - 1];
				}
				break;
			}
		}
	}


	daySecond = epochTim % epochInDay;
	epoch_s.hour = daySecond / 3600;

	daySecond %= 3600;
	epoch_s.minute = daySecond / 60;

	daySecond %= 60;
	epoch_s.second = daySecond;


	cout << "Total Day : " << (int)epoch_s.totDay << endl;
	cout << "Year : " << (int)epoch_s.year << endl;
	cout << "Month : " << (int)epoch_s.month << endl;
	cout << "Week Of Day : " << (int)epoch_s.weekDay << endl;
	cout << "Day : " << (int)epoch_s.day + 1<< endl;
	cout << "Hour : " << (int)epoch_s.hour << endl;
	cout << "Minute : " << (int)epoch_s.minute << endl;
	cout << "Second : " << (int)epoch_s.second << endl;
}
*/