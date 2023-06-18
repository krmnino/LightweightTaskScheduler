#include <assert.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"
#include "../src/CommandLine.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;
lts::CommandLine* lts::CommandLine::command_line_ptr = nullptr;

int test1(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 1: Issue the command "dump" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("dump");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The \"dump\" verb requires at least 1 argument. Issue the command \"help dump\" for options.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_dump: 1 done" << std::endl;
    return 0;
}


int test2(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 2: Issue the command "dump output ls invalid" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("dump output ls invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"dump output <name>\" does not take any additional arguments.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_dump: 2 done" << std::endl;
    return 0;
}


int test3(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 3: Dump output of one task by issuing the command "dump output ls".
    std::string ret_cmd_output;
    lts::Event ret_event;
    std::string task_name;
    std::string task_filename;
    std::string task_path_filename;
    time_t time_now;
    std::tm struct_time_now;
    std::string years;
    std::string months;
    std::string days;
    std::string hours;
    std::string minutes;
    std::string seconds;
    cl::Config* config;
    std::ifstream verify_output_file;
    std::string verify_output;
    std::string line;
    std::string output_file_contents;
    std::string task_output_filename;
    std::string verify_event_message;

    time_now = std::time(&time_now);

    // Add 2 seconds to current time
    time_now = time_now + 1;
    
    // std::tm to time_t
    struct_time_now = *std::gmtime(&time_now);

    hours = (struct_time_now.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now.tm_hour) :
             std::to_string(struct_time_now.tm_hour);
    minutes = (struct_time_now.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now.tm_min) :
               std::to_string(struct_time_now.tm_min);
    seconds = (struct_time_now.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now.tm_sec) :
               std::to_string(struct_time_now.tm_sec);

    // Create temporary task
    config = new cl::Config();
    task_name = "ZZZTestTask";
    task_filename = "ZZZTestTask.cl";
    task_path_filename = "tasks/ZZZTestTask.cl";
    config->add_entry("Name", task_name);
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

    c->set_cmd_input("dump output ZZZTestTask");
    c->parse_command();

    time_now = std::time(&time_now);

    // Add timezone offset to current time
    time_now += (TIMEZONE * 60 * 60);
    
    // time_t to std::tm
    struct_time_now = *std::gmtime(&time_now);

    years = std::to_string(1900 + struct_time_now.tm_year);
    months = (struct_time_now.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now.tm_mon + 1) :
              std::to_string(struct_time_now.tm_mon + 1);  
    days = (struct_time_now.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now.tm_mday) :
            std::to_string(struct_time_now.tm_mday);
    hours = (struct_time_now.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now.tm_hour) :
             std::to_string(struct_time_now.tm_hour);
    minutes = (struct_time_now.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now.tm_min) :
               std::to_string(struct_time_now.tm_min);
    seconds = (struct_time_now.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now.tm_sec) :
               std::to_string(struct_time_now.tm_sec);

    // Get current time to verify event
    time_now = std::time(&time_now);
    task_output_filename += task_name + "_";
    task_output_filename += years + "-" + months + "-" + days + "_" + hours + "-" + minutes + "-" + seconds;
    task_output_filename += ".dat";
    verify_event_message = "Saved task \"" + task_name + "\" output in \"dumps/" + task_output_filename + "\".";
    ret_event = e->get_last_event();

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 4);
    assert(c->get_cmds_issued() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::INFO);
    assert(ret_event.get_message() == verify_event_message);

    // Read output file and verify its contents
    verify_output_file.open("dumps/" + task_output_filename);
    verify_output = "ls -l";
    while (std::getline(verify_output_file, line)){
        output_file_contents += line;
    }
    assert(output_file_contents == verify_output);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(("dumps/" + task_output_filename).c_str());
    remove(task_path_filename.c_str());

    std::cout << ">> CommandLine_verb_dump: 3 done" << std::endl;
    return 0;
}


int test4(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 4: Issue the command "dump output invalid" and verify event error.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("dump output invalid");
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

    std::cout << ">> CommandLine_verb_reload: 4 done" << std::endl;
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

    e->EventReporter_end_instance();
    c->CommandLine_end_instance();
    s->Scheduler_end_instance();
}