# 42-Pipex

This project is the discovery in detail and by programming of a UNIX mechanism called pipe();

# How to use
1. Clone repo
2. Call ```make release``` from inside the folder
3. Start program with ```./pipex in_file "cmd 1" "cmd 2" out_file```

**practical example**

The execution of the pipex program with the following command should do the same as the next shell command:

my pipex: ```./pipex Makefile "grep printf" "wc -l" out```

orig. bash: ```< Makefile grep printf | wc -l > out```

## Other possible inputs:
**here_doc:** ```./pipex here_doc limiter "cmd 1" "cmd 2" out_file``` == ```cmd 1 << limiter | cmd 2 > out```

**multiple pipes:** <br>```./pipex here_doc limiter "cmd 1" "cmd 2" "cmd 3" "cmd ..." out_file``` == ```cmd 1 << limiter | cmd 2 | cmd 3 | cmd ... > out```

<br>
<hr>
<b>*All 42 projects must be written in C (later C++) in accordance to the 42 School Norm.<br></b>
<br>

> #### Sample restrictions:
> - All variables have to be declared and aligned at the top of each function```
> - Each function can not have more then 25 lines```
> - Projects should be created with allowed std functions otherwise it is cheating
