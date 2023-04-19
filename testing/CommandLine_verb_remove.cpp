#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"
#include "../src/CommandLine.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::EventReporter* ts::EventReporter::event_reporter_ptr = nullptr;
ts::CommandLine* ts::CommandLine::command_line_ptr = nullptr;

int test1(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 1: Issue the command "remove" and verify event warning
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    c->set_cmd_input("remove");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "The \"remove\" verb requires at least 1 argument. Issue the command \"help remove\" for options.");
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 1 done" << std::endl;
    return 0;
}


int test2(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 2: Issue the command "remove task ls invalid" and verify event warning
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    c->set_cmd_input("remove task ls invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"remove task <task_name>\" does not take any additional arguments.");
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 2 done" << std::endl;
    return 0;
}


int test3(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 3: Load scheduler tasks and issue command "remove task ls", then verify task removal
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_tasks_from_dir();

    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    c->set_cmd_input("remove task ls");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::INFO);
    assert(ret_event.get_message() == "Successfully removed task \"ls\" from the scheduler.");
    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 3 done" << std::endl;
    return 0;
}


int test4(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 4: Load scheduler tasks and issue command "remove task invalid", then verify event
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_tasks_from_dir();

    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    c->set_cmd_input("remove task invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::ERROR);
    assert(ret_event.get_message() == "The task \"invalid\" does not exist in the scheduler.");
    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 4 done" << std::endl;
    return 0;
}


int test5(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 5: Issue the command "remove invalid" and verify event warning
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

    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "An invalid argument was passed for the the \"remove\" verb. Issue the command \"help remove\" for options.");
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 5 done" << std::endl;
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