#include "include/app.h"

pthread_mutex_t console_lock = PTHREAD_MUTEX_INITIALIZER;

volatile int count = 0;
volatile int subcount = 1;
module_struct_t module;
extern char* app_mod_lvl_grp[3];

static void remove_char(char *string, char del_char)
{
   int i = 0, j = 0;
   while(string[i] != '\0')
   {
	if (string[i] != del_char)
	{
	    string[j] = string[i];
	    j++;
	}
	i++;
   }
   string[j] = '\0';
}

static app_ret_t module_main_parse(int argc, char *argv[])
{
    char *str;
    app_ret_t ret = APP_SUCCESS;
    uint8_t i = 1;
    if (argv[1] == NULL)
    {
	ret = APP_INVALID;
	goto parse_end;
    }
    while (argv[i] != NULL)
    {
	str = argv[i];
	if (str[0] == '-')
	{
	    remove_char(str, str[0]);
	}

        if (strcmp(str, INIT_DEBLOG_ARG) == 0)
        {
	    str = argv[i + 1];
	    if (strcmp(str, app_mod_lvl_grp[0]) == 0)
	    {
		module.log.log_lvl = APP_LOG_DRV; 
		break;
	    	// acitvate drv lvl logs
	    }
	    else if (strcmp(str, app_mod_lvl_grp[1]) == 0)
	    {
		// activate cli lvl logs
		module.log.log_lvl = APP_LOG_CLI; 
		break;
	    }
	    else if (strcmp(str, app_mod_lvl_grp[2]) == 0)
	    {
		// activate app lvl logs
		module.log.log_lvl = APP_LOG_USR_SPACE; 
		break;
	    }
	    else
	    {
		// report error
		printf("\n Argument type is invalid!");
		module.log.log_lvl = APP_LOG_NONE; 
		ret = APP_INVALID;
		break;
	    }
        }
        else
        {
	    // report non valid args and continue to boot the app
	    printf("\n Argument type is invalid!");
	    ret = APP_INVALID;
            module.log.log_lvl = APP_LOG_NONE; 
	    break;
        }
	i++;
    }
parse_end:
    return ret;
}


app_ret_t module_init(const eMod_type mod)
{
    app_ret_t ret = APP_ERROR;
    // Map the driver in the init based on the module type()
    switch(mod)
    {
	    case APP_MOD_CLI_TYPE:
		ret = cli_driver_init();
		break;
            case APP_MOD_LOG_TYPE:
		ret = log_module_init();
		break;
	    default:
		break;
    }

    return ret;
}

void* cli_exec_thread(void* arg)
{
    char cmd[64];
    while (1)
    {
	pthread_mutex_lock(&console_lock);
        printf("\n%d:%d>> ", count, subcount);
        fflush(stdout);
	pthread_mutex_unlock(&console_lock);

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
            APP_LOG(APP_LOG_USR_SPACE,APP_LOG_ERR, "\n Failed exec command:%s\n",cmd);
	    count++;
	}
    }
}

int main(int argc, char *argv[]) {

    app_ret_t ret = APP_ERROR;
    pthread_t tid;
    // initialize the cli module where in this module sample driver is mapped
    // just for understanding purpose
    setbuf(stdout, NULL);
    if (argc > 0)
    {
	ret = module_main_parse(argc, argv);
	if (ret == APP_SUCCESS)
        {
    	    ret = module_init(APP_MOD_LOG_TYPE);
	}
	else
	{
	    printf("logger not activated!\n");
	}
    }
    if (ret == APP_ERROR)
    {
	printf("\n log module init failed\n");
	return -1;
    }
    if (0 != pthread_create(&tid, NULL, cli_exec_thread, NULL))
    {
	printf("\n failed creating thread");
 	APP_LOG(APP_LOG_USR_SPACE,APP_LOG_ERR," Failed Creating Thread\n");
	return -1;
    }
    ret = module_init(APP_MOD_CLI_TYPE);

    if (ret == APP_ERROR)
    {
	APP_LOG(APP_LOG_USR_SPACE,APP_LOG_ERR,"module init failed\n");
	return -1;
    }

    //if (Create_Thread_and_join())

    pthread_join(tid, NULL);
    //cli_driver_command_execute("help");

    return 0;
}
