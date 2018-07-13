#!/bin/bash
EPOCH=`date +%s`
LOG="scale-log-$EPOCH"

mkdir $LOG

echo "Starting all the Datanodes"
for i in {1..5}
do
    ./out/Datanode Datanode-$i > ./$LOG/datanode-log-$i&
done

echo "Starting FS-Server..."
./out/FSServer > ./$LOG/server.log &

SERVER_PID=`pidof FSServer`
echo "FS Server PID [$SERVER_PID]"
