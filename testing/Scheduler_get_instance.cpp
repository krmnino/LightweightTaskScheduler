#include <assert.h>
#include <iostream>

#include "../src/Scheduler.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    lts::Scheduler* s = lts::Scheduler::Scheduler_get_instance();
    
    assert(s != nullptr);

    s->Scheduler_delete();

    s->Scheduler_end_instance();

    std::cout << ">> Scheduler_get_instance: 1 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    test1();
}