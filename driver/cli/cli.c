#include "cli.h"
#include "../include/driver.h"

drv_ret_t cli_help_handler(void)
{
    printf("Available commands: help, version\n");
    return APP_SUCCESS;
}

drv_ret_t cli_version_handler(void)
{
    printf("CLI Driver Version: 1.0\n");
    return APP_SUCCESS;
}
