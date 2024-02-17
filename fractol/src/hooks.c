/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 09:08:24 by aalshafy          #+#    #+#             */
/*   Updated: 2024/02/17 09:37:30 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
int	close_handler(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img.img);
	mlx_destroy_window(fractol->mlx, fractol->win);
	free(fractol->mlx);
	exit(0);
}

void	colour_shift(t_fractol *fract)
{
	static int colours[] = {WHITE, PASTELPINK, GREEN, BLUE, MAGENTA, LIME, ORANGE, PURPLE, AQUA, PINK, ELECTRIC, LIGHTENING, LAVA, YELLOW, PASTELYELLOW};
	static int colour_index = 0;

	colour_index = (colour_index + 1) % (sizeof(colours) / sizeof(colours[0]));
	fract->current_colour = colours[colour_index];
	fractol_render(fract);
}

int	key_handler(int keysym, t_fractol *fractol)
{
	if (keysym == K_ESC)
		close_handler(fractol);
	if (keysym == K_LEFT)
		fractol->shift_x += (0.5 * fractol->zoom);
	else if (keysym == K_RIGHT)
		fractol->shift_x -= (0.5 * fractol->zoom);
	else if (keysym == K_UP)
		fractol->shift_y -= (0.5 * fractol->zoom);
	else if (keysym == K_DOWN)
		fractol->shift_y += (0.5 * fractol->zoom);
	else if (keysym == Q)
		fractol->iterations += 10;
	else if (keysym == W)
		fractol->iterations -= 10;
	if (keysym == R)
		data_init(fractol);
	if (keysym == 69)
		fractol->zoom *= 0.95;
	else if (keysym == 78)
		fractol->zoom *= 1.05;
	if (keysym == SPACE)
		fractol->flag = !fractol->flag;
	if (keysym == 8)
		colour_shift(fractol);
	fractol_render(fractol);
	return (0);
}

static void	update_zoom_center(t_fractol *fractol, int mouse_x, int mouse_y)
{
	fractol->shift_x = map(mouse_x, -2, +2, WIDTH) * fractol->zoom;
	fractol->shift_y = map(mouse_y, +2, -2, HEIGHT) * fractol->zoom;
}

int	mouse_handler(int button, int x, int y, t_fractol *fractol)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		fractol->zoom *= 0.95;
		update_zoom_center(fractol, x, y);
	}
	else if (button == 5)
	{
		fractol->zoom *= 1.05;
		update_zoom_center(fractol, x, y);
	}
	fractol_render(fractol);
	return (0);
}

int	julia_track(int x, int y, t_fractol *fractol)
{
	if (!ft_strcmp(fractol->name, "julia"))
	{
		if (!fractol->flag)
		{
			fractol->mouse.x = (map(x, -2, +2, WIDTH) * fractol->zoom)
				+ fractol->shift_x;
			fractol->mouse.y = (map(y, +2, -2, HEIGHT) * fractol->zoom)
				+ fractol->shift_y;
			fractol_render(fractol);
		}
	}
	return (0);
}