// Example of brute log
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
        BRUTE_LOG(Hello Kitty, "{ %s#%d %s } also custom", BRUTE_SRC_POSEX);

        BRUTE_LF();  // print empty line

        // Each level has 7 diffrent formats to choose...
        BRUTE_DEBUG_V0("V0 means only level information...");
        BRUTE_DEBUG_V1("V1 means also output function's name");
        BRUTE_DEBUG_V2("V2 means output function's name and date-time");
        BRUTE_DEBUG_V3("V3 means output more details than V2");
        BRUTE_DEBUG_V4("V4 means output much more details than V2");
        BRUTE_DEBUG_V5("V5 means output most details, but looks too long!!!");

        FILE* logfile = fopen("mylog.txt", "w");

        #pragma push_macro("BRUTE_OSTREAM")
        #define BRUTE_OSTREAM logfile
        BRUTE_WARN("I'm redirected into %s %p", "mylog.txt", logfile);

        BRUTE_CLOSE();  // Close logging, all output will be ignored
        BRUTE_INFO("This will not be written into mylog.txt!!!");

        #pragma pop_macro("BRUTE_OSTREAM")
        BRUTE_INFO("I'm redirected to stderr again");

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
     *      fputs("ret is not true!!\n", stderr);
     *      // ......
     *  } else {
     *      // ......
     *  }
     */
    BRUTE_ASSERT_C((ret == true), BRUTE_INFO("ret is not true!"););   // won't abort
    // BRUTE_ASSERT((ret == true), BRUTE_INFO("ret is not true!"););  // will abort

    BRUTE_EXIT("Test exit\n");
}




