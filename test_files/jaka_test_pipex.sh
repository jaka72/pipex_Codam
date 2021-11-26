#/bin/bash

COL="3[4;34;37m"
YEL="\033[1;33m"
RES="\033[1;37m"
LGREY="\033[0;37m"
LCYAN="\033[1;36m"

i=0
echo -e "TEST ${i}:  infile cat 'wc -l' outfile\n  Shell:" > outfile
cat infile | wc -l >> outfile
echo "  Pipex:" >> outfile
./pipex infile cat "wc -l" tempfile;   cat tempfile >> outfile

i=$(( i+1 ))
echo -e "\nTEST ${i}:  infile cat 'wc' outfile\n  Shell:" >> outfile
cat infile | wc >> outfile
echo "  Pipex:" >> outfile
./pipex infile cat "wc" tempfile;   cat tempfile >> outfile

i=$(( i+1 ))
echo -e "\nTEST ${i}:  infile 'sleep 1' 'sleep 1' outfile\n  Shell:" >> outfile
< infile sleep 0 | sleep 0 >> outfile
echo "  Pipex:" >> outfile
./pipex infile "sleep 0" "sleep 0" tempfile;   cat tempfile >> outfile

i=$(( i+1 ))
echo -e "\nTEST ${i}:  infile cat 'grep six' outfile\n  Shell:" >> outfile
< infile cat | grep 'six' >> outfile
echo "  Pipex:" >> outfile
./pipex infile cat 'grep six' tempfile;   cat tempfile >> outfile

# cat | grep -c hello
i=$(( i+1 ))
echo -e "\nTEST ${i}:  infile cat 'grep -c hello' outfile\n  Shell:" >> outfile
< infile cat | grep -c 'hello' >> outfile
echo "  Pipex:" >> outfile
./pipex infile cat 'grep -c hello' tempfile;   cat tempfile >> outfile

# head -c 12
i=$(( i+1 ))
echo -e "\nTEST ${i}:  infile 'head -c 12' cat outfile\n  Shell:" >> outfile
< infile head -c 12 | cat  >> outfile
echo "  Pipex:" >> outfile
./pipex infile 'head -c 12' cat tempfile;   cat tempfile >> outfile


# all lines with "hello" | print number, '-' , first item
# < infile grep hello | awk '{print NR " - " $1 }' > outfile
# < infile grep six | awk '{print NR " - " $1 }' > outfile