#include "src/minirt.h"

int	key_hook(int key_code)
{
	if (key_code == ESC)
		exit(0);
	return (0);
}

int main()
{
    int R = 255; 
    int G = 177; 
    int B = 54; 
  int color = (R << 16) | (G << 8) | B;

  void *mlx = mlx_init();
  void *wind = mlx_new_window(mlx , 700 , 700 , "test");
int i , y;
i = 0;
y = 0;
while(i< 700 )
{
    y= 0;
    while(y < 700)
    {
        mlx_pixel_put(mlx, wind , i , y, color);
        y++;
    }
    i++;
}
 mlx_key_hook(wind, key_hook, NULL);

mlx_loop(mlx);
}
