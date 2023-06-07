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
#include "EventReporter.hpp"

namespace lts{

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
    std::string config_filename;
    std::string name;
    std::string description;
    std::string script_filename;
    std::string frequency;
    std::string output;
    std::mutex mtx;
    std::thread thr;
    EventReporter* event_reporter_ptr;
    time_t execution_datetime;
    time_t creation_datetime;
    TaskStatus status;
    DatetimeFormat execution_datetime_fmt;
    int id;
    bool running_thread_flag;

    static void launch_thread(Task* t){
        std::unique_lock<std::mutex> lock(t->mtx);
        time_t execution_datetime = t->get_execution_datetime(false);
        std::string event_message;
        while(!t->cv.wait_until(lock, std::chrono::system_clock::from_time_t(execution_datetime), [t] {return !t->running_thread_flag;})){
            // Before running task, update its status
            t->set_status(TaskStatus::RUNNING);

            // Log event that task started running
            event_message = "The task \"" + t->get_name() + "\" started running.";
            t->event_reporter_ptr->log_event(EventType::INFO, event_message);
            #ifndef SILENT
            t->event_reporter_ptr->publish_last_event();
            #endif

            // Run the task
            t->run_task();
            // Update next execution time based on frequency
            t->update_execution_datetime();
            // If task frequency is Once, then it is finished
            if(t->get_frequency() == "Once"){
                t->set_status(TaskStatus::FINISHED);
                
                // Log event that task ended and transition to FINISHED state
                event_message = "The task \"" + t->get_name() + "\" finished running.";
                t->event_reporter_ptr->log_event(EventType::INFO, event_message);
                #ifndef SILENT
                t->event_reporter_ptr->publish_last_event();
                #endif

                break;
            }
            else{
                // Otherwise, set it to queued status again
                t->set_status(TaskStatus::QUEUED);
                execution_datetime = t->get_execution_datetime(false);

                // Log event that task ended and transition to QUEUED state
                event_message = "The task \"" + t->get_name() + "\" finished running. It has been rescheduled for next run.";
                t->event_reporter_ptr->log_event(EventType::INFO, event_message);
                #ifndef SILENT
                t->event_reporter_ptr->publish_last_event();
                #endif
            }
        }
    }

public:
    Task();
    Task(std::string, std::string, std::string, std::string, std::string, std::string);
    ~Task();
    void run_task(void);
    void stop_thread(void);
    void update_execution_datetime(void);
    std::string get_name(void) const;
    std::string get_description(void) const;
    std::string get_script_filename(void) const;
    std::string get_frequency(void) const;
    std::string get_output(void) const;
    time_t get_creation_datetime(bool);
    time_t get_execution_datetime(bool);
    std::string get_creation_datetime_fmt(void) const;
    std::string get_execution_datetime_fmt(void) const;
    TaskStatus get_status(void) const;
    int get_id(void) const;
    DatetimeFormat get_execution_datetime_format_attr(void);
    std::string get_config_filename(void);
    void set_status(TaskStatus);
    void set_id(int);
    void set_event_reporter_ptr(EventReporter*);
};

ValidationCode validate_hms(std::string);
ValidationCode validate_wday(std::string);
ValidationCode validate_wday_hms(std::string);
ValidationCode validate_yyyymmdd(std::string);
ValidationCode validate_yyyymmdd_hms(std::string);
time_t init_today(void);
time_t init_year(void);
time_t today_add_hrs(int);
time_t today_add_hms(std::string);
time_t today_add_dhms(int, std::string);
time_t today_add_wday_hms(std::string);
time_t today_add_yyyymmdd(std::string);
time_t today_add_yyyymmdd_hms(std::string);
DatetimeFormat compute_datetime_format(std::string);
ValidationCode validate_task_parms(cl::Config*, std::string);

} // namespace ts

#endif // LTS_TASK