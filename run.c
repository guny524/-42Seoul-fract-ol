/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:56:06 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/23 20:39:40 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include "mlx.h"
#include "ft_fractol.h"

int	destroy(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	int	x;

	if_event_clear(mlx, -1, keycode);
	if (KEY_ESC == keycode)
		destroy(mlx);
	else if (KEY_UP == keycode)
		mlx->center.yi -= 0.05 * mlx->ratio;
	else if (KEY_DOWN == keycode)
		mlx->center.yi += 0.05 * mlx->ratio;
	else if (KEY_LEFT == keycode)
		mlx->center.xr -= 0.05 * mlx->ratio;
	else if (KEY_RIGHT == keycode)
		mlx->center.xr += 0.05 * mlx->ratio;
	else if (KEY_M == keycode && MOD_NORMAL_ZOOM == mlx->mod)
	{
		mlx_mouse_get_pos(mlx->win, &x, &mlx->mouseY);
		mlx->save_ratio = mlx->ratio;
		mlx->mod = MOD_MOUSE_ZOOM;
	}
	else if (KEY_M == keycode && MOD_MOUSE_ZOOM == mlx->mod)
		mlx->mod = MOD_NORMAL_ZOOM;
	else if (KEY_C == keycode)
		mlx->color = (mlx->color + 1) % 3;
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	if_event_clear(mlx, button, -1);
	if (MOUSE_UP == button)
	{
		mlx->center.xr -= (double)(x - CW) / W * 0.1 * mlx->ratio;
		mlx->center.yi -= (double)(y - CH) / H * 0.1 * mlx->ratio;
		mlx->ratio *= 0.8;
	}
	else if (MOUSE_DOWN == button)
	{
		mlx->center.xr -= (double)(x - CW) / W * 0.1 * mlx->ratio;
		mlx->center.yi -= (double)(y - CH) / H * 0.1 * mlx->ratio;
		mlx->ratio *= 1.2;
	}
	return (0);
}

/*
*   !
* 0 1 255
* 1 0 0
* 2 0 0
*
*   -1 !
* 0 -1 0 0
* 1  0 1 255
* 2  1 0 0
*
*   +1%3 !
* 0 1    0 0
* 1 2    0 0
* 2 0    1 255
*/
int	loop_hook(t_mlx *mlx)
{
	int			x;
	int			y;
	const int	i = mlx->iter;
	const int	c = mlx->color;

	if (i >= INT_MAX - 1)
		return (0);
	paint_image(mlx, mlx->name, i, (t_trgb){0, !((c + i) % 3) * 255,
		!((c + i) % 3 - 1) * 255, !(((c + i) % 3 + 1) % 3) * 255});
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	mlx_string_put(mlx->ptr, mlx->win, 30, 20, 0, "Move        : arrow");
	mlx_string_put(mlx->ptr, mlx->win, 30, 40, 0, "Zoom        : mouse wheel");
	mlx_string_put(mlx->ptr, mlx->win, 30, 60, 0, "Mouse Zoom  : m");
	mlx_string_put(mlx->ptr, mlx->win, 30, 80, 0, "Color Shift : c");
	if (MOD_MOUSE_ZOOM == mlx->mod)
	{
		mlx_mouse_get_pos(mlx->win, &x, &y);
		mlx->ratio = mlx->save_ratio
			+ mlx->save_ratio * ((double)y - mlx->mouseY) / W;
	}
	mlx->iter++;
	return (0);
}

void	run(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, W, H, "fractol");
	if (NULL == mlx->win)
		exit(1);
	mlx->img.ptr = mlx_new_image(mlx->ptr, W, H);
	if (NULL == mlx->img.ptr)
		exit(1);
	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp,
			&mlx->img.len, &mlx->img.endian);
	mlx_hook(mlx->win, 17, 0L, destroy, mlx);
	mlx_key_hook(mlx->win, key_hook, mlx);
	mlx_mouse_hook(mlx->win, mouse_hook, mlx);
	mlx_loop_hook(mlx->ptr, loop_hook, mlx);
	mlx_loop(mlx->ptr);
}
