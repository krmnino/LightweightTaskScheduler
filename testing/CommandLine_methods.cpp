#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"
#include "../src/CommandLine.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;
lts::CommandLine* lts::CommandLine::command_line_ptr = nullptr;

int test1(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 1: initialize CommandLine and verify its data members were properly zero-out
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    assert(c->get_cmd_input() == "");
    assert(c->get_cmd_output() == "");
    assert(c->get_cmds_issued() == 0);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_methods: 1 done" << std::endl;
    return 0;
}


int test2(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 2: verify CommandLine::set_cmd_input() and CommandLine::get_cmd_input() methods
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    c->set_cmd_input("help check");
    assert(c->get_cmd_input() == "help check");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_methods: 2 done" << std::endl;
    return 0;
}


int test3(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 3: verify the command count has increased by 1
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    assert(c->get_cmds_issued() == 0);
    c->set_cmd_input("help check");
    c->parse_command();
    assert(c->get_cmds_issued() == 1);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_methods: 3 done" << std::endl;
    return 0;
}


int test4(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 4: verify the command output is set properly after issuing a command
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    std::string verify_output = "";
    verify_output += "- check registry: Displays relevant information about the tasks loaded in the scheduler.\n";
    verify_output += "- check task <task_name>: Displays the full information about the specified task.\n";
    verify_output += "- check status: Displays operational information about the scheduler.\n";
    verify_output += "- check output <task_name>: Displays output of a specific task.\n";

    c->set_cmd_input("help check");
    c->parse_command();
    assert(c->get_cmd_output() == verify_output);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_methods: 4 done" << std::endl;
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