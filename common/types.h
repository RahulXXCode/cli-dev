#ifndef DEF_TYPES_H
#define DEF_TYPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define INIT_DEBLOG_ARG "debug_log"

#define FALSE (0 == 1)
#define TRUE  (0 == 0)


typedef enum {
    APP_ERROR = 0,
    APP_SUCCESS = 1,
    APP_INVALID = 2
} app_ret_t;

#endif

