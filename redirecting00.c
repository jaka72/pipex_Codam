/*

> REDIRECT OUTPUT

who
who > file1.txt		Writes output to file, not terminal

echo from terminal > file1.txt		deletes and writes to file 
echo from terminal >> file1.txt 	appends to file


------------------------------------------------------------------

< REDIRECT INPUT

Program wc can take input and gives output

wc -l file1.txt
  33 file1.txt			wc knows that it is reading from this file


< file1.txt	wc -l	
	or
wc -l < file1.txt		file content first goes to stdinput, then wc reads 
  33					reads from stdinput. wc doesn't know from which file info came 

Not possible:
  file1.txt > wc -l

*/