#!/bin/sh
gcc recv.c -lpthread -o SocketPairRecv
gcc send.c -lpthread -o SocketPairSend
