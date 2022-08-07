#ifndef TSTASK
#define TSTASK

#define DAYS_IN_WEEK 7
#define TIMEZONE -4

#define JANUARY 1
#define FEBRARY 2
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

#include <string>
#include <iomanip>

#include "ConfigLoader.hpp"

namespace ts{
enum class TaskStatus {
	FINISHED,
	ERROR,
	QUEUED,
	RUNNING,
};

enum class TaskValidate {
	OK,
	MISSING_REQUIRED_KEYVALS,
	SCRIPT_NOT_FOUND,
	BAD_FREQUENCY_VALUE,
    BAD_DATETIME
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
    BAD_WDAY,
    YEAR_OUT_OF_RANGE,
    MONTH_OUT_OF_RANGE,
    DAY_OUT_OF_RANGE,
    HOURS_OUT_OF_RANGE,
    MINUTES_OUT_OF_RANGE,
    SECONDS_OUT_OF_RANGE,
    INVALID_DATETIME_INPUT
};

class Task{
private:
    time_t starting_date;
    time_t task_creation_date;
    time_t execution_date;
    std::string name;
    std::string description;
    std::string script_filename;
    std::string frequency;
    std::string output;
    pid_t pid;
    int status;

public:
    Task();
    Task(std::string, std::string, std::string);
    ~Task();
    void launch(void);
    std::string get_name(void);
    std::string get_description(void);
    std::string get_frequency(void);
    time_t get_starting_date(void);
    time_t get_task_creation_date(void);
    time_t get_execution_date(void);
    std::string get_output(void);
    std::string get_starting_date_fmt(void);
    std::string get_task_creation_date_fmt(void);
    std::string get_execution_date_fmt(void);
};

DatetimeValidate validate_hms(std::string);
DatetimeValidate validate_wday(std::string);
DatetimeValidate validate_yyyymmdd(std::string);
DatetimeValidate validate_mmdd(std::string);
time_t init_day(void);
time_t init_day_add_hms(std::string);
time_t init_day_add_dhms(int, std::string);
time_t init_day_add_wdhms(std::string, std::string);
TaskValidate validate_task_parms(cl::Config*, std::string);
} // namespace ts

#endif // TSTASK