#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;

int test1(){
    lts::EventReporter* e = lts::EventReporter::EventReporter_get_instance();
    
    assert(e != nullptr);

    e->EventReporter_delete();

    e->EventReporter_end_instance();

    std::cout << ">> EventReporter_get_instance: 1 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    test1();
}