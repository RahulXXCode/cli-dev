#ifndef APP_DEF_H
#define APP_DEF_H

#include <stdio.h>
#include "../../common/types.h"
#include "../../driver/include/driver.h"

typedef enum {
    APP_MOD_CLI_TYPE,
    APP_MOD_MEM_TYPE
} eMod_type;

app_ret_t module_init(eMod_type mod);
#endif
