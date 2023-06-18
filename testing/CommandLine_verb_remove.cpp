#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"
#include "../src/CommandLine.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;
lts::CommandLine* lts::CommandLine::command_line_ptr = nullptr;

int test1(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 1: Issue the command "remove" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("remove");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The \"remove\" verb requires at least 1 argument. Issue the command \"help remove\" for options.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 1 done" << std::endl;
    return 0;
}


int test2(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 2: Issue the command "remove task ls invalid" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("remove task ls invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"remove task <task_name>\" does not take any additional arguments.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 2 done" << std::endl;
    return 0;
}


int test3(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 3: Load scheduler tasks and issue command "remove task ls", then verify task removal.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("remove task ls");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::INFO);
    assert(ret_event.get_message() == "Successfully removed task \"ls\" from the scheduler.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 3 done" << std::endl;
    return 0;
}


int test4(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 4: Load scheduler tasks and issue command "remove task invalid", then verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("remove task invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::ERROR);
    assert(ret_event.get_message() == "The task \"invalid\" does not exist in the scheduler.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 4 done" << std::endl;
    return 0;
}


int test5(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 5: Issue the command "remove tasks" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("remove tasks");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"remove tasks <name1, name2, ...>\" requires at least one task name.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 5 done" << std::endl;
    return 0;
}


int test6(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 6: Remove two tasks by issuing the command "remove tasks cat ls".
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;
    bool matching_event_msg;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("remove tasks cat ls");
    c->parse_command();
    std::time(&time_now);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 4);
    assert(c->get_cmds_issued() == 1);

    verify_event_message = "Successfully removed task \"ls\" from the scheduler.";
    verify_event_type = lts::EventType::INFO;
    matching_event_msg = false;
    // Look through all events and see if one matches the verification event message
    for(size_t i = 0; i < e->get_n_events(); i++){
        ret_event = e->get_event_at(i);
        if(ret_event.get_message().find(verify_event_message) != std::string::npos){
            matching_event_msg = true;
            break;
        }
    }
    assert(matching_event_msg);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    verify_event_message = "Successfully removed task \"cat\" from the scheduler.";
    verify_event_type = lts::EventType::INFO;
    matching_event_msg = false;
    // Look through all events and see if one matches the verification event message
    for(size_t i = 0; i < e->get_n_events(); i++){
        ret_event = e->get_event_at(i);
        if(ret_event.get_message().find(verify_event_message) != std::string::npos){
            matching_event_msg = true;
            break;
        }
    }
    assert(matching_event_msg);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 6 done" << std::endl;
    return 0;
}


int test7(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 7: Issue the command "remove tasks cat invalid" and verify the events.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;
    bool matching_event_msg;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("remove tasks cat invalid");
    c->parse_command();
    std::time(&time_now);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 4);
    assert(c->get_cmds_issued() == 1);

    verify_event_message = "Successfully removed task \"cat\" from the scheduler.";
    verify_event_type = lts::EventType::INFO;
    matching_event_msg = false;
    // Look through all events and see if one matches the verification event message
    for(size_t i = 0; i < e->get_n_events(); i++){
        ret_event = e->get_event_at(i);
        if(ret_event.get_message().find(verify_event_message) != std::string::npos){
            matching_event_msg = true;
            break;
        }
    }
    assert(matching_event_msg);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    verify_event_message = "The task \"invalid\" does not exist in the scheduler.";
    verify_event_type = lts::EventType::ERROR;
    matching_event_msg = false;
    // Look through all events and see if one matches the verification event message
    for(size_t i = 0; i < e->get_n_events(); i++){
        ret_event = e->get_event_at(i);
        if(ret_event.get_message().find(verify_event_message) != std::string::npos){
            matching_event_msg = true;
            break;
        }
    }
    assert(matching_event_msg);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 7 done" << std::endl;
    return 0;
}


int test8(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 8: Issue the command "remove invalid" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("remove invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "An invalid argument was passed for the the \"remove\" verb. Issue the command \"help remove\" for options.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_remove: 8 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    lts::EventReporter* e = lts::EventReporter::EventReporter_get_instance();
    lts::CommandLine* c = lts::CommandLine::CommandLine_get_instance();
    lts::Scheduler* s = lts::Scheduler::Scheduler_get_instance();

    test1(e, s, c);
    test2(e, s, c);
    test3(e, s, c);
    test4(e, s, c);
    test5(e, s, c);
    test6(e, s, c);
    test7(e, s, c);
    test8(e, s, c);

    e->EventReporter_end_instance();
    c->CommandLine_end_instance();
    s->Scheduler_end_instance();
}