/*
 * urldump2.h
 *
 *  Created on: Oct 7, 2013
 *      Author: vahid
 *
 *  This is the main header file, all the global and shared declarations has
 *  to be here. This will be included in all source files.
 */

#ifndef URLDUMP2_URLDUMP2_H_
#define URLDUMP2_URLDUMP2_H_


#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include <time.h>

#define APP_VERSION "0.1"
#define APP_NAME    "urldump2"
#define APP_DESC    "HTTP Referer Sniffer"

#define EXIT_GENERAL_FAILURE 1
#define EXIT_PCAP_FAILURE    2
#define EXIT_REDIS_FAILURE   3


#endif /* URLDUMP2_URLDUMP2_H_ */
