#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: verify that execution datetime is set properly when initializing Task object
    // Frequency: Once
    // Datetime format: HH:MM:SS

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string months_str;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string verify_datetime_str;
    std::string ret_datetime_str;

    time_now = std::time(&time_now);

    // Add one minute in seconds from current time
    time_now_add = time_now + 60;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months_str = "Jan";
        break;
    case FEBRUARY:
        months_str = "Feb";
        break;
    case MARCH:
        months_str = "Mar";
        break;
    case APRIL:
        months_str = "Apr";
        break;
    case MAY:
        months_str = "May";
        break;
    case JUNE:
        months_str = "Jun";
        break;
    case JULY:
        months_str = "Jul";
        break;
    case AUGUST:
        months_str = "Aug";
        break;
    case SEPTEMBER:
        months_str = "Sep";
        break;
    case OCTOBER:
        months_str = "Oct";
        break;
    case NOVEMBER:
        months_str = "Nov";
        break;
    case DECEMBER:
        months_str = "Dec";
        break;
    default:
        months_str = "";
        break;
    }  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Once";
    std::string t_datetime = hours + ":" + minutes + ":" + seconds;
    std::string t_config_filename = "config.cl";

    lts::Task* t = new lts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime, t_config_filename);
    
    ret_datetime_str = t->get_execution_datetime_fmt();

    // Add timezone offset to initial execution datetime
    time_now_add = time_now_add + (TIMEZONE * 60 * 60);
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months = "Jan";
        break;
    case FEBRUARY:
        months = "Feb";
        break;
    case MARCH:
        months = "Mar";
        break;
    case APRIL:
        months = "Apr";
        break;
    case MAY:
        months = "May";
        break;
    case JUNE:
        months = "Jun";
        break;
    case JULY:
        months = "Jul";
        break;
    case AUGUST:
        months = "Aug";
        break;
    case SEPTEMBER:
        months = "Sep";
        break;
    case OCTOBER:
        months = "Oct";
        break;
    case NOVEMBER:
        months = "Nov";
        break;
    case DECEMBER:
        months = "Dec";
        break;
    default:
        months = "";
        break;
    }
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    verify_datetime_str = wday_abbr + " " + months + " " + days + " " +
                          hours + ":" + minutes + ":" + seconds + " " + years;

    assert(verify_datetime_str.find(ret_datetime_str) != std::string::npos);
    assert(time_now_add == t->get_execution_datetime(true));
    assert(t->get_status() == lts::TaskStatus::QUEUED);

    delete t;

    std::cout << ">> Task_setting_exec_datetime_Once: 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: verify that execution datetime is set properly when initializing Task object
    // Frequency: Once
    // Datetime format: YYYY-MM-DD HH:MM:SS

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string months_str;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string verify_datetime_str;
    std::string ret_datetime_str;

    time_now = std::time(&time_now);

    // Add one minute in seconds from current time
    time_now_add = time_now + 60;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months_str = "Jan";
        break;
    case FEBRUARY:
        months_str = "Feb";
        break;
    case MARCH:
        months_str = "Mar";
        break;
    case APRIL:
        months_str = "Apr";
        break;
    case MAY:
        months_str = "May";
        break;
    case JUNE:
        months_str = "Jun";
        break;
    case JULY:
        months_str = "Jul";
        break;
    case AUGUST:
        months_str = "Aug";
        break;
    case SEPTEMBER:
        months_str = "Sep";
        break;
    case OCTOBER:
        months_str = "Oct";
        break;
    case NOVEMBER:
        months_str = "Nov";
        break;
    case DECEMBER:
        months_str = "Dec";
        break;
    default:
        months_str = "";
        break;
    }  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Once";
    std::string t_datetime = years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds;
    std::string t_config_filename = "config.cl";

    lts::Task* t = new lts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime, t_config_filename);
    
    ret_datetime_str = t->get_execution_datetime_fmt();

    // Add timezone offset to initial execution datetime
    time_now_add = time_now_add + (TIMEZONE * 60 * 60);
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months = "Jan";
        break;
    case FEBRUARY:
        months = "Feb";
        break;
    case MARCH:
        months = "Mar";
        break;
    case APRIL:
        months = "Apr";
        break;
    case MAY:
        months = "May";
        break;
    case JUNE:
        months = "Jun";
        break;
    case JULY:
        months = "Jul";
        break;
    case AUGUST:
        months = "Aug";
        break;
    case SEPTEMBER:
        months = "Sep";
        break;
    case OCTOBER:
        months = "Oct";
        break;
    case NOVEMBER:
        months = "Nov";
        break;
    case DECEMBER:
        months = "Dec";
        break;
    default:
        months = "";
        break;
    }
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    verify_datetime_str = wday_abbr + " " + months + " " + days + " " +
                          hours + ":" + minutes + ":" + seconds + " " + years;

    assert(verify_datetime_str.find(ret_datetime_str) != std::string::npos);
    assert(time_now_add == t->get_execution_datetime(true));
    assert(t->get_status() == lts::TaskStatus::QUEUED);

    delete t;

    std::cout << ">> Task_setting_exec_datetime_Once: 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: verify that execution datetime is set properly when initializing Task object
    // Frequency: Once
    // Datetime format: WDAY HH:MM:SS (full week day names)

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string months_str;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string verify_datetime_str;
    std::string ret_datetime_str;

    time_now = std::time(&time_now);

    // Add one minute in seconds from current time
    time_now_add = time_now + 60;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months_str = "Jan";
        break;
    case FEBRUARY:
        months_str = "Feb";
        break;
    case MARCH:
        months_str = "Mar";
        break;
    case APRIL:
        months_str = "Apr";
        break;
    case MAY:
        months_str = "May";
        break;
    case JUNE:
        months_str = "Jun";
        break;
    case JULY:
        months_str = "Jul";
        break;
    case AUGUST:
        months_str = "Aug";
        break;
    case SEPTEMBER:
        months_str = "Sep";
        break;
    case OCTOBER:
        months_str = "Oct";
        break;
    case NOVEMBER:
        months_str = "Nov";
        break;
    case DECEMBER:
        months_str = "Dec";
        break;
    default:
        months_str = "";
        break;
    }  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Once";
    std::string t_datetime = wday_full + " " + hours + ":" + minutes + ":" + seconds;
    std::string t_config_filename = "config.cl";

    lts::Task* t = new lts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime, t_config_filename);
    
    ret_datetime_str = t->get_execution_datetime_fmt();

    // Add timezone offset to initial execution datetime
    time_now_add = time_now_add + (TIMEZONE * 60 * 60);
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months = "Jan";
        break;
    case FEBRUARY:
        months = "Feb";
        break;
    case MARCH:
        months = "Mar";
        break;
    case APRIL:
        months = "Apr";
        break;
    case MAY:
        months = "May";
        break;
    case JUNE:
        months = "Jun";
        break;
    case JULY:
        months = "Jul";
        break;
    case AUGUST:
        months = "Aug";
        break;
    case SEPTEMBER:
        months = "Sep";
        break;
    case OCTOBER:
        months = "Oct";
        break;
    case NOVEMBER:
        months = "Nov";
        break;
    case DECEMBER:
        months = "Dec";
        break;
    default:
        months = "";
        break;
    }
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    verify_datetime_str = wday_abbr + " " + months + " " + days + " " +
                          hours + ":" + minutes + ":" + seconds + " " + years;

    assert(verify_datetime_str.find(ret_datetime_str) != std::string::npos);
    assert(time_now_add == t->get_execution_datetime(true));
    assert(t->get_status() == lts::TaskStatus::QUEUED);

    delete t;

    std::cout << ">> Task_setting_exec_datetime_Once: 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: verify that execution datetime is set properly when initializing Task object
    // Frequency: Once
    // Datetime format: WDAY HH:MM:SS (abbreviated week day names)

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string months_str;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string verify_datetime_str;
    std::string ret_datetime_str;

    time_now = std::time(&time_now);

    // Add one minute in seconds from current time
    time_now_add = time_now + 60;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months_str = "Jan";
        break;
    case FEBRUARY:
        months_str = "Feb";
        break;
    case MARCH:
        months_str = "Mar";
        break;
    case APRIL:
        months_str = "Apr";
        break;
    case MAY:
        months_str = "May";
        break;
    case JUNE:
        months_str = "Jun";
        break;
    case JULY:
        months_str = "Jul";
        break;
    case AUGUST:
        months_str = "Aug";
        break;
    case SEPTEMBER:
        months_str = "Sep";
        break;
    case OCTOBER:
        months_str = "Oct";
        break;
    case NOVEMBER:
        months_str = "Nov";
        break;
    case DECEMBER:
        months_str = "Dec";
        break;
    default:
        months_str = "";
        break;
    }  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Once";
    std::string t_datetime = wday_abbr + " " + hours + ":" + minutes + ":" + seconds;
    std::string t_config_filename = "config.cl";

    lts::Task* t = new lts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime, t_config_filename);
    
    ret_datetime_str = t->get_execution_datetime_fmt();

    // Add timezone offset to initial execution datetime
    time_now_add = time_now_add + (TIMEZONE * 60 * 60);
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months = "Jan";
        break;
    case FEBRUARY:
        months = "Feb";
        break;
    case MARCH:
        months = "Mar";
        break;
    case APRIL:
        months = "Apr";
        break;
    case MAY:
        months = "May";
        break;
    case JUNE:
        months = "Jun";
        break;
    case JULY:
        months = "Jul";
        break;
    case AUGUST:
        months = "Aug";
        break;
    case SEPTEMBER:
        months = "Sep";
        break;
    case OCTOBER:
        months = "Oct";
        break;
    case NOVEMBER:
        months = "Nov";
        break;
    case DECEMBER:
        months = "Dec";
        break;
    default:
        months = "";
        break;
    }
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    verify_datetime_str = wday_abbr + " " + months + " " + days + " " +
                          hours + ":" + minutes + ":" + seconds + " " + years;

    assert(verify_datetime_str.find(ret_datetime_str) != std::string::npos);
    assert(time_now_add == t->get_execution_datetime(true));
    assert(t->get_status() == lts::TaskStatus::QUEUED);

    delete t;

    std::cout << ">> Task_setting_exec_datetime_Once: 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: verify that execution datetime is set properly when initializing Task object
    // Frequency: Once
    // Datetime format: YYYY-MM-DD

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string months_str;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string verify_datetime_str;
    std::string ret_datetime_str;

    time_now = std::time(&time_now);

    // Add one day in seconds from current time
    time_now_add = time_now + (24 * 60 * 60);
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months_str = "Jan";
        break;
    case FEBRUARY:
        months_str = "Feb";
        break;
    case MARCH:
        months_str = "Mar";
        break;
    case APRIL:
        months_str = "Apr";
        break;
    case MAY:
        months_str = "May";
        break;
    case JUNE:
        months_str = "Jun";
        break;
    case JULY:
        months_str = "Jul";
        break;
    case AUGUST:
        months_str = "Aug";
        break;
    case SEPTEMBER:
        months_str = "Sep";
        break;
    case OCTOBER:
        months_str = "Oct";
        break;
    case NOVEMBER:
        months_str = "Nov";
        break;
    case DECEMBER:
        months_str = "Dec";
        break;
    default:
        months_str = "";
        break;
    }  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Once";
    std::string t_datetime = years + "-" + months + "-" + days;
    std::string t_config_filename = "config.cl";

    lts::Task* t = new lts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime, t_config_filename);
    
    ret_datetime_str = t->get_execution_datetime_fmt();

    // Obtain current time value with init_today()
    // Add one day to current time value
    // Add timezone offset 
    time_now_add = lts::init_today() + (TIMEZONE * 60 * 60) + (24 * 60 * 60);
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months = "Jan";
        break;
    case FEBRUARY:
        months = "Feb";
        break;
    case MARCH:
        months = "Mar";
        break;
    case APRIL:
        months = "Apr";
        break;
    case MAY:
        months = "May";
        break;
    case JUNE:
        months = "Jun";
        break;
    case JULY:
        months = "Jul";
        break;
    case AUGUST:
        months = "Aug";
        break;
    case SEPTEMBER:
        months = "Sep";
        break;
    case OCTOBER:
        months = "Oct";
        break;
    case NOVEMBER:
        months = "Nov";
        break;
    case DECEMBER:
        months = "Dec";
        break;
    default:
        months = "";
        break;
    }
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    verify_datetime_str = wday_abbr + " " + months + " " + days + " " +
                          hours + ":" + minutes + ":" + seconds + " " + years;

    assert(verify_datetime_str.find(ret_datetime_str) != std::string::npos);
    assert(time_now_add == t->get_execution_datetime(true));
    assert(t->get_status() == lts::TaskStatus::QUEUED);

    delete t;

    std::cout << ">> Task_setting_exec_datetime_Once: 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: verify that execution datetime is set properly when initializing Task object
    // Frequency: Once
    // Datetime format: invalid format

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Once";
    std::string t_datetime = "anything";
    std::string t_config_filename = "config.cl";

    lts::Task* t = new lts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime, t_config_filename);

    assert(t->get_execution_datetime(false) == 0);
    assert(t->get_status() == lts::TaskStatus::INIT_ERROR);

    delete t;

    std::cout << ">> Task_setting_exec_datetime_Once: 6 done" << std::endl;
    return 0;
}


int test7(){
    // TEST 7: attempt to initialize Task with invalid datetime values
    // Frequency: Once
    // Datetime format: HH:MM:SS, YYYY-MM-DD HH:MM:SS, WDAY HH:MM:SS, YYYY-MM-DD

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Once";
    std::string t_config_filename = "config.cl";
    std::vector<std::string> datetimes = {
        "60:20:00",
        "12:60:00",
        "12:20:60",
        "60:20a00",
        "60a20:00",
        "1a:20:00",
        "12:a0:00",
        "12:00:0A",
        "2022-02-15 60:20:00",
        "2022-02-15 12:60:00",
        "2022-02-15 12:20:60",
        "2022-02-15 60:20a00",
        "2022-02-15 60a20:00",
        "2022-02-15 1a:20:00",
        "2022-02-15 12:a0:00",
        "2022-02-15 12:00:0A",
        "20a2-02-15 12:00:00",
        "2022-0a-15 12:00:00",
        "2022-02-a5 12:00:00",
        "2022a02-15 12:00:00",
        "2022-02a15 12:00:00",
        "2022-02-15a12:00:00",
        "1980-02-15 12:00:00",
        "2022-80-15 12:00:00",
        "2022-02-70 12:00:00",
        "Monday 60:20:00",
        "Monday 12:60:00",
        "Monday 12:20:60",
        "Monday 60:20a00",
        "Monday 60a20:00",
        "Mondaya12:00:00",
        "Monday 1a:20:00",
        "Monday 12:a0:00",
        "Monday 12:00:0A",
        "Mxnday 12:00:00",
        "Tuexday 12:00:00",
        "Wednxsday 12:00:00",
        "Thurxday 12:00:00",
        "Fridxy 12:00:00",
        "Satuxday 12:00:00",
        "Sundax 12:00:00",
        "Mxn 12:00:00",
        "Txe 12:00:00",
        "Wxd 12:00:00",
        "Txu 12:00:00",
        "Fxi 12:00:00",
        "Sxt 12:00:00",
        "Sxn 12:00:00",
        "XYZ 12:00:00",
        "000 12:00:00",
        "20a2-02-15",
        "2022-0a-15",
        "2022-02-a5",
        "2022a02-15",
        "2022-02a15",
        "2022-02-15",
        "1980-02-15",
        "2022-80-15",
        "2022-02-70"
    };

    for(size_t i = 0; i < datetimes.size(); i++){
        lts::Task* t = new lts::Task(t_name, t_description, t_script_name, t_frequency, datetimes[i], t_config_filename);

        assert(t->get_execution_datetime(false) == 0);
        assert(t->get_status() == lts::TaskStatus::INIT_ERROR);

        delete t;
    }

    std::cout << ">> Task_setting_exec_datetime_Once: 7 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
}