# holbertonschool-simple_shell
A simple UNIX command line interpreter developed for Holberton School.

## Description
This shell can:
* Display a prompt and wait for the user to type a command.
* Execute commands with their arguments (ex: `ls -l /tmp`).
* Handle the `PATH` to find executable programs.
* Implement built-ins: `exit` and `env`.
* Handle the end-of-file (Ctrl+D).
<![IMG_7549](https://github.com/user-attachments/assets/2739e624-512b-4076-8dfe-69f80e5718e1)


## Compilation
The shell is compiled this way:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
Usage
Interactive mode:

Bash

$ ./hsh
($) /bin/ls
hsh main.c shell.h
($) exit
Non-interactive mode:

Bash

$ echo "/bin/ls" | ./hsh
hsh main.c shell.h
