#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: testing validate_task_parms() function -> PASS
    // Current time plus one minute in seconds 
    // Pass datetime formats HHMMSS and YYYYMMDD_HHMMSS
    // Frequency = Hourly

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
    lts::ValidationCode ret;     

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
        years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds, // YYYY-MM-DD HH:MM:SS
    };
    for(size_t i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Hourly");
        c->add_entry("Datetime", datetimes[i]);

        ret = lts::validate_task_parms(c, "scripts/");

        assert(ret == lts::ValidationCode::OK);

        delete c;
    }

    std::cout << ">> validate_task_parms_Hourly: 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing validate_task_parms() function -> FAIL
    // Pass bad HH:MM:SS datetime value with Frequency = Once

    std::vector<std::pair<std::string, lts::ValidationCode>> datetimes_retcodes = {
        {"60:20:00", lts::ValidationCode::HOURS_OUT_OF_RANGE},
        {"12:60:00", lts::ValidationCode::MINUTES_OUT_OF_RANGE},
        {"12:20:60", lts::ValidationCode::SECONDS_OUT_OF_RANGE},
        {"1a:20:00", lts::ValidationCode::BAD_NUMBER_CHARACTER},
        {"12:a0:00", lts::ValidationCode::BAD_NUMBER_CHARACTER},
        {"12:00:0A", lts::ValidationCode::BAD_NUMBER_CHARACTER},
        {"11111:111111:111111", lts::ValidationCode::BAD_HMS_LENGTH},
        {"11111:00:00", lts::ValidationCode::BAD_HMS_LENGTH},
        {"12:11111:00", lts::ValidationCode::BAD_HMS_LENGTH},
        {"12:00:11111", lts::ValidationCode::BAD_HMS_LENGTH},
    };

    for(size_t i = 0; i < datetimes_retcodes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Once");
        c->add_entry("Datetime", datetimes_retcodes[i].first);

        lts::ValidationCode ret = lts::validate_task_parms(c, "scripts/");

        assert(ret == datetimes_retcodes[i].second);

        delete c;
    }

    std::cout << ">> validate_task_parms_Hourly: 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD HH:MM:SS datetime value with Frequency = Hourly

    std::vector<std::pair<std::string, lts::ValidationCode>> datetimes_retcodes = {
        {"2022-02-15 60:20:00", lts::ValidationCode::HOURS_OUT_OF_RANGE},
        {"2022-02-15 12:60:00", lts::ValidationCode::MINUTES_OUT_OF_RANGE},
        {"2022-02-15 12:20:60", lts::ValidationCode::SECONDS_OUT_OF_RANGE},
        {"2022-02-15 1a:20:00", lts::ValidationCode::BAD_NUMBER_CHARACTER},
        {"2022-02-15 12:a0:00", lts::ValidationCode::BAD_NUMBER_CHARACTER},
        {"2022-02-15 12:00:0A", lts::ValidationCode::BAD_NUMBER_CHARACTER},
        {"20a2-02-15 12:00:00", lts::ValidationCode::BAD_NUMBER_CHARACTER},
        {"2022-0a-15 12:00:00", lts::ValidationCode::BAD_NUMBER_CHARACTER},
        {"2022-02-a5 12:00:00", lts::ValidationCode::BAD_NUMBER_CHARACTER},
        {"1980-02-15 12:00:00", lts::ValidationCode::PASSED_DATETIME},
        {"2022-80-15 12:00:00", lts::ValidationCode::MONTH_OUT_OF_RANGE},
        {"2022-02-70 12:00:00", lts::ValidationCode::DAY_OUT_OF_RANGE},
        {"2022-02-15 111111:111111:111111", lts::ValidationCode::BAD_HMS_LENGTH},
        {"2022-02-15 1:00:00", lts::ValidationCode::BAD_HMS_LENGTH},
        {"1111111-1111111-1111111 12:00:00", lts::ValidationCode::BAD_YYYYMMDD_LENGTH},
        {"2022-2-15 12:00:00", lts::ValidationCode::BAD_YYYYMMDD_LENGTH},
    };

    for(size_t i = 0; i < datetimes_retcodes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Hourly");
        c->add_entry("Datetime", datetimes_retcodes[i].first);

        lts::ValidationCode ret = lts::validate_task_parms(c, "scripts/");

        assert(ret == datetimes_retcodes[i].second);

        delete c;
    }

    std::cout << ">> validate_task_parms_Hourly: 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing validate_task_parms() function -> FAIL
    // Pass bad datetime value with Frequency = Hourly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test Title");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Hourly");
    c->add_entry("Datetime", "Something");

    lts::ValidationCode ret = lts::validate_task_parms(c, "scripts/");

    assert(ret == lts::ValidationCode::INCOMPATIBLE_ONCE_FREQ_DATETIME_FORMAT);

    delete c;

    std::cout << ">> validate_task_parms_Hourly: 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing validate_task_parms() function -> FAIL
    // Current time minus one minute in seconds 
    // Pass datetime formats HHMMSS and YYYYMMDD_HHMMSS
    // Frequency = Hourly

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
    lts::ValidationCode ret;     

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

    std::vector<std::string> datetimes = {
        hours + ":" + minutes + ":" + seconds, // HH:MM:SS
        years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds, // YYYY-MM-DD HH:MM:SS
    };
    for(size_t i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Hourly");
        c->add_entry("Datetime", datetimes[i]);

        ret = lts::validate_task_parms(c, "scripts/");

        assert(ret == lts::ValidationCode::PASSED_DATETIME);

        delete c;
    }

    std::cout << ">> validate_task_parms_Hourly: 5 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
}