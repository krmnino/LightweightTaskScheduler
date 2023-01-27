#ifndef LTS_TASK
#define LTS_TASK

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

#include <string>
#include <iomanip>
#include <unistd.h>
#include <sys/wait.h>
#include <array>
#include <memory>
#include <exception>
#include <filesystem>
#include <condition_variable>
#include <thread>

#include "ConfigLoader.hpp"

namespace ts{
enum class TaskStatus {
	FINISHED,
	INIT_ERROR,
	EXEC_ERROR,
	QUEUED,
	RUNNING
};

enum class TaskValidate {
	OK,
	MISSING_NAME_KEYVAL,
	MISSING_SCRIPTFN_KEYVAL,
	MISSING_FREQUENCY_KEYVAL,
	MISSING_DATETIME_KEYVAL,
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
    WDAY_HHMMSS = 44,
    YYYYMMDD = 12,
    HHMMSS = 14,
    INVALID_DATE_FORMAT = -1
};

class Task{
private:
    struct{
        unsigned long year;
        unsigned long month;
        unsigned long day;
        unsigned long wday;
        unsigned long hour;
        unsigned long minute;
        unsigned long second;
    } initial_execution_datetime;
    std::condition_variable cv;
    std::string name;
    std::string description;
    std::string script_filename;
    std::string frequency;
    std::string output;
    std::mutex mtx;
    std::thread thr;
    time_t execution_datetime;
    time_t creation_datetime;
    TaskStatus status;
    DatetimeFormat execution_datetime_fmt;
    int id;
    bool running_thread_flag;

    static void launch_thread(Task* t){
        std::unique_lock<std::mutex> lock(t->mtx);
        time_t execution_datetime = t->get_execution_datetime(false);
        while(!t->cv.wait_until(lock, std::chrono::system_clock::from_time_t(execution_datetime), [t] {return !t->running_thread_flag;})){
            // Before running task, update its status
            t->set_status(TaskStatus::RUNNING);
            // Run the task
            t->run_task();
            // Update next execution time based on frequency
            t->update_execution_datetime();
            // If task frequency is Once, then it is finished
            if(t->get_frequency() == "Once"){
                t->set_status(TaskStatus::FINISHED);
                t->running_thread_flag = false;
            }
            else{
                // Otherwise, set it to queued status again
                t->set_status(TaskStatus::QUEUED);
                execution_datetime = t->get_execution_datetime(false);
            }
        }
    }

public:
    Task();
    Task(std::string, std::string, std::string, std::string, std::string);
    Task(std::string, std::string, std::string, std::string);
    ~Task();
    void run_task(void);
    void stop_thread(void);
    void update_execution_datetime(void);
    const std::string& get_name(void);
    const std::string& get_description(void);
    const std::string& get_script_filename(void);
    const std::string& get_frequency(void);
    const std::string& get_output(void);
    time_t get_creation_datetime(bool);
    time_t get_execution_datetime(bool);
    std::string get_creation_datetime_fmt(void);
    std::string get_execution_datetime_fmt(void);
    TaskStatus get_status(void);
    int get_id(void);
    DatetimeFormat get_execution_datetime_format_attr(void);
    void set_status(TaskStatus);
    void set_id(int);
};

DatetimeValidate validate_hms(std::string);
DatetimeValidate validate_wday(std::string);
DatetimeValidate validate_wday_hms(std::string);
DatetimeValidate validate_yyyymmdd(std::string);
DatetimeValidate validate_yyyymmdd_hms(std::string);
time_t init_today(void);
time_t init_year(void);
time_t today_add_hrs(int);
time_t today_add_hms(std::string);
time_t today_add_dhms(int, std::string);
time_t today_add_wday_hms(std::string);
time_t today_add_yyyymmdd(std::string);
time_t today_add_yyyymmdd_hms(std::string);
DatetimeFormat compute_datetime_format(std::string);
TaskValidate validate_task_parms(cl::Config*, std::string);

} // namespace ts

#endif // LTS_TASK