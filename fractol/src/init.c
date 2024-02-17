/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:11:39 by aalshafy          #+#    #+#             */
/*   Updated: 2024/02/17 09:32:37 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void init_main(t_fractol *fractol)
{
    fractol->mlx = mlx_init();
    if (!fractol->mlx) 
        error("mlx_init() failed");
    fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, fractol->name);
    if (!fractol->win)
    {
        error("mlx_new_window() failed");
        free(fractol->mlx);
    }
    fractol->img.img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
    if (!fractol->img.img)
    {
        error("mlx_new_image() failed");
        destroy_mlx(fractol);
    }
    fractol->img.addr = mlx_get_data_addr(fractol->img.img, &fractol->img.pixels, &fractol->img.line_len, &fractol->img.endian);
}

void init(t_fractol *fractol, char **av)
{
    init_main(fractol);
    fractol->escape_value = 4;
	fractol->iterations = 100;
	fractol->shift_x = 0.0;
	fractol->shift_y = 0.0;
	fractol->zoom = 1.0;
	fractol->flag = 0;
    if (fractol->name == "julia")
        fractol->mouse = (t_complex){.x = ft_atof(av[2]), .y = ft_atof(av[3])};
    else
        fractol->mouse = (t_complex){0};
    // fractol->color = 0x0000FF;
}