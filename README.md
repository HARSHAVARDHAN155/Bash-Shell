# Bash-Shell
An interactive user-defined bash-like shell which supports a semicolon-separated list of commands. Implemented in C, supports I/O redirection, piping, process management, and signal handling. 


# Linux Shell built in C

# Shell

## Description of the Assignment

My bash shell built in c executes some basic commands like cd,echo,ls etc...It is completely built from scratch in c programming language. It even handles Foreground and background process.

## Execution 
- open terminal shell folder and run the following commands :

```
<harsha@harsha-Vostro-3590:~/Desired folder/> make
<harsha@harsha-Vostro-3590:~/Desired folder/> ./a.out

```
- for exiting out of program, run the following command :

```
<harsha@harsha-Vostro-3590:~> exit

```
## Functions
- functions built in this assignment works almost similar to that of the actual linux shell

#### cd : changes Directory
#### ls command
#### echo
#### pwd
#### pinfo
#### repeat
#### foreground and background process
--------------------------------------------------------------
# ASSIGNMENT 3

Assignment 3 is the  continuation of previous assignment of Shell 1, now I am extending the functions in my C shell.

In this assignment, I handled with Input output direction, piping,piping with input output direction,signal handling and jobs invoked from my c shell.

## Files included

- cshell.h      : It contains all the header files , global declared variables , functions
- cd.c          : It contains function used to implement cd command.
- echo.c        : It contains function used to implement echo command.
- fg.c          : It contains function used to implement fg and bg commands.
- ls.c          : It contains function used to implement ls command completely.
- main.c        : It contains functions like to implement background process,foreground process,sig,jobs.
- pinfo.c       : It contains function used to implement pinfo command completely.
- redirection.c : It contains function used to implement input output redirection command completely.
- pipe.c        : It contains function used to implement piping command.
- red_redi.c    : Contains fuctions used to implement Input Output redirection with piping.
- makefile      : It compiles all the c files code which are included in it.

## Functions
- mostly works same as that of actual linux shell

#### Input/Output REDIRECTION
 We know using left arrow and right arrow,we used to implement the input output redirection in actual c shell in the same way using excvp command, I built my own input output redirection.
 
#### PIPING
Using pipe command I made to built pipe command and sucessfully implemented the command

#### PIPING with INPUT OUTPUT REDIRECTION
Using above two fuctions I implemented by changing some logics, I made available to the user to use PIPING with INPUT OUTPUT REDIRECTION

#### JOBS
In printing jobs which are invoked from my C shell . I used to store all the background process in different arrays and used them back in time of printing jobs.

#### SIG
In this command I need to kill the user input job number. By using stored arrays and traversing through the job numbers  and by using kill function I implemented this command

#### fg
This command brings the process to the foreground and the actual shell waits untill its complete the process.

#### bg
This command change the stopped back ground process to running.

#### SIGNAL HANDLING
In signal Handling I controlled according to the signal from the key board.

CTRL-Z : converts the foreground to background process. Using SIGTSTP i sucessfully made the command
CTRL-C : it intterupts the current foreground process.with help of SIGINT i made it available
CTRL-D : exits from the program C shell.







