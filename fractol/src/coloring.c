/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 09:14:53 by aalshafy          #+#    #+#             */
/*   Updated: 2024/02/17 09:40:48 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void iterations(int x, int y, t_fractol *fractol)

{
	t_complex	z;
	int			i;
	int			color;

	i = 0;
	z.x = (map(x, -2, +2, WIDTH) * fractol->zoom) + fractol->shift_x;
	z.y = (map(y, +2, -2, HEIGHT) * fractol->zoom) + fractol->shift_y;
	while (i < fractol->iterations)
	{
		z = sum_complex(square_complex(z), fractol->mouse);
		if ((z.x * z.x) + (z.y * z.y) > fractol->escape_value)
		{
			color =  coloring(BLACK, fractol->current_colour, (double)i / fractol->iterations);
			// color = map(i, BLACK, WHITE, fractol->iterations);
			my_pixel_put(x, y, &fractol->img, color);
			return ;
		}
		++i;
	}
	my_pixel_put(x, y, &fractol->img, WHITE);
}

t_complex square_complex(t_complex z)
{
    t_complex result;

    result.x = (z.x * z.x) - (z.y * z.y);
    result.y = 2 * z.x * z.y;
    return (result);
}

t_complex sum_complex(t_complex a, t_complex b)
{
    t_complex result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return (result);
}