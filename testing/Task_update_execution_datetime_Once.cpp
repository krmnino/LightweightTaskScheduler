#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing Task::update_execution_datetime(), execution time should not change after the call.
    // Frequency: Once
    // Datetime format: HH:MM:SS, MM-DD HH:MM:SS, and YYYY-MM-DD HH:MM:SS 

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    std::string ret_datetime_before;     
    std::string ret_datetime_after;     

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

    std::vector<std::string> datetimes = {
        hours + ":" + minutes + ":" + seconds, // HH:MM:SS
        months + "-" + days + " " + hours + ":" + minutes + ":" + seconds, // MM-DD HH:MM:SS
        years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds, // YYYY-MM-DD HH:MM:SS
        wday_abbr + " " + hours + ":" + minutes + ":" + seconds, // WDAY HH:MM:SS (abbreviated week day name)
        wday_full + " " + hours + ":" + minutes + ":" + seconds // WDAY HH:MM:SS (full week day name)
    };

    for(int i = 0; i < datetimes.size(); i++){
        ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);
        
        ret_datetime_before = t->get_execution_datetime_fmt();
        t->update_execution_datetime();
        ret_datetime_after = t->get_execution_datetime_fmt();

        assert(ret_datetime_before.find(ret_datetime_after) != std::string::npos);

        delete t;
    }

    std::cout << ">> Task_update_execution_datetime_Once: 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing Task::update_execution_datetime(), execution time should not change after the call.
    // Frequency: Once
    // Datetime format: HH:MM:SS

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    std::string ret_datetime_str_before;     
    std::string ret_datetime_str_after;     

    time_now = std::time(&time_now);

    // Add one minute in seconds from current time
    time_now_add = time_now + (24 * 60 * 60);
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
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

    std::vector<std::string> datetimes = {
        months + "-" + days, // MM-DD
        years + "-" + months + "-" + days, // YYYY-MM-DD
    };

    for(int i = 0; i < datetimes.size(); i++){
        ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);
        
        ret_datetime_str_before = t->get_execution_datetime_fmt();
        t->update_execution_datetime();
        ret_datetime_str_after = t->get_execution_datetime_fmt();

        assert(ret_datetime_str_before.find(ret_datetime_str_after) != std::string::npos);

        delete t;
    }

    std::cout << ">> Task_update_execution_datetime_Once: 2 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
}