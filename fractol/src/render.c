/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 09:35:32 by aalshafy          #+#    #+#             */
/*   Updated: 2024/02/17 09:42:02 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void fractol_render(t_fractol *fractol)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            iterations(x, y, fractol);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}

int coloring(int start, int end, double percentage)
{
    int r;
    int g;
    int b;

    r = (int)((1 - percentage) * (start >> 16 & 0xFF) + percentage * (end >> 16 & 0xFF));
    g = (int)((1 - percentage) * (start >> 8 & 0xFF) + percentage * (end >> 8 & 0xFF));
    b = (int)((1 - percentage) * (start & 0xFF) + percentage * (end & 0xFF));
    return ((r << 16) | (g << 8) | b);
}

double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	double	old_min;

	old_min = 0;
	return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min)
		+ new_min);
}