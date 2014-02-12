srcdir    = .
prefix    = /opt/urldump2/
execdir   = ${prefix}/bin
libdir    = ${prefix}/lib
confdir   = ${prefix}/etc
target    = ${prefix}/bin

CC      = gcc
CFLAGS  = -O3 -g -Wall -D_GNU_SOURCE_ -pthread -DHAVE_NET_ETHERNET_H -static
LIBS    = -lpcap -L$(srcdir) -lpthread -lhiredis
HDRS    = urldump2_config.h urldump2_capture.h urldump2_http.h
OBJS 	= urldump2.o urldump2_capture.o urldump2_redis.o urldump2_http.o urldump2_config.o

urldump2: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) 

urldump2.o:
	$(CC) $(CFLAGS) -I. -c $(srcdir)/$*.c

clean:
	rm -rf *.o
	rm -rf urldump2

cleanall:
	rm -rf urldump2
	rm -rf urldump2.o
	rm -f ${execdir}/*
	rm -f ${libdir}/*
	rm -f ${confdir}/*

install:
	mkdir -p ${prefix} ${execdir} ${confdir}
	cp urldump2 ${execdir}/
