#include <assert.h>
#include <iostream>

#include "../src/EventReporter.hpp"

ts::EventReporter* ts::EventReporter::event_reporter_ptr = nullptr;

int test1(){
    ts::EventReporter* s = ts::EventReporter::EventReporter_get_instance();
    
    assert(s != nullptr);

    s->EventReporter_delete();

    s->EventReporter_end_instance();

    std::cout << ">> EventReporter_get_instance: 1 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    test1();
}