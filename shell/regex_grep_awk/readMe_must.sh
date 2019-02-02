########### regex  ##################
#### ==> egrep <== ###

egrep '^([0-9]{1,3}\.){3}[0-9]{1,3}$' ip_test.txt						# filt ip
egrep '^[0-9a-zA-Z_\.\-]{1,}@[0-9a-zA-Z]+\.com(\.cn)?$' ip_test.txt		# filt email
egrep '^$' ip_test.txt | wc -l											# count space line

grep -E '^[0-9a-zA-Z_\.\-]{1,}@[0-9a-zA-Z]+\.com(\.cn)?$' ip_test.txt
















