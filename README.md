# Minishell

Minishell is a 42 School project aimed at creating a minimalist shell in C, mimicking basic functionalities of Bash. This project helps deepen understanding of processes, file descriptors, and system calls in a Unix-like environment. This version successfully implements all mandatory and bonus features.


# Features

## Mandatory Part

  - **Interactive Prompt**: Displays a prompt for user input.
  - **Non-Interactive Mode**: Capable of executing commands piped from another process (e.g., `echo "ls -l" | ./minishell`).
  - **Command Execution**: Executes commands using absolute, relative, or `PATH`-based paths.
  - **Handles Built-in Commands**:
      - `echo [-n] [string ...]`: Prints text, with `-n` to suppress the newline.
      - `cd [path]`: Changes the current directory. Supports `cd -` (previous directory) and `cd` (home directory).
      - `pwd`: Prints the current working directory.
      - `export [name[=value]]`: Sets or modifies environment variables. Also supports `+=` to append to an existing value.
      - `unset [name]`: Removes environment variables.
      - `env`: Displays environment variables.
      - `exit [status]`: Exits the shell with an optional status code.
  - **Supports Input/Output Redirections** (`>`, `>>`, `<`).
  - **Implements Pipes (`|`)** for inter-process communication.
  - **Expands Environment Variables** (e.g., `$HOME`, `$?` for exit status).
  - **Handles Signals**:
      - `Ctrl+C` (`SIGINT`): Displays a new prompt on a new line.
      - `Ctrl+D` (`EOF`): Exits the shell.
      - `Ctrl+\` (`SIGQUIT`): Ignored or handled appropriately.

## Bonus Part

  - **Supports Logical Operators**:
      - `&&`: Executes the next command only if the previous succeeds.
      - `||`: Executes the next command only if the previous fails.
  - **Parentheses `()`** for command precedence.
  - **Implements Wildcard Expansion (`*`)** for file matching.


# Compilation and Usage

## Prerequisites

  - A Unix-based system (Linux or macOS).
  - `gcc` compiler and `make`.
  - The `readline` library (e.g., `libreadline-dev` or `brew install readline`).

## Compilation

```bash
# Clone the repository
git clone https://github.com/simocv00/minishell
cd minishell

# Compile the project (includes bonus features)
make
```

This generates the `minishell` executable.

## Running the Shell

```bash
./minishell
```


# Example Commands

```bash
$ ls -l | grep .c > output.txt

$ export MY_VAR=42 && echo "Var is $MY_VAR"
Var is 42

$ (ls /non_existent_dir && echo "Success") || echo "Failure"
Failure

$ ls *.c
main.c parser.c utils.c
```



# Technical Details

  - **Parsing**: Uses a lexer, parser, and expander to process user input, respecting quotes and special characters.
  - **Standard I/O**: Mimics `bash` by writing the prompt to `stderr` and uses buffered output for efficiency.
  - **Execution**: Utilizes `execve()` for external commands and custom implementations for built-ins. Pipes are handled using `pipe()` and `dup2()` for file descriptor management.
  - **Resource Management**: Ensures no memory leaks or unclosed file descriptors, tested thoroughly with `valgrind`.
  - **Bonus Features**: A doubly linked list is used to manage the command execution pipeline, allowing for correct precedence with `&&`, `||`, and parentheses. Wildcard expansion uses pattern matching in the current directory.



# Notes

  - The project adheres to 42’s `Norminette` coding standards.
  - Known limitations: Does not support multiline commands, backslashes (`\`), or semicolons (`;`) as per the project requirements.



# Credits

This project was developed in collaboration by Mohamed El ayyady and Mohammed Akarkaou as part of the 42 School curriculum.
