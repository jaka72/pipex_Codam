#!/bin/sh
make

function check()
{
	PIPEX=$(cat pipefile)
	SHELL=$(cat shellfile)
	PIPEX_E=$(cat pipefile_e)
	SHELL_E=$(cat shellfile_e)
	printf "\x1b[39m"
	#printf "Contents: $PIPEX\n"
	printf "Result : "
	if [ "$PIPEX" = "$SHELL" ]
	then 
	printf "\x1b[32m"
	printf "[OK]\n"
	else
	printf "\x1b[31m"
	printf "[You can do it!]\n"
	printf "(PIPEX) $PIPEX\n"
	printf "(SHELL) $SHELL\n"
	fi
	printf "\x1b[39m"
	printf "Environment ? : "	
	if [ "$PIPEX_E" = "$SHELL_E" ]
	then 
	printf "\x1b[32m"
	printf "[OK]($PIPEX_E)\n"
	else
	printf "\x1b[31m"
	printf "[You can do it!]\n"
	printf "(PIPEX_E) $PIPEX_E\n"
	printf "(SHELL_E) $SHELL_E\n"
	fi
	printf "\x1b[39m"	
	rm pipefile pipefile_e shellfile shellfile_e
}

#NormalFile cat | wc EmptyFile
printf "\x1b[33m"
printf "<NormalFile cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n" 
./pipex test/normal cat wc pipefile
echo $? > pipefile_e
< test/normal cat | wc > shellfile
echo $? > shellfile_e
check

#NormalFile cat -n | wc EmptyFile
printf "\x1b[33m"
printf "<NormalFile cat -n | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal "cat -n" wc pipefile
echo $? > pipefile_e
< test/normal cat -n | wc > shellfile
echo $? > shellfile_e
check

#NormalFile cat | wc -c EmptyFile
printf "\x1b[33m"
printf "<NormalFile cat | wc -c EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat "wc -c" pipefile
echo $? > pipefile_e
< test/normal cat | wc -c > shellfile
echo $? > shellfile_e
check

#NormalFile cat -n | wc -c EmptyFile
printf "\x1b[33m"
printf "<NormalFile cat -n | wc -c EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal "cat -n" "wc -c" pipefile
echo $? > pipefile_e
< test/normal cat -n | wc -c > shellfile
echo $? > shellfile_e
check

#NormalFile ca | wc EmptyFile
printf "\x1b[33m"
printf "<NormalFile ca | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal ca wc pipefile
echo $? > pipefile_e
< test/normal ca | wc > shellfile
echo $? > shellfile_e
check

#NormalFile cat | wrrr EmptyFile
printf "\x1b[33m"
printf "<NormalFile cat | wrrr EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat wrrr pipefile
echo $? > pipefile_e
< test/normal cat | wrrr > shellfile
echo $? > shellfile_e
check

#NormalFile /cat | wc EmptyFile
printf "\x1b[33m"
printf "<NormalFile /cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal /cat wc pipefile
echo $? > pipefile_e
< test/normal /cat | wc > shellfile
echo $? > shellfile_e
check

#NormalFile cat/ | wc EmptyFile
printf "\x1b[33m"
printf "<NormalFile cat/ | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat/ wc pipefile
echo $? > pipefile_e
< test/normal cat/ | wc > shellfile
echo $? > shellfile_e
check

#NoFile cat | wc EmptyFile
printf "\x1b[33m"
printf "<NoFile cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex a cat wc pipefile
echo $? > pipefile_e
< a cat | wc > shellfile
echo $? > shellfile_e
check

#File0 cat | wc EmptyFile
printf "\x1b[33m"
printf "<File0 cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/file0 cat wc pipefile
echo $? > pipefile_e
< test/file0 cat | wc > shellfile
echo $? > shellfile_e
check

#p0File cat | wc EmptyFile
printf "\x1b[33m"
printf "<p0File cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/p0file cat wc pipefile
echo $? > pipefile_e
< test/p0file cat | wc > shellfile
echo $? > shellfile_e
check

#p1File cat | wc EmptyFile
printf "\x1b[33m"
printf "<p1File cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/p1file cat wc pipefile
echo $? > pipefile_e
< test/p1file cat | wc > shellfile
echo $? > shellfile_e
check

#p2File cat | wc EmptyFile
printf "\x1b[33m"
printf "<p2File cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/p2file cat wc pipefile
echo $? > pipefile_e
< test/p2file cat | wc > shellfile
echo $? > shellfile_e
check

#p3File cat | wc EmptyFile
printf "\x1b[33m"
printf "<p3File cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/p3file cat wc pipefile
echo $? > pipefile_e
< test/p3file cat | wc > shellfile
echo $? > shellfile_e
check

#p4File cat | wc EmptyFile
printf "\x1b[33m"
printf "<p4File cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/p4file cat wc pipefile
echo $? > pipefile_e
< test/p4file cat | wc > shellfile
echo $? > shellfile_e
check

#p5File cat | wc EmptyFile
printf "\x1b[33m"
printf "<p5File cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/p5file cat wc pipefile
echo $? > pipefile_e
< test/p5file cat | wc > shellfile
echo $? > shellfile_e
check

#p6File cat | wc EmptyFile
printf "\x1b[33m"
printf "<p6File cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/p6file cat wc pipefile
echo $? > pipefile_e
< test/p6file cat | wc > shellfile
echo $? > shellfile_e
check

#p7File cat | wc EmptyFile
printf "\x1b[33m"
printf "<p7File cat | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/p7file cat wc pipefile
echo $? > pipefile_e
< test/p7file cat | wc > shellfile
echo $? > shellfile_e
check

#NoFile badcmd | wc EmptyFile
printf "\x1b[33m"
printf "<NoFile badcmd | wc EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex a badcmd wc pipefile
echo $? > pipefile_e
< a badcmd | wc > shellfile
echo $? > shellfile_e
check

#NoFile cat | badcmd EmptyFile
printf "\x1b[33m"
printf "<NoFile cat | badcmd EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex a cat badcmd pipefile
echo $? > pipefile_e
< a cat | badcmd  > shellfile
echo $? > shellfile_e
check

#NormalFile cat | cat EmptyFile
printf "\x1b[33m"
printf "<NormalFile cat | cat EmptyFile>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat cat pipefile
echo $? > pipefile_e
< test/normal cat | cat > shellfile
echo $? > shellfile_e
check

#NormalFile cat | wc np0
printf "\x1b[33m"
printf "<NormalFile cat | wc np0>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat wc test/np0_pipefile
echo $? > pipefile_e
< test/normal cat | wc > test/np0_shellfile
echo $? > shellfile_e
check

#NormalFile cat | wc np1
printf "\x1b[33m"
printf "<NormalFile cat | wc np1>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat wc test/np1_pipefile
echo $? > pipefile_e
< test/normal cat | wc > test/np1_shellfile
echo $? > shellfile_e
check

#NormalFile cat | wc np2
printf "\x1b[33m"
printf "<NormalFile cat | wc np2>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat wc test/np2_pipefile
echo $? > pipefile_e
< test/normal cat | wc > test/np2_shellfile
echo $? > shellfile_e
check

#NormalFile cat | wc np3
printf "\x1b[33m"
printf "<NormalFile cat | wc np3>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat wc test/np3_pipefile
echo $? > pipefile_e
< test/normal cat | wc > test/np3_shellfile
echo $? > shellfile_e
check

#NormalFile cat | wc np4
printf "\x1b[33m"
printf "<NormalFile cat | wc np4>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat wc test/np4_pipefile
echo $? > pipefile_e
< test/normal cat | wc > test/np4_shellfile
echo $? > shellfile_e
check

#NormalFile cat | wc np5
printf "\x1b[33m"
printf "<NormalFile cat | wc np5>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat wc test/np5_pipefile
echo $? > pipefile_e
< test/normal cat | wc > test/np5_shellfile
echo $? > shellfile_e
check

#NormalFile cat | wc np6
printf "\x1b[33m"
printf "<NormalFile cat | wc np6>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat wc test/np6_pipefile
echo $? > pipefile_e
< test/normal cat | wc > test/np6_shellfile
echo $? > shellfile_e
check

#NormalFile cat | wc np7
printf "\x1b[33m"
printf "<NormalFile cat | wc np7>\n"
printf "\x1b[39m"
printf "Error message:\n"
./pipex test/normal cat wc test/np7_pipefile
echo $? > pipefile_e
< test/normal cat | wc > test/np7_shellfile
echo $? > shellfile_e
check


#LargeFile cat | cat Emptyfile
#MiddleLarge cat | cat Emptyfile
#NormalFile ls | ls EmptyFile

printf "\x1b[39m"
make fclean
