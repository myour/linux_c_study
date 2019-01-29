#! /bin/bash


count=2
echo "Enter you name?"
read name

while [ "$name" != "ke" -a "$count" -gt 0 ];do
	echo "Password error,try again."
	read name
	count=$[$count-1]
done

if [ "$count" -le 0 -a "$name" != "ke" ];then
	echo "Sorry.try again later."
else
		echo "welcome $name."
fi

