/*
 * urldump2_redis.c
 *
 *  Created on: Oct 27, 2013
 *      Author: vahid
 */

#include "urldump2.h"
#include "urldump2_redis.h"

int connect_to_redis(void){
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    redis_ctx = redisConnectWithTimeout(URLDUMP2_DEFAULT_REDIS_HOST,
    									URLDUMP2_DEFAULT_REDIS_PORT,
    									timeout);
    if (redis_ctx == NULL) {
    	printf("Connection error: can't allocate redis context\n");
    	return -1;
    }

    if (redis_ctx->err){
		printf("Redis Connection error: %s\n", redis_ctx->errstr);
		redisFree(redis_ctx);
		return -1;
    }
    printf("Redis connection: OK\n");
    return 0;
}



void set_in_redis( char *key, char *value ){
	redisReply *reply;
    reply = redisCommand(redis_ctx,"SADD %s %s", key, value);
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);
}
