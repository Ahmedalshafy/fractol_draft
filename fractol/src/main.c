/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 07:54:13 by aalshafy          #+#    #+#             */
/*   Updated: 2024/02/17 09:04:37 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int    main(int ac, char **av)
{
    t_fractol	fractol;

    parse_args(ac, av, &fractol);
    init(&fractol, av);
    draw(&fractol);
}

void    parse_args(int ac, char **av, t_fractol *fractol)
{
    if (ac == 2 && (!ft_strcmp(av[1], "mandelbrot") || !ft_strcmp(av[1], "burningship")))
        fractol->name = av[1];
    else if (ac == 4 && (!ft_strcmp(av[1], "julia")))
        fractol->name = av[1];
    else
    {
        ft_printf(WRONG_INPUT"\n");
        exit(0);
    }
}
    