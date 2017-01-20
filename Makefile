#!/bin/sh
.SUFFIXES : .c .o 

# CONSTANTES
CC = g++  # -lc -lpthread 
MAKE = make

# make entries

CFLAGS = -Wall -g

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

help:
	echo make arinc
	
all:
	$(MAKE) arinc   #2>errlog

# ARINC examples
arinc:
	$(MAKE) Qclient
	$(MAKE) Qserver 
	$(MAKE) kernel

# QUEUING PORTS client and server examples

Qclient: ARINC_Com.o Control_client.o
	$(CC) ARINC_Com.o Control_client.o -o  Qclient

Qserver: ARINC_Com.o Control_server.o cameraController.cpp attitudeController.cpp
	$(CC) ARINC_Com.o Control_server.o cameraController.cpp attitudeController.cpp -o  Qserver

kernel: kernel_arinc.cpp
	gcc kernel_arinc.cpp

# CLEAN .o
clean:
	rm *.o


