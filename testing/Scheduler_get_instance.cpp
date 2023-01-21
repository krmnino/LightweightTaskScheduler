#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/CommandLine.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::CommandLine* ts::CommandLine::command_line_ptr = nullptr;

int test1(){
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();
    
    assert(s != nullptr);

    s->Scheduler_delete();

    s->Scheduler_end_instance();

    std::cout << ">> Scheduler_get_instance: 1 done" << std::endl;
    return 0;
}

int main(int argc, char* argv[]){
    test1();
}