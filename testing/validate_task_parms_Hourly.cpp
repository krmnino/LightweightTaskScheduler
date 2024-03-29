#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: testing validate_task_parms() function -> PASS
    // Ignored datetime value with Frequency = Hourly

    std::vector<std::string> datetimes = {
        "12:30:00",
        "01-20 12:30:00",
        "2022-01-20 12:30:00",
        "Monday 12:30:00",
        "01-20",
        "2022-01-20",
        "anything"
    };
    for(size_t i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Hourly");
        c->add_entry("Datetime", datetimes[i]);

        ts::ValidationCode ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::ValidationCode::OK);

        delete c;
    }

    std::cout << ">> validate_task_parms_Hourly: 1 done" << std::endl;
    return 0;
}


int main(){
    test1();
}