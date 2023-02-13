#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing today_add_wday_hms() function -> PASS
    // Using full weekday substrings

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::tm struct_ret;
    std::string wday;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    time_t ret;
    std::string ret_str;    

    time_now = std::time(&time_now);

    // Add one minute in seconds to current time
    time_now_add = time_now + 60;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
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

    datetime_str = wday + " " + hours + ":" + minutes + ":" + seconds;

    ret = ts::today_add_wday_hms(datetime_str);

    to_struct = std::gmtime(&ret);
    struct_ret = *to_struct;

    switch (struct_ret.tm_wday)
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
    hours = (struct_ret.tm_hour < 10) ? 
             "0" + std::to_string(struct_ret.tm_hour) :
             std::to_string(struct_ret.tm_hour);
    minutes = (struct_ret.tm_min < 10) ? 
               "0" + std::to_string(struct_ret.tm_min) :
               std::to_string(struct_ret.tm_min);
    seconds = (struct_ret.tm_sec < 10) ? 
               "0" + std::to_string(struct_ret.tm_sec) :
               std::to_string(struct_ret.tm_sec);

    ret_str = wday + " " + hours + ":" + minutes + ":" + seconds;

    assert(ret_str == datetime_str);
    assert(ret >= time_now);
       
    std::cout << ">> today_add_wday_hms: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing today_add_wday_hms() function -> PASS
    // Using abbreviated weekday substrings

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::tm struct_ret;
    std::string wday;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    time_t ret;
    std::string ret_str;

    time_now = std::time(&time_now);

    // Add one minute in seconds to current time
    time_now_add = time_now + 60;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);
    
    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    switch (struct_ret.tm_wday)
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

    datetime_str = wday + " " + hours + ":" + minutes + ":" + seconds;
    
    ret = ts::today_add_wday_hms(datetime_str);

    to_struct = std::gmtime(&ret);
    struct_ret = *to_struct;

    switch (struct_ret.tm_wday)
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
    hours = (struct_ret.tm_hour < 10) ? 
             "0" + std::to_string(struct_ret.tm_hour) :
             std::to_string(struct_ret.tm_hour);
    minutes = (struct_ret.tm_min < 10) ? 
               "0" + std::to_string(struct_ret.tm_min) :
               std::to_string(struct_ret.tm_min);
    seconds = (struct_ret.tm_sec < 10) ? 
               "0" + std::to_string(struct_ret.tm_sec) :
               std::to_string(struct_ret.tm_sec);

    ret_str = wday + " " + hours + ":" + minutes + ":" + seconds;

    assert(ret_str == datetime_str);
    assert(ret >= time_now);
       
    std::cout << ">> today_add_wday_hms: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing today_add_wday_hms() function -> PASS
    // Attempt setting input weekday to previous weekday (i.e. Sun -> Sat)

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::tm struct_ret;
    std::string years;
    std::string months;
    std::string days;
    std::string wday;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    time_t ret;
    std::string ret_str;

    time_now = std::time(&time_now);

    // Subtract one day in seconds from current time
    time_now_add = time_now - (24 * 60 * 60);
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
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

    datetime_str = wday + " " + hours + ":" + minutes + ":" + seconds;              
       
    ret = ts::today_add_wday_hms(datetime_str);

    to_struct = std::gmtime(&ret);
    struct_ret = *to_struct;

    years = std::to_string(1900 + struct_ret.tm_year);
    months = (struct_ret.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_ret.tm_mon + 1) :
              std::to_string(struct_ret.tm_mon + 1);  
    days = (struct_ret.tm_mday < 10) ? 
            "0" + std::to_string(struct_ret.tm_mday) :
            std::to_string(struct_ret.tm_mday);
    switch (struct_ret.tm_wday)
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
    hours = (struct_ret.tm_hour < 10) ? 
             "0" + std::to_string(struct_ret.tm_hour) :
             std::to_string(struct_ret.tm_hour);
    minutes = (struct_ret.tm_min < 10) ? 
               "0" + std::to_string(struct_ret.tm_min) :
               std::to_string(struct_ret.tm_min);
    seconds = (struct_ret.tm_sec < 10) ? 
               "0" + std::to_string(struct_ret.tm_sec) :
               std::to_string(struct_ret.tm_sec);

    ret_str = years + "-" + months + "-" + days + " " + wday + " " + hours + ":" + minutes + ":" + seconds;

    // Add one minute in seconds to current time
    time_now_add = time_now + (6 * 24 * 60 * 60);

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

    datetime_str = years + "-" + months + "-" + days + " " + wday + " " + hours + ":" + minutes + ":" + seconds;

    assert(ret_str == datetime_str);
    assert(ret >= time_now);
       
    std::cout << ">> today_add_wday_hms: Test 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing today_add_wday_hms() function -> FAIL
    // Invalid hours-minutes-seconds substring

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string wday;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    time_t ret;

    time_now = std::time(&time_now);
  
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now);
    
    // std::tm* to std::tm
    std::tm struct_time_now = *to_struct;

    switch (struct_time_now.tm_wday)
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

    ret = ts::today_add_wday_hms(wday + "120000");

    assert(ret == 0);
       
    std::cout << ">> today_add_wday_hms: Test 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing today_add_wday_hms() function -> PASS
    // Invalid weekday substring

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::tm struct_ret;
    std::string wday;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    time_t ret;
    std::string ret_str;    

    time_now = std::time(&time_now);

    // Add one minute in seconds to current time
    time_now_add = time_now + 60;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
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

    datetime_str = "anything " + hours + ":" + minutes + ":" + seconds;

    ret = ts::today_add_wday_hms(datetime_str);

    assert(ret == 0);
       
    std::cout << ">> today_add_wday_hms: Test 5 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
}