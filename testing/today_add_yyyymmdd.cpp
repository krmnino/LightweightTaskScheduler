#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: testing today_add_yyyymmdd() function -> PASS
    // Current time + 1 day

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::tm struct_ret;
    std::string years;
    std::string months;
    std::string days;
    std::string datetime_str;
    time_t ret;
    std::string ret_str;    

    time_now = std::time(&time_now);

    // Add one day in seconds to current time
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
        
    datetime_str = years + "-" + months + "-" + days;
    
    ret = lts::today_add_yyyymmdd(datetime_str);

    to_struct = std::gmtime(&ret);
    struct_ret = *to_struct;

    years = std::to_string(1900 + struct_ret.tm_year);
    months = (struct_ret.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_ret.tm_mon + 1) :
              std::to_string(struct_ret.tm_mon + 1);  
    days = (struct_ret.tm_mday < 10) ? 
            "0" + std::to_string(struct_ret.tm_mday) :
            std::to_string(struct_ret.tm_mday);   

    ret_str = years + "-" + months + "-" + days;

    assert(ret_str == datetime_str);
    assert(ret >= time_now);
       
    std::cout << ">> today_add_yyyymmdd: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing today_add_yyyymmdd() function -> PASS
    // Current time + 30 days

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::tm struct_ret;
    std::string years;
    std::string months;
    std::string days;
    std::string datetime_str;
    time_t ret;
    std::string ret_str;  

    time_now = std::time(&time_now);

    // Add 30 days in seconds to current time
    time_now_add = time_now + (30 * 24 * 60 * 60);
    
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
        
    datetime_str = years + "-" + months + "-" + days;

    ret = lts::today_add_yyyymmdd(datetime_str);

    to_struct = std::gmtime(&ret);
    struct_ret = *to_struct;

    years = std::to_string(1900 + struct_ret.tm_year);
    months = (struct_ret.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_ret.tm_mon + 1) :
              std::to_string(struct_ret.tm_mon + 1);  
    days = (struct_ret.tm_mday < 10) ? 
            "0" + std::to_string(struct_ret.tm_mday) :
            std::to_string(struct_ret.tm_mday);

    ret_str = years + "-" + months + "-" + days;             

    assert(ret_str == datetime_str);
    assert(ret >= time_now);
       
    std::cout << ">> today_add_yyyymmdd: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing today_add_yyyymmdd() function -> PASS
    // Current time + 365 days

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::tm struct_ret;
    std::string years;
    std::string months;
    std::string days;
    std::string datetime_str;
    time_t ret;
    std::string ret_str;  

    time_now = std::time(&time_now);

    // Add 30 days in seconds to current time
    time_now_add = time_now + (365 * 24 * 60 * 60);
    
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
        
    datetime_str = years + "-" + months + "-" + days;

    ret = lts::today_add_yyyymmdd(datetime_str);

    to_struct = std::gmtime(&ret);
    struct_ret = *to_struct;

    years = std::to_string(1900 + struct_ret.tm_year);
    months = (struct_ret.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_ret.tm_mon + 1) :
              std::to_string(struct_ret.tm_mon + 1);  
    days = (struct_ret.tm_mday < 10) ? 
            "0" + std::to_string(struct_ret.tm_mday) :
            std::to_string(struct_ret.tm_mday);

    ret_str = years + "-" + months + "-" + days;

    assert(ret_str == datetime_str);
    assert(ret >= time_now);
       
    std::cout << ">> today_add_yyyymmdd: Test 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing today_add_yyyymmdd() function -> FAIL
    // Current time - 1 day

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string datetime_str;
    time_t ret;

    time_now = std::time(&time_now);

    // Subtract one day in seconds from current time
    time_now_add = time_now - (24 * 60 * 60);
    
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
        
    ret = lts::today_add_yyyymmdd(years + "-" + months + "-" + days);

    assert(ret == 0);
       
    std::cout << ">> today_add_yyyymmdd: Test 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing today_add_yyyymmdd() function -> FAIL
    // Invalid years-months-days subtring

    time_t ret;
    ret = lts::today_add_yyyymmdd("20220212");

    assert(ret == 0);
       
    std::cout << ">> today_add_yyyymmdd: Test 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing today_add_yyyymmdd() function -> FAIL
    // Invalid years-months-days subtring

    time_t ret;
    ret = lts::today_add_yyyymmdd("2022-60-20");

    assert(ret == 0);
       
    std::cout << ">> today_add_yyyymmdd: Test 6 done" << std::endl;
    return 0;
}


int test7(){
    // TEST 7: testing today_add_yyyymmdd() function -> FAIL
    // Invalid years-months-days subtring

    time_t ret;
    ret = lts::today_add_yyyymmdd("2022-02-60");

    assert(ret == 0);
       
    std::cout << ">> today_add_yyyymmdd: Test 7 done" << std::endl;
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