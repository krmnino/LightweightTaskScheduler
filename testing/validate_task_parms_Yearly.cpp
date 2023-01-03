#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

int test1(){
    // TEST 1: testing validate_task_parms() function -> PASS
    // Current time plus one minute in seconds 
    // Pass datetime formats MMDD_HHMMSS and YYYYMMDD_HHMMSS.
    // Frequency = Yearly

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
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
        months + "-" + days + " " + hours + ":" + minutes + ":" + seconds, // MM-DD HH:MM:SS
        years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds // YYYY-MM-DD HH:MM:SS
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Yearly");
        c->add_entry("Datetime", datetimes[i]);

        ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::OK);

        delete c;
    }

    std::cout << ">> validate_task_parms_Yearly: 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_task_parms() function -> PASS
    // Current time plus one day in seconds 
    // Pass datetime formats MMDD, YYYYMMDD. 
    // Frequency = Yearly

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string datetime_str;
    ts::TaskValidate ret;     

    time_now = std::time(&time_now);

    // Add one day in seconds from current time
    time_now_add = time_now + (24 * 60 * 60);
    
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

    std::vector<std::string> datetimes = {
        months + "-" + days, // MM-DD
        years + "-" + months + "-" + days, // YYYY-MM-DD
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Yearly");
        c->add_entry("Datetime", datetimes[i]);

        ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::OK);

        delete c;
    }

    std::cout << ">> validate_task_parms_Yearly: 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_task_parms() function -> FAIL
    // Current time plus one minute in seconds 
    // Pass incompatible datetime HH:MM:SS and WDAY_HHMMSS formats. 
    // Frequency = Yearly

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
        wday_abbr + " " + hours + ":" + minutes + ":" + seconds, // WDAY HH:MM:SS (abbreviated week day name)
        wday_full + " " + hours + ":" + minutes + ":" + seconds // WDAY HH:MM:SS (full week day name)
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Yearly");
        c->add_entry("Datetime", datetimes[i]);

        ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Yearly: 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing validate_task_parms() function -> FAIL
    // Pass bad MM-DD HH:MM:SS datetime value with Frequency = Yearly
    
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
        c->add_entry("Frequency", "Yearly");
        c->add_entry("Datetime", datetimes[i]);

        ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Yearly: 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD HH:MM:SS datetime value with Frequency = Yearly

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
        c->add_entry("Frequency", "Yearly");
        c->add_entry("Datetime", datetimes[i]);

        ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Yearly: 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing validate_task_parms() function -> FAIL
    // Pass bad MM-DD datetime value with Frequency = Yearly

    std::vector<std::string> datetimes = {
        "0a-15",
        "02-a5",
        "02a15",
        "80-15",
        "02-70"
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Yearly");
        c->add_entry("Datetime", datetimes[i]);

        ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Yearly: 6 done" << std::endl;
    return 0;
}


int test7(){
    // TEST 7: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD datetime value with Frequency = Yearly

    std::vector<std::string> datetimes = {
        "20a2-02-15",
        "2022-0a-15",
        "2022-02-a5",
        "2022a02-15",
        "2022-02a15",
        "2022-02-15",
        "1980-02-15",
        "2022-80-15",
        "2022-02-70"
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Yearly");
        c->add_entry("Datetime", datetimes[i]);

        ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Yearly: 7 done" << std::endl;
    return 0;
}


int test8(){
    // TEST 8: testing validate_task_parms() function -> FAIL
    // Pass bad datetime value with Frequency = Yearly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", "Something");

    ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> validate_task_parms_Yearly: 8 done" << std::endl;
    return 0;
}


int test9(){
    // TEST 9: testing validate_task_parms() function -> FAIL
    // Current time minus one minute in seconds 
    // Pass datetime format YYYYMMDD_HHMMSS. 
    // Frequency = Yearly

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
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
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    datetime_str = years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds; // YYYY-MM-DD HH:MM:SS

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", datetime_str);

    ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> validate_task_parms_Yearly: 9 done" << std::endl;
    return 0;
}


int test10(){
    // TEST 10: testing validate_task_parms() function -> FAIL
    // Current time minus one day in seconds 
    // Pass datetime formats YYYYMMDD. 
    // Frequency = Yearly

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string datetime_str;
    ts::TaskValidate ret;     

    time_now = std::time(&time_now);

    // Add one day in seconds from current time
    time_now_add = time_now - (24 * 60 * 60);
    
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

    datetime_str = years + "-" + months + "-" + days; // YYYY-MM-DD

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", datetime_str);

    ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> validate_task_parms_Yearly: 10 done" << std::endl;
    return 0;
}


int test11(){
    // TEST 11: testing validate_task_parms() function -> FAIL
    // Current time plus one minute in seconds 
    // Pass datetime formats HHMMSS. 
    // Frequency = Yearly

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

    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    datetime_str = hours + ":" + minutes + ":" + seconds; // HH:MM:SS

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", datetime_str);

    ret = ts::validate_task_parms(c, "scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> validate_task_parms_Yearly: 11 done" << std::endl;
    return 0;
}


int test12(){
    // TEST 12: testing validate_task_parms() function -> FAIL
    // Current time plus one minute in seconds. Test different week day names (full and abbreviated)
    // Pass datetime format WDAY_HHMMSS. 
    // Frequency = Yearly

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
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
        std::string("Monday") + " " + hours + ":" + minutes + ":" + seconds,    // WDAY HH:MM:SS (full week day name)
        std::string("Tuesday") + " " + hours + ":" + minutes + ":" + seconds,   // WDAY HH:MM:SS (full week day name)
        std::string("Wednesday") + " " + hours + ":" + minutes + ":" + seconds, // WDAY HH:MM:SS (full week day name)
        std::string("Thursday") + " " + hours + ":" + minutes + ":" + seconds,  // WDAY HH:MM:SS (full week day name)
        std::string("Friday") + " " + hours + ":" + minutes + ":" + seconds,    // WDAY HH:MM:SS (full week day name)
        std::string("Saturday") + " " + hours + ":" + minutes + ":" + seconds,  // WDAY HH:MM:SS (full week day name)
        std::string("Sunday") + " " + hours + ":" + minutes + ":" + seconds,    // WDAY HH:MM:SS (full week day name)
        std::string("Mon") + " " + hours + ":" + minutes + ":" + seconds,       // WDAY HH:MM:SS (abbreviated week day name)
        std::string("Tue") + " " + hours + ":" + minutes + ":" + seconds,       // WDAY HH:MM:SS (abbreviated week day name)
        std::string("Wed") + " " + hours + ":" + minutes + ":" + seconds,       // WDAY HH:MM:SS (abbreviated week day name)
        std::string("Thu") + " " + hours + ":" + minutes + ":" + seconds,       // WDAY HH:MM:SS (abbreviated week day name)
        std::string("Fri") + " " + hours + ":" + minutes + ":" + seconds,       // WDAY HH:MM:SS (abbreviated week day name)
        std::string("Sat") + " " + hours + ":" + minutes + ":" + seconds,       // WDAY HH:MM:SS (abbreviated week day name)
        std::string("Sun") + " " + hours + ":" + minutes + ":" + seconds        // WDAY HH:MM:SS (abbreviated week day name)
    };
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Yearly");
        c->add_entry("Datetime", datetimes[i]);

        ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

        delete c;
    }

    std::cout << ">> validate_task_parms_Yearly: 12 done" << std::endl;
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
}