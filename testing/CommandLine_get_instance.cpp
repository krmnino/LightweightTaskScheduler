#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"
#include "../src/CommandLine.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;
lts::CommandLine* lts::CommandLine::command_line_ptr = nullptr;

int test1(){
    lts::CommandLine* c = lts::CommandLine::CommandLine_get_instance();
    
    assert(c != nullptr);

    c->CommandLine_delete();

    c->CommandLine_end_instance();

    std::cout << ">> CommandLine_get_instance: 1 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    test1();
}