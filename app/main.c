#include "include/app.h"
#include <pthread.h>

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

void* cli_exec_thread(void* arg)
{
    char cmd[64];
    int count = 0;
    int subcount = 1;
    while (1)
    {
        printf("\n%d:%d>> ", count, subcount);
        fflush(stdout);

        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
            continue;

	subcount++;
        // Remove newline
        cmd[strcspn(cmd, "\n")] = 0;

	if (cmd[0] == '\0')
            continue;

        if (strcmp(cmd, "exit") == 0)
            break;

        if (APP_SUCCESS != cli_driver_command_execute(cmd))
	{
            printf("\n Failed exec command:%s\n",cmd);
	    count++;
	}
    }
}

int main(void) {

    app_ret_t ret = APP_ERROR;
    pthread_t tid;
    // initialize the cli module where in this module sample driver is mapped
    // just for understanding purpose
    ret = module_init(APP_MOD_CLI_TYPE);

    if (ret == APP_ERROR)
    {
	printf("\n module init failed\n");
	return -1;
    }

    if (0 != pthread_create(&tid, NULL, cli_exec_thread, NULL))
    {
	printf("\n Failed Creating Thread");
    }

    pthread_join(tid, NULL);
    //cli_driver_command_execute("help");

    return 0;
}
