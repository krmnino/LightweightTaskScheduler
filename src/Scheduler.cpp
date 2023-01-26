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

    return id;
}

void Scheduler::stop_thread(Task* t){
    // If thread is not running, then no need to stop it
    if(!t->get_running_thread_flag()){
        return;
    }
    std::unique_lock<std::mutex> lock(t->mtx);
    t->set_running_thread_flag(false);
    lock.unlock();
    t->cv.notify_one();
    this->thread_collection[t->get_id()].join();
}

void Scheduler::Scheduler_init(void){
    this->n_tasks = 0;
    this->exec_path = "";
}

void Scheduler::Scheduler_delete(void){
    // Delete tasks by iterating through task registry
    for (std::map<std::string, Task*>::iterator it = this->task_registry.begin(); it != this->task_registry.end(); it++) {
        this->stop_thread(it->second);
        delete it->second;
        this->n_tasks--;
    }
    this->task_registry.clear();
    this->thread_collection.clear();
}

void Scheduler::obtain_exec_path(void){
    this->exec_path = std::filesystem::current_path();
}

void Scheduler::load_tasks_from_dir(void){
    cl::Config* task_config;
    ts::TaskValidate ret_task_validate;
    bool valid_task;
    std::string task_name;
    std::string task_description;
    std::string task_script_name;
    std::string task_frequency;
    std::string task_execution_datetime;
    Task* t;

    // Check if tasks directory exists 
    if(!std::filesystem::exists(this->exec_path + "/tasks")){
        // TODO: implement Reporter class
        std::cout << "tasks directory does not exist" << std::endl;
        return;
    }

    // Check if scripts directory exists 
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
        if (this->task_exists(task_name)) {
            // TODO: implement Reporter class
            std::cout << "duplicate name" << std::endl;
            return;
        }

        task_description = task_config->get_value("Description")->get_data<std::string>();
        task_script_name = task_config->get_value("ScriptFilename")->get_data<std::string>();
        // Check if script file associated with task exists
        if(!std::filesystem::exists(this->exec_path + "/scripts/" + task_script_name)){
            // TODO: implement Reporter class
            std::cout << "scripts directory does not exist" << std::endl;
            return;
        }

        task_frequency = task_config->get_value("Frequency")->get_data<std::string>();
        if(task_config->key_exists("Datetime")){
            task_execution_datetime = task_config->get_value("Datetime")->get_data<std::string>();
        }
        delete task_config;

        // An hourly task does not require execution time parameter
        if(task_frequency == "Hourly"){
            t = new Task(task_name, task_description, task_script_name, task_frequency);
        }
        else{
            t = new Task(task_name, task_description, task_script_name, task_frequency, task_execution_datetime);
        }

        // Assign task id to task object
        int task_id = generate_task_id(t);
        t->set_id(task_id);
        t->set_status(ts::TaskStatus::QUEUED);

        this->task_registry.insert(std::make_pair(task_name, t));
        this->thread_collection.insert(std::make_pair(task_id, std::thread(&Scheduler::launch_thread, t)));
        this->n_tasks++;
    }
}

void Scheduler::load_task(std::string& task_filename){
    cl::Config* task_config;
    ts::TaskValidate ret_task_validate;
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

    if(!std::filesystem::exists(this->exec_path + "/tasks/" + task_filename)){
        // TODO: implement Reporter class
        std::cout << "task does not exist in tasks directory" << std::endl;
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
    if (this->task_exists(task_name)) {
        // TODO: implement Reporter class
        std::cout << "duplicate name" << std::endl;
        return;
    }

    task_description = task_config->get_value("Description")->get_data<std::string>();
    task_script_name = task_config->get_value("ScriptFilename")->get_data<std::string>();
    // Check if script file associated with task exists
    if(!std::filesystem::exists(this->exec_path + "/scripts/" + task_script_name)){
        // TODO: implement Reporter class
        std::cout << "scripts directory does not exist" << std::endl;
        return;
    }

    task_frequency = task_config->get_value("Frequency")->get_data<std::string>();
    if(task_config->key_exists("Datetime")){
        task_execution_datetime = task_config->get_value("Datetime")->get_data<std::string>();
    }
    delete task_config;

    // An hourly task does not require execution time parameter
    if(task_frequency == "Hourly"){
        t = new Task(task_name, task_description, task_script_name, task_frequency);
    }
    else{
        t = new Task(task_name, task_description, task_script_name, task_frequency, task_execution_datetime);
    }

    // Assign task id to task object
    int task_id = generate_task_id(t);
    t->set_id(task_id);
    t->set_status(ts::TaskStatus::QUEUED);

    this->task_registry.insert(std::make_pair(task_name, t));
    this->n_tasks++;
}

void Scheduler::remove_task(std::string& key){
    // Check if key exists in task registry
    if(!this->task_exists(key)){
        // TODO: implement Reporter class
        std::cout << "task does not exist" << std::endl;
        return;
    }
    Task* t = this->task_registry[key];
    // Stop thread if running
    this->stop_thread(t);
    this->task_registry.erase(key);
    this->thread_collection.erase(t->get_id());
    delete t;
    this->n_tasks--;
}

bool Scheduler::task_exists(std::string& key){
    std::map<std::string, Task*>::iterator it;
    for (it = this->task_registry.begin(); it != this->task_registry.end(); it++) {
        if(it->first == key){
            return true;
        }
    }
    return false;
}

const std::string& Scheduler::get_current_path(void){
    return this->exec_path;
}

unsigned int Scheduler::get_n_tasks(){
    return this->n_tasks;
}

const Task* Scheduler::get_task(std::string& key){
    // Check if key exists in task registry
    if(!this->task_exists(key)){
        // TODO: implement Reporter class
        std::cout << "task does not exist" << std::endl;
        return nullptr;
    }
    return this->task_registry[key];
}

} // namespace ts