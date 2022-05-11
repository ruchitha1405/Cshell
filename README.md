### To Run
Run the following commands to start the shell:
```
$ make
$ ./a.out
```
The shell displays a prompt and is ready to take input commands. <br>
To quit, enter 'quit' or hit Ctrl D.

###Functionality:

1.main.c

This contains the main function of the program. The main function includes the primary shell-loop of the program. It reads the input string and parse into commands broken by a semi-colon and  execute commands.

2.prompt.c

This file is responsible for implementing and printing the prompt of the shell. 

3.cd.c

This is responsible for implementing 'cd' functionality.

4.echo.c

This is responsible for implementing 'echo' functionality.

5.pwd.c

This is responsible for implementing 'pwd' functionality.

6.ls.c

This is responsible for implementing 'ls' functionality.<br>
can enter max 60 directories as arguments for an ls command.

7.pinfo.c

This is responsible for implementing 'pinfo' functionality which prints the information regarding a process on the terminal.

8.repeat.c

This is responsible for implementing 'pinfo' functionality.

9.headers.h

This includes all the header files used from C Library and user defined header files. it also has global variables declared.

10.ctrl.c

Ctrl-D Exits the shell.<br>
Ctrl-Z Pushes the currently running foregorund job to background after stopping it.<br>
Ctrl-C Sends the SIGINT signal to interrupt the current foreground process.<br>


11.jobs.c

Displays all the currently Running/Stopped jobs based on the flag given as argument.

12.fbg.c

bg < jobnumber > Changes a stopped background job given by job number to running.<br>
fg < jobnumber > Resumes a running or stopped background process given by the entered job number and brings it to the foreground.<br>

13.pipe.c

This is responsible for implementing piping functionality.

14.redirection.c.

This is responsible for implementing redirection functionality.<br>
Both redirection and piping can be handled with use of the " < "," > "," >> " or "| " operators.

15.bg_exitstatus.c

This is responsible for printing exit status of background processes.

12.sig.c

This is responsible for implementing sig command.

Assumptions:

1.inputstr can be 100000 characters long i.e, The total no. of commands  separated by semi-colon should be less than  100.<br>
2.lenth of each command is at most 1000.<br>
3.total number of background processes that can be run during one session of shell program is 100.


