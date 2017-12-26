#
# Copyright (c) Microsoft Corporation. All rights reserved.
#

#
# Makefile for spray RPC client and server.
# Copyright 1994, Olaf Kirch, <okir@monad.swb.de>
#

ALL = sprayd spray
CFLAGS += -D_ALL_SOURCE
LIB = -lrpclib

build: $(ALL)

sprayd:	sprayd.o spraystat.o spray_xdr.o
	$(CC) $(LDFLAGS) -o $@ sprayd.o spraystat.o spray_xdr.o $(LIB)

spray:	spray.o  spray_xdr.o
	$(CC) $(LDFLAGS) -o $@ spray.o spray_xdr.o $(LIB)

spraystat.o:	spraystat.c spraystat.h spray.h
sprayd.o:	sprayd.c spraystat.h spray.h
spray_xdr.o:	spray_xdr.c spray.h
spray.o:	spray.c spray.h

clean:
	rm -f *.o

clobber: clean
	rm -f $(ALL)
