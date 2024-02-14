 #include "minilibx_opengl_20191021/mlx.h"
#include <stdlib.h>
#define WIDTH 800
#define HEIGHT 600

typedef struct {
    double real;
    double imag;
} Complex;

int mandelbrot(Complex c) {
    Complex z = {0, 0};
    int iterations = 0;
    
    while (z.real * z.real + z.imag * z.imag <= 4 && iterations < 1000) {
        double temp = z.real * z.real - z.imag * z.imag + c.real;
        z.imag = 2 * z.real * z.imag + c.imag;
        z.real = temp;
        iterations++;
    }
    
    return iterations;
}

int main() {
    void *mlx = mlx_init();
    void *window = mlx_new_window(mlx, WIDTH, HEIGHT, "Mandelbrot Set");
    void *image = mlx_new_image(mlx, WIDTH, HEIGHT);
    int *image_data = (int *)mlx_get_data_addr(image, &(int){0}, &(int){0}, &(int){0});
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Complex c = {
                (x - WIDTH / 2.0) * 4.0 / WIDTH,
                (y - HEIGHT / 2.0) * 4.0 / HEIGHT
            };
            
            int iterations = mandelbrot(c);
            int color = iterations * 255 / 1000;
            image_data[y * WIDTH + x] = (color << 16) | (color << 8) | color;
        }
    }
    
    mlx_put_image_to_window(mlx, window, image, 0, 0);
    mlx_loop(mlx);
    
    return 0;
}
