#ifndef LTS_CONSTANTS
#define LTS_CONSTANTS

#define DAYS_IN_WEEK 7
#define TIMEZONE -5

#define SUNDAY 0
#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6

#define JANUARY 0
#define FEBRUARY 1
#define MARCH 2
#define APRIL 3
#define MAY 4
#define JUNE 5
#define JULY 6
#define AUGUST 7
#define SEPTEMBER 8
#define OCTOBER 9
#define NOVEMBER 10
#define DECEMBER 11

#define JANUARY_DAYS 31
#define FEBRUARY_DAYS 28
#define MARCH_DAYS 31
#define APRIL_DAYS 30
#define MAY_DAYS 31
#define JUNE_DAYS 30
#define JULY_DAYS 31
#define AUGUST_DAYS 31
#define SEPTEMBER_DAYS 30
#define OCTOBER_DAYS 31
#define NOVEMBER_DAYS 30
#define DECEMBER_DAYS 31

namespace ts{

enum class TaskStatus {
	FINISHED,
	INIT_ERROR,
	EXEC_ERROR,
	QUEUED,
	RUNNING
};

enum class ValidationCode {
	OK,
	MISSING_NAME_KEYVAL,
	MISSING_SCRIPTFN_KEYVAL,
	MISSING_FREQUENCY_KEYVAL,
	MISSING_DATETIME_KEYVAL,
	SCRIPT_NOT_FOUND,
	BAD_FREQUENCY_VALUE,
    INCOMPATIBLE_ONCE_FREQ_DATETIME_FORMAT,
    INCOMPATIBLE_DAILY_FREQ_DATETIME_FORMAT,
    INCOMPATIBLE_WEEKLY_FREQ_DATETIME_FORMAT,
    INCOMPATIBLE_MONTHLY_FREQ_DATETIME_FORMAT,
    INCOMPATIBLE_YEARLY_FREQ_DATETIME_FORMAT,
    PASSED_DATETIME,
    BAD_HMS_LENGTH,
    BAD_YYYYMMDD_LENGTH,
    BAD_NUMBER_CHARACTER,
    MISSING_DATETIME_COLON,
    MISSING_DATETIME_DASH,
    MISSING_DATETIME_SPACE,
    BAD_WDAY,
    YEAR_OUT_OF_RANGE,
    MONTH_OUT_OF_RANGE,
    DAY_OUT_OF_RANGE,
    HOURS_OUT_OF_RANGE,
    MINUTES_OUT_OF_RANGE,
    SECONDS_OUT_OF_RANGE,
};

enum class DatetimeFormat {
    YYYYMMDD_HHMMSS,
    WDAY_HHMMSS,
    YYYYMMDD,
    HHMMSS,
    INVALID_DATE_FORMAT
};

enum class EventType{
    UNDEFINED,
    INFO,
    WARNING,
    ERROR
};

const long unsigned int TASK_ID_FIELD_MAX_LEN = 10;
const long unsigned int TASK_NAME_FIELD_MAX_LEN = 32;
const long unsigned int TASK_EXEC_DATE_FIELD_MAX_LEN = 32;
const long unsigned int TASK_STATUS_FIELD_MAX_LEN = 10;

}

#endif