#!/bin/bash

# REDIRECTING STREAMS /////////////////////////////////////////////

# SYMBOL $@		It means all parameters after executable.
#				ie:  ./test.sh one two three

# >&1	to stdout
# >&2	to stderr

#																	
echo "This is Standard Output (stdout) and my parameters are: \"$@\" " #!!!!!!!!!!!!!
echo "This is Standard Error  (stderr) and my parameters are: \"$@\" "   >&2 # THIS LINE
#																	  	  GOES TO STDERR	 

# TRY RUNNING: 	./test.sh one two three
# output:
#	This is Standard Output (stdout) and my parameters are: "one two three"
#	This is Standard Error  (stderr) and my parameters are: "one two three"

# TRY RUNNING: 	
#	./test.sh one two three  > /dev/null   OR
#	./test.sh one two three 1> /dev/null
#   output:
#	  This is Standard Error  (stderr) and my parameters are: "one two three"
#			(only stderr is preserved and displayed)


# TRY RUNNING: 	./test.sh one two three 2> /dev/null
# output:
#	This is Standard Output  (stdout) and my parameters are: "one two three"
#			(only stdout is preserved and displayed)

# Also possible
#	./test.sh one two three  >&1			all output goes to stdout
#	./test.sh one two three 1>&1			same
#	./test.sh one two three 2>&1			same
#	./test.sh one two three 2> /dev/null	stderr is not displayed, but discarded



