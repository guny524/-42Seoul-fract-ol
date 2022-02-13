/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:38:41 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/18 17:38:52 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	strcomp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/*
* 못 찾으면 -1 리턴
* 찾으면 찾은 index 리턴
*/
int	isstrin(const char *str, const char *names[], int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (0 == strcomp(str, names[i]))
			return (i);
	}
	return (-1);
}

void	init_screen_parameter(t_mlx *mlx)
{
	mlx->center = (t_inum){0.0, 0.0};
	mlx->ratio = 4;
	mlx->mod = MOD_NORMAL_ZOOM;
	mlx->color = 0;
}

int	main(int argc, char *argv[])
{
	const char	*names[] = {"Mandelbrot", "Julia", "Powertower"};
	const int	size = sizeof(names) / sizeof(char *);
	t_mlx		mlx;

	mlx.init_num = (t_inum){0, 0};
	mlx.bound = 2;
	if (!(2 <= argc && argc <= 5))
		print_manual();
	mlx.name = isstrin(argv[1], names, size);
	if (-1 == mlx.name)
		print_manual();
	if (3 <= argc)
		mlx.init_num.xr = get_double(argv[2]);
	if (4 <= argc)
		mlx.init_num.yi = get_double(argv[3]);
	if (5 <= argc)
		mlx.bound = get_double(argv[4]);
	if (mlx.bound * mlx.bound < mlx.init_num.xr * mlx.init_num.xr
		+ mlx.init_num.yi * mlx.init_num.yi)
		print_bound(mlx.init_num.xr, mlx.init_num.yi, mlx.bound);
	init_screen_parameter(&mlx);
	run(&mlx);
	return (0);
}
