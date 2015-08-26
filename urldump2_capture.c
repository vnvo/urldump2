/*
 * urldump2_capture.c
 *
 *  Created on: Oct 12, 2013
 *      Author: vahid
 */

#include "urldump2.h"
#include "urldump2_config.h"
#include "urldump2_capture.h"
#include "urldump2_http.h"
#include "urldump2_redis.h"

void
process_http_request(u_char *args,
                     const struct pcap_pkthdr *header,
                     const u_char *packet)
{
    char src_addr[64];// = (char *)calloc(20, sizeof(char) );// = (char *) malloc( sizeof(char) * 16 );
    char dst_addr[64];// = (char *)calloc(20, sizeof(char) );// = (char *) malloc( sizeof(char) * 16 );
    static long int now = NULL;

    /* declare pointers to packet headers */
    const struct sniff_ip *ip;              /* The IP header */
    const struct sniff_tcp *tcp;            /* The TCP header */
    const char *payload;                    /* Packet payload */

    int size_ip;
    int size_tcp;
    int size_payload;

    /* define/compute ip header offset */
    ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
    size_ip = IP_HL(ip)*4;
    if (size_ip < 20) {
        return;
    }

    /* define/compute tcp header offset */
    tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
    size_tcp = TH_OFF(tcp)*4;
    if (size_tcp < 20) {
        return;
    }

    inet_ntop(AF_INET, &ip->ip_src, src_addr, sizeof(src_addr));
    inet_ntop(AF_INET, &ip->ip_dst, dst_addr, sizeof(dst_addr));

    src_addr[ strlen(src_addr)+1 ] = '\0';
    dst_addr[ strlen(dst_addr)+1 ] = '\0';

    /* define/compute tcp payload (segment) offset */
    payload = (char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);

    /* compute tcp payload (segment) size */
    size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);

    if(strstr(payload, "GET") == NULL)
        return;

    struct HttpContext *http_ctx = (
        struct HttpContext *
        )malloc(sizeof(struct HttpContext));

    if(http_ctx == NULL){
        printf("Can not allocate memory for http context\n");
        syslog(LOG_CRIT, "Can not allocate memory for http context");
        return;
    }

    printf("pasring http: (%d)%s\n", size_payload, payload);
    get_now( &now );
    parse_http_header(payload, http_ctx);

    http_ctx->src_ip = strdup( src_addr );
    http_ctx->dst_ip = strdup( dst_addr );


    if(src_addr != NULL && dst_addr!= NULL){
        printf("RESULT: %ld - %s - %s - %s - %s - %s - %s \n",
               now,
               http_ctx->src_ip, http_ctx->dst_ip,
               http_ctx->hostname, http_ctx->visited_url,
               http_ctx->uri, http_ctx->referer
            );

        char key[256]; //time:src_ip
        char val[2048]; //hostname:uri

        sprintf(key, "%ld:%s", now, http_ctx->src_ip);

        if( http_ctx->referer != NULL )
            sprintf(val, "%s", http_ctx->referer);
        else
            sprintf(val, "%s%s", http_ctx->hostname, http_ctx->uri);

        printf("%s=%s\n", key, val);
        set_in_redis( key, val);

        //free(key);
        //free(val);
    }

    //free(&now);
    free(http_ctx->dst_ip);
    free(http_ctx->src_ip);
    free(http_ctx->hostname);
    free(http_ctx->referer);
    free(http_ctx->uri);
    free(http_ctx->visited_url);
    free(http_ctx);
    http_ctx = NULL;

    return;
}

void get_now( long int *now){
    //time_t now;
    *now = (long int)time(0);
    printf("now=%ld\n", *now);
}

void capture_traffic(){

    char errbuf[PCAP_ERRBUF_SIZE];      /* error buffer */
    pcap_t *handle;                     /* packet capture handle */
    struct bpf_program fp;              /* compiled filter program (expression) */
    bpf_u_int32 net = 0;                /* ip */

    handle = pcap_open_live(confs->dev, SNAP_LEN, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", confs->dev, errbuf);
        exit(EXIT_PCAP_FAILURE);
    }

    /* make sure we're capturing on an Ethernet device */
    if (pcap_datalink(handle) != DLT_EN10MB) {
        fprintf(stderr, "%s is not an Ethernet\n", confs->dev);
        exit(EXIT_PCAP_FAILURE);
    }

    /* compile the filter expression */
    if (pcap_compile(handle, &fp, confs->pattern, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n",
                confs->pattern, pcap_geterr(handle));
        exit(EXIT_PCAP_FAILURE);
    }

    /* apply the compiled filter */
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n",
                confs->pattern, pcap_geterr(handle));
        exit(EXIT_PCAP_FAILURE);
    }

    pcap_loop(handle, 0, process_http_request, NULL);
    pcap_freecode(&fp);
    pcap_close(handle);
}
