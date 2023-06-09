#include <assert.h>
#include <iostream>
#include <unistd.h>

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
    // TEST 9: Issue command "check status invalid" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("check status invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    ret_cmd_output = c->get_cmd_output();
    std::time(&time_now);
    
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"check status\" does not take any additional arguments.");
    assert(e->get_n_events() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 9 done" << std::endl;
    return 0;
}


int test10(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 10: Load scheduler tasks and issue command "check status", then schdeuler status print.
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

    std::cout << ">> CommandLine_verb_check: 10 done" << std::endl;
    return 0;
}


int test11(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 11: Issue command "check output" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("check output");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);
    
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"check output <task_name>\" requires a task name for the third parameter.");
    assert(c->get_cmds_issued() == 0);
    assert(e->get_n_events() == 3);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 11 done" << std::endl;
    return 0;
}


int test12(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 12: Issue command "check output ls invalid" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("check output ls invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);
    
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"check output <task_name>\" does not take any additional arguments.");
    assert(c->get_cmds_issued() == 0);
    assert(e->get_n_events() == 3);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 12 done" << std::endl;
    return 0;
}


int test13(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 13: Load scheduler tasks and issue command "check output ls", then verify the task attributes.
    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string task_filename;
    std::string task_path_filename;
    cl::Config* config;
    std::string ret_cmd_output;

    time_now = std::time(&time_now);

    // Add 2 seconds to current time
    time_now_add = time_now + 1;
    
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

    // Create temporary task
    config = new cl::Config();
    task_filename = "ZZZTestTask.cl";
    task_path_filename = "tasks/ZZZTestTask.cl";
    config->add_entry("Name", "ZZZTestTask");
    config->add_entry("Description", "A short description");
    config->add_entry("ScriptFilename", "cat_test.sh");
    config->add_entry("Frequency", "Daily");
    config->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    config->save_config(task_path_filename);
    delete config;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);
    
    s->obtain_exec_path();
    s->load_task(task_filename);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    c->set_cmd_input("check output ZZZTestTask");
    c->parse_command();
    ret_cmd_output = c->get_cmd_output();
    
    assert(ret_cmd_output == "ls -l");
    assert(c->get_cmds_issued() == 1);
    assert(e->get_n_events() == 3);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(task_path_filename.c_str());

    std::cout << ">> CommandLine_verb_check: 13 done" << std::endl;
    return 0;
}


int test14(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 14: Issue command "check output invalid_name" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("check output invalid_name");
    c->parse_command();
    ret_event = e->get_last_event();
    ret_cmd_output = c->get_cmd_output();
    std::time(&time_now);
    
    assert(c->get_cmds_issued() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The task \"invalid_name\" does not exist in the scheduler.");
    assert(e->get_n_events() == 3);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_check: 14 done" << std::endl;
    return 0;
}


int test15(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 15: Issue command "check invalid" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("check invalid");
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

    std::cout << ">> CommandLine_verb_check: 15 done" << std::endl;
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
    test11(e, s, c);
    test12(e, s, c);
    test13(e, s, c);
    test14(e, s, c);
    test15(e, s, c);

    e->EventReporter_end_instance();
    c->CommandLine_end_instance();
    s->Scheduler_end_instance();
}