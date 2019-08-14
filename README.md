# brute-log

A tiny tool for printing, debugging and logging in C/C++.  

Only works on linux system with GCC compiler.

No functions or global variables. Only macros in one header file.

It's brute and crude, so, really fast...  
  

### Usage:
>./runtest.sh  


### Example:
```cpp
#include "brute-log.h"

class Sample
{
public:
    bool test()
    {
        BRUTE_INFO("This is info message: %s", "string");
        BRUTE_WARN("This is warn message: %c++", 'C');
        BRUTE_ERROR("This is error message: %f", 0.618);
        BRUTE_FATAL("This is fatal message: %p", this);

        // If -DBRUTE_NDEBUG, this level won't be printed.
        BRUTE_DEBUG("This is debug message: %d %d", 123, 456);

        // If I want a new level named "Lucky" ...
        BRUTE_LOG(LUCKY, "This is my custom level message: %s", "^_^");
        BRUTE_LOG(Hello Kitty, "{ %s#%d %s } also custom", BRUTE_SRC_POS);

        BRUTE_LF();  // print empty line

        // Each level has 7 diffrent formats to choose...
        BRUTE_DEBUG_V0("V0 means only level information...");
        BRUTE_DEBUG_V1("V1 means also output function's name");
        BRUTE_DEBUG_V2("V2 means output function's name and date-time");
        BRUTE_DEBUG_V3("V3 means output more details than V2");
        BRUTE_DEBUG_V4("V4 means output much more details than V2");
        BRUTE_DEBUG_V5("V5 means output most details, but looks too long!!!");

        FILE* logfile = fopen("mylog.txt", "w");

        #define BRUTE_OSTREAM logfile
        BRUTE_WARN("I'm redirected into %s %p", "mylog.txt", logfile);

        // This means you can change buffering method: line-buffered, full-buffered, or none-buffered.
        BRUTE_SET_BUFFERING_METHOD(0, 1024, BRUTE_LINE_BUFFERED);

        __BRUTE_GET_DT__(dt);
        BRUTE_FPRINT("%s [%s] If all the methods are not suitable, %s\n", dt, "CRITICAL", "still this one");

        BRUTE_CLOSE();  // Close logging, all output will be ignored
        BRUTE_INFO("This will not be written into mylog.txt!!!");

        #define BRUTE_OSTREAM stdout
        BRUTE_INFO("I'm redirected to stdout %d", fileno(stdout));

        // And other debug tools, like print every "interval" steps:
        for (int i = 1; i <= 10000; ++i) {
            BRUTE_PROGRESS_RATE(i, 10000, 1500, "rest: %d", 10000-i);
        }

        int* data = 0;
        // This macro check null pointer. If null, print error message and return,
        // the second arg also can be: BRUTE_CHECK_PTR(data, foo(), bar(), blah; blah; blah);
        BRUTE_CHECK_PTR(data, return false);

        // Won't reach here...
        return true;
    }
};

int main(int argc, char* argv[])
{
    BRUTE_PRINTLN(argv[0]);

    bool ret = Sample().test();

    /** Like BRUTE_CHECK_PTR, but this one accept non-pointer arguments.
     *  This macro equals to these codes:
     *  if (ret != true) {
     *      // Can append more codes here ...
     *      fputs("[2012-12-12 12:12:12] [ERROR] [example.cc:69] [main()] Assertion: `ret == true` failed!\n", stderr);
     *      fputs("Test finished!\n", stderr);
     *      return 99;
     *  } else {
     *      return 0;
     *  }
     */
    BRUTE_ASSERT((ret == true), BRUTE_PRINT("Test finished!\n"); return 99);

    return 0;
}
```

### Output:
```
./brute_example0
[2019-08-14 22:31:48.485110] [INFO]  This is info message: string
[2019-08-14 22:31:48.485165] [WARN]  This is warn message: C++
[2019-08-14 22:31:48.485171] [ERROR] This is error message: 0.618000
[2019-08-14 22:31:48.485181] [FATAL] This is fatal message: 0x7ffc977f0ec0
[2019-08-14 22:31:48.485188] [DEBUG] This is debug message: 123 456
[2019-08-14 22:31:48.485194] [LUCKY] This is my custom level message: ^_^
[2019-08-14 22:31:48.485199] [Hello Kitty] { example.cc#19 test } also custom

[DEBUG] V0 means only level information...
[DEBUG] [test] V1 means also output function's name
[2019-08-14 22:31:48.485213] [DEBUG] [test] V2 means output function's name and date-time
[2019-08-14 22:31:48.485221] [DEBUG] [bool Sample::test()] V3 means output more details than V2
[2019-08-14 22:31:48.485229] [DEBUG] [example.cc:28] [test] V4 means output much more details than V2
[2019-08-14 22:31:48.485237] [DEBUG] [example.cc:29] [bool Sample::test()] V5 means output most details, but looks too long!!!
[2019-08-14 22:31:48.485352] [INFO]  I'm redirected to stdout 1
[2019-08-14 22:31:48.485282] [INFO] [test] 1500/10000 15.00% rest: 8500
[2019-08-14 22:31:48.485282] [INFO] [test] 3000/10000 30.00% rest: 7000
[2019-08-14 22:31:48.485282] [INFO] [test] 4500/10000 45.00% rest: 5500
[2019-08-14 22:31:48.485282] [INFO] [test] 6000/10000 60.00% rest: 4000
[2019-08-14 22:31:48.485282] [INFO] [test] 7500/10000 75.00% rest: 2500
[2019-08-14 22:31:48.485282] [INFO] [test] 9000/10000 90.00% rest: 1000
[2019-08-14 22:31:48.485282] [INFO] [test] 10000/10000 100.00% rest: 0
[2019-08-14 22:31:48.494085] [ERROR] [example.cc:56] [test] Arg `data` is null or zero!
[2019-08-14 22:31:48.494092] [ERROR] [example.cc:80] [main] Assertion: `(ret == true)` failed!
Test finished!
```

```
cat mylog.txt 
[2019-08-12 21:02:50.568275] [WARN]  I'm redirected into mylog.txt 0x16d84a0
[2019-08-12 21:02:50.568304] [CRITICAL] If all the methods are not suitable, still this one

```


