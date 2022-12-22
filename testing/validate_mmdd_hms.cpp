#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing validate_mmdd_hms() function. Valid MM-DD HH:MM:SS string.

    std::string mmdd_hms;
    ts::DatetimeValidate ret;

    mmdd_hms = "10-25 01:00:00";
    ret = ts::validate_mmdd_hms(mmdd_hms);
    assert(ret == ts::DatetimeValidate::OK);

    std::cout << ">> validate_mmdd_hms: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_mmdd_hms() function. Invalid MM-DD HH:MM:SS string.

    std::string mmdd_hms;
    ts::DatetimeValidate ret;

    mmdd_hms = "Monday01:00:00";
    ret = ts::validate_mmdd_hms(mmdd_hms);
    assert(ret == ts::DatetimeValidate::MISSING_SPACE);

    std::cout << ">> validate_mmdd_hms: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_mmdd_hms() function. Invalid MM-DD HH:MM:SS string.

    std::string mmdd_hms;
    ts::DatetimeValidate ret;

    mmdd_hms = "56-25 01:00:00";
    ret = ts::validate_mmdd_hms(mmdd_hms);
    assert(ret == ts::DatetimeValidate::MONTH_OUT_OF_RANGE);

    std::cout << ">> validate_mmdd_hms: Test 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing validate_mmdd_hms() function. Invalid MM-DD HH:MM:SS string.

    std::string mmdd_hms;
    ts::DatetimeValidate ret;

    mmdd_hms = "01-50 01:00:00";
    ret = ts::validate_mmdd_hms(mmdd_hms);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);

    std::cout << ">> validate_mmdd_hms: Test 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing validate_mmdd_hms() function. Invalid MM-DD HH:MM:SS string.

    std::string mmdd_hms;
    ts::DatetimeValidate ret;

    mmdd_hms = "10-25 35:00:00";
    ret = ts::validate_mmdd_hms(mmdd_hms);
    assert(ret == ts::DatetimeValidate::HOURS_OUT_OF_RANGE);

    std::cout << ">> validate_mmdd_hms: Test 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing validate_mmdd_hms() function. Invalid MM-DD HH:MM:SS string.

    std::string mmdd_hms;
    ts::DatetimeValidate ret;

    mmdd_hms = "10-25 12:99:00";
    ret = ts::validate_mmdd_hms(mmdd_hms);
    assert(ret == ts::DatetimeValidate::MINUTES_OUT_OF_RANGE);

    std::cout << ">> validate_mmdd_hms: Test 6 done" << std::endl;
    return 0;
}


int test7(){
    // TEST 7: testing validate_mmdd_hms() function. Invalid MM-DD HH:MM:SS string.

    std::string mmdd_hms;
    ts::DatetimeValidate ret;

    mmdd_hms = "10-25 12:00:99";
    ret = ts::validate_mmdd_hms(mmdd_hms);
    assert(ret == ts::DatetimeValidate::SECONDS_OUT_OF_RANGE);

    std::cout << ">> validate_mmdd_hms: Test 7 done" << std::endl;
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