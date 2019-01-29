#!/bin/bash



echo "Enter yes or no."
read Y_OR_N
case "$Y_OR_N" in

	YES|yes|y|Y)
		echo "Get yes.";;
	[nN]?)
		echo "Get no.";;
	*)
		echo "Get others.";;
esac

echo "going to return."
return 0
echo "return done."
	
