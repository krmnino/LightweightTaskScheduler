#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing Task::update_execution_datetime(), execution time should increase by 1 hour.
    // Frequency: Daily
    // Datetime format: HH:MM:SS

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string verify_datetime_str;
    std::string ret_datetime_str;

    time_now = std::time(&time_now);

    // Add 5 seconds to current time
    time_now_add = time_now + 5;
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;
    
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
    std::string t_frequency = "Daily";
    std::string t_datetime = hours + ":" + minutes + ":" + seconds; ;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    time_now = std::time(&time_now);

    // Add one day in seconds to current time
    // Add timezone offset
    time_now_add = time_now_add + (24 * 60 * 60) + (TIMEZONE * 60 * 60);
    
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
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_abbr = "Fri";
        break;
    case SATURDAY:
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

    assert(ret_datetime_str.find(verify_datetime_str) != std::string::npos);
    delete t;

    std::cout << ">> Task_update_execution_datetime_Daily: 1 done" << std::endl;
    return 0;
}


int main(){
    test1();
}