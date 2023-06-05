#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"
#include "../src/CommandLine.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::EventReporter* ts::EventReporter::event_reporter_ptr = nullptr;
ts::CommandLine* ts::CommandLine::command_line_ptr = nullptr;

int test1(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 1: Issue the command "reload" and verify event warning.
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("reload");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "The \"reload\" verb requires at least 1 argument. Issue the command \"help reload\" for options.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_reload: 1 done" << std::endl;
    return 0;
}


int test2(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 2: Issue the command "reload task ls invalid" and verify event warning.
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("reload task ls invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"reload task <config_name>\" does not take any additional arguments.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_reload: 2 done" << std::endl;
    return 0;
}


int test3(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 3: Reload one task by issuing the command "reload task ls".
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("reload task ls");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::INFO);
    assert(ret_event.get_message() == "Successfully reloaded task \"ls\".");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_reload: 3 done" << std::endl;
    return 0;
}


int test4(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 4: Issue the command "reload task invalid" and verify event error.
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("reload task invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::ERROR);
    assert(ret_event.get_message() == "The task \"invalid\" does not exist in the scheduler.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_reload: 4 done" << std::endl;
    return 0;
}


int test5(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 5: Issue the command "reload tasks" and verify event warning.
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("reload tasks");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"reload tasks <config_name1, config_name2, ...>\" requires at least one task name.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_reload: 5 done" << std::endl;
    return 0;
}


int test6(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 6: Reload two tasks by issuing the command "reload tasks cat ls".
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;
    bool matching_event_msg;
    std::string verify_event_message;
    ts::EventType verify_event_type;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("reload tasks cat ls");
    c->parse_command();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 4);
    assert(c->get_cmds_issued() == 1);

    verify_event_message = "Successfully reloaded task \"ls\".";
    verify_event_type = ts::EventType::INFO;
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

    verify_event_message = "Successfully reloaded task \"cat\".";
    verify_event_type = ts::EventType::INFO;
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

    std::cout << ">> CommandLine_verb_reload: 6 done" << std::endl;
    return 0;
}


int test7(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 7: Issue the command "reload tasks cat invalid" and verify the events.
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;
    bool matching_event_msg;
    std::string verify_event_message;
    ts::EventType verify_event_type;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("reload tasks cat invalid");
    c->parse_command();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 4);
    assert(c->get_cmds_issued() == 1);

    verify_event_message = "Successfully reloaded task \"cat\".";
    verify_event_type = ts::EventType::INFO;
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
    verify_event_type = ts::EventType::ERROR;
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

    std::cout << ">> CommandLine_verb_reload: 7 done" << std::endl;
    return 0;
}


int test8(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 8: Issue the command "reload all invalid" and verify event warning.
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("reload all invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"reload all\" does not take any additional arguments.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_reload: 8 done" << std::endl;
    return 0;
}


int test9(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 9: Reload all tasks by issuing the command "reload all".
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;
    bool matching_event_msg;
    std::string verify_event_message;
    ts::EventType verify_event_type;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("reload all");
    c->parse_command();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 4);
    assert(c->get_cmds_issued() == 1);

    verify_event_message = "Successfully reloaded task \"ls\".";
    verify_event_type = ts::EventType::INFO;
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

    verify_event_message = "Successfully reloaded task \"cat\".";
    verify_event_type = ts::EventType::INFO;
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

    std::cout << ">> CommandLine_verb_reload: 9 done" << std::endl;
    return 0;
}


int test10(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 10: Issue the command "reload invalid" and verify event warning.
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    c->set_cmd_input("reload invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "An invalid argument was passed for the the \"reload\" verb. Issue the command \"help reload\" for options.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_reload: 10 done" << std::endl;
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
    test6(e, s, c);
    test7(e, s, c);
    test8(e, s, c);
    test9(e, s, c);
    test10(e, s, c);

    e->EventReporter_end_instance();
    c->CommandLine_end_instance();
    s->Scheduler_end_instance();
}