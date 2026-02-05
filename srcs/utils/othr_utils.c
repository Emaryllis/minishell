/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   othr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2026/02/04 19:52:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	malloc_error(int ret)
{
	ft_printfd(2, NAME": malloc: Cannot allocate memory\n");
	return (ret);
}

int	malloc_fail_exit(void)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}
