/*
** EPITECH PROJECT, 2023
** B-PSU-400-LYN-4-1-strace-oscar.deschamps
** File description:
** strace
*/

#ifndef STRACE_H_
    #define STRACE_H_
    #include "syscall.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/ptrace.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <sys/reg.h>
    #include <sys/syscall.h>
    #include <fcntl.h>
    #include <sys/user.h>
    #include <stdarg.h>
    #include "../include/strace.h"
    #include <stdint.h>
    #include <signal.h>

    int print_args(struct user_regs_struct regs, int i);
#endif /* !STRACE_H_ */
