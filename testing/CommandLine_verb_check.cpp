#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"
#include "../src/CommandLine.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;
lts::CommandLine* lts::CommandLine::command_line_ptr = nullptr;

int test1(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 1: Issue the command "check" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("check");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);
    
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The \"check\" verb requires at least 1 argument. Issue the command \"help check\" for options.");
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 1 done" << std::endl;
    return 0;
}


int test2(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 2: Issue the command "check registry invalid" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("check registry invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);
    
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"check registry\" does not take any additional arguments.");
    assert(e->get_n_events() == 1);
    assert(c->get_cmds_issued() == 0);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 2 done" << std::endl;
    return 0;
}


int test3(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 3: Issue the command "check registry" and verify an empty task table is printed.
    std::string ret_cmd_output;
    std::string verify_cmd_output;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);
    
    verify_cmd_output += "TASK_ID | NAME | STATUS | EXECUTION_DATETIME\n";
    verify_cmd_output += "--------+------+--------+-------------------\n";
    c->set_cmd_input("check registry");
    c->parse_command();

    assert(c->get_cmds_issued() == 1);
    assert(c->get_cmd_output() == verify_cmd_output);
    assert(e->get_n_events() == 0);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 3 done" << std::endl;
    return 0;
}


int test4(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 4: Load scheduler tasks and issue command "check registry", then verify table contents.
    std::string ret_cmd_output;
    std::string verify_cmd_output_l1;
    std::string verify_cmd_output_l2;
    std::string verify_cmd_output_l3;
    std::string verify_cmd_output_l4;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);
    
    s->obtain_exec_path();
    s->load_all_tasks();

    verify_cmd_output_l1 = "| NAME | STATUS |";
    verify_cmd_output_l2 = "| cat  | QUEUED |";
    verify_cmd_output_l3 = "| ls   | QUEUED |";

    c->set_cmd_input("check registry");
    c->parse_command();
    ret_cmd_output = c->get_cmd_output();

    assert(c->get_cmds_issued() == 1);
    assert(ret_cmd_output.find(verify_cmd_output_l1) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l2) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l3) != std::string::npos);
    assert(e->get_n_events() == 2);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 4 done" << std::endl;
    return 0;
}


int test5(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 5: Issue command "check task" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("check task");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);
    
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"check task <task_name>\" requires a task name for the third parameter.");
    assert(c->get_cmds_issued() == 0);
    assert(e->get_n_events() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 5 done" << std::endl;
    return 0;
}


int test6(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 6: Issue command "check task ls invalid" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("check task ls invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);
    
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"check task <task_name>\" does not take any additional arguments.");
    assert(c->get_cmds_issued() == 0);
    assert(e->get_n_events() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 6 done" << std::endl;
    return 0;
}


int test7(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 7: Load scheduler tasks and issue command "check task ls", then verify the task attributes.
    std::string ret_cmd_output;
    std::string verify_cmd_output_l1;
    std::string verify_cmd_output_l2;
    std::string verify_cmd_output_l3;
    std::string verify_cmd_output_l4;
    std::string verify_cmd_output_l5;
    std::string verify_cmd_output_l6;
    std::string verify_cmd_output_l7;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);
    
    s->obtain_exec_path();
    s->load_all_tasks();

    verify_cmd_output_l1 = "-TASK ID:";
    verify_cmd_output_l2 = "-TASK NAME: ls";
    verify_cmd_output_l3 = "-TASK DESCRIPTION: Test task: call command ls";
    verify_cmd_output_l4 = "-TASK CREATION DATETIME:";
    verify_cmd_output_l5 = "-TASK EXECUTION DATETIME:";
    verify_cmd_output_l6 = "-TASK FREQUENCY: Once";
    verify_cmd_output_l7 = "-TASK STATUS: QUEUED";

    c->set_cmd_input("check task ls");
    c->parse_command();
    ret_cmd_output = c->get_cmd_output();

    assert(c->get_cmds_issued() == 1);
    assert(ret_cmd_output.find(verify_cmd_output_l1) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l2) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l3) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l4) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l5) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l6) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l7) != std::string::npos);
    assert(c->get_cmds_issued() == 1);
    assert(e->get_n_events() == 2);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 7 done" << std::endl;
    return 0;
}


int test8(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 8: Issue command "check task invalid_name" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("check task invalid_name");
    c->parse_command();
    ret_event = e->get_last_event();
    ret_cmd_output = c->get_cmd_output();
    std::time(&time_now);
    
    assert(c->get_cmds_issued() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The task \"invalid_name\" does not exist in the scheduler.");
    assert(e->get_n_events() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 8 done" << std::endl;
    return 0;
}


int test9(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 9: Load scheduler tasks and issue command "check status", then schdeuler status print.
    std::string ret_cmd_output;
    std::string verify_cmd_output_l1;
    std::string verify_cmd_output_l2;
    std::string verify_cmd_output_l3;
    std::string verify_cmd_output_l4;
    std::string verify_cmd_output_l5;
    std::string verify_cmd_output_l6;
    std::string verify_cmd_output_l7;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);
    
    s->obtain_exec_path();
    s->load_all_tasks();

    verify_cmd_output_l1 = "-TASKS LOADED: 2";
    verify_cmd_output_l2 = "-EVENTS RECORDED: 2";
    verify_cmd_output_l3 = "-TASKS FINISHED: 0";
    verify_cmd_output_l4 = "-TASKS INIT_ERROR: 0";
    verify_cmd_output_l5 = "-TASKS EXEC_ERROR: 0";
    verify_cmd_output_l6 = "-TASKS QUEUED: 2";
    verify_cmd_output_l7 = "-TASKS RUNNING: 0";

    c->set_cmd_input("check status");
    c->parse_command();
    ret_cmd_output = c->get_cmd_output();

    assert(c->get_cmds_issued() == 1);
    assert(ret_cmd_output.find(verify_cmd_output_l1) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l2) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l3) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l4) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l5) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l6) != std::string::npos);
    assert(ret_cmd_output.find(verify_cmd_output_l7) != std::string::npos);
    assert(e->get_n_events() == 2);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 9 done" << std::endl;
    return 0;
}


int test10(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 10: Issue command "check invalid args" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("check invalid args");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);
    
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "An invalid argument was passed for the the \"check\" verb. Issue the command \"help check\" for options.");
    assert(c->get_cmds_issued() == 0);
    assert(e->get_n_events() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 10 done" << std::endl;
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
    test9(e, s, c);
    test10(e, s, c);

    e->EventReporter_end_instance();
    c->CommandLine_end_instance();
    s->Scheduler_end_instance();
}