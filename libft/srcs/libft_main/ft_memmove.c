/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:45:18 by julhong           #+#    #+#             */
/*   Updated: 2025/05/19 15:29:16 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*uc_dst;
	unsigned char	*uc_src;
	size_t			i;

	uc_dst = (unsigned char *)dest;
	uc_src = (unsigned char *)src;
	if (uc_dst > uc_src && uc_dst < uc_src + n)
	{
		i = n;
		while (i > 0)
		{
			i--;
			uc_dst[i] = uc_src[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			uc_dst[i] = uc_src[i];
			i++;
		}
	}
	return (dest);
}
