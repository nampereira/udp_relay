#!/bin/bash

N=10000

# send burst of N UDP packets to the port where the relay is listening (on localhost)
for i in {1..$N}
do 
     echo "Hello $i times" > /dev/udp/127.0.0.1/1511
done
