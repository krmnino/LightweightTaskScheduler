#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing validate_yyyymmdd() function. Valid YYYY-MM-DD string.

    ts::DatetimeValidate ret;
    std::vector<std::string> yyyymmdd = {
        "2022-01-01",
        "2022-01-31",
        "2022-02-01",
        "2022-02-28",
        "2024-02-29",
        "2022-03-01",
        "2022-03-31",
        "2022-04-01",
        "2022-04-30",
        "2022-05-01",
        "2022-05-31",
        "2022-06-01",
        "2022-06-30",
        "2022-07-01",
        "2022-07-31",
        "2022-08-01",
        "2022-08-31",
        "2022-09-01",
        "2022-09-30",
        "2022-10-01",
        "2022-10-31",
        "2022-11-01",
        "2022-11-30",
        "2022-12-01",
        "2022-12-31"
    };

    for(int i = 0; i < yyyymmdd.size(); i++){
        ret = ts::validate_yyyymmdd(yyyymmdd[i]);
        assert(ret == ts::DatetimeValidate::OK);
    }

    std::cout << ">> validate_yyyymmdd: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_yyyymmdd() function. Invalid YYYY-MM-DD string.

    std::string yyyymmdd;
    ts::DatetimeValidate ret;

    yyyymmdd = "2022-31-2222";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::BAD_YYYYMMDD_LENGTH);

    std::cout << ">> validate_yyyymmdd: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_yyyymmdd() function. Invalid YYYY-MM-DD string.

    ts::DatetimeValidate ret;
    std::vector<std::string> yyyymmdd = {
        "2a22-12-31",
        "2022-1a-31",
        "2022-12-3a"
    };

    for(int i = 0; i < yyyymmdd.size(); i++){
        ret = ts::validate_yyyymmdd(yyyymmdd[i]);
        assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);
    }

    std::cout << ">> validate_yyyymmdd: Test 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing validate_yyyymmdd() function. Invalid YYYY-MM-DD string.

    ts::DatetimeValidate ret;
    std::vector<std::string> yyyymmdd = {
        "2022a12a30",
        "2022-12a30",
        "2022a12-30"
    };

    for(int i = 0; i < yyyymmdd.size(); i++){
        ret = ts::validate_yyyymmdd(yyyymmdd[i]);
        assert(ret == ts::DatetimeValidate::MISSING_DASH);
    }

    std::cout << ">> validate_yyyymmdd: Test 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing validate_yyyymmdd() function. Invalid YYYY-MM-DD string.

    std::string yyyymmdd;
    ts::DatetimeValidate ret;

    yyyymmdd = "2022-25-30";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::MONTH_OUT_OF_RANGE);

    std::cout << ">> validate_yyyymmdd: Test 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing validate_yyyymmdd() function. Invalid YYYY-MM-DD string.

    std::string yyyymmdd;
    ts::DatetimeValidate ret;

    yyyymmdd = "2022-01-40";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);

    std::cout << ">> validate_yyyymmdd: Test 6 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}