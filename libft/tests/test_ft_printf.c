/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:21:31 by julhong           #+#    #+#             */
/*   Updated: 2026/01/03 00:24:42 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main (void)
{
	// Testing 'c''
	char	a = '1';
	char	b = '2';
	char	c = '3';
	printf("\n\n\nTesting for 'c' char > Basic\n");
	printf("%d", printf("Actual: I am %c, he is %c, they are %c.\n", a, b, c));
	printf("%d", ft_printf("Result: I am %c, he is %c, they are %c.\n", a, b, c));

	printf("\n\n\nTesting for 'c' char > Empty String\n");
	printf("%d", printf("%s", ""));
	printf("%d", ft_printf("%s", ""));

	printf("\n\n\nTesting for 'c' char > Format > Left Justify, Width with * and -ve\n");
	printf("%d", printf("Actual: I am %10c, he is %-10c, they are %*c.\n", a, b, -5, c));
	printf("%d", ft_printf("Result: I am %10c, he is %-10c, they are %*c.\n", a, b, -5, c));
	fflush(NULL);
	write(1, "\n", 1);
	write_nchars(1, '-', 80);

	// Testing '%'
	printf("\n\n\nTesting for '%%' > Format\n");
	printf("%d", printf("Actual: I am %-5%, he is %5%, they are %.*%.\n", 5));
	printf("%d", ft_printf("Result: I am %-5%, he is %5%, they are %.*%.\n", 5));
	fflush(NULL);
	write(1, "\n", 1);
	write_nchars(1, '-', 80);

	// Testing 's'
	char	*s1 = "first";
	char	*s2 = "second";
	char	*s3 = "third";
	printf("\n\n\nTesting for 's' str > Basic\n");
	printf("%d", printf("Actual: I am %s, he is %s, they are %s.\n", s1, s2, s3));
	printf("%d", ft_printf("Result: I am %s, he is %s, they are %s.\n", s1, s2, s3));

	printf("\n\n\nTesting for 's' str > Format > Left Justify, Width with * and -ve\n");
	printf("%d", printf("Actual: I am %10s, he is %s, they are %*s.\n", s1, s2, -10, s3));
	printf("%d", ft_printf("Result: I am %10s, he is %s, they are %*s.\n", s1, s2, -10, s3));

	printf("\n\n\nTesting for 's' str > Format > With precision truncation, *, -ve\n");
	printf("%d", printf("Actual: I am %10.1s, he is %5.3s, they are %*.*s.\n", s1, s2, -5, 2, s3));
	printf("%d", ft_printf("Result: I am %10.1s, he is %5.3s, they are %*.*s.\n", s1, s2, -5, 2, s3));
	fflush(NULL);
	write(1, "\n", 1);
	write_nchars(1, '-', 80);
	
	// Testing 'di'
	int	n1 = 42;
	int n2 = 2;
	int n3 = 3;
	printf("\n\n\nTesting for 'd,i' int > Basic\n");
	printf("%d", printf("Actual: I am %d, he is %i, they are %d.\n", n1, n2, n3));
	printf("%d", ft_printf("Result: I am %d, he is %i, they are %d.\n", n1, n2, n3));

	printf("\n\n\nTesting for 'd,i' int > Format > Width\n");
	printf("%d", printf("Actual: I am %d, he is %5i, they are %10d.\n", n1, n2, n3));
	printf("%d", ft_printf("Result: I am %d, he is %5i, they are %10d.\n", n1, n2, n3));

	printf("\n\n\nTesting for 'd,i' int > Format > Width 0pad\n");
	printf("%d", printf("Actual: I am %d, he is %05i, they are %010d.\n", n1, n2, n3));
	printf("%d", ft_printf("Result: I am %d, he is %05i, they are %010d.\n", n1, n2, n3));

	printf("\n\n\nTesting for 'd,i' int > Format > Width 0pad left just\n");
	printf("%d", printf("Actual: I am %d, he is %-5i, they are %-10d.\n", n1, n2, n3));
	printf("%d", ft_printf("Result: I am %d, he is %-5i, they are %-10d.\n", n1, n2, n3));

	printf("\n\n\nTesting for 'd,i' int > Format > Width 0pad left just with less preci\n");
	printf("%d", printf("Actual: I am %.0d, he is %-4.0i, they are %-10.5d.\n", n1, n2, n3));
	printf("%d", ft_printf("Result: I am %.0d, he is %-4.0i, they are %-10.5d.\n", n1, n2, n3));

	printf("\n\n\nTesting for 'd,i' int > Format > Sign, width with space vs 0 pad\n");
	printf("%d", printf("Actual: I am %+10d, he is %0+10i, they are %-+10.5d.\n", n1, n2, n3));
	printf("%d", ft_printf("Result: I am %+10d, he is %0+10i, they are %-+10.5d.\n", n1, n2, n3));
	fflush(NULL);
	write(1, "\n", 1);
	write_nchars(1, '-', 80);

#include	<limits.h>
	// Testing 'u'
	unsigned int	u0 = 0;
	unsigned int	u1 = INT_MIN;
	unsigned int	u2 = UINT_MAX;
	unsigned int	u3 = -3;
	printf("\n\n\nTesting for 'u' unsigned int\n");
	printf("%d", printf("Actual: I am %u, he is %u, they are %u.\n", u1, u2, u3));
	printf("%d", ft_printf("Result: I am %u, he is %u, they are %u.\n", u1, u2, u3));
	
	printf("\n\n\nTesting for 'u' unsigned int > Width with space vs 0 pad, preci\n");
	printf("%d", printf("Actual: We are %.u, I am %20u, he is %*.13u, they are %-20.5u.\n", u0, u1, -20, u2, u3));
	printf("%d", ft_printf("Result: We are %.u, I am %20u, he is %*.13u, they are %-20.5u.\n", u0, u1, -20, u2, u3));
	fflush(NULL);
	write(1, "\n", 1);
	write_nchars(1, '-', 80);

	// Testing 'p'
	void	*p1 = "check";
	void	*p2 = "this";
	void	*p3 = "out";
	printf("\n\n\nTesting for 'p' address > Basic\n");
	printf("%d", printf("Actual: I am %p, he is %p, they are %p.\n", p1, p2, p3));
	printf("%d", ft_printf("Result: I am %p, he is %p, they are %p.\n", p1, p2, p3));
	
	p1 = "check";
	p2 = NULL;
	p3 = "out";
	printf("\n\n\nTesting for 'p' address > Width, justify, null, and ignore flags\n");
	printf("%d", printf("Actual: I am %*p, he is %p, they are %*p.\n", 20, p1, p2, -20, p3));
	printf("%d", ft_printf("Result: I am %*.10p, he is %p, they are %*p.\n", 20, p1, p2, -20, p3));
	ft_printf("Result: I am %*p, he is %p, they are %-0 +*.999p.\n", 20, p1, p2, -20, p3);
	
	printf("\n\n\nTesting for 'p' address > (\" %%-1p %%-2p \", 0, 0)\n");
	printf("%d", printf(" %-1p %-2p \n", (void *)0, (void *)0));
	printf("%d", ft_printf(" %-1p %-2p \n", 0, 0));
	fflush(NULL);
	write(1, "\n", 1);
	write_nchars(1, '-', 80);

	// Testing 'X'
	printf("\n\n\nTesting for 'X' hex > Basics\n");
	printf("%d", printf("Actual: I am %0#*.*x, he is %0#7.4X, they are %x.\n", 20, 15, -1, 200, 200));
	printf("%d", ft_printf("Result: I am %0#*.*x, he is %0#7.4X, they are %x.\n", 20, 15, -1, 200, 200));
	
	fflush(NULL);
	write(1, "\n", 1);
	write_nchars(1, '-', 80);

	// Other Tests
	printf("\n\n\nTesting for others");
	//printf("%d", printf("%\n", 0));
	// printf("%d", ft_printf("%\n", 0));
	printf("%d", ft_printf("%"));
	
	fflush(NULL);
	write(1, "\n", 1);
	write_nchars(1, '-', 80);
	return (0);
}
