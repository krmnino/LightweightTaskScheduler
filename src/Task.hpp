#ifndef TSTASK
#define TSTASK

#define DAYS_IN_WEEK 7
#define TIMEZONE -4

#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12

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

#include <string>
#include <iomanip>

#include "ConfigLoader.hpp"

namespace ts{
enum class TaskStatus {
	FINISHED,
	ERROR,
	QUEUED,
	RUNNING
};

enum class TaskValidate {
	OK,
	MISSING_REQUIRED_KEYVALS,
	SCRIPT_NOT_FOUND,
	BAD_FREQUENCY_VALUE,
    BAD_DATETIME_VALUE,
    MISSING_DATETIME_VALUE
};

enum class DatetimeValidate{
    OK,
    BAD_HMS_LENGTH,
    BAD_YYYYMMDD_LENGTH,
    BAD_MMDD_LENGTH,
    BAD_NUMBER_CHARACTER,
    BAD_APHABETIC_CHARACTER,
    MISSING_COLON,
    MISSING_DASH,
    MISSING_SPACE,
    BAD_WDAY,
    YEAR_OUT_OF_RANGE,
    MONTH_OUT_OF_RANGE,
    DAY_OUT_OF_RANGE,
    HOURS_OUT_OF_RANGE,
    MINUTES_OUT_OF_RANGE,
    SECONDS_OUT_OF_RANGE,
    INVALID_DATETIME_INPUT
};

enum class DatetimeFormat {
    YYYYMMDD_HHMMSS = 32,
    WDAY6_HHMMSS = 68,
    WDAY7_HHMMSS = 76,
    WDAY8_HHMMSS = 84,
    WDAY9_HHMMSS = 92,
    MMDD_HHMMSS = 26,
    WDAY_HHMMSS = 44,
    YYYYMMDD = 12,
    HHMMSS = 14,
    MMDD = 6,
    INVALID_DATE_FORMAT = -1
};

class Task{
private:
    time_t execution_datetime;
    time_t creation_datetime;
    std::string name;
    std::string description;
    std::string script_filename;
    std::string frequency;
    std::string input_execution_datetime;
    std::string output;
    pid_t pid;
    TaskStatus status;
    int id;

public:
    Task();
    Task(std::string, std::string, std::string, std::string, std::string);
    Task(std::string, std::string, std::string, std::string);
    ~Task();
    void run_task(void);
    std::string get_name(void);
    std::string get_description(void);
    std::string get_script_filename(void);
    std::string get_frequency(void);
    time_t get_creation_datetime(void);
    time_t get_execution_datetime(void);
    std::string get_output(void);
    std::string get_creation_datetime_fmt(void);
    std::string get_execution_datetime_fmt(void);
    std::string get_input_execution_datetime(void);
    TaskStatus get_status(void);
    int get_id(void);
    void set_status(TaskStatus);
    void set_id(int);
    void update_execution_datetime(void);
};

DatetimeValidate validate_hms(std::string);
DatetimeValidate validate_wday(std::string);
DatetimeValidate validate_wday_hms(std::string);
DatetimeValidate validate_mmdd(std::string);
DatetimeValidate validate_mmdd_hms(std::string);
DatetimeValidate validate_yyyymmdd(std::string);
DatetimeValidate validate_yyyymmdd_hms(std::string);
time_t init_today(void);
time_t init_year(void);
time_t today_add_hms(std::string);
time_t today_add_dhms(int, std::string);
time_t today_add_wday_hms(std::string);
time_t today_add_mmdd(std::string);
time_t today_add_mmdd_hms(std::string);
time_t today_add_yyyymmdd(std::string);
time_t today_add_yyyymmdd_hms(std::string);
DatetimeFormat get_datetime_format(std::string);
TaskValidate validate_task_parms(cl::Config*, std::string);
} // namespace ts

#endif // TSTASK