#!/bin/bash
TRAYER="/usr/bin/trayer"
PID=$(ps -ef | grep -v 'grep' | grep "$TRAYER" | awk '{print $2}')
echo $PID

if [[ $PID == '' ]]; then
	$TRAYER --widthtype request --edge top --align right --padding 3 --distance 25 &
else
	kill -9 $PID
fi


