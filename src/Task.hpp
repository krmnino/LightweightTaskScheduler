#ifndef LTS_TASK
#define LTS_TASK

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

#include "Constants.hpp"
#include "ConfigLoader.hpp"

namespace ts{

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
                break;
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