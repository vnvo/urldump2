/*
 * urldump2_config.c
 *
 *  Created on: Oct 11, 2013
 *      Author: vahid
 */
#include "urldump2_config.h"


void load_confs( FILE *fd){
	if(fd == NULL){
		printf("No conf file specified\n");
	}
	struct urldump2_config *urldump_conf = init_conf_holder();

	confs = urldump_conf;
}


struct urldump2_config *init_conf_holder(){
	struct urldump2_config *urldump_conf = (struct urldump2_config *)malloc( sizeof(struct urldump2_config) );
	if(urldump_conf == NULL){
		printf("FATAL: Failed to allocate memory for configurations.\n");
		return NULL;
	}

	urldump_conf->dev = URLDUMP2_DEFAULT_DEV;
	urldump_conf->pattern = URLDUMP2_DEFAULT_PATTERN;
	urldump_conf->flush_time = URLDUMP2_DEFAULT_CACHE;

	urldump_conf->redis_host = URLDUMP2_DEFAULT_REDIS_HOST;
	urldump_conf->redis_port = URLDUMP2_DEFAULT_REDIS_PORT;
	urldump_conf->redis_db = URLDUMP2_DEFAULT_REDIS_DB;

	return urldump_conf;
}
