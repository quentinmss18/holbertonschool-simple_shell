# HOLBERTON SCHOOL — simple_shell

Minimal UNIX command line interpreter written in C.
Holberton School project: simple_shell.

---

## Compilation

bash
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 *.c -o hsh
./hsh

---

## Usage

./hsh
$ ls
$ /bin/ls
$ ls -l /tmp
$ exit

- The prompt is displayed only if stdin is a terminal (isatty).
- Ctrl+D (EOF) exits the shell.
- Ctrl+C prints a new prompt without exiting.

---

## Core behavior

Input reading
- Uses getline() to read input from stdin.
- A loop processes one command per line.

Command splitting
- The input line is split into a char ** using strtow().
- Separators handled: space, tab, newline.
- ':' is also handled internally for PATH splitting.

PATH handling
- get_path() retrieves PATH from the environment.
- If the command is not a direct path (/ or ./), PATH directories are searched.
- When found, cmd[0] is replaced with the full executable path.
- fork() is never called if the command does not exist.

Execution
- execve_cmd():
- fork()
- child process runs execve()
- parent waits with waitpid()

Error handling
- Errors match /bin/sh output format.
- Example:
./hsh: 1: qwerty: not found
- Errors are printed to stderr.

---

## Builtins (depending on task progression)

exit
- exit
- exit N (status modulo 256)

env
- prints the current environment

---

## Project files

📁shell.c
- main loop
- prompt handling (isatty)
- signal handling (SIGINT)
- builtins dispatch
- error printing functions

📁execve.c
- execve_cmd(): fork + execve + waitpid

📁get_path.c
- PATH resolution
- command path replacement

📁strtow.c
- input string tokenization

📁shell.h
- function prototypes
- include guards
- extern char **environ
![IMG_7549](https://github.com/user-attachments/assets/0f08bf60-0c4c-4f1b-88b2-cea0610bd14b)
