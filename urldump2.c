/*
 * urldump2.c
 *
 *  Created on: Oct 7, 2013
 *      Author: vahid
 */

#include "urldump2.h"
#include "urldump2_config.h"
#include "urldump2_capture.h"
#include "urldump2_redis.h"

int main(int argc, char **argv){
    printf("starting ...\n");
    load_confs(NULL);
    connect_to_redis();
    //syslog(LOG_NOTICE, "Starting URLDUMP2 v%s . PID : %d", APP_VERSION, getpid());
    //connect_cache();
    capture_traffic();
    return 0;

}
