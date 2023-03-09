/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:32:59 by mla-rosa          #+#    #+#             */
/*   Updated: 2023/03/03 17:00:28 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

// Pourquoi refaire un ft_putchar alors que tu l'as déjà fait dans ton libft ?
void ft_putchar(char c)
{
    write(1, &c, 1);
}



// Quasiment parfaitement propre (check malloccc)


// Dans le directory lexer de préférence
// t_list *lexer(t_list *str)
// {
//     t_list *list;
//     char **tab;
// 	char *tp = (char *)str->content;
//     int i = 0;
//     t_list *tmp = malloc(sizeof(t_list) * 100); // Check tes mallocs mon coeuuurrrrr
//     if (!tmp)
//     {
//         printf("malloc error\n");
//         exit(-127);
//     }
//     tab = ft_split(tp);
//     while (tab[i])
//     {
//         list = ft_lstnew(tab[i]);
//         list->next = tmp;
//         tmp = list;
//         i++;
//     }
// 	//printf("TAB VA SUIVRE---->\n");
// 	//afftab(tab);
//     afflist(list, "Lexer");
//     printf("je vois avant tokenizateur\n");
//     tokenizateur(list);
//     //printf("sortie\n");
//     return (list);
// }

/* by mathieu
Le soucis c'est que tu fais un list->next = tmp et apparament ca faisait un peu n'importe quoi
Donc vaut mieux utiliser une fonction que tu as faites comme ft_lstadd qui elle meme te rajoute une node a la fin
ensuite a chaque fois tu realloues list donc tu auras des leaks alors que tu peux directement donner en argument ft_lstnew 
a ton ft_lstadd, ensuite ton tab recupere les espaces. 
*/

void	*manage_double();

void	free_tab(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i] != NULL)
		free(cmd[i++]);
	free(cmd);
}

int main(int ac, char **av, char **env)
{
	t_list	*history = NULL;
    t_list *str = NULL;
	history = ft_lstnew(NULL);
    g_data.env = get_env(env);
    (void)ac;
    (void)av;
	printf("tu sors\n");
    while (42)
	{
		// g_data.token = (t_token *)malloc(sizeof(t_token));
	 	ft_putstr("minishell>");
        g_data.cmd = get_next_line(0);
		str = ft_lstnew(g_data.cmd);
		printf("g_data.cmd = %s\n", g_data.cmd);
		ft_lstadd(&history, str);
		if (checking_closed((char *)str->content) != 0 && checking_closed((char *)str->content) != -1)
 	    {  
			str = lexer(str);
			parsor(str);
			//printf("la str == %s\n", (char *)str->content);
			ft_exec(str); //il devrait etre la mais d'ici je get pas la commande je la get pour le moment depuis le split_cmd_file.
		}
		delete_token(&g_data.token);
	}
    return (0);
}
