#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing Task::update_execution_datetime(), execution time should 
    // increase to the calendar day of the next month.
    // Frequency: Monthly
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
    std::string t_frequency = "Monthly";
    std::string t_datetime = hours + ":" + minutes + ":" + seconds;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    // Add necessary number of days until the day of the next month
    switch((struct_time_now_add.tm_mon) % 12)
    {
    case JANUARY:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (JANUARY_DAYS * 24 * 60 * 60);
        break;
    case FEBRUARY:
        // Check if we are currently on a leap year
        if(struct_time_now_add.tm_mday > FEBRUARY_DAYS & 1900 + struct_time_now_add.tm_year % 4 == 0){
            // Add 29 days in seconds to current time
            time_now_add = time_now + ((FEBRUARY_DAYS + 1) * 24 * 60 * 60);
        }
        else{
            // Add 28 days in seconds to current time
            time_now_add = time_now + (FEBRUARY_DAYS * 24 * 60 * 60);
        }
        break;
    case MARCH:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (MARCH_DAYS * 24 * 60 * 60);
        break;
    case APRIL:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (APRIL_DAYS * 24 * 60 * 60);
        break;
    case MAY:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (MAY_DAYS * 24 * 60 * 60);
        break;
    case JUNE:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (JUNE_DAYS * 24 * 60 * 60);
        break;
    case JULY:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (JULY_DAYS * 24 * 60 * 60);
        break;
    case AUGUST:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (AUGUST_DAYS * 24 * 60 * 60);
        break;
    case SEPTEMBER:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (SEPTEMBER_DAYS * 24 * 60 * 60);
        break;
    case OCTOBER:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (OCTOBER_DAYS * 24 * 60 * 60);
        break;
    case NOVEMBER:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (NOVEMBER_DAYS * 24 * 60 * 60);
        break;
    case DECEMBER:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (DECEMBER_DAYS * 24 * 60 * 60);
        break;
    default:
        time_now_add = 0;
        break;
    }

    // Add timezone offset and 5 seconds from initial execution datetime
    time_now_add = time_now_add + (TIMEZONE * 60 * 60) + 5;
    
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

    std::cout << ">> Task_update_execution_datetime_Monthly: 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing Task::update_execution_datetime(), execution time should 
    // increase to the calendar day of the next month.
    // Frequency: Monthly
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
    std::string t_frequency = "Monthly";
    std::string t_datetime = months + "-" + days + " " + hours + ":" + minutes + ":" + seconds;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    // Add necessary number of days until the day of the next month
    switch((struct_time_now_add.tm_mon) % 12)
    {
    case JANUARY:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (JANUARY_DAYS * 24 * 60 * 60);
        break;
    case FEBRUARY:
        // Check if we are currently on a leap year
        if(struct_time_now_add.tm_mday > FEBRUARY_DAYS & 1900 + struct_time_now_add.tm_year % 4 == 0){
            // Add 29 days in seconds to current time
            time_now_add = time_now + ((FEBRUARY_DAYS + 1) * 24 * 60 * 60);
        }
        else{
            // Add 28 days in seconds to current time
            time_now_add = time_now + (FEBRUARY_DAYS * 24 * 60 * 60);
        }
        break;
    case MARCH:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (MARCH_DAYS * 24 * 60 * 60);
        break;
    case APRIL:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (APRIL_DAYS * 24 * 60 * 60);
        break;
    case MAY:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (MAY_DAYS * 24 * 60 * 60);
        break;
    case JUNE:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (JUNE_DAYS * 24 * 60 * 60);
        break;
    case JULY:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (JULY_DAYS * 24 * 60 * 60);
        break;
    case AUGUST:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (AUGUST_DAYS * 24 * 60 * 60);
        break;
    case SEPTEMBER:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (SEPTEMBER_DAYS * 24 * 60 * 60);
        break;
    case OCTOBER:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (OCTOBER_DAYS * 24 * 60 * 60);
        break;
    case NOVEMBER:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (NOVEMBER_DAYS * 24 * 60 * 60);
        break;
    case DECEMBER:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (DECEMBER_DAYS * 24 * 60 * 60);
        break;
    default:
        time_now_add = 0;
        break;
    }

    // Add timezone offset and 5 seconds from initial execution datetime
    time_now_add = time_now_add + (TIMEZONE * 60 * 60) + 5;
    
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

    std::cout << ">> Task_update_execution_datetime_Monthly: 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing Task::update_execution_datetime(), execution time should 
    // increase to the calendar day of the next month.
    // Frequency: Monthly
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
    std::string t_frequency = "Monthly";
    std::string t_datetime = months + "-" + days + " " + hours + ":" + minutes + ":" + seconds;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    // Add necessary number of days until the day of the next month
    switch((struct_time_now_add.tm_mon) % 12)
    {
    case JANUARY:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (JANUARY_DAYS * 24 * 60 * 60);
        break;
    case FEBRUARY:
        // Check if we are currently on a leap year
        if(struct_time_now_add.tm_mday > FEBRUARY_DAYS & 1900 + struct_time_now_add.tm_year % 4 == 0){
            // Add 29 days in seconds to current time
            time_now_add = time_now + ((FEBRUARY_DAYS + 1) * 24 * 60 * 60);
        }
        else{
            // Add 28 days in seconds to current time
            time_now_add = time_now + (FEBRUARY_DAYS * 24 * 60 * 60);
        }
        break;
    case MARCH:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (MARCH_DAYS * 24 * 60 * 60);
        break;
    case APRIL:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (APRIL_DAYS * 24 * 60 * 60);
        break;
    case MAY:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (MAY_DAYS * 24 * 60 * 60);
        break;
    case JUNE:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (JUNE_DAYS * 24 * 60 * 60);
        break;
    case JULY:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (JULY_DAYS * 24 * 60 * 60);
        break;
    case AUGUST:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (AUGUST_DAYS * 24 * 60 * 60);
        break;
    case SEPTEMBER:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (SEPTEMBER_DAYS * 24 * 60 * 60);
        break;
    case OCTOBER:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (OCTOBER_DAYS * 24 * 60 * 60);
        break;
    case NOVEMBER:
        // Add 30 days in seconds to current time
        time_now_add = time_now + (NOVEMBER_DAYS * 24 * 60 * 60);
        break;
    case DECEMBER:
        // Add 31 days in seconds to current time
        time_now_add = time_now + (DECEMBER_DAYS * 24 * 60 * 60);
        break;
    default:
        time_now_add = 0;
        break;
    }

    // Add timezone offset and 5 seconds from initial execution datetime
    time_now_add = time_now_add + (TIMEZONE * 60 * 60) + 5;
    
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

    std::cout << ">> Task_update_execution_datetime_Monthly: 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing Task::update_execution_datetime(), execution time should 
    // increase to the calendar day of the next month.
    // Frequency: Monthly
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
    std::string t_frequency = "Monthly";
    std::string t_datetime = months + "-" + days;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    time_now_add = ts::init_today();
    // Add necessary number of days until the day of the next month
    switch((struct_time_now_add.tm_mon) % 12)
    {
    case JANUARY:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (JANUARY_DAYS * 24 * 60 * 60);
        break;
    case FEBRUARY:
        // Check if we are currently on a leap year
        if(struct_time_now_add.tm_mday > FEBRUARY_DAYS & 1900 + struct_time_now_add.tm_year % 4 == 0){
            // Add 29 days in seconds to current time
            time_now_add = time_now_add + ((FEBRUARY_DAYS + 1) * 24 * 60 * 60);
        }
        else{
            // Add 28 days in seconds to current time
            time_now_add = time_now_add + (FEBRUARY_DAYS * 24 * 60 * 60);
        }
        break;
    case MARCH:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (MARCH_DAYS * 24 * 60 * 60);
        break;
    case APRIL:
        // Add 30 days in seconds to current time
        time_now_add = time_now_add + (APRIL_DAYS * 24 * 60 * 60);
        break;
    case MAY:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (MAY_DAYS * 24 * 60 * 60);
        break;
    case JUNE:
        // Add 30 days in seconds to current time
        time_now_add = time_now_add + (JUNE_DAYS * 24 * 60 * 60);
        break;
    case JULY:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (JULY_DAYS * 24 * 60 * 60);
        break;
    case AUGUST:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (AUGUST_DAYS * 24 * 60 * 60);
        break;
    case SEPTEMBER:
        // Add 30 days in seconds to current time
        time_now_add = time_now_add + (SEPTEMBER_DAYS * 24 * 60 * 60);
        break;
    case OCTOBER:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (OCTOBER_DAYS * 24 * 60 * 60);
        break;
    case NOVEMBER:
        // Add 30 days in seconds to current time
        time_now_add = time_now_add + (NOVEMBER_DAYS * 24 * 60 * 60);
        break;
    case DECEMBER:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (DECEMBER_DAYS * 24 * 60 * 60);
        break;
    default:
        time_now_add = 0;
        break;
    }

    // Add timezone offset and 1 day in seconds from initial execution datetime
    time_now_add = time_now_add + (TIMEZONE * 60 * 60) + (24 * 60 * 60);
    
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

    std::cout << ">> Task_update_execution_datetime_Monthly: 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing Task::update_execution_datetime(), execution time should 
    // increase to the calendar day of the next month.
    // Frequency: Monthly
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
    std::string t_frequency = "Monthly";
    std::string t_datetime = months + "-" + days;

    // Task's execution datetime is set to be one hour in the future from current time
    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);

    t->update_execution_datetime();
    ret_datetime_str = t->get_execution_datetime_fmt();

    time_now_add = ts::init_today();
    // Add necessary number of days until the day of the next month
    switch((struct_time_now_add.tm_mon) % 12)
    {
    case JANUARY:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (JANUARY_DAYS * 24 * 60 * 60);
        break;
    case FEBRUARY:
        // Check if we are currently on a leap year
        if(struct_time_now_add.tm_mday > FEBRUARY_DAYS & 1900 + struct_time_now_add.tm_year % 4 == 0){
            // Add 29 days in seconds to current time
            time_now_add = time_now_add + ((FEBRUARY_DAYS + 1) * 24 * 60 * 60);
        }
        else{
            // Add 28 days in seconds to current time
            time_now_add = time_now_add + (FEBRUARY_DAYS * 24 * 60 * 60);
        }
        break;
    case MARCH:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (MARCH_DAYS * 24 * 60 * 60);
        break;
    case APRIL:
        // Add 30 days in seconds to current time
        time_now_add = time_now_add + (APRIL_DAYS * 24 * 60 * 60);
        break;
    case MAY:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (MAY_DAYS * 24 * 60 * 60);
        break;
    case JUNE:
        // Add 30 days in seconds to current time
        time_now_add = time_now_add + (JUNE_DAYS * 24 * 60 * 60);
        break;
    case JULY:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (JULY_DAYS * 24 * 60 * 60);
        break;
    case AUGUST:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (AUGUST_DAYS * 24 * 60 * 60);
        break;
    case SEPTEMBER:
        // Add 30 days in seconds to current time
        time_now_add = time_now_add + (SEPTEMBER_DAYS * 24 * 60 * 60);
        break;
    case OCTOBER:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (OCTOBER_DAYS * 24 * 60 * 60);
        break;
    case NOVEMBER:
        // Add 30 days in seconds to current time
        time_now_add = time_now_add + (NOVEMBER_DAYS * 24 * 60 * 60);
        break;
    case DECEMBER:
        // Add 31 days in seconds to current time
        time_now_add = time_now_add + (DECEMBER_DAYS * 24 * 60 * 60);
        break;
    default:
        time_now_add = 0;
        break;
    }

    // Add timezone offset and 1 day in seconds from initial execution datetime
    time_now_add = time_now_add + (TIMEZONE * 60 * 60) + (24 * 60 * 60);
    
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

    std::cout << ">> Task_update_execution_datetime_Monthly: 5 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
    //test6();
    //test7();
}