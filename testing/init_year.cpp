#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: testing init_year() function

    time_t ret;
    time_t time_now;

    ret = lts::init_year();
    time_now = std::time(&time_now);
  
    std::tm* to_struct;

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    to_struct = std::gmtime(&time_now);
    std::tm struct_time_now = *to_struct;
    
    assert(struct_ret.tm_sec == 0);
    assert(struct_ret.tm_min == 0);
    assert(struct_ret.tm_hour == 0);
    assert(struct_ret.tm_yday == 0);
    assert(struct_ret.tm_mday == 1);
    assert(struct_ret.tm_mon == 0);
    assert(struct_ret.tm_year == struct_time_now.tm_year);
    
    std::cout << ">> init_year: Test 1 done" << std::endl;
    return 0;
}


int main(){
    test1();
}