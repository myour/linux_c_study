#! /bin/bash -x


is_dir()
{
	set -x
	ARG_NAME=$1
	set +x
	if [ -d "$ARG_NAME" ];then
		return 0
	else
		return 1
	fi
	
}


for DIR in "$@";do
	if is_dir "$DIR"
		then :
	else
		echo "$DIR doesn't exist,Creating it now..."
		mkdir "$DIR" > /dev/null 2>&1
		
		if [ $? -ne 0 ];then
			echo "Can not create directory $DIR"
			exit 1
		fi
	fi
done





