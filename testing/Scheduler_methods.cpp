#include <assert.h>
#include <iostream>
#include <filesystem>

#include "../src/Scheduler.hpp"
#include "../src/CommandLine.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::CommandLine* ts::CommandLine::command_line_ptr = nullptr;

int test1(ts::Scheduler* s){
    // TEST 1: verify that n_tasks and exec_path data members are set 0 and "" respectively.
    // Check with Scheduler::get_n_tasks() and Scheduler::get_current_path()
    s->Scheduler_init();

    assert(s->get_n_tasks() == 0);
    assert(s->get_current_path() == "");

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 1 done" << std::endl;
    return 0;
}


int test2(ts::Scheduler* s){
    // TEST 2: verify exec_path data member has been updated after Scheduler::obtain_exec_path()
    // Check with Scheduler::get_current_path()
    s->Scheduler_init();

    std::string current_path = std::filesystem::current_path();
    s->obtain_exec_path();
    assert(current_path == s->get_current_path());

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 2 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();

    test1(s);
    test2(s);

    s->Scheduler_end_instance();
}