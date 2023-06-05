#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"
#include "../src/CommandLine.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::EventReporter* ts::EventReporter::event_reporter_ptr = nullptr;
ts::CommandLine* ts::CommandLine::command_line_ptr = nullptr;

int test1(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 1: Issue the command "help" and verify command output.
    std::string ret_cmd_output;
    std::string verify_cmd_output;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    verify_cmd_output = "";
    verify_cmd_output += "- help: Displays this dialog.\n";
    verify_cmd_output += "- help check: Displays usage for the \"check\" verb only.\n";
    verify_cmd_output += "- help remove: Displays usage for the \"remove\" verb only.\n";
    verify_cmd_output += "- help load: Displays usage for the \"load\" verb only.\n";
    verify_cmd_output += "- help reload: Displays usage for the \"reload\" verb only.\n";
    verify_cmd_output += "- close: Terminates the scheduler program.\n";
    verify_cmd_output += "- check registry: Displays relevant information about the tasks loaded in the scheduler.\n";
    verify_cmd_output += "- check task <task_name>: Displays the full information about the specified task.\n";
    verify_cmd_output += "- check status: Displays operational information about the scheduler.\n";
    verify_cmd_output += "- remove task <task_name>: Removes the specified task from the scheduler.\n";
    verify_cmd_output += "- load task <config_name>: Load task in scheduler from specified configuration filename.\n";
    verify_cmd_output += "- reload task <name>: Reload task in scheduler from specified task name attribute.\n";
    verify_cmd_output += "- reload tasks <name1, name2...>: Reload multiple tasks in scheduler from specified list of task name attributes.\n";
    verify_cmd_output += "- reload all: Reload all tasks loaded in the Scheduler.\n";

    c->set_cmd_input("help");
    c->parse_command();

    assert(e->get_n_events() == 0);
    assert(c->get_cmd_output() == verify_cmd_output);
    assert(c->get_cmds_issued() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_help: 1 done" << std::endl;
    return 0;
}


int test2(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 2: Issue the command "help check" and verify command output.
    std::string ret_cmd_output;
    std::string verify_cmd_output;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    verify_cmd_output = "";
    verify_cmd_output += "- check registry: Displays relevant information about the tasks loaded in the scheduler.\n";
    verify_cmd_output += "- check task <task_name>: Displays the full information about the specified task.\n";
    verify_cmd_output += "- check status: Displays operational information about the scheduler.\n";

    c->set_cmd_input("help check");
    c->parse_command();

    assert(e->get_n_events() == 0);
    assert(c->get_cmd_output() == verify_cmd_output);
    assert(c->get_cmds_issued() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_help: 2 done" << std::endl;
    return 0;
}


int test3(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 3: Issue the command "help remove" and verify command output.
    std::string ret_cmd_output;
    std::string verify_cmd_output;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    verify_cmd_output = "";
    verify_cmd_output += "- remove task <task_name>: Removes the specified task from the scheduler.\n";

    c->set_cmd_input("help remove");
    c->parse_command();

    assert(e->get_n_events() == 0);
    assert(c->get_cmd_output() == verify_cmd_output);
    assert(c->get_cmds_issued() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_help: 3 done" << std::endl;
    return 0;
}


int test4(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 4: Issue the command "help load" and verify command output.
    std::string ret_cmd_output;
    std::string verify_cmd_output;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    verify_cmd_output = "";
    verify_cmd_output += "- load task <config_name>: Load task in scheduler from specified configuration filename.\n";

    c->set_cmd_input("help load");
    c->parse_command();

    assert(e->get_n_events() == 0);
    assert(c->get_cmd_output() == verify_cmd_output);
    assert(c->get_cmds_issued() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_help: 4 done" << std::endl;
    return 0;
}


int test5(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 5: Issue the command "help reload" and verify command output.
    std::string ret_cmd_output;
    std::string verify_cmd_output;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    verify_cmd_output = "";
    verify_cmd_output += "- reload task <name>: Reload task in scheduler from specified task name attribute.\n";
    verify_cmd_output += "- reload tasks <name1, name2...>: Reload multiple tasks in scheduler from specified list of task name attributes.\n";
    verify_cmd_output += "- reload all: Reload all tasks loaded in the Scheduler.\n";

    c->set_cmd_input("help reload");
    c->parse_command();

    assert(e->get_n_events() == 0);
    assert(c->get_cmd_output() == verify_cmd_output);
    assert(c->get_cmds_issued() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_help: 5 done" << std::endl;
    return 0;
}


int test6(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 6: Issue the command "help invalid" and verify event warning.
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("help invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "An invalid argument was passed for the the \"help\" verb. Issue the command \"help\" for options.");
    assert(c->get_cmds_issued() == 0);
    assert(e->get_n_events() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_help: 6 done" << std::endl;
    return 0;
}


int test7(ts::EventReporter* e, ts::Scheduler* s, ts::CommandLine* c){
    // TEST 7: Issue the command "help invalid invalid" and verify event warning.
    std::string ret_cmd_output;
    ts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("help invalid invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == ts::EventType::WARNING);
    assert(ret_event.get_message() == "An invalid argument was passed for the the \"help\" verb. Issue the command \"help\" for options.");
    assert(c->get_cmds_issued() == 0);
    assert(e->get_n_events() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_help: 7 done" << std::endl;
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

    e->EventReporter_end_instance();
    c->CommandLine_end_instance();
    s->Scheduler_end_instance();
}