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
### **Task_constructor.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify Task object instantiation with constructor.|`Task(std::string, std::string, std::string, std::string)`<br/>`Task::get_name(void)`<br/> `Task::get_description(void)`<br/>`Task::get_script_name(void)`<br/>`Task::get_frequency(void)` |<span style="color:green">Passed|
|`test2()`|Verify Task object instantiation with constructor.|`Task(std::string, std::string, std::string, std::string, std::string)`<br/>`Task::get_name(void)`<br/> `Task::get_description(void)`<br/>`Task::get_script_name(void)`<br/>`Task::get_frequency(void)` |<span style="color:green">Passed|

### **Task_methods.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Obtain the `time_t` value when `Task` is created.|`Task::get_creation_datetime(bool)`|<span style="color:green">Passed|
|`test2()`|Obtain system's current time + 5 seconds for `Task`'s execution time attribute. Then, verify the returned `time_t` time of execution value.|`Task::get_execution_datetime(bool)`|<span style="color:green">Passed|
|`test3()`|Obtain formated time of creation `string` value.|`Task::get_creation_datetime_fmt(void)`|<span style="color:green">Passed|
|`test4()`|Obtain formated time of execution `string` value.|`Task::get_execution_datetime_fmt(void)`|<span style="color:green">Passed|
|`test5()`|Obtain system's current time + 5 seconds for `Task`'s execution time attribute in `HH:MM:SS` format. Then, verify the returned `DatetimeFormat` value.|`Task::get_execution_datetime_format_attr(void)`|<span style="color:green">Passed|
|`test6()`|Set and get task id and status values.|`Task::set_id(int)`<br/>`Task::get_id(void)`<br/>`Task::set_status(TaskStatus)`<br/>`Task::get_status(void)`<br/>|<span style="color:green">Passed|
|`test7()`|Create `Task` object and run it. Then, verify that the command-line output has been successfully routed to output data member.|`Task::run_task(void)`<br/>`Task::get_output(void)`<br/>|<span style="color:green">Passed|

### **validate_hms.cpp**

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

### **validate_wday.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid full week day names.|`validate_wday(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass valid abbreviated week day names.|`validate_wday(std::string)`|<span style="color:green">Passed|
|`test3()`|Invalid week day name.|`validate_wday(std::string)`|<span style="color:green">Passed|

### **validate_wday_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid full week day names and `HH:MM:SS` string.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass valid abbreviated week day names and `HH:MM:SS` string.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `WDAY HH:MM:SS` string with missing space.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `WDAY HH:MM:SS` string with bad `WDAY` field.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `WDAY HH:MM:SS` string with bad `HH:MM:SS` field.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|

### **validate_yyyymmdd.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid `YYYY-MM-DD` strings, lower and upper bound days for each month.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass invalid `YYYY-MM-DD` string with bad length.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `YYYY-MM-DD` strings: bad `YYYY` field, bad `MM` field, and bad `DD` field.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `YYYY-MM-DD` strings with misplaced dashes.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `YYYY-MM-DD` string with `MM` out of range.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass invalid `YYYY-MM-DD` string with `DD` out of range.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|

### **validate_yyyymmdd_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid `YYYY-MM-DD HH:MM:SS` string.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with missing space.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `YYYY-MM-DD HH:MM:SS` strings: alphabetic character in `YYYY-MM-DD` section, and alphabetic character in `HH:MM:SS` section.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `YYYY-MM-DD HH:MM:SS` strings with missing dash characters.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `YYYY-MM-DD HH:MM:SS` strings with missing colon characters.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|

### **init_today.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify that `init_today()` returns the correct `time_t` value that corresponds to the very beginning of the current day in UTC time.|`init_today()`|<span style="color:green">Passed|

### **init_year.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify that `init_year()` returns the correct `time_t` value that corresponds to the very beginning of the current year in UTC time.|`init_year()`|<span style="color:green">Passed|

### **today_add_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one minute in seconds to input `HH:MM:SS` string. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Subtract one minute in seconds to input `HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_hms(std::string)`|<span style="color:green">Passed|

### **today_add_dhms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one minute in seconds to input `HH:MM:SS` string and zero days. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test2()`|Add one minute in seconds to input `HH:MM:SS` string and two days. Call should succeed and return `time_t` with a value two days and one minute in the future.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test3()`|Subtract one minute in seconds to input `HH:MM:SS` string and zero days. Call should fail and return `time_t` with a value of zero.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass negative value for days attribute. Call should fail and return `time_t` with a value of zero.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_dhms(std::string)`|<span style="color:green">Passed|

### **today_add_wday_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify week day full name. Add one minute in seconds to input `HH:MM:SS` section. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Verify week day abbreviated name. Add one minute in seconds to input `HH:MM:SS` section. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Subtract 24 hours from current time to obtain previous week day name; then, use this week day as input for the function. Call should succeed and return `time_t` with a value 6 days into the future.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid string input with bad `HH:MM:SS` section. Call should fail and return `time_t` with a value of zero.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid string input with bad `WDAY` section. Call should fail and return `time_t` with a value of zero.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|

### **today_add_yyyymmdd.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one day in seconds to input `YYYY-MM-DD` string. Call should succeed and return `time_t` with a value of one day into the future.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test2()`|Add 30 days in seconds to input `YYYY-MM-DD` string. Call should succeed and return `time_t` with a value of 30 days into the future.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test3()`|Add 365 days in seconds to input `YYYY-MM-DD` string. Call should succeed and return `time_t` with a value of 365 days into the future.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test4()`|Subtract one day in seconds to input `YYYY-MM-DD` string. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `YYYY-MM-DD` string with missing dashes. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass invalid `YYYY-MM-DD` string with `MM` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test7()`|Pass invalid `YYYY-MM-DD` string with `DD` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|

### **today_add_yyyymmdd_hms.cpp**

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

### **get_datetime_format.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass string with a valid `HH:MM:SS` datetime format. Call should succeed with return value of `DatetimeFormat::HHMMSS`.|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass strings with a valid `WDAY HH:MM:SS` datetime format with `WDAY` section being abbreviated week day name for all days in the week. Call should succeed with return value of `DatetimeFormat::WDAY_HHMMSS`.|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass strings with a valid `WDAY HH:MM:SS` datetime format with `WDAY` section being full week day name for all days in the week. The call should succeed and the return value may vary depending on the length of the week day name (either `WDAY6_HHMMSS`, `WDAY7_HHMMSS`, `WDAY8_HHMMSS`, or `WDAY9_HHMMSS`).|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass string with a valid `YYYY-MM-DD` datetime format. Call should succeed with return value of `DatetimeFormat::YYYYMMDD`.|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass string with a valid `YYYY-MM-DD HH:MM:SS` datetime format. Call should succeed with return value of `DatetimeFormat::YYYYMMDD_HHMMSS`.|`get_datetime_format(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass string with invalid datetime format. Call should fail with return value of  `DatetimeFormat::INVALID_DATE_FORMAT`.|`get_datetime_format(std::string)`|<span style="color:green">Passed|

### **validate_task_parms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Provide the mandatory valid attributes to instantiate `Task` object. These include `Name`, `ScriptFilename`, `Frequency`, and `Datetime`. Call should succeed with return value of  `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Provide all possible valid attributes to instantiate `Task` object. These include `Name`, `ScriptFilename`, `Frequency`, and `Datetime`. Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Fail to pass `Name` attribute. Call should fail with return value of `TaskValidate::MISSING_REQUIRED_KEYVALS`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Fail to pass `ScriptFilename` attribute. Call should fail with return value of `TaskValidate::MISSING_REQUIRED_KEYVALS`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Fail to pass `Frequency` attribute. Call should fail with return value of `TaskValidate::MISSING_REQUIRED_KEYVALS`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Fail to pass `Datetime` attribute. Call should fail with return value of  `TaskValidate::MISSING_REQUIRED_KEYVALS`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Provide all possible valid attributes to instantiate `Task` object. `ScriptFilename` value should point to an invalid file location. Call should fail with return value of  `TaskValidate::SCRIPT_NOT_FOUND`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Provide all possible valid attributes to instantiate `Task` object. `Frequency` value should be invalid. Call should fail with return value of `TaskValidate::BAD_FREQUENCY_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Once.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `WDAY HH:MM:SS` (abbreviated and full week day names). Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Pass a `Datetime` attribute with `HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of`TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Pass a `Datetime` attribute with `YYYY-MM-DD HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Pass a `Datetime` attribute with `WDAY HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Pass a `Datetime` attribute with `YYYY-MM-DD` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Pass a `Datetime` attribute with invalid value that does not follow any datetime format. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS`, and `YYYY-MM-DD HH:MM:SS`. The format `WDAY HH:MM:SS` does not require to be tested because it will always rollover to the next week. The datetime value is one minute in the past. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test9()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. The datetime value is one day in the past. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test10()`|Test the datetime format `WDAY HH:MM:SS` of the `Datetime` attribute. The datetime value is 60 seconds in the past. This format allows wrapping the resulting `time_t` to the next week day if the indicated week day already passed. Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Hourly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Provide all possible valid attributes to instantiate `Task` object. With an `Hourly` frequency, the `Datetime` value is ignored regardless. Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Daily.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `WDAY HH:MM:SS` (abbreviated and full week day names). Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Test the incompatible datetime format `YYYY-MM-DD`. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Pass a `Datetime` attribute with `HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Pass a `Datetime` attribute with `YYYY-MM-DD HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Pass a `Datetime` attribute with `WDAY HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Pass a `Datetime` attribute with invalid value that does not follow any datetime format. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS` and `YYYY-MM-DD HH:MM:SS`. The format `WDAY HH:MM:SS` does not require to be tested because it will always rollover to the next week and next year, respectively. The datetime value is one minute in the past. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Test the datetime format `WDAY HH:MM:SS` of the `Datetime` attribute. The datetime value is 60 seconds in the past. This format allows wrapping the resulting `time_t` to the next week day if the indicated week day already passed. Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Weekly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `WDAY HH:MM:SS` (abbreviated and full week day names). Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Pass a `Datetime` attribute with `HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of`TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Pass a `Datetime` attribute with `YYYY-MM-DD HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Pass a `Datetime` attribute with `WDAY HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Pass a `Datetime` attribute with `YYYY-MM-DD` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Pass a `Datetime` attribute with invalid value that does not follow any datetime format. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS` and `YYYY-MM-DD HH:MM:SS`. The format `WDAY HH:MM:SS` does not require to be tested because it will always rollover to the next year. The datetime value is one minute in the past. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test9()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. The datetime value is one day in the past. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test10()`|Test the datetime format `WDAY HH:MM:SS` of the `Datetime` attribute. The datetime value is 60 seconds in the past. This format allows wrapping the resulting `time_t` to the next week day if the indicated week day already passed. Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Monthly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS` and `YYYY-MM-DD HH:MM:SS`. Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Pass a valid `Datetime` value with the format `WDAY HH:MM:SS`. The datetime format `WDAY HH:MM:SS` is incompatible with `Monthly` frequency attribute. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Pass a `Datetime` attribute with `HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of`TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Pass a `Datetime` attribute with `YYYY-MM-DD HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Pass a `Datetime` attribute with `YYYY-MM-DD` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Pass a `Datetime` attribute with invalid value that does not follow any datetime format. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS` and `YYYY-MM-DD HH:MM:SS`. The datetime value is one minute in the past. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test9()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. The datetime value is one day in the past. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test10()`|Test incompatible datetime format `WDAY HH:MM:SS` of the `Datetime` attribute. The datetime value is 60 seconds in the past. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Yearly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Test the datetime format `YYYY-MM-DD HH:MM:SS` of the `Datetime` attribute. Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. Call should succeed with return value of `TaskValidate::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Pass a valid `Datetime` values with the format `HH:MM:SS` and `WDAY HH:MM:SS`. The datetime formats `HH:MM:SS` and `WDAY HH:MM:SS` are incompatible with `Yearly` frequency attribute. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Pass a `Datetime` attribute with `YYYY-MM-DD HH:MM:SS` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Pass a `Datetime` attribute with `YYYY-MM-DD` format. The `Datetime` attribute is invalid. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Pass a `Datetime` attribute with invalid value that does not follow any datetime format. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Test the datetime format `YYYY-MM-DD HH:MM:SS` of the `Datetime` attribute. The datetime value is one minute in the past. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. The datetime value is one minute in the past. Call should fail with return value of `TaskValidate::BAD_DATETIME_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **Task_update_execution_datetime_Once.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Call the method with tasks using the following `Datetime` formats: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `WDAY HH:MM:SS` (abbreviated and full week day names). Tasks with `Frequency` of `Once` should not have the execution datetime value updated.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test2()`|Call the method with task using the `Datetime` format `YYYY-MM-DD`. Tasks with `Frequency` of `Once` should not have the execution datetime value updated.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|

### **Task_update_execution_datetime_Hourly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Tasks with `Frequency` of `Hourly` should have the execution datetime value increased by 1 hour after the method call succeeded.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|

### **Task_update_execution_datetime_Daily.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Daily`. After a successful method call, the execution datetime value should have increased by 1 day.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Daily`. After a successful method call, the execution datetime value should have increased by 1 day.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Daily`. After a successful method call, the execution datetime value should have increased by 1 day.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with a `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Daily`. After a successful method call, the execution datetime value should have increased by 1 day.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|

### **Task_update_execution_datetime_Weekly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Weekly`. After a successful method call, the execution datetime value should have increased by 7 days.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Weekly`. After a successful method call, the execution datetime value should have increased by 7 days.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Weekly`. After a successful method call, the execution datetime value should have increased by 7 days.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with a `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Weekly`. After a successful method call, the execution datetime value should have increased by 7 days.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Weekly`. Initial execution datetime has an offset of one day into the future. After a successful method call, the execution datetime value should have increased by 7 days.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|

### **Task_update_execution_datetime_Monthly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Monthly`. After a successful method call, the execution datetime value should correspond the calendar day of the next month.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Monthly`. After a successful method call, the execution datetime value should correspond the calendar day of the next month.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Monthly`. Initial execution datetime has an offset of one day into the future. After a successful method call, the execution datetime value should correspond the calendar day of the next month.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|

### **Task_update_execution_datetime_Yearly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Yearly`. After a successful method call, the execution datetime value should correspond the calendar day of the next year.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Yearly`. Initial execution datetime has an offset of one day into the future. After a successful method call, the execution datetime value should correspond the calendar day of the next year.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Once.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Once`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Once`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Once`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with a `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Once`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Once`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test6()`|Initialize `Task` with an invalid datetime format and `Frequency` of `Once`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test7()`|Initialize `Task` with constructor `Task::Task(std::string, std::string, std::string, std::string)` and `Frequency` of `Once`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test8()`|Attempt to initialize `Task` with invalid datetime values with datetime formats `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, `WDAY HH:MM:SS`, and `YYYY-MM-DD` and `Frequency` of `Daily`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Hourly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with no datetime parameter and `Frequency` of `Hourly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with valid datetime parameters and `Frequency` of `Hourly`. The datetime formats tested are the following: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, `WDAY HH:MM:SS` (full week day names), `WDAY HH:MM:SS` (abbreviated week day names), and `YYYY-MM-DD`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a datetime parameter, with an invalid datetime format, and `Frequency` of `Hourly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Daily.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Daily`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Daily`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Daily`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with a `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Daily`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with an invalid datetime format and `Frequency` of `Daily`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test6()`|Initialize `Task` with constructor `Task::Task(std::string, std::string, std::string, std::string)` and `Frequency` of `Daily`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test7()`|Initialize `Task` with incompatible datetime format `YYYY-MM-DD` datetime format and `Frequency` of `Daily`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test8()`|Attempt to initialize `Task` with invalid datetime values with datetime formats `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `WDAY HH:MM:SS` and `Frequency` of `Daily`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Weekly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Weekly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Weekly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Weekly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with a `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Weekly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Weekly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test6()`|Initialize `Task` with an invalid datetime format and `Frequency` of `Weekly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test7()`|Initialize `Task` with constructor `Task::Task(std::string, std::string, std::string, std::string)` and `Frequency` of `Weekly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test8()`|Attempt to initialize `Task` with invalid datetime values with datetime formats `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, `WDAY HH:MM:SS`, and `YYYY-MM-DD` and `Frequency` of `Weekly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Monthly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Monthly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Monthly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Monthly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with an invalid datetime format and `Frequency` of `Monthly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with constructor `Task::Task(std::string, std::string, std::string, std::string)` and `Frequency` of `Monthly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test6()`|Initialize `Task` with incompatible datetime format `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Monthly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test7()`|Initialize `Task` with incompatible datetime format `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Monthly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test8()`|Attempt to initialize `Task` with invalid datetime values with datetime formats `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `YYYY-MM-DD` and `Frequency` of `Monthly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Yearly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Yearly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Yearly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with an invalid datetime format and `Frequency` of `Yearly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with constructor `Task::Task(std::string, std::string, std::string, std::string)` and `Frequency` of `Yearly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with incompatible datetime format `HH:MM:SS` datetime format and `Frequency` of `Yearly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test6()`|Initialize `Task` with incompatible datetime format `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Yearly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test7()`|Initialize `Task` with incompatible datetime format `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Yearly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test8()`|Attempt to initialize `Task` with invalid datetime values with datetime formats `YYYY-MM-DD HH:MM:SS` and `YYYY-MM-DD` and `Frequency` of `Yearly`. The constructor call must end with the `Task->status` set to `TaskStatus::ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|