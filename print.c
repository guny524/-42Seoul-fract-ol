/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:37:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/19 21:11:11 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	print_defaults(void)
{
	printf("\n");
	printf("  (X, iY)  : defaults (0, 0)\n");
	printf("  bound    : defaults 2\n");
	printf("    try fractol Julia -0.8 0.156\n");
	printf("    try fractol Julia -0.75\n");
	exit(1);
}

void	print_manual(const char	*names[], size_t size)
{
	size_t	i;

	printf("usage : fractol [fractols] [real X] [imagenary Y] [bound^2]\n");
	printf("  fractols :\n");
	i = 0;
	while (i < size)
		printf("    --> %s :\n", names[i++]);
	print_defaults();
}

void	print_wrong_input(char *str)
{
	printf("usage : fractol [fractols] [real X] [imagenary Y] [bound^2]\n");
	printf("  double form must be : ");
	printf("  [minus][at least 1 digit][.][at least 0 digit]\n");
	printf("    examples\n");
	printf("      -1.33\n");
	printf("      10.1\n");
	printf("      4\n");
	printf("    now %s\n", str);
	print_defaults();
}

void	print_bound(double x, double y, double bound)
{
	printf("usage : fractol [fractols] [real X] [imagenary Y] [bound^2]\n");
	printf("  bound must be : (Xn)^2 + (Yn)^2 <= (bound)^2\n");
	printf("            now : %lf + %lf == %lf <= %lf\n", x * x, y * y,
		x * x + y * y, bound * bound);
	print_defaults();
}
