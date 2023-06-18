#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;

int test1(lts::EventReporter* e){
    // TEST 1: initialize EventReporter and verify its data members were properly zero-out
    e->EventReporter_init();

    assert(e->get_n_events() == 0);

    e->EventReporter_delete();

    std::cout << ">> EventReporter_methods: 1 done" << std::endl;
    return 0;
}


int test2(lts::EventReporter* e){
    // TEST 2: log one event and verify its attributes
    time_t time_now;
    std::string message;
    lts::EventType event_type;
    lts::Event ret_event;
    time_t ret_event_time;

    e->EventReporter_init();
    
    event_type = lts::EventType::ERROR;
    message = "Test error message";

    std::time(&time_now);
    e->log_event(event_type, message);
    ret_event = e->get_last_event();
    ret_event_time = ret_event.get_event_time();

    assert(e->get_n_events() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert((std::string)ctime(&ret_event_time) == (std::string)ctime(&time_now));
    assert(ret_event.get_type() == event_type);
    assert(ret_event.get_message() == message);
    
    e->EventReporter_delete();

    std::cout << ">> EventReporter_methods: 2 done" << std::endl;
    return 0;
}


int test3(lts::EventReporter* e){
    // TEST 3: log 3 events and verify they exist by in the EventReporter with 
    // their respective attributes.
    time_t time_now_1;
    time_t time_now_2;
    time_t time_now_3;
    std::string message_1;
    std::string message_2;
    std::string message_3;
    lts::EventType event_type_1;
    lts::EventType event_type_2;
    lts::EventType event_type_3;
    lts::Event ret_event_1;
    lts::Event ret_event_2;
    lts::Event ret_event_3;
    time_t ret_event_time_1;
    time_t ret_event_time_2;
    time_t ret_event_time_3;

    e->EventReporter_init();
    
    event_type_1 = lts::EventType::ERROR;
    event_type_2 = lts::EventType::WARNING;
    event_type_3 = lts::EventType::INFO;
    message_1 = "Test error message 1";
    message_2 = "Test error message 2";
    message_3 = "Test error message 3";

    std::time(&time_now_1);
    e->log_event(event_type_1, message_1);
    std::time(&time_now_2);
    e->log_event(event_type_2, message_2);
    std::time(&time_now_3);
    e->log_event(event_type_3, message_3);
    ret_event_1 = e->get_event_at(2);
    ret_event_2 = e->get_event_at(1);
    ret_event_3 = e->get_event_at(0);
    ret_event_time_1 = ret_event_1.get_event_time();
    ret_event_time_2 = ret_event_2.get_event_time();
    ret_event_time_3 = ret_event_3.get_event_time();

    assert(e->get_n_events() == 3);

    assert(ret_event_1.get_event_time() == time_now_1);
    assert((std::string)ctime(&ret_event_time_1) == (std::string)ctime(&time_now_1));
    assert(ret_event_1.get_type() == event_type_1);
    assert(ret_event_1.get_message() == message_1);

    assert(ret_event_2.get_event_time() == time_now_2);
    assert((std::string)ctime(&ret_event_time_2) == (std::string)ctime(&time_now_2));
    assert(ret_event_2.get_type() == event_type_2);
    assert(ret_event_2.get_message() == message_2);

    assert(ret_event_3.get_event_time() == time_now_3);
    assert((std::string)ctime(&ret_event_time_3) == (std::string)ctime(&time_now_3));
    assert(ret_event_3.get_type() == event_type_3);
    assert(ret_event_3.get_message() == message_3);
    
    e->EventReporter_delete();

    std::cout << ">> EventReporter_methods: 3 done" << std::endl;
    return 0;
}


int test4(lts::EventReporter* e){
    // TEST 4: log 3 events and verify that get_event_at(unsigned int) at index 0 and
    // get_last_event(void) get the same task 
    time_t time_now_1;
    time_t time_now_2;
    time_t time_now_3;
    std::string message_1;
    std::string message_2;
    std::string message_3;
    lts::EventType event_type_1;
    lts::EventType event_type_2;
    lts::EventType event_type_3;
    lts::Event ret_event_1;
    lts::Event ret_event_2;
    time_t ret_event_time_1;
    time_t ret_event_time_2;

    e->EventReporter_init();
    
    event_type_1 = lts::EventType::ERROR;
    event_type_2 = lts::EventType::WARNING;
    event_type_3 = lts::EventType::INFO;
    message_1 = "Test error message 1";
    message_2 = "Test error message 2";
    message_3 = "Test error message 3";

    std::time(&time_now_1);
    e->log_event(event_type_1, message_1);
    std::time(&time_now_2);
    e->log_event(event_type_2, message_2);
    std::time(&time_now_3);
    e->log_event(event_type_3, message_3);
    ret_event_1 = e->get_event_at(0);
    ret_event_2 = e->get_last_event();
    ret_event_time_1 = ret_event_1.get_event_time();
    ret_event_time_2 = ret_event_2.get_event_time();

    assert(e->get_n_events() == 3);

    assert(ret_event_1.get_event_time() == ret_event_2.get_event_time());
    assert((std::string)ctime(&ret_event_time_1) == (std::string)ctime(&ret_event_time_2));
    assert(ret_event_1.get_type() == ret_event_2.get_type());
    assert(ret_event_1.get_message() == ret_event_2.get_message());
    
    e->EventReporter_delete();

    std::cout << ">> EventReporter_methods: 4 done" << std::endl;
    return 0;
}


int test5(lts::EventReporter* e){
    // TEST 5: verify that messages are generated based on lts::ValidationCode and task configuration 
    std::string task_path_filename;
    std::string task_filename;
    std::string task_name;
    std::string ret_message;
    cl::Config* c;
    std::vector<std::pair<lts::ValidationCode, std::string>> codes_ret_messages;

    
    // Create temporary task
    c = new cl::Config();
    task_path_filename = "tasks/TestTask.cl";
    task_filename = "TestTask.cl";
    task_name = "TestTask";
    c->add_entry("Name", "TestTask");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Daily");
    c->add_entry("Datetime", "12:00:00");

    codes_ret_messages = {
        {lts::ValidationCode::MISSING_NAME_KEYVAL, "The configuration file \"TestTask.cl\" does not contain the required key-value pair Name."},
        {lts::ValidationCode::MISSING_SCRIPTFN_KEYVAL, "The configuration file \"TestTask.cl\" does not contain the required key-value pair ScriptFilename."},
        {lts::ValidationCode::MISSING_FREQUENCY_KEYVAL, "The configuration file \"TestTask.cl\" does not contain the required key-value pair Frequency."},
        {lts::ValidationCode::MISSING_DATETIME_KEYVAL, "The configuration file \"TestTask.cl\" does not contain the required key-value pair Datetime."},
        {lts::ValidationCode::SCRIPT_NOT_FOUND, "The configuration file \"TestTask.cl\" specifies the script file \"cat_test.sh\" that could not be found."},
        {lts::ValidationCode::BAD_FREQUENCY_VALUE, "An invalid frequency value of \"Daily\" was specified in the configuration file \"TestTask.cl\"."},
        {lts::ValidationCode::INCOMPATIBLE_ONCE_FREQ_DATETIME_FORMAT, "The configuration file \"TestTask.cl\" specifies a datetime value of \"12:00:00\" that has an invalid format for a Once frequency."},
        {lts::ValidationCode::INCOMPATIBLE_DAILY_FREQ_DATETIME_FORMAT, "The configuration file \"TestTask.cl\" specifies a datetime value of \"12:00:00\" that has an invalid format for a Daily frequency."},
        {lts::ValidationCode::INCOMPATIBLE_WEEKLY_FREQ_DATETIME_FORMAT, "The configuration file \"TestTask.cl\" specifies a datetime value of \"12:00:00\" that has an invalid format for a Weekly frequency."},
        {lts::ValidationCode::INCOMPATIBLE_MONTHLY_FREQ_DATETIME_FORMAT, "The configuration file \"TestTask.cl\" specifies a datetime value of \"12:00:00\" that has an invalid format for a Monthly frequency."},
        {lts::ValidationCode::INCOMPATIBLE_YEARLY_FREQ_DATETIME_FORMAT, "The configuration file \"TestTask.cl\" specifies a datetime value of \"12:00:00\" that has an invalid format for a Yearly frequency."},
        {lts::ValidationCode::PASSED_DATETIME, "The configuration file \"TestTask.cl\" specifies a datetime value of \"12:00:00\" that is in the past."},
        {lts::ValidationCode::BAD_HMS_LENGTH, "The HH:MM:SS section of datetime value in the configuration file \"TestTask.cl\" has an invalid length."},
        {lts::ValidationCode::BAD_YYYYMMDD_LENGTH, "The YYYY-MM-DD section of datetime value in the configuration file \"TestTask.cl\" has an invalid length."},
        {lts::ValidationCode::BAD_NUMBER_CHARACTER, "The datetime value specified in the configuration file \"TestTask.cl\" contains a character that is expected to be an integer."},
        {lts::ValidationCode::MISSING_DATETIME_COLON, "The datetime value specified in the configuration file \"TestTask.cl\" contains a character that is expected to be a colon \":\"."},
        {lts::ValidationCode::MISSING_DATETIME_DASH, "The datetime value specified in the configuration file \"TestTask.cl\" contains a character that is expected to be a dash \"-\"."},
        {lts::ValidationCode::MISSING_DATETIME_SPACE, "The datetime value specified in the configuration file \"TestTask.cl\" contains a character that is expected to be a space \" \"."},
        {lts::ValidationCode::BAD_WDAY, "The WDAY section of datetime value in the configuration file \"TestTask.cl\" is not a valid full or abbreviated weekday name."},
        {lts::ValidationCode::YEAR_OUT_OF_RANGE, "The datetime value specified in the configuration file \"TestTask.cl\" contains an out of range year value."},
        {lts::ValidationCode::MONTH_OUT_OF_RANGE, "The datetime value specified in the configuration file \"TestTask.cl\" contains an out of range month value."},
        {lts::ValidationCode::DAY_OUT_OF_RANGE, "The datetime value specified in the configuration file \"TestTask.cl\" contains an out of range day value."},
        {lts::ValidationCode::HOURS_OUT_OF_RANGE, "The datetime value specified in the configuration file \"TestTask.cl\" contains an out of range hours value."},
        {lts::ValidationCode::MINUTES_OUT_OF_RANGE, "The datetime value specified in the configuration file \"TestTask.cl\" contains an out of range minutes value."},
        {lts::ValidationCode::SECONDS_OUT_OF_RANGE, "The datetime value specified in the configuration file \"TestTask.cl\" contains an out of range seconds value."},
        {lts::ValidationCode::OK, "An undefined error has occured."},
        {(lts::ValidationCode)0xFFFFFFFF, "An undefined error has occured."},
    };

    for(size_t i = 0; i < codes_ret_messages.size(); i++){
        e->EventReporter_init();
        ret_message = e->generate_load_task_msg(codes_ret_messages[i].first, task_filename, c);
        assert(ret_message == codes_ret_messages[i].second);
        e->EventReporter_delete();
    }
    delete c;

    std::cout << ">> EventReporter_methods: 5 done" << std::endl;
    return 0;
}


int test6(lts::EventReporter* e){
    // TEST 6: attempt to retrieve last event when EventReporter is empty
    time_t time_now;
    lts::Event ret_event;
    time_t ret_event_time;

    e->EventReporter_init();

    std::time(&time_now);
    ret_event = e->get_last_event();
    ret_event_time = ret_event.get_event_time();

    assert(e->get_n_events() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert((std::string)ctime(&ret_event_time) == (std::string)ctime(&time_now));
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The event reporter was empty before quering the last event.");
    
    e->EventReporter_delete();

    std::cout << ">> EventReporter_methods: 6 done" << std::endl;
    return 0;
}


int test7(lts::EventReporter* e){
    // TEST 7: attempt to retrieve event at a negative index 
    time_t time_now;
    std::string message;
    lts::EventType event_type;
    lts::Event ret_event;
    time_t ret_event_time;

    e->EventReporter_init();
    
    event_type = lts::EventType::ERROR;
    message = "Test error message";

    e->log_event(event_type, message);
    assert(e->get_n_events() == 1);

    std::time(&time_now);
    ret_event = e->get_event_at(-10);
    assert(e->get_n_events() == 2);
    ret_event_time = ret_event.get_event_time();

    assert(ret_event.get_event_time() == time_now);
    assert((std::string)ctime(&ret_event_time) == (std::string)ctime(&time_now));
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The event index passed is either negative or greater than the number of recorded events.");
    
    e->EventReporter_delete();

    std::cout << ">> EventReporter_methods: 7 done" << std::endl;
    return 0;
}


int test8(lts::EventReporter* e){
    // TEST 8: attempt to retrieve event at an index equal to the number of events recorded
    time_t time_now;
    std::string message;
    lts::EventType event_type;
    lts::Event ret_event;
    time_t ret_event_time;

    e->EventReporter_init();
    
    event_type = lts::EventType::ERROR;
    message = "Test error message";

    e->log_event(event_type, message);
    assert(e->get_n_events() == 1);

    std::time(&time_now);
    ret_event = e->get_event_at(1);
    assert(e->get_n_events() == 2);
    ret_event_time = ret_event.get_event_time();

    assert(ret_event.get_event_time() == time_now);
    assert((std::string)ctime(&ret_event_time) == (std::string)ctime(&time_now));
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The event index passed is either negative or greater than the number of recorded events.");
    
    e->EventReporter_delete();

    std::cout << ">> EventReporter_methods: 8 done" << std::endl;
    return 0;
}


int test9(lts::EventReporter* e){
    // TEST 9: attempt to retrieve event at an index greater than the number of events recorded
    time_t time_now;
    std::string message;
    lts::EventType event_type;
    lts::Event ret_event;
    time_t ret_event_time;

    e->EventReporter_init();
    
    event_type = lts::EventType::ERROR;
    message = "Test error message";

    e->log_event(event_type, message);
    assert(e->get_n_events() == 1);

    std::time(&time_now);
    ret_event = e->get_event_at(10);
    assert(e->get_n_events() == 2);
    ret_event_time = ret_event.get_event_time();

    assert(ret_event.get_event_time() == time_now);
    assert((std::string)ctime(&ret_event_time) == (std::string)ctime(&time_now));
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The event index passed is either negative or greater than the number of recorded events.");
    
    e->EventReporter_delete();

    std::cout << ">> EventReporter_methods: 9 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    lts::EventReporter* e = lts::EventReporter::EventReporter_get_instance();

    test1(e);
    test2(e);
    test3(e);
    test4(e);
    test5(e);
    test6(e);
    test7(e);
    test8(e);
    test9(e);

    e->EventReporter_end_instance();
}