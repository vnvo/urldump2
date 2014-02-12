/*
 * urldump2_redis.h
 *
 *  Created on: Oct 27, 2013
 *      Author: vahid
 */

#ifndef URLDUMP2_REDIS_H_
#define URLDUMP2_REDIS_H_

#include "urldump2_redis.h"
#include "urldump2_config.h"
#include <hiredis/hiredis.h>


redisContext *redis_ctx;

int connect_to_redis(void);
void set_in_redis( char *key, char *value );

#endif /* URLDUMP2_REDIS_H_ */
