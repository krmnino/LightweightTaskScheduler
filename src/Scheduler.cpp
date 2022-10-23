#include "Scheduler.hpp"

namespace ts{

Scheduler::Scheduler(std::string& top_level_dir, std::string& tasks_dir, std::string& scripts_dir){
    this->top_level_dir = top_level_dir;
    this->tasks_dir = tasks_dir;
    this->scripts_dir = scripts_dir;

    cl::Config* task_config;
    bool valid_task;
    std::string task_name;
    std::string task_description;
    std::string task_script_name;
    std::string task_frequency;
    std::string task_execution_datetime;
    Task* t;
    for(const auto & file : std::filesystem::directory_iterator(this->top_level_dir + this->tasks_dir)){
        task_config = new cl::Config(file.path());
        if(ts::validate_task_parms(task_config, this->top_level_dir + this->scripts_dir) != TaskValidate::OK){
            std::cout << "invalid config" << std::endl;
        }

        // Get task attributes from config file and validate them, check if task name is repeated
        task_name = task_config->get_value("Name")->get_data<std::string>();
        std::map<std::string, Task*>::const_iterator it = this->task_registry.find(task_name);
	    if (it != this->task_registry.end()) {
		    std::cout << "duplicate name" << std::endl;
            continue;
	    }

        task_description = task_config->get_value("Description")->get_data<std::string>();
        task_frequency = task_config->get_value("Frequency")->get_data<std::string>();
        if(task_config->key_exists("Datetime")){
            task_execution_datetime = task_frequency = task_config->get_value("Datetime")->get_data<std::string>();
        }
        delete task_config;

        // An hourly task does not require execution time parameter
        if(task_frequency == "Hourly"){
            t = new Task(task_name, task_description, task_frequency, task_frequency);
        }
        else{
            t = new Task(task_name, task_description, task_frequency, task_frequency, task_execution_datetime);
        }

        // Assign task id to task object
        int task_id = generate_task_id(t);
        t->set_id(task_id);

        t->set_status(ts::TaskStatus::QUEUED);

        this->task_registry.insert(std::make_pair(task_name, t));
    }
}

Scheduler::Scheduler(){
    this->n_tasks = 0;
    this->top_level_dir = "";
    this->tasks_dir = "";
    this->scripts_dir = "";
}

Scheduler::~Scheduler(){
    // delete tasks from task registry
}

void Scheduler::launch_task_thread(std::string& task_name){
    Task* task = this->task_registry[task_name];
    std::function<void(void)> run_task_fn = [&]{task->run_task();};
    auto key_thread = std::make_pair(task->get_id(), [task](){
        while(true){
            // Get task scheduled execution time 
            time_t execution_datetime = task->get_execution_datetime();
            // Convert time_t to std::chrono::system_clock::time_point and put thread to sleep until then
            std::this_thread::sleep_until(std::chrono::system_clock::from_time_t(execution_datetime));
            // Update next execution time based on frequency
            task->update_execution_datetime();
            
            // Before running task, update its status
            task->set_status(TaskStatus::RUNNING);
            
            // Run the task
            task->run_task();

            // If task frequency is Once, then it is finished
            if(task->get_frequency() == "Once"){
                task->set_status(TaskStatus::FINISHED);
            }
            else{
                // Otherwise, set it to queued status again
                task->set_status(TaskStatus::QUEUED);
            }
        }
    });
    // Add task name - thread pair to thread collection map
    this->thread_collection.insert(key_thread);
}

int Scheduler::generate_task_id(Task* task){
    // Get task attributes
    std::string task_name = task->get_name();
    std::string task_description = task->get_description();
    std::string task_script_filename = task->get_script_filename();
    std::string task_frequency = task->get_frequency();
    std::string task_creation_datetime_fmt = task->get_creation_datetime_fmt();
    std::string task_input_execution_datetime = task->get_input_execution_datetime();

    // Get attribute string lengths
    int task_name_len = task_name.length();
    int task_description_len = task_description.length();
    int task_script_filename_len = task_script_filename.length();
    int task_frequency_len = task_frequency.length();
    int task_creation_datetime_fmt_len = task_creation_datetime_fmt.length();
    int task_input_execution_datetime_len = task_input_execution_datetime.length();

    unsigned int acc_seed = 0;

    // Add string char values and lengths together to create seed
    for(int i = 0; i < task_name_len; i++){
        acc_seed += (unsigned int)task_name.at(i);
    }
    acc_seed += task_name_len;

    for(int i = 0; i < task_description_len; i++){
        acc_seed += (unsigned int)task_description.at(i);
    }
    acc_seed += task_description_len;

    for(int i = 0; i < task_script_filename_len; i++){
        acc_seed += (unsigned int)task_script_filename.at(i);
    }
    acc_seed += task_script_filename_len;

    for(int i = 0; i < task_frequency_len; i++){
        acc_seed += (unsigned int)task_frequency.at(i);
    }
    acc_seed += task_frequency_len;

    for(int i = 0; i < task_creation_datetime_fmt_len; i++){
        acc_seed += (unsigned int)task_creation_datetime_fmt.at(i);
    }
    acc_seed += task_creation_datetime_fmt_len;

    for(int i = 0; i < task_input_execution_datetime_len; i++){
        acc_seed += (unsigned int)task_input_execution_datetime.at(i);
    }
    acc_seed += task_input_execution_datetime_len;

    // Set seed and generate id
    srand(acc_seed);
    int id = rand();

    // If task id exists, then increase by one until unique id is found
    while(true){
        std::map<int, std::thread>::const_iterator it = this->thread_collection.find(id);
        if (it == this->thread_collection.end()) {
            break;
        }
        id++;
    }

    return id;
}

void Scheduler::run(){
    std::string input;
    while(true){
        std::cout << ">> ";
        std::cin >> input;
        if(input == "exit"){
            break;
        }
        else if(input == "help"){
            break;
        }
    }
}

void Scheduler::help(){
    std::cout << "exit: Close the program." << std::endl;
    std::cout << "help: Display this menu." << std::endl;
}

} // namespace ts