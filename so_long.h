#ifndef SO_LONG
# define SO_LONG
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
#include <stdio.h>
#include <string.h>
#include "keys.h"
# include "./includes/gnl/get_next_line.h"

# ifndef ANIMATION_FRAMES
#  define ANIMATION_FRAMES 10
# endif

#define MLX_SYNC_IMAGE_WRITABLE		1
#define MLX_SYNC_WIN_FLUSH_CMD		2
#define MLX_SYNC_WIN_CMD_COMPLETED	3

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
	void	*img_0;
	void	*img_1;
	char	*path;
	int		img_width;
	int		img_height;
	int		anim_frame;
	int		framecount;
    t_vector position;
}				t_coin;

typedef struct	s_enemy{
	void	*img;
	char	*path;
	int		img_width;
	int		img_height;
    t_vector position;
}				t_enemy;

typedef struct	s_anim_end{
	void	*img_1;
	void	*img_2;
	void	*img_3;
	void	*img_4;
	void	*img_5;
	void	*img_6;
	void	*img_7;
	void	*img_8;
	void	*img_9;
	void	*img_10;
	void	*img_11;
	void	*img_12;
}			t_anim_end;

typedef struct	s_person{
	void		*img;
    void        *idle_image_0;
    void        *idle_image_1;
    void        *idle_image_2;
	void        *idle_image_3;
    void        *idle_image_4;
    void        *idle_image_5;
	void        *idle_image_6;
    void        *idle_image_7;
    void        *idle_image_8;
	void        *idle_image_9;
    void        *idle_image_10;
    void        *idle_image_11;
	void        *idle_image_12;
    void        *idle_image_13;
	t_anim_end	anim_end;
	char		*path;
	int			img_width;
	int			img_height;
	t_vector	position;
    int         anim_frame;
    int         framecount;
	float		anim_rum;
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
	int			exit;
	int			start;
	char		*movements;
	int			move;
	int			game_status;
}               t_game;

void	load_mlx(int fd);

#endif