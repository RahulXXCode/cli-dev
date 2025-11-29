#include "include/driver.h"
#include "cli/cli.h"

typedef struct
{
    drv_cli_help_t help;
    drv_cli_version_t version;
    // Add more CLI commands here

} cli_driver_t;

static cli_driver_t *g_cli_driver;

drv_ret_t cli_driver_init()
{
    g_cli_driver = malloc(sizeof(cli_driver_t));
    if (!g_cli_driver)
        return APP_ERROR;
    // Assign handlers to structure
    g_cli_driver->help    = cli_help_handler;
    g_cli_driver->version = cli_version_handler;
    printf("\n Module initialization complete\n");
}

drv_ret_t cli_driver_command_execute(char* cmd)
{
    if (cmd == NULL)
    {
        printf("\n driver execute failed");
        return APP_ERROR;
    }
    if (strcmp(cmd, "help") == 0)
        return g_cli_driver->help();

    if (strcmp(cmd, "version") == 0)
        return g_cli_driver->version();

    printf("Unknown command: %s\n", cmd);
    return APP_ERROR;
}
