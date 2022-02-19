/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:56:01 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/19 15:36:57 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTOL_H
# define FT_FRACTOL_H

# include <stddef.h>

# define W 1920.0
# define H 1080.0
# define CW 960.0
# define CH 540.0

typedef enum e_name
{
	Mandelbrot,
	Julia,
	Powertower
}	t_enum;

typedef enum e_input
{
	MOUSE_UP = 4,
	MOUSE_DOWN = 5,
	KEY_C = 8,
	KEY_M = 46,
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_UP = 126
}	t_input;

typedef enum s_mod
{
	MOD_NORMAL_ZOOM,
	MOD_MOUSE_ZOOM,
}	t_mod;

typedef enum s_state
{
	STATE_ERROR,
	STATE_SIGN,
	STATE_DECIMAL,
	STATE_FLOAT
}	t_state;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct s_inum
{
	double	xr;
	double	yi;
}	t_inum;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	img;
	int		name;
	double	bound;
	t_inum	init_num;
	t_inum	center;
	double	ratio;
	double	save_ratio;
	int		mouseY;
	t_mod	mod;
	int		color;
}	t_mlx;

typedef struct s_trgb
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_trgb;

typedef int	(*t_fp)(t_mlx *, double, double, int);

/*
* main.c
*/
int		strcomp(const char *s1, const char *s2);
int		isstrin(const char *str, const char *names[], int size);
void	init_screen_parameter(t_mlx *mlx);
/*
* input.c
*/
int		state_sign(char *str, double *ret, int *sign);
int		state_decimal(char *str, double *ret);
int		state_float(char *str, double *ret, int *div);
double	get_double(char *str);
/*
* print.c
*/
void	print_defaults(void);
void	print_manual(const char	*names[], size_t size);
void	print_wrong_input(char *str);
void	print_bound(double x, double y, double bound);
/*
* run.c
*/
int		destroy(t_mlx *mlx);
int		key_hook(int keycode, t_mlx *mlx);
int		mouse_hook(int button, int x, int y, t_mlx *mlx);
int		loop_hook(t_mlx *mlx);
void	run(t_mlx *mlx);
/*
* color.c
*/
int		mandelbrot(t_mlx *mlx, double a, double b, int iter);
int		julia(t_mlx *mlx, double x, double y, int iter);
int		burningship(t_mlx *mlx, double a, double b, int iter);
void	clear_image(t_img *img);
void	paint_image(t_mlx *mlx, int func_index, int iter, t_trgb trgb);

#endif
