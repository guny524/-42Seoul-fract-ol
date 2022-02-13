/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:31:29 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/19 15:11:21 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_fractol.h"

/*
* Zn = Xn + iYn, C = a + ib 로 정의 되고
* Zn+1 = (Zn)^2 + C 이 발산하지 않는 복소수 C의 집합을 구하면 된다.
*
* (Xn)^2 + (Yn)^2 <= (bound)^2
* 복소평면에서 원점으로 부터 특정 거리 안에서 안 벗어나면 발산 안 함
*
* Z가 고정되어 있고, C가 변하면 Mandelbrot이다.
*
* Zn = Xn + iYn, C = a + ib
* (Zn)^2 = (Xn)^2 - (Yn)^2 + 2iXnYn
* (Zn)^2 + C = (Xn)^2 - (Yn)^2 + a + i(2XnYn + b)
*/
int	mandelbrot(t_mlx *mlx, double a, double b, int iter)
{
	int		i;
	double	xn;
	double	yn;
	double	x1n;
	double	y1n;

	x1n = mlx->init_num.xr;
	y1n = mlx->init_num.yi;
	i = -1;
	while (++i < iter)
	{
		xn = x1n;
		yn = y1n;
		x1n = xn * xn - yn * yn + a;
		y1n = 2 * xn * yn + b;
		if (x1n * x1n + y1n * y1n > mlx->bound * mlx->bound)
			return (0);
	}
	return (1);
}

/*
* Zn = Xn + iYn, C = a + ib 로 정의 되고
* Zn+1 = (Zn)^2 + C 이 발산하지 않는 복소수 Z의 집합을 구하면 된다.
*
* (Xn)^2 + (Yn)^2 <= (bound)^2
* 복소평면에서 원점으로 부터 특정 거리 안에서 안 벗어나면 발산 안 함
*
* C가 고정되어 있고, Z가 변하면 Julia이고,
*
* Zn = Xn + iYn, C = a + ib
* (Zn)^2 = (Xn)^2 - (Yn)^2 + 2iXnYn
* (Zn)^2 + C = (Xn)^2 - (Yn)^2 + a + i(2XnYn + b)
*/
int	julia(t_mlx *mlx, double xn, double yn, int iter)
{
	int		i;
	double	x1n;
	double	y1n;

	x1n = xn;
	y1n = yn;
	i = -1;
	while (++i < iter)
	{
		xn = x1n;
		yn = y1n;
		x1n = xn * xn - yn * yn + mlx->init_num.xr;
		y1n = 2 * xn * yn + mlx->init_num.yi;
		if (x1n * x1n + y1n * y1n > mlx->bound * mlx->bound)
			return (0);
	}
	return (1);
}

/*
* Zn = Xn + iYn 로 정의 되고
* Zn+1 = (Zn)^(Zn) 이 발산하지 않는 복소수 Z의 집합을 구하면 된다.
*
* (Xn)^2 + (Yn)^2 <= (bound)^2
* 복소평면에서 원점으로 부터 특정 거리 안에서 안 벗어나면 발산 안 함
*
* complex 라이브러리 구현 참고
* https://github.com/bminor/musl/tree/master/src/complex
* cpow(z, c) = cexp(c * clog(z));
* cexp(a + bi) = {exp(a)*cos(b),exp(a)*sin(b)};
* clog(z) = {log(cabs(z)), carg(z)};
* carg(a + bi) = atan2(b, a);
* cabs(a + bi) = hypot(a, b);
*/
int	powertower(t_mlx *mlx, double xn, double yn, int iter)
{
	int		i;
	double	x1n;
	double	y1n;

	x1n = xn;
	y1n = yn;
	i = -1;
	while (++i < iter)
	{
		xn = x1n;
		yn = y1n;
		// complex log
		x1n = log(hypot(xn, yn));
		y1n = atan2(yn, xn);
		// multiply
		xn = x1n * x1n - y1n * y1n;
		yn = 2 * x1n * y1n;
		// exponent
		x1n = exp(xn) * cos(yn);
		y1n = exp(xn) * sin(yn);
		if (hypot(x1n, y1n) > mlx->bound * mlx->bound)
			return (0);
	}
	return (1);
}

void	clear_image(t_img *img)
{
	int		x;
	int		y;
	int		*tmp;

	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			tmp = (int *)(img->addr + y * img->len + x * img->bpp / 8);
			*tmp = *(int *)(char [4]){0, 0, 0, 0};
		}
	}
}

/*
* 함수 포인터의 배열 해석 하는 법 clockwise spiral rule 참고
* http://c-faq.com/decl/spiral.anderson.html
* https://www.geeksforgeeks.org/clockwise-spiral-rule-in-c-c-with-examples/
*/
void	paint_image(t_mlx *mlx, int func_index, int iter, t_trgb trgb)
{
	int			x;
	int			y;
	int			*tmp;
	int			ret;
	const t_fp	cal_trgb[] = {mandelbrot, julia, powertower};

	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			tmp = (int *)(mlx->img.addr + y * mlx->img.len + x
				* mlx->img.bpp / 8);
			ret = cal_trgb[func_index](mlx,
				(x - CW) / W * mlx->ratio - mlx->center.xr,
				(y - CH) / W * mlx->ratio - mlx->center.yi,
				iter);
			if (ret)
				*tmp = *(int *)(char [4]){trgb.b, trgb.g, trgb.r, trgb.t};
		}
	}
}
