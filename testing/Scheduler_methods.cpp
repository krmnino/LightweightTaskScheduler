#include <assert.h>
#include <iostream>
#include <filesystem>
#include <cstdio>

#include "../src/Task.hpp"
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


int test3(ts::Scheduler* s){
    // TEST 3: load tasks from tasks directory with Scheduler::load_tasks_from_dir()
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    s->Scheduler_init();

    s->obtain_exec_path();
    s->load_tasks_from_dir();
    assert(s->get_n_tasks() == 2);

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 3 done" << std::endl;
    return 0;
}


int test4(ts::Scheduler* s){
    // TEST 4: load a single task from tasks directory with Scheduler::load_task()
    std::string task_config_fn = "cat_test.cl";

    s->Scheduler_init();

    s->obtain_exec_path();
    s->load_task(task_config_fn);
    assert(s->get_n_tasks() == 1);

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 4 done" << std::endl;
    return 0;
}


int test5(ts::Scheduler* s){
    // TEST 5: remove one task from scheduler after loading tasks from tasks directory
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    // Task to be removed: cat
    std::string t_name = "cat";

    s->Scheduler_init();

    s->obtain_exec_path();
    s->load_tasks_from_dir();
    assert(s->get_n_tasks() == 2);

    s->remove_task(t_name);
    assert(!s->task_exists(t_name));
    assert(s->get_n_tasks() == 1);

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 5 done" << std::endl;
    return 0;
}


int test6(ts::Scheduler* s){
    // TEST 6: remove two tasks from scheduler after loading tasks from tasks directory
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    // Task to be removed: cat and ls
    std::string t_name1 = "cat";
    std::string t_name2 = "ls";

    s->Scheduler_init();

    s->obtain_exec_path();
    s->load_tasks_from_dir();
    assert(s->get_n_tasks() == 2);

    s->remove_task(t_name1);
    assert(!s->task_exists(t_name1));
    assert(s->get_n_tasks() == 1);

    s->remove_task(t_name2);
    assert(!s->task_exists(t_name2));
    assert(s->get_n_tasks() == 0);

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 6 done" << std::endl;
    return 0;
}


int test7(ts::Scheduler* s){
    // TEST 7: search for a task that does not exist in Scheduler
    std::string t_name = "any_name";

    s->Scheduler_init();

    assert(!s->task_exists(t_name));

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 7 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();

    test1(s);
    test2(s);
    test3(s);
    test4(s);
    test5(s);
    test6(s);
    test7(s);

    s->Scheduler_end_instance();
}