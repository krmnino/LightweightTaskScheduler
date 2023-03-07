#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing validate_wday_hms() function. Valid WDAY HH:MM:SS string.

    ts::ValidationCode ret;
    std::vector<std::string> wday_hms = {
        "Monday 01:00:00",
        "Tuesday 01:00:00",
        "Wednesday 01:00:00",
        "Thursday 01:00:00",
        "Friday 01:00:00",
        "Saturday 01:00:00",
        "Sunday 01:00:00"
    };

    for(size_t i = 0; i < wday_hms.size(); i++){
        ret = ts::validate_wday_hms(wday_hms[i]);
        assert(ret == ts::ValidationCode::OK);
    }

    std::cout << ">> validate_wday_hms: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_wday_hms() function. Valid WDAY HH:MM:SS string.

    ts::ValidationCode ret;
    std::vector<std::string> wday_hms = {
        "Mon 01:00:00",
        "Tue 01:00:00",
        "Wed 01:00:00",
        "Thu 01:00:00",
        "Fri 01:00:00",
        "Sat 01:00:00",
        "Sun 01:00:00"
    };

    for(size_t i = 0; i < wday_hms.size(); i++){
        ret = ts::validate_wday_hms(wday_hms[i]);
        assert(ret == ts::ValidationCode::OK);
    }

    std::cout << ">> validate_wday_hms: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_wday_hms() function. Invalid WDAY HH:MM:SS string.

    std::string wday_hms;
    ts::ValidationCode ret;

    wday_hms = "Monday01:00:00";
    ret = ts::validate_wday_hms(wday_hms);
    assert(ret == ts::ValidationCode::MISSING_DATETIME_SPACE);

    std::cout << ">> validate_wday_hms: Test 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing validate_wday_hms() function. Invalid WDAY HH:MM:SS string.

    std::string wday_hms;
    ts::ValidationCode ret;

    wday_hms = "Anything 01:00:00";
    ret = ts::validate_wday_hms(wday_hms);
    assert(ret == ts::ValidationCode::BAD_WDAY);  

    std::cout << ">> validate_wday_hms: Test 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing validate_wday_hms() function. Invalid HH:MM:SS string.

    std::string wday_hms;
    ts::ValidationCode ret;

    wday_hms = "Friday 35:00:00";
    ret = ts::validate_wday_hms(wday_hms);
    assert(ret == ts::ValidationCode::HOURS_OUT_OF_RANGE);

    std::cout << ">> validate_wday_hms: Test 5 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
}