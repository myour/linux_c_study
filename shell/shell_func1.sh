#! /bin/bash



echo "Test input args."
echo "------- before --------"
echo $0
echo $1
echo $2
echo $3
echo $4
echo $#
echo $@

foo(){

	echo "------- foo --------"
	echo $0
	echo $1
	echo $2
	echo $3
	echo $4
	echo $#
	echo $@

}


foo 11 22 33 44 55



