/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:34:36 by dojannin          #+#    #+#             */
/*   Updated: 2023/02/28 14:59:32 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
	echo et l’option -n
◦ cd uniquement avec un chemin relatif ou absolu
◦ pwd sans aucune option
◦ export sans aucune option
◦ unset sans aucune option
◦ env sans aucune option ni argument
◦ exit sans aucune option
*/


// SI LANCEMENT DU MINISHELL ON VIRE JUSTE AVANT LANCEMENT L'ENV AVEC UN UNSET, LE MINISHELL DOIT SE TROUVER OU CREER UN ENV,
// UN PWD, OU UN OLD_PWD, ET UN HOME POUR TENIR LA ROUTE, AINSI QUE DES PATH. Fixer avant l'env

//ECHO SEC ➜ 
//  Back_to_F git:(main) ✗ echo test | cat -e
// test$
// ➜  Back_to_F git:(main) ✗ echo -n test | cat -e
// test%                              

void	ft_exit(int nb)
{
	//Limite de 255 comme valeur de retour, apres faire des modulos pour "fit" par rapport a 255 (un cas tricky a veri aupres de max)
	if (!nb)
	{	
		printf("exit\n");
		exit(1);
	}
	else
	{
		printf("exit\n");
		if (nb > 255)
			exit(nb % 255);
		else
			exit(nb);
	}
}

void	ft_cd(char *path)
{
	char	*res = search_env_content(g_data.env, "$PWD");
	if (!path)
		chdir(search_env_content(g_data.env, "$HOME"));
	else if (chdir(path) == -1)
	{
		if (chdir(ft_strjoin(res, path)) == -1)
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putchar_fd(':', STDERR_FILENO);
			ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		}		
	}
}


unsigned int	starter_env(char *s)
{
	unsigned int	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}




/* Obtenir l'env grace a la struct global et le print dans un tmp. Parcourir jusquau bout. 
	Cette fonction doit etre lance avant l'exec generale (builtin tricky)
		->Si possible obtenir les cmd des le debut, identifier les redir, gerer les fd pour l'entree, 
		identifier le reste des builtins tricky et return en fonction
		Sinon lancer pleinement l'exec avec les param need (redir determinee (INT), cmd (CHAR **), fd[0])
			->fd[0] correspond au file d'entree, redir a notre sortie, 
	Dans la fonction exec on reverifie les builtins, puis les path de la dite cmd,\
	dup2(fd, stdin_fileno), dup redir stdout si elle est valablem un tmp prendra le path de cmd[0]
	Execv tout ca dans un fork, close les fd et redir, waitpid, return;
*/

// void	check_exec()
// {
// 	t_token	*tmp = NULL;
	
// 	tmp = g_data.token;
// }