#include <assert.h>
#include <iostream>
#include <vector>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: testing validate_wday() function. Full day names.

    ts::ValidationCode ret;
    std::vector<std::string> days = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };

    for(size_t i = 0; i < days.size(); i++){
        ret = ts::validate_wday(days[i]);
        assert(ret == ts::ValidationCode::OK);
    }

    std::cout << ">> validate_wday: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_wday() function. Abbreviated day names.

    ts::ValidationCode ret;
    std::vector<std::string> days = {
        "Mon",
        "Tue",
        "Wed",
        "Thu",
        "Fri",
        "Sat",
        "Sun"
    };

    for(size_t i = 0; i < days.size(); i++){
        ret = ts::validate_wday(days[i]);
        assert(ret == ts::ValidationCode::OK);
    }

    std::cout << ">> validate_wday: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_wday() function. Invalid weekday string.

    ts::ValidationCode ret;
    std::string day = "anything";

    ret = ts::validate_wday(day);
    assert(ret == ts::ValidationCode::BAD_WDAY);

    std::cout << ">> validate_wday: Test 3 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
    test3();
}