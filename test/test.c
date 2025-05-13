#include <gp_logger.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    const char* test1 = "Info Test!";
    const char* test2 = "Debug Test!";
    const char* test3 = "Warning Test!";
    const char* test4 = "Error Test!";
    const char* test5 = "Test\n with\n new\n line\n";
    const char* test6 = "Test without new line!";

    GP_Logger_t* log = NULL;
    gp__logger__init(&log);

    printf_s("Log Test started!\n");

    gp__logger__log (log, GP__LOGGER__LOG_LEVEL__INFO,    test1, strlen(test1));
    gp__logger__log (log, GP__LOGGER__LOG_LEVEL__DEBUG,   test2, strlen(test2));
    gp__logger__log (log, GP__LOGGER__LOG_LEVEL__WARNING, test3, strlen(test3));
    gp__logger__log (log, GP__LOGGER__LOG_LEVEL__ERROR,   test4, strlen(test4));
    gp__logger__set_line_length(log, 44);
    gp__logger__log(log, GP__LOGGER__LOG_LEVEL__WARNING,  test5, strlen(test5));
    gp__logger__log(log, GP__LOGGER__LOG_LEVEL__INFO,  test6, strlen(test6));

    printf_s("Log Test ended!\n");

    gp__logger__destroy (&log);

    return 0;
}