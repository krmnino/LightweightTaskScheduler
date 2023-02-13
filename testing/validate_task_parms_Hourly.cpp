#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"

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
    for(int i = 0; i < datetimes.size(); i++){
        cl::Config* c = new cl::Config();
        c->add_entry("Name", "Test Title");
        c->add_entry("Description", "A short description");
        c->add_entry("ScriptFilename", "ls_test.sh");
        c->add_entry("Frequency", "Hourly");
        c->add_entry("Datetime", datetimes[i]);

        ts::TaskValidate ret = ts::validate_task_parms(c, "scripts/");

        assert(ret == ts::TaskValidate::OK);

        delete c;
    }

    std::cout << ">> validate_task_parms_Hourly: 1 done" << std::endl;
    return 0;
}


int main(){
    test1();
}