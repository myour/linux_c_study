#!/bin/bash


echo "It is morning or afternoon? YES/NO"
read YES_OR_NO
if [ "$YES_OR_NO" = "yes" ];then
	echo "Good morning!"
elif [ "$YES_OR_NO" = "no" ];then
	echo "Good afternoon."
else
	echo "Input not igill."
#	exit 1
fi
#exit 0


