#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"
#include "../src/CommandLine.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::EventReporter* ts::EventReporter::event_reporter_ptr = nullptr;
ts::CommandLine* ts::CommandLine::command_line_ptr = nullptr;

int test1(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 1: Issue the command "load" and verify event warning.
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("load");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "The \"load\" verb requires at least 1 argument. Issue the command \"help load\" for options.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_load: 1 done" << std::endl;
    return 0;
}


int test2(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 2: Issue the command "load task ls_test.cl invalid" and verify event warning.
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("load task ls_test.cl invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"load task <config_name>\" does not take any additional arguments.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_load: 2 done" << std::endl;
    return 0;
}


int test3(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 3: Load one task in the scheduler by issuing the command "load task ls_test.cl".
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();

    c->set_cmd_input("load task ls_test.cl");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::INFO);
    assert(ret_event.get_message() == "Successfully loaded task \"ls\" from \"ls_test.cl\".");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_load: 3 done" << std::endl;
    return 0;
}


int test4(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 4: Attempt to load one task in the scheduler from a missing confioguration file 
    // by issuing the command "load task invalid", then verify event error.
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("load task invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::ERROR);
    assert(ret_event.get_message() == "The task file configuration file \"invalid\" could not be found.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_load: 4 done" << std::endl;
    return 0;
}


int test5(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 5: Issue the command "load invalid" and verify event warning.
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    c->set_cmd_input("load invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "An invalid argument was passed for the the \"load\" verb. Issue the command \"help load\" for options.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_load: 5 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    ts::EventReporter* e = ts::EventReporter::EventReporter_get_instance();
    ts::CommandLine* c = ts::CommandLine::CommandLine_get_instance();
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();

    test1(e, s, c);
    test2(e, s, c);
    test3(e, s, c);
    test4(e, s, c);
    test5(e, s, c);

    e->EventReporter_end_instance();
    c->CommandLine_end_instance();
    s->Scheduler_end_instance();
}