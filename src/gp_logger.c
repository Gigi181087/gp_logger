#ifndef __GP_LOGGER_C_
#define __GP_LOGGER_C_

#include <gp_logger.h>

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

#define __assert_initialized(x) do{ if (NULL == x) { return GP__LOGGER__ERRORS__NOTINITIALIZED;}} while(0)

struct GP_Logger_int {
    uint16_t line_length;
    uint8_t logfile_enabled;

    char info_color[8];
    char warning_color[8];
    char error_color[8];
    char debug_color[8];

    char* file_path;
};

uint8_t gp__logger__init (GP_Logger_t** module_param) {
    // alloc buffer from heap
    *module_param = (GP_Logger_t*) malloc (sizeof (GP_Logger_t*));
    
    if (NULL == *module_param) {

        return GP__LOGGER__ERRORS__ALLOCFAILED;
    }
    
    (*module_param)->file_path = NULL;
    (*module_param)->logfile_enabled = 0;
    (*module_param)->line_length = MAXUINT8;
    memcpy((*module_param)->info_color, GP__LOGGER__COLOR__WHITE, 8);
    memcpy((*module_param)->warning_color, GP__LOGGER__COLOR__YELLOW, 8);
    memcpy((*module_param)->error_color, GP__LOGGER__COLOR__RED, 8);
    memcpy((*module_param)->debug_color, GP__LOGGER__COLOR__BLUE, 8);

    return GP__LOGGER__ERRORS__NOERROR;
}

uint8_t gp__logger__destroy (GP_Logger_t** module_param) {
    __assert_initialized(module_param);


    (*module_param)->line_length = 0;
    (*module_param)->logfile_enabled = 0;
    free((*module_param)->file_path);
    free(*module_param);
    *module_param = NULL;

    return GP__LOGGER__ERRORS__NOERROR;
}

uint8_t gp__logger__log (GP_Logger_t* module_param, GP_Logger_Types_e log_level_param, const char* message_param, size_t message_length_param) {
    __assert_initialized(module_param);


    char log_level[40];
    char* color;
    SYSTEMTIME time;
    size_t message_length = strnlen_s(message_param, message_length_param);

    if(0 == message_length || message_length > message_length_param) {

        return GP__LOGGER__ERRORS__PARAMETERINVALID;
    }

    memset(log_level, ' ', 39);
    log_level[39] = '\0';
    
    // Get Systemtime
    GetLocalTime(&time);

    uint16_t result = snprintf(log_level, 24,"%04d/%02d/%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
    log_level[23] = ' ';

    // Get Color and spacing
    switch(log_level_param) {

        case GP__LOGGER__LOG_LEVEL__INFO:
            color = module_param->info_color;
            memcpy (&log_level[27], "INFO", 4);

            break;

        case GP__LOGGER__LOG_LEVEL__WARNING:
            color = module_param->warning_color;
            memcpy (&log_level[27], "WARNING", 7);

            break;

        case GP__LOGGER__LOG_LEVEL__ERROR:
            color = module_param->error_color;
            memcpy (&log_level[27], "ERROR", 5);

            break;

        default:
            color = module_param->debug_color;
            memcpy (&log_level[27], "DEBUG", 5);
    }

    uint16_t offset = 0;

    while(offset < message_length) {
        // check for return in text
        uint16_t text_length = 0;
        uint8_t new_line = 0;

        for(uint16_t i = 0; (offset + i) < message_length && i < module_param->line_length - 39; i++) {

            if('\n' == message_param[offset + i]) {
                new_line = 1;

                break;
            }

            text_length++;
            
        }

        if(text_length > 0) {

            if(0 == new_line && ' ' == message_param[offset]) {
                offset++;
                text_length--;
            }

            printf_s("%s%s%.*s\n%s", color, log_level, text_length, &message_param[offset], GP__LOGGER__COLOR__RESET);
            memset(log_level, ' ', 39);
            
        }
        
        offset += text_length + new_line;

    }

    return GP__LOGGER__ERRORS__NOERROR;
}

uint8_t gp__logger__set_line_length (GP_Logger_t* module_param, uint16_t line_length_param) {
    __assert_initialized(module_param);


    if(line_length_param < 41) {
        
        return GP__LOGGER__ERRORS__PARAMETERINVALID;
    }

    module_param->line_length = line_length_param;

    return GP__LOGGER__ERRORS__NOERROR;
}

uint8_t gp__logger__enable_logfile (GP_Logger_t* module_param, const char* path_param) {
    __assert_initialized(module_param);


    error_status_t result;
    
    // check path to logfile
    if (NULL == path_param) {

        return GP__LOGGER__ERRORS__PATHINVALID;        
    }

    // ToDo: Check if path is valid

    module_param->file_path = (char*) malloc (sizeof(char) * sizeof(path_param));
    
    if (NULL == module_param->file_path) {

        return GP__LOGGER__ERRORS__ALLOCFAILED;
    }

    result = strcpy_s(module_param->file_path, sizeof(char) * sizeof(path_param), path_param);
    

    
    
    DWORD attribut = GetFileAttributesA(path_param);
    
    if (INVALID_FILE_ATTRIBUTES == attribut || (attribut & FILE_ATTRIBUTE_DIRECTORY == 0)) {

        return GP__LOGGER__ERRORS__PATHINVALID;
    }

    return GP__LOGGER__ERRORS__NOERROR;
}

uint8_t gp__logger__set_color (GP_Logger_t* module_param, GP_Logger_Types_e log_level, const char* color_param) {


    return GP__LOGGER__ERRORS__NOERROR;
}

#endif // __GP_LOGGER_C_