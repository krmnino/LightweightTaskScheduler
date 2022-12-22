#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing today_add_dhms() function -> PASS
    // Add one minute in seconds to current time and 0 days

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::tm struct_ret;
    std::string years;
    std::string months;
    std::string days;
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

    datetime_str = hours + ":" + minutes + ":" + seconds;

    ret = ts::today_add_dhms(0, datetime_str);

    to_struct = std::gmtime(&ret);
    struct_ret = *to_struct;

    years = std::to_string(1900 + struct_ret.tm_year);
    months = (struct_ret.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_ret.tm_mon + 1) :
              std::to_string(struct_ret.tm_mon + 1);  
    days = (struct_ret.tm_mday < 10) ? 
            "0" + std::to_string(struct_ret.tm_mday) :
            std::to_string(struct_ret.tm_mday);
    hours = (struct_ret.tm_hour < 10) ? 
             "0" + std::to_string(struct_ret.tm_hour) :
             std::to_string(struct_ret.tm_hour);
    minutes = (struct_ret.tm_min < 10) ? 
               "0" + std::to_string(struct_ret.tm_min) :
               std::to_string(struct_ret.tm_min);
    seconds = (struct_ret.tm_sec < 10) ? 
               "0" + std::to_string(struct_ret.tm_sec) :
               std::to_string(struct_ret.tm_sec);

    ret_str = years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds;

    // Add one minute in seconds to current time
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
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    datetime_str = years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds;

    assert(ret_str == datetime_str);
    assert(ret >= time_now);
       
    std::cout << ">> today_add_dhms: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing today_add_dhms() function -> PASS
    // Add one minute in seconds to current time and 2 days

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::tm struct_ret;
    std::string years;
    std::string months;
    std::string days;
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

    datetime_str = hours + ":" + minutes + ":" + seconds;

    ret = ts::today_add_dhms(2, datetime_str);

    to_struct = std::gmtime(&ret);
    struct_ret = *to_struct;

    years = std::to_string(1900 + struct_ret.tm_year);
    months = (struct_ret.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_ret.tm_mon + 1) :
              std::to_string(struct_ret.tm_mon + 1);  
    days = (struct_ret.tm_mday < 10) ? 
            "0" + std::to_string(struct_ret.tm_mday) :
            std::to_string(struct_ret.tm_mday);
    hours = (struct_ret.tm_hour < 10) ? 
             "0" + std::to_string(struct_ret.tm_hour) :
             std::to_string(struct_ret.tm_hour);
    minutes = (struct_ret.tm_min < 10) ? 
               "0" + std::to_string(struct_ret.tm_min) :
               std::to_string(struct_ret.tm_min);
    seconds = (struct_ret.tm_sec < 10) ? 
               "0" + std::to_string(struct_ret.tm_sec) :
               std::to_string(struct_ret.tm_sec);

    ret_str = years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds;

    // Add 2 days and one minute in seconds to current time
    time_now_add = time_now + (2 * 24 * 60 * 60) + 60;

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
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    datetime_str = years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds;

    assert(ret_str == datetime_str);
    assert(ret >= time_now);
       
    std::cout << ">> today_add_dhms: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing today_add_dhms() function -> FAIL
    // Invalid time. Current time minus 1 minute

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    time_t ret;

    time_now = std::time(&time_now);

    // Subtract one minute in seconds from current time
    time_now_add = time_now - 60;

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

    datetime_str = hours + ":" + minutes + ":" + seconds;

    ret = ts::today_add_dhms(0, datetime_str);

    assert(ret == 0);
       
    std::cout << ">> today_add_dhms: Test 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing today_add_dhms() function -> FAIL
    // Invalid value for day parameter

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    time_t ret;    

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

    datetime_str = hours + ":" + minutes + ":" + seconds;
    
    ret = ts::today_add_dhms(-15, datetime_str);

    assert(ret == 0);
       
    std::cout << ">> today_add_dhms: Test 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 4: testing today_add_dhms() function -> FAIL
    // Invalid hours-minutes-seconds subtring

    time_t ret;
    ret = ts::today_add_dhms(1, "120000");

    assert(ret == 0);
       
    std::cout << ">> today_add_dhms: Test 5 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
}