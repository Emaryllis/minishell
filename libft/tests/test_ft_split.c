/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:20:55 by julhong           #+#    #+#             */
/*   Updated: 2025/09/25 23:54:46 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	printf("...starting... Tests:\n\n\n");
	
	char	*str;
	char	**str_ptr;
	
	str = ",.,.,.,.,.,my,.,.,.,name.   ,.,.,.,us";
	str_ptr = ft_splitchset(str, " ,.");
	ft_printf("Res: %s", str_ptr[2]);
	
	printf("\n\n...end tests...\n");
	return (0);

}