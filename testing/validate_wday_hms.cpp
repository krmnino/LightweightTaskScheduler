#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing validate_wday_hms() function. Valid HH:MM:SS string.

    std::string wday_hms;
    ts::DatetimeValidate ret;

    wday_hms = "Monday 01:00:00";
    ret = ts::validate_wday_hms(wday_hms);
    assert(ret == ts::DatetimeValidate::OK);

    std::cout << ">> validate_wday_hms: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_wday_hms() function. Invalid HH:MM:SS string.

    std::string wday_hms;
    ts::DatetimeValidate ret;

    wday_hms = "Monday01:00:00";
    ret = ts::validate_wday_hms(wday_hms);
    assert(ret == ts::DatetimeValidate::MISSING_SPACE);

    std::cout << ">> validate_wday_hms: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_wday_hms() function. Invalid HH:MM:SS string.

    std::string wday_hms;
    ts::DatetimeValidate ret;

    wday_hms = "Anything 01:00:00";
    ret = ts::validate_wday_hms(wday_hms);
    assert(ret == ts::DatetimeValidate::BAD_WDAY);  

    std::cout << ">> validate_wday_hms: Test 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing validate_wday_hms() function. Invalid HH:MM:SS string.

    std::string wday_hms;
    ts::DatetimeValidate ret;

    wday_hms = "Friday 35:00:00";
    ret = ts::validate_wday_hms(wday_hms);
    assert(ret == ts::DatetimeValidate::HOURS_OUT_OF_RANGE);

    std::cout << ">> validate_wday_hms: Test 4 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
    test3();
    test4();
}