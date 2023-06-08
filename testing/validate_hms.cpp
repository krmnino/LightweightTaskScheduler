#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: testing validate_hms() function. Valid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "12:00:00";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::OK);

    std::cout << ">> validate_hms: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "12:00";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::BAD_HMS_LENGTH);

    std::cout << ">> validate_hms: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "1a:00:00";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::BAD_NUMBER_CHARACTER);

    std::cout << ">> validate_hms: Test 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "12:a0:00";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::BAD_NUMBER_CHARACTER);

    std::cout << ">> validate_hms: Test 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "12:00:a0";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::BAD_NUMBER_CHARACTER);

    std::cout << ">> validate_hms: Test 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "30:00:00";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::HOURS_OUT_OF_RANGE);

    std::cout << ">> validate_hms: Test 6 done" << std::endl;
    return 0;
}


int test7(){
    // TEST 7: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "12:90:00";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::MINUTES_OUT_OF_RANGE);    

    std::cout << ">> validate_hms: Test 7 done" << std::endl;
    return 0;
}


int test8(){
    // TEST 8: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "12:00:88";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::SECONDS_OUT_OF_RANGE); 

    std::cout << ">> validate_hms: Test 8 done" << std::endl;
    return 0;
}


int test9(){
    // TEST 9: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "12A00:00";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::MISSING_DATETIME_COLON); 

    std::cout << ">> validate_hms: Test 9 done" << std::endl;
    return 0;
}


int test10(){
    // TEST 10: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "12:00A00";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::MISSING_DATETIME_COLON);

    std::cout << ">> validate_hms: Test 10 done" << std::endl;
    return 0;
}


int test11(){
    // TEST 11: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "12:";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::BAD_HMS_LENGTH);

    std::cout << ">> validate_hms: Test 11 done" << std::endl;
    return 0;
}


int test12(){
    // TEST 12: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "ANYTHING HERE";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::BAD_HMS_LENGTH);

    std::cout << ">> validate_hms: Test 12 done" << std::endl;
    return 0;
}


int test13(){
    // TEST 13: testing validate_hms() function. Invalid HH:MM:SS string.

    std::string hms;
    lts::ValidationCode ret;

    hms = "ANYTHING";
    ret = lts::validate_hms(hms);
    assert(ret == lts::ValidationCode::BAD_NUMBER_CHARACTER);

    std::cout << ">> validate_hms: Test 13 done" << std::endl;
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
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
}