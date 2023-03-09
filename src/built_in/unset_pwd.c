/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:55:48 by imac21            #+#    #+#             */
/*   Updated: 2023/02/28 02:15:40 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void	ft_pwd(int redir)
{
	char	pwd[1000];
	char	*tmp = NULL;
	
	tmp = getcwd(pwd, sizeof(pwd));
	if (tmp == NULL)
		return ;
	ft_putstr_fd(tmp, redir);
	return ;
}

t_env *delete_node(t_env* head, int position) {
    if (head == NULL) {
        // la liste est vide
        return head;
    }
    // supprime le premier élément
    if (position == 0) {
       	t_env* new_head = head->next;
        free(head);
        return new_head;
    }
    // supprime un élément dans la liste
    t_env* current = head;
    for (int i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }
    if (current == NULL || current->next == NULL) {
        // la position est en dehors de la liste
        return head;
    }
    t_env* next_node = current->next->next;
    free(current->next);
    current->next = next_node;
    return head;
}

void	ft_unset(char *name)
{
	char	*path = NULL;
	t_env	*tmp = g_data.env;
	t_env	*head = tmp;
	int		i = 0;

	if (!name)
		return ;
	printf("la \n");
	printf("name == %s\n", name);
	path = search_env_content(g_data.env, name);
	if (path == NULL)
		return ;
	if (path != NULL)
	{
		while (strcmp(tmp->name, name) != 0 && tmp)
		{
			tmp = tmp->next;
			i++;
		}
		if (strcmp(tmp->name, name) == 0)
			delete_node(g_data.env, i);
	}
	tmp = head;
}