#!/bin/sh


for myfile in $(ls);do

	printf "$myfile"
	if [ -d "$myfile" ];then
		echo " is a directory."
	elif [ -f "$myfile" ];then
		if [ -x "$myfile" ];then
			echo " is a execute file."
		else
			echo " is a common file."
		fi
	else
		echo " is a other file."
	fi

done
