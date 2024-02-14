#include "minilibx_opengl_20191021/mlx.h"
#include <stdlib.h>

typedef struct s_data
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    double zoom;
    double moveX;
    double moveY;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_julia_set(t_data *img)
{
    double zoom = img->zoom;
    double moveX = img->moveX;
    double moveY = img->moveY;

    int max_iter = 100;

    for (int x = 0; x < 800; x++)
    {
        for (int y = 0; y < 600; y++)
        {
            double zx = 1.5 * (x - 800 / 2) / (0.5 * zoom * 800) + moveX;
            double zy = (y - 600 / 2) / (0.5 * zoom * 600) + moveY;

            double cRe = -0.7; // Change this value to explore different Julia sets
            double cIm = 0.27015;

            int iter = 0;
            while (zx * zx + zy * zy < 4 && iter < max_iter)
            {
                double tmp = zx * zx - zy * zy + cRe;
                zy = 2.0 * zx * zy + cIm;
                zx = tmp;
                iter++;
            }

            int color = iter * 0x010101; // Simple color assignment based on iterations
            color = color | ((iter % 256) << 16); // Add red component based on iterations
            color = color | ((iter % 256) << 8);  // Add green component based on iterations

            my_mlx_pixel_put(img, x, y, color);
        }
    }
}

int close_window(void *param)
{
    // Free resources or perform cleanup if needed
    exit(EXIT_SUCCESS);
}

int mouse_press(int button, int x, int y, void *param)
{
    t_data *img = (t_data *)param;

    if (button == 4) // Mouse wheel up
    {
        img->zoom *= 1.1;
        draw_julia_set(img);
        mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
    }
    else if (button == 5) // Mouse wheel down
    {
        img->zoom /= 1.1;
        draw_julia_set(img);
        mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
    }
	else if (button == 1) // Left mouse button click
    {
        // Update moveX and moveY based on the mouse click position
        img->moveX = 1.2 * (x - 800 / 2) / (0.2 * img->zoom * 800);
        img->moveY = (y - 600 / 2) / (0.2 * img->zoom * 600);

        draw_julia_set(img);
        mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
    }

    return 0;
}

// int mouse_move(int x, int y, void *param)
// {
//     t_data *img = (t_data *)param;

//     img->moveX = (x - 800 / 2) / (0.5 * img->zoom * 800);
//     img->moveY = (y - 600 / 2) / (0.5 * img->zoom * 600);

//     draw_julia_set(img);
//     mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);

//     return 0;
// }

int main()
{
    t_data img;

    img.zoom = 1.0; // Initial zoom level
    img.moveX = 0.0; // Initial position
    img.moveY = 0.0;

    img.mlx = mlx_init();
    img.win = mlx_new_window(img.mlx, 800, 600, "Julia Set");

    img.img = mlx_new_image(img.mlx, 800, 600);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    draw_julia_set(&img);

    mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);

    mlx_hook(img.win, 17, 0, close_window, NULL);
    mlx_mouse_hook(img.win, mouse_press, &img); // Mouse press event
    // mlx_hook(img.win, 6, 0, mouse_move, &img);  // Mouse move event

    mlx_loop(img.mlx);

    return 0;
}
