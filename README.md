urldump2
========

simple experimental libpcap based dumper for http header info!
currently you can specify a libpcap filter in config file and it will
dump referer data into a redis backend.

you can modify it to extract any required field from http header.


TODO:
- config file parser
- make target header item configurable (referer, location, agent, ...)


Dependencies:
```
libpcap
hiredis
```

To Use:
```
# make
```

To use default config:
```
# ./urldump2
```

To specify a config file (TBD)
```
# ./urldump2 -c /path/to/urldump2.config
```
