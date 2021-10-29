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


# REDIRECT OUTPUT > (STREAMING DATA INTO FILE) 
  echo  "good day" > file1.txt			# "goot tay"


# !! CAN'T STREAM INTO COMMAND !! 
  echo 'good day' > tr t d >&1 # The command tr turns into a file


# REDIRECT INPUT < (STREAMING DATA INTO COMMAND)
  tr < file1.txt  t d  # OK
# tr < 'good tay' t d  # not working
# file1.txt > tr  t d  # not working
# tr   file1.txt  t d  # not working



# STREAMING DATA VIA PIPE | ,THEN INTO FILE VIA > 
  echo  "goot tay" | tr t d > file1.txt 	# "good day"


# MORE EXAMPLES VIA PIPE
  echo 'goot day' | tr t d				# OK
  echo 'goot day' | tr t d >&1			# OK
  echo 'goot tay' | tr t d >file1.txt	# OK
  cat   file1.txt | tr t d				# OK
