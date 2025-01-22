#include "mlx/mlx.h"
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < 1920 && y < 1080) // Ensure within bounds
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}
void draw_x(t_data *data, int x, int y, int color, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        my_mlx_pixel_put(data, x + i, y, color);
		i++;
    }
    
}
void draw_y(t_data *data, int x, int y, int color, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        my_mlx_pixel_put(data, x , y + i, color);
		i++;
    }
    
}

void	draw_squir(t_data *data, int x, int y, int color, int size)
{
	while (size-- >= 0)
	{
		
		draw_x(data, x, y, color, size);
		draw_y(data, x, y, color, size);
		draw_y(data, x + size, y , color, size);
		draw_x(data, x , y + size, color, size);
		x--;
		y--;
	}
	
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 2920, 2080, "Draw Circle");
	img.img = mlx_new_image(mlx, 2920, 2080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// Draw a circle at (960, 540) with radius 100 and red color

    draw_squir(&img , 960, 540, 0x00FF0000, 250);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

