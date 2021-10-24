#!/bin/bash

# DIFFERENCE PIPE vs REDIRECTION

# A) Pipe is used to pass output to another program or utility.

	./a.out > file2.txt 

# B) Redirect is used to pass output to either a file or stream.

 ####


#       INPUT            OUTPUT
#	  result goes      from output
#	   to output         to file
	sort  <  file2.txt  >  file1.txt 
#	( (1st action )   2nd action )



grep one file1.txt
# to use with < input redirection,
# needs to be reversed:
< file1.txt grep lucy   > file2.txt 		# prints that line into file

< file1.txt grep lucy  |  wc -l > file2.txt # prints nr lines to file




