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

Task* Scheduler::get_task_from_registry(std::string& key){
    return this->task_registry[key];
}

void Scheduler::Scheduler_init(EventReporter* er_ptr){
    this->n_tasks = 0;
    this->exec_path = "";
    // Link Event Reporter to Scheduler
    this->event_reporter_ptr = er_ptr;
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
    ts::ValidationCode ret_task_validate;
    bool valid_task;
    std::string task_name;
    std::string task_description;
    std::string task_script_name;
    std::string task_frequency;
    std::string task_execution_datetime;
    std::string event_message;
    std::string task_filename;
    Task* t;
    int task_id;

    // Check if tasks directory exists 
    if(!std::filesystem::exists(this->exec_path + "/tasks")){
        event_message = "Could not find tasks directory.";
        this->event_reporter_ptr->log_event(EventType::ERROR, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }

    // Check if scripts directory exists 
    if(!std::filesystem::exists(this->exec_path + "/scripts")){
        event_message = "Could not find scripts directory.";
        this->event_reporter_ptr->log_event(EventType::ERROR, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }

    for(const auto & file : std::filesystem::directory_iterator(this->exec_path + "/tasks/")){
        task_config = new cl::Config(file.path());
        task_filename = file.path().filename().string();
        ret_task_validate = ts::validate_task_parms(task_config, this->exec_path + "/scripts/");
        if(ret_task_validate != ValidationCode::OK){
            event_message = this->event_reporter_ptr->generate_load_task_msg(ret_task_validate, task_filename, task_config);
            this->event_reporter_ptr->log_event(EventType::ERROR, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
            continue;
        }

        // Get task attributes from config file and validate them, check if task name is repeated
        task_name = task_config->get_value("Name")->get_data<std::string>();
        if (this->task_exists(task_name)) {
            event_message = "A task with the name \"" + task_name + "\" already exists in the scheduler." ;
            this->event_reporter_ptr->log_event(EventType::ERROR, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
            continue;
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

        event_message = "Successfully loaded task \"" + task_name + "\" from \"" + task_filename + "\".";
        this->event_reporter_ptr->log_event(EventType::INFO, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
    }
}

void Scheduler::load_task(std::string& task_filename){
    cl::Config* task_config;
    ts::ValidationCode ret_task_validate;
    std::string task_name;
    std::string task_description;
    std::string task_script_name;
    std::string task_frequency;
    std::string task_execution_datetime;
    std::string event_message;
    Task* t;
    int task_id;

    if(!std::filesystem::exists(this->exec_path + "/tasks")){
        event_message = "Could not find tasks directory.";
        this->event_reporter_ptr->log_event(EventType::ERROR, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }

    if(!std::filesystem::exists(this->exec_path + "/scripts")){
        event_message = "Could not find scripts directory.";
        this->event_reporter_ptr->log_event(EventType::ERROR, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }

    if(!std::filesystem::exists(this->exec_path + "/tasks/" + task_filename)){
        event_message = "The task file configuration file " + task_filename + " could not be found.";
        this->event_reporter_ptr->log_event(EventType::ERROR, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }

    task_config = new cl::Config(this->exec_path + "/tasks/" + task_filename);
    ret_task_validate = ts::validate_task_parms(task_config, this->exec_path + "/scripts/");
    if(ret_task_validate != ValidationCode::OK){
        event_message = this->event_reporter_ptr->generate_load_task_msg(ret_task_validate, task_filename, task_config);
        this->event_reporter_ptr->log_event(EventType::ERROR, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }

    // Get task attributes from config file and validate them, check if task name is repeated
    task_name = task_config->get_value("Name")->get_data<std::string>();
    if (this->task_exists(task_name)) {
        event_message = "A task with the name \"" + task_name + "\" already exists in the scheduler." ;
        this->event_reporter_ptr->log_event(EventType::ERROR, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
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
    t->set_event_reporter_ptr(this->event_reporter_ptr);

    this->task_registry.insert(std::make_pair(task_name, t));
    this->n_tasks++;

    event_message = "Successfully loaded task \"" + task_name + "\" from \"" + task_filename + "\".";
    this->event_reporter_ptr->log_event(EventType::INFO, event_message);
    #ifndef SILENT
    this->event_reporter_ptr->publish_last_event();
    #endif
}

void Scheduler::remove_task(std::string& key){
    // Check if key exists in task registry
    if(!this->task_exists(key)){
        std::string event_message = "The task \"" + key + "\" does not exist in the scheduler." ;
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }
    Task* t = this->task_registry[key];
    // Stop thread if running
    t->stop_thread();
    this->task_registry.erase(key);
    delete t;
    this->n_tasks--;

    std::string event_message = "Successfully removed task \"" + key + "\" from the scheduler.";
    this->event_reporter_ptr->log_event(EventType::INFO, event_message);
    #ifndef SILENT
    this->event_reporter_ptr->publish_last_event();
    #endif
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

void Scheduler::display_registry(void){
    std::map<std::string, Task*>::iterator it;
    Task* t;
    size_t counter = 0;
    int padding;
    std::vector<std::string> header = {"TASK_ID", "NAME", "STATUS", "EXECUTION_DATETIME"};
    std::vector<size_t> field_curr_max_len = {
        header[0].length(), /* TASK ID CURRENT MAX LENGTH */
        header[1].length(), /* TASK NAME CURRENT MAX LENGTH */
        header[2].length(), /* TASK STATUS CURRENT MAX LENGTH */
        header[3].length(), /* Task EXECUTION DATETIME CURRENT MAX LENGTH */
    };
    std::vector<std::string> task_ids;
    std::vector<std::string> task_names;
    std::vector<std::string> task_statuses;
    std::vector<std::string> task_exec_dates;

    /* Loop through all tasks in the scheduler and collect all their attributes to be printed */
    for (it = this->task_registry.begin(); it != this->task_registry.end(); it++) {
        t = it->second;
        
        /* Collect task id attribute */
        task_ids.push_back(std::to_string(t->get_id()));
        /* Update maximum field length for pretty print */
        field_curr_max_len[0] = std::max(field_curr_max_len[0], task_ids[counter].length());
        field_curr_max_len[0] = std::min(field_curr_max_len[0], TASK_ID_FIELD_MAX_LEN);

        /* Collect task name attribute */
        task_names.push_back(t->get_name());
        /* Update maximum field length for pretty print */
        field_curr_max_len[1] = std::max(field_curr_max_len[1], task_names[counter].length());
        field_curr_max_len[1] = std::min(field_curr_max_len[1], TASK_NAME_FIELD_MAX_LEN);

        /* Collect task status attribute */
        switch(t->get_status()){
        case ts::TaskStatus::FINISHED:
            task_statuses.push_back("FINISHED");
            break;
        case ts::TaskStatus::INIT_ERROR:
            task_statuses.push_back("INIT_ERROR");
            break;
        case ts::TaskStatus::EXEC_ERROR:
            task_statuses.push_back("EXEC_ERROR");
            break;
        case ts::TaskStatus::QUEUED:
            task_statuses.push_back("QUEUED");
            break;
        case ts::TaskStatus::RUNNING:
            task_statuses.push_back("RUNNING");
            break;
        default:
            task_statuses.push_back("UNDEFINED");
            break;
        }
        /* Update maximum field length for pretty print */
        field_curr_max_len[2] = std::max(field_curr_max_len[2], task_statuses[counter].length());
        field_curr_max_len[2] = std::min(field_curr_max_len[2], TASK_EXEC_DATE_FIELD_MAX_LEN);

        /* Collect task execution datetime attribute */
        task_exec_dates.push_back(t->get_execution_datetime_fmt());
        /* Update maximum field length for pretty print */
        field_curr_max_len[3] = std::max(field_curr_max_len[3], task_exec_dates[counter].length());
        field_curr_max_len[3] = std::min(field_curr_max_len[3], TASK_EXEC_DATE_FIELD_MAX_LEN);

        counter++;
    }

    /* Add padding for header */
    for(size_t i = 0; i < header.size(); i++){
        padding = field_curr_max_len[i] - header[i].length();
        if(padding <= 0){
            padding = 0;
        }
        for(size_t j = 0; j < padding; j++){
            header[i] += " ";
        }
        if(i == header.size() - 1){
            std::cout << header[i];
        }
        else{
            std::cout << header[i] << " | ";
        }
    }
    std::cout << std::endl;

    /* Generate delimiter between header and table body */
    for(size_t i = 0; i < header.size(); i++){
        std::string delim = "";
        for(size_t j = 0; j < header[i].length(); j++){
            delim += "-";
        }
        if(i == header.size() - 1){
            std::cout << delim;
        }
        else{
            std::cout << delim << "-+-";
        }
    }
    std::cout << std::endl;

    /* Add padding task attributes */
    for(size_t i = 0; i < counter; i++){
        padding = field_curr_max_len[0] - task_ids[i].length();
        if(padding <= 0){
            padding = 0;
        }
        for(size_t j = 0; j < padding; j++){
            task_ids[i] += " ";
        }

        if(task_names[i].length() > TASK_NAME_FIELD_MAX_LEN){
            // Cap task name to 29 characters and add ellipsis at the end of it
            task_names[i] = task_names[i].substr(0, TASK_NAME_FIELD_MAX_LEN - 3) + "...";
        }   
        else{
            // Otherwise, check if padding is needed
            padding = field_curr_max_len[1] - task_names[i].length();
            if(padding <= 0){
                padding = 0;
            }
            for(size_t j = 0; j < padding; j++){
                task_names[i] += " ";
            }
        } 

        padding = field_curr_max_len[2] - task_statuses[i].length();
        if(padding <= 0){
            padding = 0;
        }
        for(size_t j = 0; j < padding; j++){
            task_statuses[i] += " ";
        }

        padding = field_curr_max_len[3] - task_exec_dates[i].length();
        if(padding <= 0){
            padding = 0;
        }
        for(size_t j = 0; j < padding; j++){
            task_exec_dates[i] += " ";
        }

        std::cout << task_ids[i] << " | " << task_names[i] << " | " << task_statuses[i] << " | " << task_exec_dates[i] << std::endl;
    }
}

void Scheduler::display_task(std::string& key){
    const Task* t;
    std::string task_id;
    std::string task_name;
    std::string task_description;
    std::string task_creation_datetime;
    std::string task_execution_datetime;
    std::string task_frequency;
    std::string task_status;
    if(!this->task_exists(key)){
        std::string event_message = "The task \"" + key + "\" does not exist in the scheduler." ;
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }
    t = this->get_task(key);
    task_id = std::to_string(t->get_id());
    task_name = t->get_name();
    task_description = t->get_description();
    task_creation_datetime = t->get_creation_datetime_fmt();
    task_execution_datetime = t->get_execution_datetime_fmt();
    task_frequency = t->get_frequency();
    switch(t->get_status()){
    case ts::TaskStatus::FINISHED:
        task_status = "FINISHED";
        break;
    case ts::TaskStatus::INIT_ERROR:
        task_status = "INIT_ERROR";
        break;
    case ts::TaskStatus::EXEC_ERROR:
        task_status = "EXEC_ERROR";
        break;
    case ts::TaskStatus::QUEUED:
        task_status = "QUEUED";
        break;
    case ts::TaskStatus::RUNNING:
        task_status = "RUNNING";
        break;
    default:
        task_status = "UNDEFINED";
        break;
    }
    std::cout << "-TASK ID: " << task_id << std::endl;
    std::cout << "-TASK NAME: " << task_name << std::endl;
    std::cout << "-TASK DESCRIPTION: " << task_description << std::endl;
    std::cout << "-TASK CREATION DATETIME: " << task_creation_datetime << std::endl;
    std::cout << "-TASK EXECUTION DATETIME: " << task_execution_datetime << std::endl;
    std::cout << "-TASK FREQUENCY: " << task_frequency << std::endl;
    std::cout << "-TASK STATUS: " << task_status << std::endl;
}

const std::string& Scheduler::get_current_path(void){
    return this->exec_path;
}

unsigned int Scheduler::get_n_tasks(){
    return this->n_tasks;
}

const Task* Scheduler::get_task(std::string& key) const{
    // Check if key exists in task registry
    if(!const_cast<Scheduler*>(this)->task_exists(key)){
        std::string event_message = "The task \"" + key + "\" does not exist in the scheduler." ;
        this->event_reporter_ptr->log_event(EventType::INFO, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return nullptr;
    }
    return const_cast<Scheduler*>(this)->get_task_from_registry(key);
}

} // namespace ts