/*
** EPITECH PROJECT, 2023
** B-PSU-400-LYN-4-1-strace-oscar.deschamps
** File description:
** main
*/

#include "../include/strace.h"

int print_syscall_bis(pid_t child, int i, int bit, int lenght)
{
    struct user_regs_struct regs;
    ptrace(PT_GETREGS, child, NULL, &regs);
    lenght += print_args(regs, i);
    for (int x = 0; lenght + x <= 39; x++)
        printf(" ");
    printf("= ");
    if (bit == 1)
        printf("?\n");
    else if (regs.rax == 0xffffffffffffffda)
        printf("0x0\n");
    else
        printf("0x%llx\n", regs.rax);
    return 0;
}

int print_syscall(pid_t child)
{
    long orig_eax = ptrace(PTRACE_PEEKUSER, child, sizeof(long) *
    ORIG_RAX, NULL);
    char *syscall_name;
    uint64_t ret;
    int bit = 0;
    int i = 0;

    if (orig_eax == -1) {
        return 84;
    }
    for (; i != 330; i++) {
        if (table[i].num == orig_eax) {
            syscall_name = strdup(table[i].name);
            (table[i].ret_type == VOID) ? bit = 1 : 0;
            break;
        }
    }
    printf("%s(", syscall_name);
    return (print_syscall_bis(child, i, bit, strlen(syscall_name) + 1));
}

int strace(int status, pid_t child, int argc, char **argv)
{
    if (child == 0) {
        if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
            return 84;
        }
        printf("%s\n", argv[1]);
        if (execvp(argv[1], argv + 1) == -1) {
            printf("efqzqdz\n");
            return 84;
        }
    } else {
        waitpid(child, &status, 0);
        while (WIFSTOPPED(status)) {
            print_syscall(child);
            ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
            waitpid(child, &status, 0);
        }
    printf("exit_group(0x0)                         = ?\n");
    printf("+++ exited with 0 +++\n");
    }
    return 0;
}

int parsing(int argc, char **argv, int opt, pid_t child)
{
    int status;

    if (argv[1 + opt] && !strcmp(argv[1 + opt], "-p") && argv[2 + opt]) {
        child = atoi(argv[2 + opt]);
        if (ptrace(PTRACE_ATTACH, child, 0, 0) == -1)
            return 84;
    } else {
        if (!argv[1 + opt]) {
            printf("Invalid option\n");
            return 84;
        }
        child = fork();
        if (child == -1) {
            perror("fork");
            return 84;
        }
    }
    return (strace(status, child, argc, argv));
}

int main(int argc, char *argv[])
{
    pid_t child;
    int status;
    int opt = 0;

    if (argc < 2)
        return (printf("Usage : %s [-s] [-p <pid>|<command>]\n",
            argv[0]) || 0);
    if (!strcmp(argv[1], "-s"))
        opt = 1;
    return (parsing(argc, argv, opt, child));
}
