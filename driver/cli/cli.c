#include "cli.h"
#include "../include/driver.h"

drv_ret_t cli_help_handler(void)
{
    APP_LOG(APP_LOG_CLI,APP_LOG_INFO, "Available commands: help, version\n");
    return APP_SUCCESS;
}

drv_ret_t cli_version_handler(void)
{
    APP_LOG(APP_LOG_CLI,APP_LOG_INFO,"CLI Driver Version: 1.0\n");
    return APP_SUCCESS;
}
