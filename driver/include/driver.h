#ifndef DRIVER_H
#define DRIVER_H
#include "../../app/include/app.h"

typedef app_ret_t drv_ret_t;

drv_ret_t cli_driver_init();
drv_ret_t cli_driver_command_execute(char*);

typedef drv_ret_t (*drv_cli_help_t)(void);
typedef drv_ret_t (*drv_cli_version_t)(void);
#endif
