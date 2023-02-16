#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing validate_yyyymmdd() function. Valid YYYY-MM-DD HH:MM:SS string.

    std::string yyyymmdd_hms;
    ts::ValidationCode ret;

    yyyymmdd_hms = "2022-01-01 12:00:00";
    ret = ts::validate_yyyymmdd_hms(yyyymmdd_hms);
    assert(ret == ts::ValidationCode::OK);

    std::cout << ">> validate_yyyymmdd_hms: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_yyyymmdd() function. Invalid YYYY-MM-DD HH:MM:SS string.

    std::string yyyymmdd_hms;
    ts::ValidationCode ret;

    yyyymmdd_hms = "2022-01-0112:00:00";
    ret = ts::validate_yyyymmdd_hms(yyyymmdd_hms);
    assert(ret == ts::ValidationCode::MISSING_DATETIME_SPACE);

    std::cout << ">> validate_yyyymmdd_hms: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_yyyymmdd() function. Invalid YYYY-MM-DD HH:MM:SS string.

    ts::ValidationCode ret;
    std::vector<std::string> yyyymmdd_hms = {
        "202a-01-01 12:00:00",
        "2022-01-01 12:0a:00"
    };

    for(int i = 0; i < yyyymmdd_hms.size(); i++){
        ret = ts::validate_yyyymmdd_hms(yyyymmdd_hms[i]);
        assert(ret == ts::ValidationCode::BAD_NUMBER_CHARACTER);
    }

    std::cout << ">> validate_yyyymmdd_hms: Test 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing validate_yyyymmdd() function. Invalid YYYY-MM-DD HH:MM:SS string.

    ts::ValidationCode ret;
    std::vector<std::string> yyyymmdd_hms = {
        "2022a01a01 12:00:00",
        "2022a01-01 12:00:00",
        "2022-01a01 12:00:00"
    };

    for(int i = 0; i < yyyymmdd_hms.size(); i++){
        ret = ts::validate_yyyymmdd_hms(yyyymmdd_hms[i]);
        assert(ret == ts::ValidationCode::MISSING_DATETIME_DASH);
    }

    std::cout << ">> validate_yyyymmdd_hms: Test 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing validate_yyyymmdd() function. Invalid YYYY-MM-DD HH:MM:SS string.

    ts::ValidationCode ret;
    std::vector<std::string> yyyymmdd_hms = {
        "2022-01-01 12a00a00",
        "2022-01-01 12a00:00",
        "2022-01-01 12:00a00"
    };

    for(int i = 0; i < yyyymmdd_hms.size(); i++){
        ret = ts::validate_yyyymmdd_hms(yyyymmdd_hms[i]);
        assert(ret == ts::ValidationCode::MISSING_DATETIME_COLON);
    }

    std::cout << ">> validate_yyyymmdd_hms: Test 5 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
}