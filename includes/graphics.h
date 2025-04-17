
#ifndef GRAPHICS_H
# define GRAPHICS_H

typedef struct s_graphic
{
    void *mlx;
    void *win;
    void *img_wall;
    void *img_floor;
    void *img_coll;
    void *img_exit;
    void *img_player[4];
}  t_graphic;

#endif