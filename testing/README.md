# **Light-weight Task Scheduler - Testing**
This directory contains unit tests for all specific functions, classes and its methods to verify the appropiate execution and handling of different cases (and edge-cases).

---
## **Organization**
The `/testing` directory contains exclusive test-related source files. That includes:
- **\*.cpp:** testcase implementation source files
- **Makefile:** contains rules to compile testcase builds
- **RunTests.sh:** a bash scripts that runs testcase builds
- **`scripts` directory:** contains Bash shell files required by certain testcases
- **`tasks` directory:** contains configuration files required by certain testcases

---
## **Tests**
### **1. Task_constructor.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify Task object instantiation with constructor|`Task(std::string, std::string, std::string, std::string)`<br/>`Task::get_name()`<br/> `Task::get_description()`<br/>`Task::get_script_name()`<br/>`Task::get_frequency()` |<span style="color:green">Passed|
|`test2()`|Verify Task object instantiation with constructor|`Task(std::string, std::string, std::string, std::string, std::string)`<br/>`Task::get_name()`<br/> `Task::get_description()`<br/>`Task::get_script_name()`<br/>`Task::get_frequency()` |<span style="color:green">Passed|

### **2. Task_methods.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Obtain the `time_t` value when `Task` is created|`Task::get_creation_datetime()`|<span style="color:green">Passed|
|`test2()`|Obtain system's current time + 5 seconds for `Task`'s execution time parameter. Then, verify the returned `time_t` time of execution value.|`Task::get_execution_datetime()`|<span style="color:green">Passed|
|`test3()`|Obtain formated time of creation `string` value|`Task::get_creation_datetime_fmt()`|<span style="color:green">Passed|
|`test4()`|Obtain formated time of execution `string` value|`Task::get_creation_datetime_fmt()`|<span style="color:green">Passed|
|`test5()`|Obtain system's current time + 5 seconds for `Task`'s execution time parameter in `HH:MM:SS` format. Then, verify the returned `DatetimeFormat` value|`Task::get_execution_datetime_format_attr()`|<span style="color:green">Passed|
|`test6()`|Set and get task id and status values|`Task::set_id()`<br/>`Task::get_id()`<br/>`Task::set_status()`<br/>`Task::get_status()`<br/>|<span style="color:green">Passed|
|`test7()`|Create `Task` object and run it. Then, verify that the command-line output has been successfully routed to output data member|`Task::run_task()`<br/>`Task::get_output()`<br/>|<span style="color:green">Passed|

### **3. validate_hms.cpp**

### **4. validate_wday.cpp**

### **5. validate_wday_hms.cpp**
### **6. validate_mmdd.cpp**
### **7. validate_mmdd_hms.cpp**
### **8. validate_yyyymmdd.cpp**
### **9. validate_yyyymmdd_hms.cpp**
### **10. init_today.cpp**
### **11. init_year.cpp**
### **12. today_add_hms.cpp**
### **13. today_add_dhms.cpp**
### **14. today_add_wday_hms.cpp**
### **15. today_add_mmdd.cpp**
### **15. today_add_mmdd_hms.cpp**
