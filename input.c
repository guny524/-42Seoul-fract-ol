/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:56:14 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/18 17:58:31 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	state_sign(char *str, double *ret, int *sign)
{
	*sign = 1;
	if ('-' == *str)
		*sign = -1;
	else if ('0' <= *str && *str <= '9')
		*ret += *str - '0';
	else
		return (STATE_ERROR);
	return (STATE_DECIMAL);
}

int	state_decimal(char *str, double *ret)
{
	if ('0' <= *str && *str <= '9')
		*ret = *ret * 10 + (*str - '0');
	else if ('.' == *str)
		return (STATE_FLOAT);
	else
		return (STATE_ERROR);
	return (STATE_DECIMAL);
}

int	state_float(char *str, double *ret, int *div)
{
	*div *= 10;
	if ('0' <= *str && *str <= '9')
		*ret += (double)(*str - '0') / *div;
	else
		return (STATE_ERROR);
	return (STATE_FLOAT);
}

double	get_double(char *str)
{
	int			sign;
	double		ret;
	int			state;
	int			div;
	char		*sstr;

	sstr = str;
	ret = 0;
	div = 1;
	state = STATE_SIGN;
	while (*str)
	{
		if (STATE_ERROR == state)
			print_wrong_input(sstr);
		else if (STATE_SIGN == state)
			state = state_sign(str, &ret, &sign);
		else if (STATE_DECIMAL == state)
			state = state_decimal(str, &ret);
		else if (STATE_FLOAT == state)
			state = state_float(str, &ret, &div);
		++str;
	}
	if (STATE_ERROR == state)
		print_wrong_input(sstr);
	return (sign * ret);
}
