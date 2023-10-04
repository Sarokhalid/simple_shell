# Testing-Simple-Shell
Pre Poject

This C program is a simple shell-like application that allows users to execute commands, maintains command history, and handles signals like Ctrl+C (SIGINT) and Ctrl+Z (SIGTSTP). Let's break it down:

    Header Files and Constants:
        The program includes several standard C libraries for file handling, string manipulation, and process control.
        It defines some constants, such as MAX_CMD_LEN for the maximum command length, HISTORY_COUNT for the number of command history entries to keep, and HISTORY_FILE for the filename where history is stored.

    Data Structures:
        It defines a Node structure to create a linked list to store command history.
        A global variable head is used to keep track of the linked list's head.

    Signal Handling:
        There are two signal handler functions: handle_sigint for Ctrl+C and handle_sigtstp for Ctrl+Z. These functions display prompts when these signals are received.

    Command History:
        The insert_cmd function is used to insert a new command into the command history. It dynamically allocates memory for a new node and stores the command.
        clear_history frees the memory occupied by the history list.
        write_history writes the command history to a file specified by HISTORY_FILE.
        read_history reads the command history from the same file during program startup.

    Executing Commands:
        The execute_cmd function is used to execute commands. It forks a new process, parses the command into arguments, and uses execvp to execute the command in the child process.
        It also waits for the child process to finish using waitpid.

    Main Function:
        The main function initializes signal handlers, reads command history from the file, and enters a loop to accept user commands.
        It gets the current working directory and username to display a custom prompt.
        User input is read using fgets, and if it exceeds MAX_CMD_LEN, an error message is displayed.
        The program checks if the command is exit to break out of the loop and exit.
        Otherwise, it inserts the command into history and executes it.

    Cleanup and Exiting:
        After the loop, the program clears the history and writes the updated history to the file before exiting.

## Functions:

    void handle_sigint(int signum):
        This function is a signal handler for Ctrl+C (SIGINT).
        When Ctrl+C is pressed, it prints a newline and a shell prompt to the console, effectively cancelling the current command.
        It's registered as the handler for SIGINT using signal(SIGINT, handle_sigint); in the main function.

    void handle_sigtstp(int signum):
        This function is a signal handler for Ctrl+Z (SIGTSTP).
        When Ctrl+Z is pressed, it prints a newline to the console, effectively suspending the current command.
        It's registered as the handler for SIGTSTP using signal(SIGTSTP, handle_sigtstp); in the main function.

    void insert_cmd(const char* cmd):
        This function inserts a command into the command history linked list.
        It dynamically allocates memory for a new Node, copies the command into it, and adds it to the beginning of the linked list.
        If the number of commands exceeds HISTORY_COUNT, it trims the oldest command from the list.

    void clear_history():
        This function deallocates memory for all nodes in the command history linked list, effectively clearing the history.

    void write_history():
        This function writes the command history to a file specified by HISTORY_FILE.
        It opens the file in write mode, iterates through the linked list, and writes each command to the file.

    void read_history():
        This function reads the command history from the file specified by HISTORY_FILE during program startup.
        It opens the file in read mode, reads each line (representing a command), and inserts it into the command history using insert_cmd.

    void execute_cmd(const char* cmd):
        This function is responsible for executing a command passed as an argument.
        It forks a new process using fork(). In the child process, it parses the command into arguments and attempts to execute it using execvp.
        If execution fails, it prints an error message.

    int main():
        The main function initializes signal handlers, reads command history from a file, and enters a command execution loop.
        It gets the current working directory and username for the custom shell prompt.
        It reads user input using fgets, checks for exit to exit the program, inserts commands into history, and executes them.
        After the loop, it clears the history and writes it to a file before exiting.
