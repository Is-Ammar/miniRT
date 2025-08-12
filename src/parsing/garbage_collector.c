/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:42:20 by yel-alja          #+#    #+#             */
/*   Updated: 2025/08/10 21:42:27 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_garbage	*lst(void *ptr)
{
	t_garbage	*node;

	node = malloc(sizeof(t_garbage));
	if (!node)
	{
		free(ptr);
		garbage_collect(NULL, EXIT_FAILURE);
	}
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}

void	free_list(t_garbage *lst)
{
	t_garbage	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->ptr)
			free(tmp->ptr);
		if (tmp)
			free(tmp);
	}
}

void	garbage_collect(void *ptr, int exit_status)
{
	static t_garbage	*head;
	t_garbage			*tmp;

	tmp = NULL;
	if (ptr != NULL)
	{
		if (head == NULL)
			head = lst(ptr);
		else
		{
			tmp = head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = lst(ptr);
		}
	}
	else
	{
		free_list(head);
		exit(exit_status);
	}
}
