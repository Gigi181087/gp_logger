#include <gp_logger.h>

int main() {
    GP_Logger_t* log;
    gp__logger__init(&log);

    gp__logger__log (log, GP__LOGGER__LOG_LEVEL__INFO, "Log started!");
    gp__logger__log (log, GP__LOGGER__LOG_LEVEL__DEBUG, "Debug Test!");
    gp__logger__log (log, GP__LOGGER__LOG_LEVEL__WARNING, "Warning Test!");
    gp__logger__log (log, GP__LOGGER__LOG_LEVEL__ERROR, "Error Test!");

    gp__logger__destroy (&log);

    return 0;
}