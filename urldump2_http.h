/*
 * http.h
 *
 *  Created on: Oct 8, 2013
 *      Author: vahid
 */

#ifndef URLDUMP2_HTTP_H_
#define URLDUMP2_HTTP_H_

#include "urldump2.h"

struct HttpContext {
    ulong req_epoch; // time of request
    char *src_ip;   // source ip of request
    char *dst_ip;   // destination ip of request
    char *hostname;
    char *referer;
    char *uri;
    char *visited_url;
};


int parse_http_header( const char *http_req, struct HttpContext *ctx);
char *get_header_value( char *header_line );
char *get_uri( char *header_line );

#endif /* URLDUMP2_HTTP_H_ */
