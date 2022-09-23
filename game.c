#include "so_long.h"

void    gen_tiles(void *mlx_program)
{
    t_game *game = (t_game *)mlx_program;

    game->sprites.person.anim_frame = 10;
    game->sprites.person.framecount = 0;
    game->sprites.box.img = mlx_xpm_file_to_image(game->mlx, "./sprites/box/tile-box-64px.xpm", &game->sprites.box.img_width, &game->sprites.box.img_height);
    game->sprites.tiles.img = mlx_xpm_file_to_image(game->mlx, "./sprites/tile/tile-64px.xpm", &game->sprites.tiles.img_width, &game->sprites.tiles.img_height);
    game->sprites.coin.img = mlx_xpm_file_to_image(game->mlx, "./sprites/collectable/diamond.xpm", &game->sprites.coin.img_width, &game->sprites.coin.img_height);
    game->sprites.exit.img = mlx_xpm_file_to_image(game->mlx, "./sprites/exit/exit-closed.xpm", &game->sprites.exit.img_width, &game->sprites.exit.img_height);
    game->sprites.exit.exit_open = mlx_xpm_file_to_image(game->mlx, "./sprites/exit/exit-open.xpm", &game->sprites.exit.img_width, &game->sprites.exit.img_height);
    game->sprites.person.img = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/1.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.idle_image_0 = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/2.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.idle_image_1 = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/3.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.idle_image_2 = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/4.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
}

void    load_mlx(int map)
{
    char    *line;
    t_game   game;
    game.coins = 1;
    game.mlx_win.vector.x = 832;
    game.mlx_win.vector.y = 320;
	game.mlx = mlx_init();
    game.mlx_win.mlx_win = mlx_new_window(game.mlx, game.mlx_win.vector.x, game.mlx_win.vector.y, "Hello world!");
    gen_tiles(&game);
    game.map = file_map(map);
    mlx_key_hook(game.mlx_win.mlx_win, press_key, &game);
    mlx_loop_hook(game.mlx, *ft_update, &game);
    load_map(&game);
    mlx_loop(game.mlx);
}