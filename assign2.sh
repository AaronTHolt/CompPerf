#!/bin/bash

COUNTER=0

while [ $COUNTER -lt 11 ]; do
    
    echo $COUNTER

    date >> data.txt

    snmpwalk -v 2c -c public 128.138.207.5:7777 >> data.txt
    
    let COUNTER=COUNTER+1

    date >> data.txt

    sleep 600

done