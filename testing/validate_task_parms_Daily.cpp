#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing validate_task_parms() function -> PASS
    // Pass valid HH:MM:SS datetime values with Frequency = Daily
    // TODO: add support for MMDD_HHMMSS, YYYYMMDD_HHMMSS, and WDAY_HHMMSS

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    ts::TaskValidate ret;     

    time_now = std::time(&time_now);

    // Add one minute in seconds from current time
    time_now_add = time_now + 60;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    std::vector<std::string> datetimes = {
        hours + ":" + minutes + ":" + seconds, // HH:MM:SS
        //months + "-" + days + " " + hours + ":" + minutes + ":" + seconds, // MM-DD HH:MM:SS
        //years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds, // YYYY-MM-DD HH:MM:SS
        //wday_abbr + " " + hours + ":" + minutes + ":" + seconds, // WDAY HH:MM:SS (abbreviated week day name)
        //wday_full + " " + hours + ":" + minutes + ":" + seconds // WDAY HH:MM:SS (full week day name)
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Once");
        c->add_entry("Datetime", datetimes[i]);

        ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::OK);

        delete c;
    }

    std::cout << ">> validate_task_parms_Daily: 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_task_parms() function -> PASS
    // Pass valid datetime values that are non compatible for Daily frequency 

    std::vector<std::string> datetimes = {
        "02-15", // MM-DD
        "2022-12-25", // YYYY-MM-DD
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Once");
        c->add_entry("Datetime", datetimes[i]);

        ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Daily: 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_task_parms() function -> FAIL
    // Pass bad HH:MM:SS datetime value with Frequency = Daily

    std::vector<std::string> datetimes = {
        "60:20:00",
        "12:60:00",
        "12:20:60",
        "60:20a00",
        "60a20:00",
        "1a:20:00",
        "12:a0:00",
        "12:00:0A"
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Daily");
        c->add_entry("Datetime", datetimes[i]);

        ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Daily: 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing validate_task_parms() function -> FAIL
    // Pass bad MM-DD HH:MM:SS datetime value with Frequency = Daily
    
    std::vector<std::string> datetimes = {
        "02-15 60:20:00",
        "02-15 12:60:00",
        "02-15 12:20:60",
        "02-15 60:20a00",
        "02-15 60a20:00",
        "02-15 1a:20:00",
        "02-15 12:a0:00",
        "02-15 12:00:0A",
        "0a-15 12:00:00",
        "02-a5 12:00:00",
        "02a15 12:00:00",
        "02-15a12:00:00",
        "80-15 12:00:00",
        "02-70 12:00:00"
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Daily");
        c->add_entry("Datetime", datetimes[i]);

        ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Daily: 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD HH:MM:SS datetime value with Frequency = Daily

    std::vector<std::string> datetimes = {
        "2022-02-15 60:20:00",
        "2022-02-15 12:60:00",
        "2022-02-15 12:20:60",
        "2022-02-15 60:20a00",
        "2022-02-15 60a20:00",
        "2022-02-15 1a:20:00",
        "2022-02-15 12:a0:00",
        "2022-02-15 12:00:0A",
        "20a2-02-15 12:00:00",
        "2022-0a-15 12:00:00",
        "2022-02-a5 12:00:00",
        "2022a02-15 12:00:00",
        "2022-02a15 12:00:00",
        "2022-02-15a12:00:00",
        "1980-02-15 12:00:00",
        "2022-80-15 12:00:00",
        "2022-02-70 12:00:00"
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Daily");
        c->add_entry("Datetime", datetimes[i]);

        ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Daily: 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing validate_task_parms() function -> FAIL
    // Pass bad WDAY HH:MM:SS datetime value with Frequency = Daily

    std::vector<std::string> datetimes = {
        "Monday 60:20:00",
        "Monday 12:60:00",
        "Monday 12:20:60",
        "Monday 60:20a00",
        "Monday 60a20:00",
        "Mondaya12:00:00",
        "Monday 1a:20:00",
        "Monday 12:a0:00",
        "Monday 12:00:0A",
        "Mxnday 12:00:00",
        "Tuexday 12:00:00",
        "Wednxsday 12:00:00",
        "Thurxday 12:00:00",
        "Fridxy 12:00:00",
        "Satuxday 12:00:00",
        "Sundax 12:00:00",
        "Mxn 12:00:00",
        "Txe 12:00:00",
        "Wxd 12:00:00",
        "Txu 12:00:00",
        "Fxi 12:00:00",
        "Sxt 12:00:00",
        "Sxn 12:00:00",
        "XYZ 12:00:00",
        "000 12:00:00",
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Daily");
        c->add_entry("Datetime", datetimes[i]);

        ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Daily: 6 done" << std::endl;
    return 0;
}


int test7(){
    // TEST 7: testing validate_task_parms() function -> FAIL
    // Pass bad datetime value with Frequency = Daily

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Daily");
    c->add_entry("Datetime", "Something");

    ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> validate_task_parms_Daily: 7 done" << std::endl;
    return 0;
}


int test8(){
    // TEST 8: testing validate_task_parms() function -> FAIL
    // Pass HH:MM:SS datetime values in the past with Frequency = Daily
    // TODO: add support for MMDD_HHMMSS, YYYYMMDD_HHMMSS, and WDAY_HHMMSS

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;
    ts::TaskValidate ret;     

    time_now = std::time(&time_now);

    // Subtract one minute in seconds from current time
    time_now_add = time_now - 60;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);                       

    std::vector<std::string> datetimes = {
        hours + ":" + minutes + ":" + seconds, // HH:MM:SS
        //months + "-" + days + " " + hours + ":" + minutes + ":" + seconds, // MM-DD HH:MM:SS
        //years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds, // YYYY-MM-DD HH:MM:SS
        //wday_abbr + " " + hours + ":" + minutes + ":" + seconds, // WDAY HH:MM:SS (abbreviated week day name)
        //wday_full + " " + hours + ":" + minutes + ":" + seconds // WDAY HH:MM:SS (full week day name)
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Once");
        c->add_entry("Datetime", datetimes[i]);

        ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Daily: 8 done" << std::endl;
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
}