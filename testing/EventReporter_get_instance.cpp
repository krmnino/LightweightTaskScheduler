#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::EventReporter* ts::EventReporter::event_reporter_ptr = nullptr;

int test1(){
    ts::EventReporter* e = ts::EventReporter::EventReporter_get_instance();
    
    assert(e != nullptr);

    e->EventReporter_delete();

    e->EventReporter_end_instance();

    std::cout << ">> EventReporter_get_instance: 1 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    test1();
}