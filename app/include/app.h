#ifndef APP_DEF_H
#define APP_DEF_H

#include <stdio.h>
#include <pthread.h>
#include "../../common/types.h"
#include "../../driver/include/driver.h"

#define APP_LOG(mod_lvl, err_code,f, ...) \
    app_log(mod_lvl, err_code, __FUNCTION__, __LINE__, f, ##__VA_ARGS__)

#define MAX_LOG_INFO_TXT_SIZE   256U
#define MAX_API_TXT_SIZE        128U

typedef enum {
    APP_MOD_CLI_TYPE,
    APP_MOD_MEM_TYPE,
    APP_MOD_LOG_TYPE
} eMod_type;

typedef enum
{
    APP_LOG_DRV,
    APP_LOG_CLI,
    APP_LOG_USR_SPACE,
    APP_LOG_NONE
} log_module_lvl_t;

typedef enum
{
    APP_LOG_ERR,
    APP_LOG_DBG,
    APP_LOG_INFO
} log_code_t;

typedef struct {
    log_module_lvl_t log_lvl;
    log_code_t log_code;
    int line_no;
    char fn_name[MAX_API_TXT_SIZE];
    char info_pr[MAX_LOG_INFO_TXT_SIZE];
} log_module_t;

typedef struct {
    log_module_t log;
} module_struct_t;

extern pthread_mutex_t console_lock;

extern volatile int count;
extern volatile int subcount;
extern module_struct_t module;
app_ret_t module_init(eMod_type mod);
app_ret_t log_module_init();
void app_log(log_module_lvl_t mod, const uint8_t code, const char* func, int line, char* fmt, ...);

#endif
