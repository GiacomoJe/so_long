#ifndef SO_LONG
# define SO_LONG
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
#include <stdio.h>
#include <string.h>
# include "./includes/gnl/get_next_line.h"

# ifndef ANIMATION_FRAMES
#  define ANIMATION_FRAMES 10
# endif

typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct s_vector
{
    int x;
    int y;
}               t_vector;

typedef struct	s_box{
	void	*img;
	char	*path;
	int		img_width;
	int		img_height;
    t_vector position;
}           t_box;

typedef struct	s_coin{
	void	*img;
	char	*path;
	int		img_width;
	int		img_height;
    t_vector position;
}				t_coin;

typedef struct	s_enemy{
	void	*img;
	char	*path;
	int		img_width;
	int		img_height;
    t_vector position;
}				t_enemy;

typedef struct	s_person{
	void		*img;
    void        *idle_image_0;
    void        *idle_image_1;
    void        *idle_image_2;
	char		*path;
	int			img_width;
	int			img_height;
	t_vector	position;
    int         anim_frame;
    int         framecount;
}				t_person;

typedef struct	s_tiles{
	void	*img;
	char	*path;
	int		img_width;
	int		img_height;
}				t_tiles;

typedef struct	s_exit{
	void	*img;
    void    *exit_open;
	char	*path;
	int		img_width;
	int		img_height;
}				t_exit;

typedef struct  s_sprites
{
    t_tiles     tiles;
    t_person    person;
    t_box       box;
    t_coin      coin;
    t_enemy     enemy;
    t_exit      exit;
}               t_sprites;

typedef struct s_window
{
    void    *mlx_win;
    t_vector  vector;
}   t_window;


typedef struct s_game
{
    void        *mlx;
    t_window    mlx_win;
    t_sprites   sprites;
    char        **map;
    int         coins;
}               t_game;

void    load_mlx(int fd);

#endif