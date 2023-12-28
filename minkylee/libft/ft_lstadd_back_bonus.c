/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 06:02:19 by minkylee          #+#    #+#             */
/*   Updated: 2023/04/07 10:31:34 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst == NULL || new == NULL)
		return ;
	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (temp -> next != NULL)
			temp = temp -> next;
	}
	temp -> next = new;
}
