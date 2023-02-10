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

/*
std::string Scheduler::generate_TaskValidate_msg(ts::TaskValidate code, cl::Config* task_config){
    std::string report_message;
    switch(code){
        case TaskValidate::MISSING_NAME_KEYVAL:
            report_message = "Name key-value pair does not exist in task configuration file.";
            break;
        case TaskValidate::MISSING_SCRIPTFN_KEYVAL:
            report_message = "Script filename key-value pair does not exist in task configuration file.";
            break;
        case TaskValidate::MISSING_FREQUENCY_KEYVAL:
            report_message = "Frequency key-value pair does not exist in task configuration file.";
            break;
        case TaskValidate::SCRIPT_NOT_FOUND:
            report_message = "The task script file associated with the task could not be found in the scripts directory.";
            break;
        case TaskValidate::BAD_FREQUENCY_VALUE:
            report_message = "An invalid Frequency value has been specified in the task configuration file.";
            break;
        case TaskValidate::MISSING_DATETIME_KEYVAL:
            report_message = "Datetime key-value pair does not exist in task configuration file.";
            report_message += "The task Frequency ";
            report_message += task_config->get_value("Frequency")->get_data<std::string>();
            report_message += "requrires it.";
            break;
        case TaskValidate::BAD_DATETIME_VALUE:
            report_message = "An invalid Datetime value has been specified in the task configuration file.";
            break;
        default:
            report_message = "Undefined error.";
            break;
    }
    return report_message;
}
*/

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
    this->task_registry.clear();
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
    std::string report_message;
    Task* t;
    int task_id;

    // Check if tasks directory exists 
    if(!std::filesystem::exists(this->exec_path + "/tasks")){
        report_message = "Could not find tasks directory";
        //this->log_event(EventType::ERROR, report_message);
        //this->publish_last_event();
        return;
    }

    // Check if scripts directory exists 
    if(!std::filesystem::exists(this->exec_path + "/scripts")){
        report_message = "Could not find scripts directory";
        //this->log_event(EventType::ERROR, report_message);
        //this->publish_last_event();
        return;
    }

    for(const auto & file : std::filesystem::directory_iterator(this->exec_path + "/tasks/")){
        task_config = new cl::Config(file.path());
        ret_task_validate = ts::validate_task_parms(task_config, this->exec_path + "/scripts/");
        if(ret_task_validate != TaskValidate::OK){
            //report_message = this->generate_TaskValidate_msg(ret_task_validate, task_config);
            //this->log_event(EventType::ERROR, report_message);
            //this->publish_last_event();
            continue;
        }

        // Get task attributes from config file and validate them, check if task name is repeated
        task_name = task_config->get_value("Name")->get_data<std::string>();
        if (this->task_exists(task_name)) {
            report_message = "A task with the name \"" + task_name + "\" already exists in the scheduler." ;
            //this->log_event(EventType::ERROR, report_message);
            //this->publish_last_event();
            return;
        }

        task_description = task_config->get_value("Description")->get_data<std::string>();
        task_script_name = task_config->get_value("ScriptFilename")->get_data<std::string>();
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
        task_id = this->generate_task_id(t);
        t->set_id(task_id);
        t->set_status(ts::TaskStatus::QUEUED);

        this->task_registry.insert(std::make_pair(task_name, t));
        this->n_tasks++;

        report_message = "Successfully loaded task \"" + task_name + "\".";
        //this->log_event(EventType::INFO, report_message);
        //this->publish_last_event();
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
    std::string err_message;
    Task* t;
    int task_id;

    if(!std::filesystem::exists(this->exec_path + "/tasks")){
        err_message = "Could not find tasks directory";
        //this->log_event(EventType::ERROR, err_message);
        //this->publish_last_event();
        return;
    }

    if(!std::filesystem::exists(this->exec_path + "/scripts")){
        err_message = "Could not find scripts directory";
        //this->log_event(EventType::ERROR, err_message);
        //this->publish_last_event();
        return;
    }

    if(!std::filesystem::exists(this->exec_path + "/tasks/" + task_filename)){
        err_message = "The task file configuration file " + task_filename + "could not be found.";
        //this->log_event(EventType::ERROR, err_message);
        //this->publish_last_event();
        return;
    }

    task_config = new cl::Config(this->exec_path + "/tasks/" + task_filename);
    ret_task_validate = ts::validate_task_parms(task_config, this->exec_path + "/scripts/");
    if(ret_task_validate != TaskValidate::OK){
        //err_message = this->generate_TaskValidate_msg(ret_task_validate, task_config);
        //this->log_event(EventType::ERROR, err_message);
        //this->publish_last_event();
        return;
    }

    // Get task attributes from config file and validate them, check if task name is repeated
    task_name = task_config->get_value("Name")->get_data<std::string>();
    if (this->task_exists(task_name)) {
        err_message = "A task with the name " + task_name + " already exists in the scheduler." ;
        //this->log_event(EventType::ERROR, err_message);
        //this->publish_last_event();
        return;
    }

    task_description = task_config->get_value("Description")->get_data<std::string>();
    task_script_name = task_config->get_value("ScriptFilename")->get_data<std::string>();
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
    task_id = this->generate_task_id(t);
    t->set_id(task_id);
    t->set_status(ts::TaskStatus::QUEUED);

    this->task_registry.insert(std::make_pair(task_name, t));
    this->n_tasks++;
}

void Scheduler::remove_task(std::string& key){
    // Check if key exists in task registry
    if(!this->task_exists(key)){
        std::string err_message = "The task " + key + " does not exist in the scheduler." ;
        //this->log_event(EventType::WARNING, err_message);
        //this->publish_last_event();
        return;
    }
    Task* t = this->task_registry[key];
    // Stop thread if running
    t->stop_thread();
    this->task_registry.erase(key);
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

Task* Scheduler::get_task(std::string& key){
    // Check if key exists in task registry
    if(!this->task_exists(key)){
        std::string err_message = "The task " + key + " does not exist in the scheduler." ;
        //this->log_event(EventType::INFO, err_message);
        //this->publish_last_event();
        return nullptr;
    }
    return this->task_registry[key];
}

} // namespace ts