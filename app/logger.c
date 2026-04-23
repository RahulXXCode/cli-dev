#include "include/app.h"
#include <mqueue.h>
#include <fcntl.h>  // For O_* constants
#include <sys/stat.h> // For mode constants
#include <stdarg.h>

// create a queue log array and process the queue!
static mqd_t log_rx_queue_handle;
static mqd_t log_tx_queue_handle;
static void* log_thread_exec();

module_struct_t *log_module = &module;

char* app_mod_lvl_grp[3] = 
{
    "DRV",
    "CLI",
    "APP"   
};

app_ret_t log_module_init()
{
    // create log_thread()
    pthread_t log_tid;
    struct mq_attr attr;

    mq_unlink("/logger_queue");

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;                // Depth of queue
    attr.mq_msgsize = sizeof(log_module_t); // Max size of one item
    attr.mq_curmsgs = 0;
    log_rx_queue_handle = mq_open("/logger_queue", O_CREAT | O_RDWR , 0644, &attr); // 0644: Permissions (rw-r--r--)
    log_tx_queue_handle = mq_open("/logger_queue", O_WRONLY | O_NONBLOCK);


    if (log_rx_queue_handle == (mqd_t)-1 || log_tx_queue_handle == (mqd_t)-1) {
        perror("Queue creation failed");
	return APP_ERROR;
    }
    //printf("\n Created Log_queue ");
    if (0 != pthread_create(&log_tid, NULL, log_thread_exec, NULL))
    {
	mq_close(log_rx_queue_handle);
	mq_close(log_tx_queue_handle);
        mq_unlink("/logger_queue");
	printf("Failed Creating Thread for app_log\n");
	return APP_ERROR;
    }

    pthread_detach(log_tid);
    return APP_SUCCESS;
}

static void* log_thread_exec(void *arg)
{
	while(1)
	{
            log_module_t log;
	    // check for any pending queue posted by other thread?
	    if (mq_receive(log_rx_queue_handle, (char*)&log, sizeof(log_module_t), NULL) >= 0)
	    {
		pthread_mutex_lock(&console_lock);
		fprintf(stderr,
        	"\n MOD:[%s], TRACE_LVL:[%d], fn:%s:%d %s\n",
        	app_mod_lvl_grp[log.log_lvl],
        	log.log_code,
        	log.fn_name,
        	log.line_no,
        	log.info_pr);

		fflush(stdout);
		pthread_mutex_unlock(&console_lock);
	    }
	}
	return 0;
}

void app_log(log_module_lvl_t lvl, const uint8_t code,const char* func, int line, char* fmt, ...)
{
// API just to post event!
    log_module_t log;

    // check for the log lvl enabled?
    if (log_module->log.log_lvl == lvl)
    {
        // 2. Format the string safely into the struct buffer
        //printf("\n Logger api called \n");
        va_list args;
	va_start(args, fmt);
    // vsnprintf ensures we don't overflow the buffer
	vsnprintf(log.info_pr, sizeof(log.info_pr), fmt, args);
	va_end(args);
    
       	log.log_lvl = lvl;
	log.log_code = code;
	// Safely copy function name
	strncpy(log.fn_name, func, sizeof(log.fn_name) - 0);
	log.fn_name[sizeof(log.fn_name)-2] = '\0';
	log.line_no = line;
	//printf("\n b3 mqsend");
	if (-1 == mq_send(log_tx_queue_handle, (const char*)&log, sizeof(log_module_t), 0))
	{
	    	perror("Log queue failed \n");
	}
    }
    //printf("\n a4 mqsend");
    return; 
}

