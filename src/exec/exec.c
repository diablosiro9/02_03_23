/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:40:12 by imac21            #+#    #+#             */
/*   Updated: 2023/03/02 11:02:58 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"


int ft_exec(t_list *str)
{
    char *command;
    char *sub_command;
    char *saveptr;
    char *path;
    char *option;
    pid_t pid;
    int pipefd[2];
    int last_pipefd[2];

    printf("slaut\n");
    path = split_cmd_file(); // ici je recup bien le bon path
    printf("path == %s\n", path);
    // faire attention, si je vire le path de l env pdt l'exec, prochaine exec cest ici que le path vaut null et return rien mais a ameliorer
	// if (path == NULL)
    //     return (0);
    // ft_unset();
	// ft_env(NULL);
	// ft_pwd();
    //CHECKING PREMIER BUILTIN A FAIRE ICI A MON AVIS
    if (str != NULL) {
        command = str->content;
        if (strcmp(command , "export") == 0)
        {
	        ft_export(1);
            return (1);
        }
        if (strcmp(command , "env") == 0)
        {
            if (str->next)
				ft_env(str->next->content);
			else
	            ft_env(NULL);
            return (1);
        }
        if (strcmp(command, "cd") == 0){
            if (str->next)
				ft_cd(str->next->content);
			else
	            ft_cd("$HOME");
            return (1);
		}
        if (strcmp(command, "pwd") == 0)
            ft_pwd(1);
		if (strcmp(command, "exit") == 0)
		{
            if (str->next)
				ft_exit(ft_atoi(str->next->content));
			else
	            ft_exit(0);
		}
		if (strcmp(command, "echo") == 0)
		{
			if (str->next)
				ft_echo(1);
			else
				ft_echo(0);
            return (1);
		}
		if (strcmp(command, "unset") == 0)
		{
			printf("entrreeee\n");
			if (str->next)
				ft_unset(str->next->content);
			else
				ft_unset();
		}
	    // //printf("Commande : %s\n", command);
        // if (strcmp(command, "exit") == 0) {
        //     printf("Bye\n");
        //     exit(0);
        // }
        if (str->next != NULL)
            option = str->next->content;
        else
            option = NULL;
        sub_command = strtok_r(command, " ", &saveptr);
        //printf("sub_command == %s\n", sub_command);
        while (sub_command != NULL) {
            if (pipe(pipefd) == -1) {
                perror("Erreur pipe");
                exit(1);
            }
            pid = fork();
            if (pid == -1) {
                perror("Erreur fork");
                exit(1);
            }
            if (pid == 0) {
                // Nous sommes dans le processus enfant
                if (last_pipefd[0] != 0) {
                    dup2(last_pipefd[0], 0);
                    close(last_pipefd[0]);
                }
                close(pipefd[0]);
                close(pipefd[1]);
                char *args[] = {path, option, NULL};
                printf("path == %s\n", path);
                printf("option == %s\n", option);
                printf("la sub_command == %s\n", sub_command);
                execve(args[0], args, NULL);
               
                perror("Erreur execvp");
                 } else {
                // Nous sommes dans le processus parent
                if (last_pipefd[0] != 0) {
                    close(last_pipefd[0]);
                }
                last_pipefd[0] = pipefd[0];
                close(pipefd[1]);
            }
            sub_command = strtok_r(NULL, "|", &saveptr);
        }
        if (last_pipefd[0] != 0) {
            close(last_pipefd[0]);
        }
        //printf("La commande a été exécutée avec succès\n");
        //free(command);
        //pourattendre le procesessus fils
        while(wait(NULL) != -1);
    }
    return 0;
}
