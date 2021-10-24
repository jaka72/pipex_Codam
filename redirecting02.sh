#!/bin/bash

# REDIRECTING TO ANOTHER FILE

#																	
echo "This is Standard Output (stdout) and my parameters are: \"$@\" " #!!!!!!!!!!!!!
echo "This is Standard Error (stderr)  and my parameters are: \"$@\" "   >&2 # THIS LINE
#																		GOES TO STDERR	 

# ./redirecting02.sh  hello  > temp.txt
# output:
#			/
#		(both lines go to the file temp.txt)


# ./redirecting02.sh  hello  2> error.log
# output:
# 	This is Standard Output (stdout) and my parameters are: "hello temp.txt" 
#		(second line goes to the file error.log)


# call executable to produce error
# gcc give_error.c && ./a.out



echo  "goot tay" | tr t d > file1.txt 
# 	good day
file1.txt > tr  t d  # not working
tr   file1.txt  t d  # not working
tr < file1.txt  t d  # OK
tr < 'good tay' t d  # not working


echo 'goot day' > tr t d >&1 # nothing happens
echo 'goot day' | tr t d     # OK
echo 'goot day' | tr t d >&1 # OK
echo 'goot tay' | tr t d >file1.txt # OK
cat   file1.txt | tr t d 	 # OK
