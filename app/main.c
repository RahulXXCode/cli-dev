#include "include/app.h"

app_ret_t module_init(const eMod_type mod)
{
    app_ret_t ret = APP_ERROR;
    // Map the driver in the init based on the module type()
    switch(mod)
    {
	    case APP_MOD_CLI_TYPE:
		ret = cli_driver_init();
		break;
	    default:
		break;
    }

    return ret;
}

int main(void) {

    app_ret_t ret = APP_ERROR;
    // initialize the cli module where in this module sample driver is mapped
    // just for understanding purpose
    ret = module_init(APP_MOD_CLI_TYPE);

    if (ret == APP_ERROR)
    {
	printf("\n module init failed\n");
	return -1;
    }

    cli_driver_command_execute("help");

    return 0;
}
