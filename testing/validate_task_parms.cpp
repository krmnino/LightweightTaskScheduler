#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: testing validate_task_parms() function -> PASS
    // Pass mandatory task attributes only

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    ts::ValidationCode ret;

    time_now = std::time(&time_now);

    // Add five minutes in seconds to current time
    time_now_add = time_now + (5 * 60);
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);                       
                          std::to_string(struct_time_now_add.tm_sec);                       
               std::to_string(struct_time_now_add.tm_sec);                       
                          std::to_string(struct_time_now_add.tm_sec);                       
               std::to_string(struct_time_now_add.tm_sec);                       
        
    datetime_str =  hours + ":" + minutes + ":" + seconds;

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", datetime_str);

    ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::OK);

    delete c;

    std::cout << ">> validate_task_parms: 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_task_parms() function -> PASS
    // Pass mandatory task attributes + description attribute

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    ts::ValidationCode ret;    

    time_now = std::time(&time_now);

    // Add five minutes in seconds to current time
    time_now_add = time_now + 300;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);                       
                          std::to_string(struct_time_now_add.tm_sec);                       
               std::to_string(struct_time_now_add.tm_sec);                       
                          std::to_string(struct_time_now_add.tm_sec);                       
               std::to_string(struct_time_now_add.tm_sec);                       
        
    datetime_str =  hours + ":" + minutes + ":" + seconds;

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", datetime_str);

    ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::OK);

    delete c;

    std::cout << ">> validate_task_parms: 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_task_parms() function -> FAIL
    // Missing Name attribute

    cl::Config* c = new cl::Config();
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "12:00:00");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::MISSING_NAME_KEYVAL);

    delete c;

    std::cout << ">> validate_task_parms: 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing validate_task_parms() function -> FAIL
    // Missing ScriptFilename attribute

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "12:00:00");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::MISSING_SCRIPTFN_KEYVAL);

    delete c;

    std::cout << ">> validate_task_parms: 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing validate_task_parms() function -> FAIL
    // Missing Frequency attribute

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Datetime", "12:00:00");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::MISSING_FREQUENCY_KEYVAL);

    delete c;

    std::cout << ">> validate_task_parms: 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing validate_task_parms() function -> FAIL
    // Missing Datetime attribute with Frequency Once

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::MISSING_DATETIME_KEYVAL);

    delete c;

    std::cout << ">> validate_task_parms: 6 done" << std::endl;
    return 0;
}


int test7(){
    // TEST 7: testing validate_task_parms() function -> FAIL
    // Missing Datetime attribute with Frequency Hourly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Hourly");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::MISSING_DATETIME_KEYVAL);

    delete c;

    std::cout << ">> validate_task_parms: 7 done" << std::endl;
    return 0;
}


int test8(){
    // TEST 8: testing validate_task_parms() function -> FAIL
    // Missing Datetime attribute with Frequency Daily

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Daily");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::MISSING_DATETIME_KEYVAL);

    delete c;

    std::cout << ">> validate_task_parms: 8 done" << std::endl;
    return 0;
}


int test9(){
    // TEST 9: testing validate_task_parms() function -> FAIL
    // Missing Datetime attribute with Frequency Weekly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Weekly");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::MISSING_DATETIME_KEYVAL);

    delete c;

    std::cout << ">> validate_task_parms: 9 done" << std::endl;
    return 0;
}


int test10(){
    // TEST 10: testing validate_task_parms() function -> FAIL
    // Missing Datetime attribute with Frequency Monthly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Monthly");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::MISSING_DATETIME_KEYVAL);

    delete c;

    std::cout << ">> validate_task_parms: 10 done" << std::endl;
    return 0;
}


int test11(){
    // TEST 11: testing validate_task_parms() function -> FAIL
    // Missing Datetime attribute with Frequency Yearly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Yearly");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::MISSING_DATETIME_KEYVAL);

    delete c;

    std::cout << ">> validate_task_parms: 11 done" << std::endl;
    return 0;
}


int test12(){
    // TEST 12: testing validate_task_parms() function -> FAIL
    // Script file not found

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "fakename");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "12:00:00");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::SCRIPT_NOT_FOUND);

    delete c;

    std::cout << ">> validate_task_parms: 12 done" << std::endl;
    return 0;
}


int test13(){
    // TEST 13: testing validate_task_parms() function -> FAIL
    // Bad frequency value

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Bad value");
    c->add_entry("Datetime", "12:00:00");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::BAD_FREQUENCY_VALUE);

    delete c;

    std::cout << ">> validate_task_parms: 13 done" << std::endl;
    return 0;
}


int test14(){
    // TEST 14: testing validate_task_parms() function -> FAIL
    // Bad name length

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "ThisTaskNameIsOver32CharactersLong");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Hourly");
    c->add_entry("Datetime", "12:00:00");

    ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::ValidationCode::INVALID_NAME_LENGTH);

    delete c;

    std::cout << ">> validate_task_parms: 14 done" << std::endl;
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
    test14();
}