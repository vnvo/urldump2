/*
 * urldump2_config.h
 *
 *  Created on: Oct 7, 2013
 *      Author: vahid
 */

#include "urldump2.h"

#ifndef URLDUMP2_CONFIG_H_
#define URLDUMP2_CONFIG_H_

#define CONF_LINE_BUF_SIZE 1024

/* Default configurations */
#define URLDUMP2_CONF_PATH          "/etc/urldump.conf"
#define URLDUMP2_DEFAULT_DEV        "wlan0"
#define URLDUMP2_DEFAULT_CACHE      15
#define URLDUMP2_DEFAULT_PATTERN    "tcp dst port 80"
#define URLDUMP2_DEFAULT_REDIS_HOST "127.0.0.1"
#define URLDUMP2_DEFAULT_REDIS_PORT 6379
#define URLDUMP2_DEFAULT_REDIS_DB   1


struct urldump2_config{
    char *dev;          // device to listen on
    char *pattern;      // pattern to match traffic
    int  flush_time;    // delay time to fill the cache in seconds
    char *redis_host;   // redis db host
    int  redis_port;    // redis port number
    int  redis_db;      // redis db number
};

struct urldump2_config *confs;

void load_confs(FILE *fd);
struct urldump2_config *parse_config_file( FILE * fd);
struct urldump2_config *init_conf_holder();
void set_conf_param(struct urldump2_config *conf,
                    char *conf_key,
                    char *conf_value);

#endif /* URLDUMP2_CONFIG_H_ */
