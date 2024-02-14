Name = fractol
CFILES := $(wildcard *.c)
CC = gcc

all:
	$(MAKE) -C ./minilibx_opengl_20191021
	$(CC) $(CFLAGS) $(CFILES) -o $(Name) -L ./minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit

clean:
	$(MAKE) clean -C ./minilibx_opengl_20191021

fclean:
	$(MAKE) fclean -C ./minilibx_opengl_20191021
	rm -rf $(Name)