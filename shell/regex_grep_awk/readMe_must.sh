########### regex  ##################
#### ==> egrep <== ###

egrep '^([0-9]{1,3}\.){3}[0-9]{1,3}$' ip_test.txt						# filt ip
egrep '^[0-9a-zA-Z_\.\-]{1,}@[0-9a-zA-Z]+\.com(\.cn)?$' ip_test.txt		# filt email
egrep '^$' ip_test.txt | wc -l											# count space line


grep -E '^[0-9a-zA-Z_\.\-]{1,}@[0-9a-zA-Z]+\.com(\.cn)?$' ip_test.txt   # filt email



#### ==> find <== ###
find ../ -mtime -1				# in 1 day modified
find ../ -mtime 1				# before yestday modified
find ./ -name "ip_test.tex" 	# find file by name 
find . -type f -exec ls -l {} \;	# -exec attention format
find ./logs -type f -ctime +5 -exec rm -rf {} \;	# find file in logs dir,del file before 5 days ago.
find . -name "*.config" -mtime +5 -ok rm {} \;		# del file with confirm


sudo find /etc/ -name "passwd*" -exec grep "root" {} \;		# find -name -exec grep "" {} \;













