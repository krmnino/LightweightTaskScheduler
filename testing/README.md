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
|`test1()`|Verify Task object instantiation with constructor.|`Task(std::string, std::string, std::string, std::string)`<br/>`Task::get_name(void)`<br/> `Task::get_description(void)`<br/>`Task::get_script_name(void)`<br/>`Task::get_frequency(void)` |<span style="color:green">Passed|
|`test2()`|Verify Task object instantiation with constructor.|`Task(std::string, std::string, std::string, std::string, std::string)`<br/>`Task::get_name(void)`<br/> `Task::get_description(void)`<br/>`Task::get_script_name(void)`<br/>`Task::get_frequency(void)` |<span style="color:green">Passed|

### **2. Task_methods.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Obtain the `time_t` value when `Task` is created.|`Task::get_creation_datetime(bool)`|<span style="color:green">Passed|
|`test2()`|Obtain system's current time + 5 seconds for `Task`'s execution time parameter. Then, verify the returned `time_t` time of execution value.|`Task::get_execution_datetime(bool)`|<span style="color:green">Passed|
|`test3()`|Obtain formated time of creation `string` value.|`Task::get_creation_datetime_fmt(void)`|<span style="color:green">Passed|
|`test4()`|Obtain formated time of execution `string` value.|`Task::get_execution_datetime_fmt(void)`|<span style="color:green">Passed|
|`test5()`|Obtain system's current time + 5 seconds for `Task`'s execution time parameter in `HH:MM:SS` format. Then, verify the returned `DatetimeFormat` value.|`Task::get_execution_datetime_format_attr(void)`|<span style="color:green">Passed|
|`test6()`|Set and get task id and status values.|`Task::set_id(int)`<br/>`Task::get_id(void)`<br/>`Task::set_status(TaskStatus)`<br/>`Task::get_status(void)`<br/>|<span style="color:green">Passed|
|`test7()`|Create `Task` object and run it. Then, verify that the command-line output has been successfully routed to output data member.|`Task::run_task(void)`<br/>`Task::get_output(void)`<br/>|<span style="color:green">Passed|

### **3. validate_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass a valid `HH:MM:SS` string.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass an invalid `HH:MM:SS` string with missing `SS` field.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass an invalid `HH:MM:SS` string with alphabetic character in `HH` field.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass an invalid `HH:MM:SS` string with alphabetic character in `MM` field.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass an invalid `HH:MM:SS` string with alphabetic character in `SS` field.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass an invalid `HH:MM:SS` string with `HH` field out of range.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test7()`|Pass an invalid `HH:MM:SS` string with `MM` field out of range.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test8()`|Pass an invalid `HH:MM:SS` string with `SS` field out of range.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test9()`|Pass an invalid `HH:MM:SS` string with missing first colon.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test10()`|Pass an invalid `HH:MM:SS` string with missing second colon.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test11()`|Pass an invalid `HH:MM:SS` string with missing `:MM:SS` fields.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test12()`|Pass an invalid `HH:MM:SS` string with bad length and all alphabetic characters.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test13()`|Pass an invalid `HH:MM:SS` string with valid length and all alphabetic characters.|`validate_hms(std::string)`|<span style="color:green">Passed|

### **4. validate_wday.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid full week day names.|`validate_wday(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass valid abbreviated week day names.|`validate_wday(std::string)`|<span style="color:green">Passed|
|`test3()`|Invalid week day name.|`validate_hms(std::string)`|<span style="color:green">Passed|

### **5. validate_wday_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid full week day names and `HH:MM:SS` string.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass valid abbreviated week day names and `HH:MM:SS` string.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `WDAY HH:MM:SS` string with missing space.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `WDAY HH:MM:SS` string with bad `WDAY` field.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `WDAY HH:MM:SS` string with bad `HH:MM:SS` field.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|

### **6. validate_mmdd.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid `MM-DD` strings, lower and upper bound days for each month.|`validate_mmdd(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass invalid `MM-DD` string with bad length.|`validate_mmdd(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `MM-DD` strings: bad `MM` field and bad `DD` field.|`validate_mmdd(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `MM-DD` string with missing dash.|`validate_mmdd(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `MM-DD` string with `MM` field out of range.|`validate_mmdd(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass invalid `MM-DD` string with `MM` field out of range.|`validate_mmdd(std::string)`|<span style="color:green">Passed|
|`test7()`|Pass invalid `MM-DD` string with `DD` field out of range.|`validate_mmdd(std::string)`|<span style="color:green">Passed|

### **7. validate_mmdd_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid `MM-DD HH:MM:SS` string.|`validate_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass invalid `MM-DD HH:MM:SS` string with missing space.|`validate_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `MM-DD HH:MM:SS` string with `MM` out of range.|`validate_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `MM-DD HH:MM:SS` string with `DD` out of range.|`validate_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `MM-DD HH:MM:SS` string with `HH` out of range.|`validate_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass invalid `MM-DD HH:MM:SS` string with `MM` out of range.|`validate_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test7()`|Pass invalid `MM-DD HH:MM:SS` string with `SS` out of range.|`validate_mmdd_hms(std::string)`|<span style="color:green">Passed|

### **8. validate_yyyymmdd.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid `YYYY-MM-DD` strings, lower and upper bound days for each month.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass invalid `YYYY-MM-DD` string with bad length.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `YYYY-MM-DD` strings: bad `YYYY` field, bad `MM` field, and bad `DD` field.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `YYYY-MM-DD` strings with misplaced dashes.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `YYYY-MM-DD` string with `MM` out of range.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass invalid `YYYY-MM-DD` string with `DD` out of range.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|

### **9. validate_yyyymmdd_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid `YYYY-MM-DD HH:MM:SS` string.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with missing space.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `YYYY-MM-DD HH:MM:SS` strings: alphabetic character in `YYYY-MM-DD` section, and alphabetic character in `HH:MM:SS` section.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `YYYY-MM-DD HH:MM:SS` strings with missing dash characters.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `YYYY-MM-DD HH:MM:SS` strings with missing colon characters.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|

### **10. init_today.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify that `init_today()` returns the correct `time_t` value that corresponds to the very beginning of the current day in UTC time.|`init_today()`|<span style="color:green">Passed|

### **11. init_year.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify that `init_year()` returns the correct `time_t` value that corresponds to the very beginning of the current year in UTC time.|`init_year()`|<span style="color:green">Passed|

### **12. today_add_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one minute in seconds to input `HH:MM:SS` string. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Subtract one minute in seconds to input `HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_hms(std::string)`|<span style="color:green">Passed|

### **13. today_add_dhms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one minute in seconds to input `HH:MM:SS` string and zero days. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test2()`|Add one minute in seconds to input `HH:MM:SS` string and two days. Call should succeed and return `time_t` with a value two days and one minute in the future.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test3()`|Subtract one minute in seconds to input `HH:MM:SS` string and zero days. Call should fail and return `time_t` with a value of zero.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass negative value for days parameter. Call should fail and return `time_t` with a value of zero.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_dhms(std::string)`|<span style="color:green">Passed|

### **14. today_add_wday_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify week day full name. Add one minute in seconds to input `HH:MM:SS` section. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Verify week day abbreviated name. Add one minute in seconds to input `HH:MM:SS` section. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Subtract 24 hours from current time to obtain previous week day name; then, use this week day as input for the function. Call should succeed and return `time_t` with a value 6 days into the future.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid string input with bad `HH:MM:SS` section. Call should fail and return `time_t` with a value of zero.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid string input with bad `WDAY` section. Call should fail and return `time_t` with a value of zero.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|

### **15. today_add_mmdd.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one day in seconds to input `MM-DD` string. Call should succeed and return `time_t` with a value of one day in the future.|`today_add_mmdd(std::string)`|<span style="color:green">Passed|
|`test2()`|Subtract one day in seconds to input `MM-DD` string. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `MM-DD` string with missing dash. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `MM-DD` string with `DD` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `MM-DD` string with `MM` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass `MM-DD` string indicating the current date. This call should fail because the returned `time_t` value is equivalent to the `MM-DD` date at `00:00:00` UTC. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd(std::string)`|<span style="color:green">Passed|

### **16. today_add_mmdd_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add 60 seconds in seconds to input `MM-DD HH:MM:SS` string. Call should succeed and return `time_t` with a value of 60 seconds into the future.|`today_add_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Add one day seconds in seconds to input `MM-DD HH:MM:SS` string. Call should succeed and return `time_t` with a value of one day into the future.|`today_add_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Subtract one day in seconds to input `MM-DD HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `MM-DD HH:MM:SS` string with bad `MM-DD` field. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `MM-DD HH:MM:SS` string with bad `HH:MM:SS` field. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass invalid `MM-DD HH:MM:SS` string with `DD` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test7()`|Pass invalid `MM-DD HH:MM:SS` string with `MM` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test8()`|Pass invalid `MM-DD HH:MM:SS` string with `HH` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test9()`|Pass invalid `MM-DD HH:MM:SS` string with `MM` (minutes) field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd_hms(std::string)`|<span style="color:green">Passed|
|`test10()`|Pass invalid `MM-DD HH:MM:SS` string with `SS` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_mmdd_hms(std::string)`|<span style="color:green">Passed|

### **17. today_add_yyyymmdd.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one day in seconds to input `YYYY-MM-DD` string. Call should succeed and return `time_t` with a value of one day into the future.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test2()`|Add 30 days in seconds to input `YYYY-MM-DD` string. Call should succeed and return `time_t` with a value of 30 days into the future.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test3()`|Add 365 days in seconds to input `YYYY-MM-DD` string. Call should succeed and return `time_t` with a value of 365 days into the future.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test4()`|Subtract one day in seconds to input `YYYY-MM-DD` string. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `YYYY-MM-DD` string with missing dashes. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass invalid `YYYY-MM-DD` string with `MM` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test7()`|Pass invalid `YYYY-MM-DD` string with `DD` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|

### **18. today_add_yyyymmdd_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one day in seconds to input `YYYY-MM-DD HH:MM:SS` string. Call should succeed and return `time_t` with a value of one day into the future.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Add 30 days in seconds to input `YYYY-MM-DD HH:MM:SS` string. Call should succeed and return `time_t` with a value of 30 days into the future.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Add 365 days in seconds to input `YYYY-MM-DD HH:MM:SS` string. Call should succeed and return `time_t` with a value of 365 days into the future.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Add 60 seconds to input `YYYY-MM-DD HH:MM:SS` string. Call should succeed and return `time_t` with a value of 60 seconds into the future.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Subtract one day in seconds to input `YYYY-MM-DD HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass invalid `YYYY-MM-DD  HH:MM:SS` string with missing dashes. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test7()`|Pass invalid `YYYY-MM-DD  HH:MM:SS` string with missing colons. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test8()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with `MM` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test9()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with `DD` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test10()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with `HH` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test11()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with `MM` (minutes) field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test12()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with `SS` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|

### **19. get_datetime_format.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass string with a valid `HH:MM:SS` datetime format.|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass strings with a valid `WDAY HH:MM:SS` datetime format with `WDAY` section being abbreviated week day name for all days in the week.|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass strings with a valid `WDAY HH:MM:SS` datetime format with `WDAY` section being full week day name for all days in the week. The return value may vary depending on the length of the week day name (either `WDAY6_HHMMSS`, `WDAY7_HHMMSS`, `WDAY8_HHMMSS`, or `WDAY9_HHMMSS`).|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass string with a valid `MM-DD` datetime format.|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass string with a valid `MM-DD HH:MM:SS` datetime format.|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass string with a valid `YYYY-MM-DD` datetime format.|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test7()`|Pass string with a valid `YYYY-MM-DD HH:MM:SS` datetime format.|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test8()`|Pass string with invalid datetime format. Call should retrun `DatetimeFormat::INVALID_DATE_FORMAT` value.|`get_datetime_format(std::string)`|<span style="color:green">Passed|