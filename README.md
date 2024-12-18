# Minishell  
**As beautiful as a shell**  

## Summary  
Minishell is a project designed to create a minimal shell (like Bash), allowing users to interact with a computer through command-line input. It provides an opportunity to explore process management, file descriptors, signal handling, and many other low-level programming concepts.  

---

## Features  

### **Mandatory Features**  
- **Interactive Prompt**: Displays a prompt and waits for user commands.  
- **Command Execution**: Executes commands using the `PATH` environment variable or relative/absolute paths.  
- **History Management**: Keeps track of previously executed commands.  
- **Quoting System**:  
  - Single quotes (`'`) prevent interpretation of meta-characters.  
  - Double quotes (`"`) prevent interpretation except for `$`.  
- **Redirections**:  
  - `<`: Redirects input.  
  - `>`: Redirects output.  
  - `<<`: Reads input until a given delimiter (heredoc).  
  - `>>`: Redirects output in append mode.  
- **Pipes**: Implements pipelines to connect the output of one command to the input of another (e.g., `ls | grep file`).  
- **Environment Variables**: Handles variables starting with `$` and supports `$?` for the last exit status.  
- **Signal Handling**:  
  - `Ctrl+C`: Displays a new prompt.  
  - `Ctrl+D`: Exits the shell.  
  - `Ctrl+\`: Does nothing.  
- **Built-in Commands**:  
  - `echo`: Prints to standard output.  
  - `cd`: Changes the current directory.  
  - `pwd`: Prints the current directory.  
  - `export`: Sets environment variables.  
  - `unset`: Unsets environment variables.  
  - `env`: Prints all environment variables.  
  - `exit`: Exits the shell.  

### **Bonus Features**  
*The bonus features will only be evaluated if the mandatory part is perfect.*  
- Logical operators (`&&` and `||`) with support for parentheses.  
- Wildcard (`*`) support for the current working directory.  

---

## Requirements  
- **Programming Language**: C  
- **External Libraries**:  
  - [Readline](https://tiswww.case.edu/php/chet/readline/rltop.html)  
- **System Calls**:  
  - `fork`, `execve`, `pipe`, `dup2`, `read`, `write`, `open`, `close`, `kill`, etc.  
- **Code Norms**: Follow the [42 Norm](https://github.com/42School/norminette).  

---

## Installation  

1. Clone the repository:  
   ```bash  
   git clone https://github.com/oelbouha/minishell 
   cd minishell  
Compile the project:

bash
make  
Run the shell:

bash
./minishell  
Usage
Launch the shell using the above steps.
Use standard commands like ls, pwd, or any custom-built commands.
Test features like redirections, pipes, and environment variable expansion.
Examples:

bash
> echo "Hello, Minishell!"  
Hello, Minishell!  

> ls | grep minishell  
minishell.c  

> export VAR=42  
> echo $VAR  
42  
Project Structure

minishell/  
├── Makefile          # Build script  
├── src/              # Source code files  
│   ├── main.c        # Entry point for the shell  
│   ├── parser.c      # Handles command parsing  
│   ├── executor.c    # Executes commands  
│   ├── builtins.c    # Implements built-in commands  
│   ├── signals.c     # Signal handling  
│   └── utils.c       # Utility functions  
├── include/          # Header files  
│   ├── minishell.h   # Main header file  
│   └── ...  
└── libft/            # 42's Libft library (if used)  
Key Concepts
Processes: Mastering fork, execve, and managing process hierarchies.
File Descriptors: Redirections and pipes are based on file descriptor manipulation.
Signal Handling: Handling user interrupts like Ctrl+C gracefully.
Memory Management: Ensuring no memory leaks using tools like valgrind.
Challenges Faced
Parsing commands with quotes and special characters.
Managing multiple processes in a pipeline.
Handling edge cases for built-in commands and redirections.
Resources
GNU Readline Documentation
Linux System Calls<br>
