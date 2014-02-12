"""
    This script will flush all data in urldump's redis db into
    Postgresql DB
"""

import redis
import pg
import sys

data = []

def getRedisConnection():
    c = redis.Redis()
    return c

def getPGConnection():
    pass

def prepareData(epoch, ip, url):
    _epoch = None

def flushToPG(data):
    pass

def main():
    c = getRedisConnection()
    keys = c.keys()
    for k in keys:
        try:
            url_set = c.smembers( k )
        except:
            continue
        epoch, ip = k.split(":")
        for url in url_set:
            prepareData(epoch, ip, url)
            
    pprint.pprint( data )
        
        