#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int BATCH = 0;
int REDIR = -1;

void Print(char* string) {
    write(STDOUT_FILENO, string, strlen(string));
    return;
}

void Error() {
    Print("An error has occurred\n");
    return;
}

char* trimSpace(char* string) {
    if (!string) {
        return NULL;
    }
    size_t len = strlen(string);
    while (isspace(string[len - 1])) {
        len--;
    }
    while (*string && isspace(*string)) {
        string++;
        len--;
    }
    char* trimmed_string = strndup(string, len);
    return trimmed_string;
}

int isBuiltIn(char* command) {
    if(!strncmp(command, "cd", strlen("cd"))){
        return 0;
    } else if (!strncmp(command, "exit", strlen("exit"))) {
        return 1;
    } else if (!strncmp(command, "pwd", strlen("pwd"))) {
        return 2;
    } else {
        return -1;
    }
}

int isValidFilePath(char* file_path) {
    return !access(file_path, F_OK);
}

int isBlank(char* string) {
    while (*string != '\0') {
        if (!isspace(*string)) {
            return false;
        }
        string++;
    }
    return true;
}

unsigned int getlen(char* command) {
    unsigned int length = 0;
    while (*command) {
        if (*command == ' ')
            length++;
        command++;
    }
    return length + 1;
}

int filter_redir(char* command) {
    if (strstr(command, ">+")) {
        return 0;
    } else if (strstr(command, ">")) {
        return 1;
    } else {
        return -1;
    }
}

int isValidRedirection(char* redir_path, char* redir_cmd) {
    if (!strcmp(redir_path, "")){
        return 0;
    } else if (strchr(redir_path, '>') || strchr(redir_path, ' ')) {
        return 0;
    } else if (!strcmp(redir_cmd, ">") && isValidFilePath(redir_path)) {
        return 0;
    } else {
        return 1;
    }
}

void cpyToFile(int copy_fd, int original_fd) {
    ssize_t bytes;
    char c_buff[1];
    if ((bytes = read(original_fd, c_buff, 1)) < 0)
        Error();
    while (bytes > 0) {
        if (write(copy_fd, c_buff, bytes) < 0)
            Error();
        if ((bytes = read(original_fd, c_buff, 1)) < 0)
            Error();
    }
}

void CMD_CD(char* command) {
    char* file_path;
    if (!command[2]) {
        chdir(getenv("HOME"));
        return;
    }
    if ((file_path = trimSpace(strchr(command, ' ')))) {
        if (isValidFilePath(file_path)) {
            chdir(file_path);
            return;
        }
    }
    Error();
    return;
}

void CMD_EXIT(char* command) {
    if (strcmp(command, "exit")) {
        Error();
        return;
    }
    exit(0);
}

void CMD_PWD(char* command) {
    if (strcmp(command, "pwd") != 0) {
        Error();
        return;
    }
    char* cwd_buff = NULL;
    cwd_buff = getcwd(cwd_buff, 0);
    if (cwd_buff == NULL) {
        perror("getcwd() failed");
        return;
    }
    Print(cwd_buff);
    Print("\n");
    free(cwd_buff);
}

void (*builtin_CMDS[])(char*) = {
    &CMD_CD,
    &CMD_EXIT,
    &CMD_PWD
};

int readline(FILE** inputstream, char (*line_buff)[514],
               char** line_ptr) {
    *line_ptr = fgets(*line_buff, 514, *inputstream);
    if (!(*line_ptr)) {
        exit(0);
    }
    if (isBlank(*line_ptr))
        return 0;
    if (strchr(*line_ptr, '\n')) {
        if (BATCH)
            Print(*line_ptr);
        *line_ptr = trimSpace(*line_ptr);
        return 1;
    }
    while (!strchr(*line_ptr, '\n')) {
        Print(*line_ptr);
        *line_ptr = fgets(*line_buff, 514, *inputstream);
        if (!(*line_ptr))
            exit(0);
    }
    Print(*line_ptr);
    Error();
    return 0;
}

char** Parsecommand(char* command, char** output_path) {
    int is_redir;
    char* redir_cmd;
    unsigned int length = getlen(command);
    int i;
    char** cmd_args;
    if ((is_redir = filter_redir(command)) != -1) {
        if (is_redir == 0){
            redir_cmd = ">+";
        } else {
            redir_cmd = ">";
        }
        *output_path = trimSpace(strstr(command, redir_cmd) + strlen(redir_cmd));
        if (isValidRedirection(*output_path, redir_cmd)) {
            REDIR = is_redir;
            command = trimSpace(strtok_r(command, redir_cmd, &command));
        } else {
            Error();
            return NULL;
        }
    }
    cmd_args = (char**)malloc((length + 1) * sizeof(char*));
    for (i = 0; i < length; i++) {
        cmd_args[i] = strtok_r(command, " ", &command);
    }
    cmd_args[i] = NULL;
    return cmd_args;
}

int redir_help(char** output_path, int* discp, int* temp_discp) {
    if (REDIR == 1 || access(*output_path, F_OK) != 0) {
        if ((*discp = open(*output_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) < 0) {
            return 0;
        }
        return 1;
    } else if ((*temp_discp = open("temp", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR)) < 0) {
        return 0;
    } else if ((*discp = open(*output_path, O_RDWR | O_APPEND)) < 0) {
        return 0;
    } else {
        cpyToFile(*temp_discp, *discp);
        if (ftruncate(*discp, 0) < 0) {
            return 0;
        }
        return 1;
    }
}

void Execute(char* line) {
    char* command = trimSpace(strtok_r(line, ";", &line));
    int is_builtin;
    char** cmd_args;
    int output_discp, temp_discp = 0;
    pid_t pid;
    char* path;
    while (command) {
        if ((is_builtin = isBuiltIn(command)) == -1) {
            cmd_args = Parsecommand(command, &path);
            if (REDIR != -1) {
                if (!redir_help(&path, &output_discp, &temp_discp)) {
                    Error();
                    cmd_args = NULL;
                }
            }
            if (!(pid = fork())) {
                if (REDIR != -1) {
                    if(dup2(output_discp, STDOUT_FILENO) < 0) {
                        exit(1);
                    }
                }
                if (execvp(cmd_args[0], cmd_args) < 0){
                    Error();
                }
                exit(1);
            } else {
                wait(NULL);
                free(cmd_args);
                if (temp_discp) {
                    if ((output_discp = open(path, O_WRONLY | O_APPEND)) < 0){
                        Error();
                    }
                    if ((temp_discp = open("temp", O_RDONLY)) < 0){
                        Error();
                    }
                    cpyToFile(output_discp, temp_discp);
                }
            }
        } else {
            builtin_CMDS[is_builtin](command);
        }
        REDIR = -1;
        command = trimSpace(strtok_r(line, ";", &line));
    }
}

int main(int argc, char *argv[]) {
    char* line_ptr;
    char line_buff[514];
    FILE* inputstream = stdin;
    if (argc > 2) {
        Error();
        exit(1);
    }
    if (argc > 1) {
        BATCH = 1;
        inputstream = fopen(argv[1], "r");
        if (!inputstream) {
            Error();
            exit(1);
        }
    }
    while (1) {
        if (!BATCH)
            Print("myshell> ");
        if (readline(&inputstream, &line_buff, &line_ptr))
            Execute(line_ptr);
    }
}