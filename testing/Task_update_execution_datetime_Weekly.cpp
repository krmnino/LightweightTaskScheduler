#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing Task::update_execution_datetime(), execution time should increase by 1 hour.
    // Frequency: Weekly
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
    std::string t_frequency = "Weekly";
    std::string t_datetime = hours + ":" + minutes + ":" + seconds;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    time_now = std::time(&time_now);

    // Add seven days in seconds to initial execution time
    // Add timezone offset
    time_now_add = time_now_add + (7 * 24 * 60 * 60) + (TIMEZONE * 60 * 60);
    
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

    std::cout << ">> Task_update_execution_datetime_Weekly: 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing Task::update_execution_datetime(), execution time should increase by 1 hour.
    // Frequency: Weekly
    // Datetime format: MM-DD HH:MM:SS

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
    
    months = (struct_time_now_add.tm_mon < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
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
    std::string t_frequency = "Weekly";
    std::string t_datetime = months + "-" + days + " " + hours + ":" + minutes + ":" + seconds;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    time_now = std::time(&time_now);

    // Add seven days in seconds to initial execution time
    // Add timezone offset
    time_now_add = time_now_add + (7 * 24 * 60 * 60) + (TIMEZONE * 60 * 60);
    
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

    std::cout << ">> Task_update_execution_datetime_Weekly: 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing Task::update_execution_datetime(), execution time should increase by 1 hour.
    // Frequency: Weekly
    // Datetime format: YYYY-MM-DD HH:MM:SS

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
    
    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
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
    std::string t_frequency = "Weekly";
    std::string t_datetime = years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    time_now = std::time(&time_now);

    // Add seven days in seconds to initial execution time
    // Add timezone offset
    time_now_add = time_now_add + (7 * 24 * 60 * 60) + (TIMEZONE * 60 * 60);
    
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

    std::cout << ">> Task_update_execution_datetime_Weekly: 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing Task::update_execution_datetime(), execution time should increase by 1 hour.
    // Frequency: Weekly
    // Datetime format: WDAY HH:MM:SS (full week day names)

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string wday_abbr;
    std::string wday;
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
    
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday = "Sunday";
        break;
    case MONDAY:
        wday = "Monday";
        break;
    case TUESDAY:
        wday = "Tuesday";
        break;
    case WEDNESDAY:
        wday = "Wednesday";
        break;
    case THURSDAY:
        wday = "Thursday";
        break;
    case FRIDAY:
        wday = "Friday";
        break;
    case SATURDAY:
        wday = "Saturday";
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
    std::string t_frequency = "Weekly";
    std::string t_datetime = wday + " " + hours + ":" + minutes + ":" + seconds;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    time_now = std::time(&time_now);

    // Add seven days in seconds to initial execution time
    // Add timezone offset
    time_now_add = time_now_add + (7 * 24 * 60 * 60) + (TIMEZONE * 60 * 60);
    
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

    std::cout << ">> Task_update_execution_datetime_Weekly: 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing Task::update_execution_datetime(), execution time should increase by 1 hour.
    // Frequency: Weekly
    // Datetime format: WDAY HH:MM:SS (abbreviated week day names)

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string wday_abbr;
    std::string wday;
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
    
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday = "Sun";
        break;
    case MONDAY:
        wday = "Mon";
        break;
    case TUESDAY:
        wday = "Tue";
        break;
    case WEDNESDAY:
        wday = "Wed";
        break;
    case THURSDAY:
        wday = "Thu";
        break;
    case FRIDAY:
        wday = "Fri";
        break;
    case SATURDAY:
        wday = "Sat";
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
    std::string t_frequency = "Weekly";
    std::string t_datetime = wday + " " + hours + ":" + minutes + ":" + seconds;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    time_now = std::time(&time_now);

    // Add seven days in seconds to initial execution time
    // Add timezone offset
    time_now_add = time_now_add + (7 * 24 * 60 * 60) + (TIMEZONE * 60 * 60);
    
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

    std::cout << ">> Task_update_execution_datetime_Weekly: 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing Task::update_execution_datetime(), execution time should increase by 1 hour.
    // Frequency: Weekly
    // Datetime format: MM-DD

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

    // Add 1 day in seconds to current time
    time_now_add = time_now + (24 * 60 * 60);
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;
    
    months = (struct_time_now_add.tm_mon < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Weekly";
    std::string t_datetime = months + "-" + days;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    time_now = std::time(&time_now);

    // Obtain current time value with init_today(). 
    // Add eight days in seconds to current time 
    //   -> 1 day for initial execution time and 7 days after update_execution_datetime()
    // Add timezone offset
    time_now_add = ts::init_today() + (8 * 24 * 60 * 60) + (TIMEZONE * 60 * 60);
    
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

    std::cout << ">> Task_update_execution_datetime_Weekly: 6 done" << std::endl;
    return 0;
}


int test7(){
    // TEST 7: testing Task::update_execution_datetime(), execution time should increase by 1 hour.
    // Frequency: Weekly
    // Datetime format: YYYY-MM-DD

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

    // Add 1 day in seconds to current time
    time_now_add = time_now + (24 * 60 * 60);
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;
    
    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Weekly";
    std::string t_datetime = years + "-" + months + "-" + days;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    time_now = std::time(&time_now);

    // Obtain current time value with init_today(). 
    // Add eight days in seconds to current time 
    //   -> 1 day for initial execution time and 7 days after update_execution_datetime()
    // Add timezone offset
    time_now_add = ts::init_today() + (8 * 24 * 60 * 60) + (TIMEZONE * 60 * 60);
    
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

    std::cout << ">> Task_update_execution_datetime_Weekly: 7 done" << std::endl;
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