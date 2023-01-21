#include "Scheduler.hpp"

namespace ts{

unsigned int Scheduler::generate_task_id(Task* task){
    // Get task attributes
    std::string task_name = task->get_name();
    std::string task_description = task->get_description();
    std::string task_script_filename = task->get_script_filename();
    std::string task_frequency = task->get_frequency();
    std::string task_creation_datetime_fmt = task->get_creation_datetime_fmt();

    // Get attribute string lengths
    int task_name_len = task_name.length();
    int task_description_len = task_description.length();
    int task_script_filename_len = task_script_filename.length();
    int task_frequency_len = task_frequency.length();
    int task_creation_datetime_fmt_len = task_creation_datetime_fmt.length();

    unsigned int acc_seed = 0;
    unsigned int id;

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

    acc_seed += (int)task->get_execution_datetime_format_attr() % 255;

    #ifndef DEBUG
    // Set seed and generate id
    srand(acc_seed);
    id = rand();
    #else
    id = acc_seed;
    #endif

    // If task id exists, then increase it by one until unique id is found
    while(true){
        std::map<unsigned int, std::thread>::const_iterator it = this->thread_collection.find(id);
        if (it == this->thread_collection.end()) {
            break;
        }
        id++;
    }

    return id;
}

void Scheduler::Scheduler_init(void){
    this->n_tasks = 0;
    this->exec_path = "";
}

void Scheduler::Scheduler_delete(void){
    // Delete tasks by iterating through task registry
    for (std::map<std::string, Task*>::iterator it = this->task_registry.begin(); it != this->task_registry.end(); it++) {
        delete it->second;
        this->n_tasks--;
    }
}

void Scheduler::obtain_exec_path(void){
    this->exec_path = std::filesystem::current_path();
}

void Scheduler::launch_task_thread(std::string& task_name){
    Task* task = this->task_registry[task_name];
    std::function<void(void)> run_task_fn = [&]{task->run_task();};
    auto key_thread = std::make_pair(task->get_id(), [task](){
        while(true){
            // Get task scheduled execution time 
            time_t execution_datetime = task->get_execution_datetime(false);
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

void Scheduler::load_tasks_from_dir(void){
    cl::Config* task_config;
    ts::TaskValidate ret_task_validate;
    std::map<std::string, Task*>::const_iterator task_dir_itr;
    bool valid_task;
    std::string task_name;
    std::string task_description;
    std::string task_script_name;
    std::string task_frequency;
    std::string task_execution_datetime;
    Task* t;

    if(!std::filesystem::exists(this->exec_path + "/tasks")){
        // TODO: implement Reporter class
        std::cout << "tasks directory does not exist" << std::endl;
        return;
    }

    if(!std::filesystem::exists(this->exec_path + "/scripts")){
        // TODO: implement Reporter class
        std::cout << "scripts directory does not exist" << std::endl;
        return;
    }

    for(const auto & file : std::filesystem::directory_iterator(this->exec_path + "/tasks/")){
        task_config = new cl::Config(file.path());
        ret_task_validate = ts::validate_task_parms(task_config, this->exec_path + "/scripts/");
        if(ret_task_validate != TaskValidate::OK){
            // TODO: implement Reporter class
            std::cout << "invalid config" << std::endl;
            continue;
        }

        // Get task attributes from config file and validate them, check if task name is repeated
        task_name = task_config->get_value("Name")->get_data<std::string>();
        task_dir_itr = this->task_registry.find(task_name);
	    if (task_dir_itr != this->task_registry.end()) {
            // TODO: implement Reporter class
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
        this->n_tasks++;
    }
}

void Scheduler::load_task(std::string& task_filename){
    cl::Config* task_config;
    ts::TaskValidate ret_task_validate;
    std::map<std::string, Task*>::const_iterator task_dir_itr;
    std::string task_name;
    std::string task_description;
    std::string task_script_name;
    std::string task_frequency;
    std::string task_execution_datetime;
    Task* t;

    if(!std::filesystem::exists(this->exec_path + "/tasks")){
        // TODO: implement Reporter class
        std::cout << "tasks directory does not exist" << std::endl;
        return;
    }

    if(!std::filesystem::exists(this->exec_path + "/scripts")){
        // TODO: implement Reporter class
        std::cout << "scripts directory does not exist" << std::endl;
        return;
    }

    task_config = new cl::Config(this->exec_path + "/tasks/" + task_filename);
    ret_task_validate = ts::validate_task_parms(task_config, this->exec_path + "/scripts/");
    if(ret_task_validate != TaskValidate::OK){
        // TODO: implement Reporter class
        std::cout << "invalid config" << std::endl;
        return;
    }

    // Get task attributes from config file and validate them, check if task name is repeated
    task_name = task_config->get_value("Name")->get_data<std::string>();
    task_dir_itr = this->task_registry.find(task_name);
    if (task_dir_itr != this->task_registry.end()) {
        // TODO: implement Reporter class
        std::cout << "duplicate name" << std::endl;
        return;
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
    this->n_tasks++;
}

void Scheduler::remove_task(std::string& key){
    Task* t;
    std::map<std::string, Task*>::iterator it;
    for (it = this->task_registry.begin(); it != this->task_registry.end(); it++) {
        if(it->first == key){
            break;
        }
    }
    if(it == this->task_registry.end()){
        std::cout << "task does not exist" << std::endl;
        return;
    }
    t = it->second;
    this->task_registry.erase(key);
    this->thread_collection.erase(t->get_id());
    delete t;
}

const std::string& Scheduler::get_current_path(void){
    return this->exec_path;
}

unsigned int Scheduler::get_n_tasks(){
    return this->n_tasks;
}

} // namespace ts