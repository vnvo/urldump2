/*
 * http.c
 *
 *  Created on: Oct 8, 2013
 *      Author: vahid
 */

#include "urldump2.h"
#include "urldump2_http.h"


int parse_http_header( const char *payload, struct HttpContext *ctx ){
    char *next_tok;

    ctx->hostname = NULL;
    ctx->referer = NULL;
    ctx->uri = NULL;
    ctx->visited_url = NULL;

    //We are interested in GET requests only.
    if(strstr(payload, "GET") == NULL)
        return 0;

    next_tok = strtok( (char *)payload, "\r\n" );
    do {
        if( strncasecmp(next_tok, "Host: ", 6)==0 )
            ctx->hostname = get_header_value( next_tok );

        else if( strncasecmp(next_tok, "Referer: ", 9)==0 )
            ctx->referer = get_header_value( next_tok );

        else if( strncasecmp(next_tok, "GET ", 4)==0 ||
                 strncasecmp(next_tok, "POST ", 5)==0 ||
                 strncasecmp(next_tok, "CONNECT ", 8)==0){

            ctx->uri = get_uri( next_tok );
        }

    } while( (next_tok = strtok(NULL, "\r\n")) != NULL );

    return 0;
}

char *get_header_value( char *header_line ){
    printf("get_header_value: %s \n", header_line);
    char *val_p;
    char *value;
    val_p = strstr(header_line, ": ");
    if (val_p == NULL)
        return NULL;
    val_p += 2;

    value = (char *) malloc((strlen(val_p)+2)*sizeof(char));

    strcpy(value, val_p);
    printf("value=%s\n", value);
    return value;
}

char *get_uri( char *header_line ){
    char *uri_p;
    char *uri_end_p;
    char *uri;
    uri_p = strstr(header_line, "GET ");
    if (uri_p==NULL){
        uri_p = strstr(header_line, "POST ");
        if(uri_p==NULL)
            return NULL;
        uri_p += 5;

    }else
        uri_p += 4;

    uri = (char *) malloc((strlen(uri_p)+1)*sizeof(char));

    strcpy( uri, uri_p );
    uri_end_p = strstr(uri, " HTTP/1.");
    if(uri_end_p != NULL)
        *uri_end_p = '\0';

    return uri;
}
