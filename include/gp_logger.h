#ifndef __GP_LOGGER_H_
#define __GP_LOGGER_H_

#include <stdint.h>

#include "typedefs/errors.h"
#include "typedefs/colors.h"


typedef enum {
    GP__LOGGER__LOG_LEVEL__INFO,
    GP__LOGGER__LOG_LEVEL__WARNING,
    GP__LOGGER__LOG_LEVEL__ERROR,
    GP__LOGGER__LOG_LEVEL__DEBUG
} GP_Logger_Types_e;

typedef struct GP_Logger_int GP_Logger_t;

/// @brief initializes a new module
/// @param module module to initialize
uint8_t gp__logger__init (GP_Logger_t** module);

/// @brief destroys a created module
/// @param module module to destroy
uint8_t gp__logger__destroy (GP_Logger_t** module);

/// @brief logs a message and writes it into logfile
uint8_t gp__logger__log (GP_Logger_t*module, GP_Logger_Types_e log_type, const char* log_message, size_t message_length);

/// @brief set the maximum line length of the log
/// @param module_param 
/// @param line_length_param 
/// @return 
uint8_t gp__logger__set_line_length (GP_Logger_t* module_param, uint16_t line_length_param);

uint8_t gp__logger__enable_debug_log (GP_Logger_t*);
uint8_t gp__logger__disable_debug_log (GP_Logger_t*);

#endif //__GP_LOGGER_H_