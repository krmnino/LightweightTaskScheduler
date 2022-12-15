#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing validate_mmdd() function. Valid MM-DD string.

    ts::DatetimeValidate ret;
    std::vector<std::string> mmdd = {
        "01-01",
        "01-31",
        "02-01",
        "02-28",
        "03-01",
        "03-31",
        "04-01",
        "04-30",
        "05-01",
        "05-31",
        "06-01",
        "06-30",
        "07-01",
        "07-31",
        "08-01",
        "08-31",
        "09-01",
        "09-30",
        "10-01",
        "10-31",
        "11-01",
        "11-30",
        "12-01",
        "12-31"
    };

    for(int i = 0; i < mmdd.size(); i++){
        ret = ts::validate_mmdd(mmdd[i]);
        assert(ret == ts::DatetimeValidate::OK);
    }

    std::cout << ">> validate_mmdd: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_mmdd() function. Invalid MM-DD string.

    std::string mmdd;
    ts::DatetimeValidate ret;

    mmdd = "12-31-22";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::BAD_MMDD_LENGTH); 

    std::cout << ">> validate_mmdd: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_mmdd() function. Invalid MM-DD string.

    ts::DatetimeValidate ret;
    std::vector<std::string> mmdd = { "a2-31", "12-3a" };

    for(int i = 0; i < mmdd.size(); i++){
        ret = ts::validate_mmdd(mmdd[i]);
        assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);
    }

    std::cout << ">> validate_mmdd: Test 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing validate_mmdd() function. Invalid MM-DD string.

    std::string mmdd;
    ts::DatetimeValidate ret;

    mmdd = "12a30";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::MISSING_DASH); 

    std::cout << ">> validate_mmdd: Test 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing validate_mmdd() function. Invalid MM-DD string.

    std::string mmdd;
    ts::DatetimeValidate ret;

    mmdd = "25-30";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::MONTH_OUT_OF_RANGE); 

    std::cout << ">> validate_mmdd: Test 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing validate_mmdd() function. Invalid MM-DD string.

    std::string mmdd;
    ts::DatetimeValidate ret;

    mmdd = "00-30";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::MONTH_OUT_OF_RANGE); 

    std::cout << ">> validate_mmdd: Test 6 done" << std::endl;
    return 0;
}


int test7(){
    // TEST 7: testing validate_mmdd() function. Invalid MM-DD string.

    ts::DatetimeValidate ret;
    std::vector<std::string> mmdd = {
        "01-40",
        "02-40",
        "03-40",
        "04-40",
        "05-40",
        "06-40",
        "07-40",
        "08-40",
        "09-40",
        "10-40",
        "11-40",
        "12-40",
        "01-00",
        "02-00",
        "03-00",
        "04-00",
        "05-00",
        "06-00",
        "07-00",
        "08-00",
        "09-00",
        "10-00",
        "11-00",
        "12-00"
    };

    for(int i = 0; i < mmdd.size(); i++){
        ret = ts::validate_mmdd(mmdd[i]);
        assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);
    }

    std::cout << ">> validate_mmdd: Test 7 done" << std::endl;
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