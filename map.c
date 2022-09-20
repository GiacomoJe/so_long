#include "so_long.h"
#include <fcntl.h>

void    print_line(char **map, int i)
{
    int x;

    x = 0;
    while(x < i)
    {
        printf("%s", map[x]);
        x++;
    }
}

void    gen_map(char **mapstr, int i)
{
    int x;
    int y;
    int fd;
    char **teste;

    fd = open("map1.ber", O_RDWR);
    x = 0;
    while(x < i)
    {
        *(mapstr + x) = get_next_line(fd);
        x++;
    }
    *(mapstr + x) = NULL;
}

char    **alloc_strmap(int number_lines)
{
    int i;
    char **map_str;

    i = 0;
    map_str = malloc(sizeof(char *) * number_lines + 1);
    gen_map(&*map_str, number_lines);
    return(map_str);
}

char    **file_map(int fd)
{
    int number_lines;
    char c;
    int linecheck;
    char **map_str;

    number_lines = 1;
    while(1)
    {
        linecheck = read(fd, &c, 1);
        if(linecheck == 0)
            break;
        if(linecheck == -1)
            break;
        if(c == '\n')
            number_lines++;

    }
    close(fd);
    //printf("numero de linhas - %d\n", number_lines);
    map_str = alloc_strmap(number_lines);
    return (map_str);
}

void    gen_tiles(void *mlx_program)
{
    t_game *game = (t_game *)mlx_program;

    game->sprites.person.anim_frame = 10;
    game->sprites.person.framecount = 0;
    game->sprites.box.img = mlx_xpm_file_to_image(game->mlx, "./tile-box-64px.xpm", &game->sprites.box.img_width, &game->sprites.box.img_height);
    game->sprites.tiles.img = mlx_xpm_file_to_image(game->mlx, "./tile-64px.xpm", &game->sprites.tiles.img_width, &game->sprites.tiles.img_height);
    game->sprites.coin.img = mlx_xpm_file_to_image(game->mlx, "./sprites/collectable/diamond.xpm", &game->sprites.coin.img_width, &game->sprites.coin.img_height);
    game->sprites.exit.img = mlx_xpm_file_to_image(game->mlx, "./sprites/exit/exit-closed.xpm", &game->sprites.exit.img_width, &game->sprites.exit.img_height);
    game->sprites.exit.exit_open = mlx_xpm_file_to_image(game->mlx, "./sprites/exit/exit-open.xpm", &game->sprites.exit.img_width, &game->sprites.exit.img_height);
    game->sprites.person.img = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/1.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.idle_image_0 = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/2.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.idle_image_1 = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/3.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.idle_image_2 = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/4.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
}

void    load_map(void *mlx_program)
{
    t_game *game = (t_game *)mlx_program;
    char    *line;
    int x;
    int y;

    x = 0;
    y = 0;

    mlx_clear_window(game->mlx, game->mlx_win.mlx_win);
    //printf("%d - %d", x, y);
    //printf("%s\n", game->sprites.person.path);

        while(game->map[y][x])
        {
            if(game->map[y][x] == '1')
            {
               mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.box.img, x * 64, y * 64);
               x++;
            }
            if(game->map[y][x] == '0')
            {
                mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.tiles.img, x * 64, y * 64);
                x++;
            }
            if(game->map[y][x] == 'C')
            {
                mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.tiles.img, x * 64, y * 64);
                mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.coin.img, x * 64, y * 64);
                x++;
            }
            if(game->map[y][x] == 'E')
            {
                if(game->coins <= 0)
                    mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.exit.exit_open, x * 64, y * 64);
                else
                    mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.exit.img, x * 64, y * 64);
                x++;
            }
            if(game->map[y][x] == 'P')
            {
                mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.tiles.img, x * 64, y * 64);
                mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.person.img, x * 64, y * 64);
                game->sprites.person.position.x = x;
                game->sprites.person.position.y = y;
                x++;
            }
            if(game->map[y][x] == '\n')
            {
                y++;
                x = 0;
            }
            //printf("x = %d | y = %d | win_width = %d | win_height = %d |\n", x, y, game->mlx_win.vector.x, game->mlx_win.vector.y);
        }
}

int    check_tile(void *mlx_program, int y, int x)
{
    t_game *game = (t_game *)mlx_program;

    if(game->map[y][x] == 'C')
        game->coins--;
    game->map[y][x] = 'P';
    if(game->map[y][x] == 'E' && game->coins == 0)
        return(2);
    return(1);
}

int move_person(void *mlx_program, char *direction)
{
    t_game *game = (t_game *)mlx_program;
    int y;
    int x;

    y = game->sprites.person.position.y;
    x = game->sprites.person.position.x;
    if(direction == "LEFT")
    {
        if(game->map[y][x - 1] != '1')
            return (check_tile(game, y, x - 1));
        else
            return (0);
    }
    if(direction == "RIGHT")
    {
        if(game->map[y][x + 1] != '1')
            return (check_tile(game, y, x + 1));
        else
            return (0);
    }
    if(direction == "DOWN")
    {
        if(game->map[y + 1][x] != '1')
            return (check_tile(game, y + 1, x));
        else
            return (0);
    }
    if(direction == "UP")
    {
        if(game->map[y - 1][x] != '1')
            return (check_tile(game, y - 1, x));
        else
            return (0);
    }
    return (0);
}

int	press_key(int keycode, void *mlx_program)
{
    t_game *game = (t_game *)mlx_program;
    int check;
    int static moves;
    int x;
    int y;

    y = game->sprites.person.position.y;
    x = game->sprites.person.position.x;
    //printf("Atual - %d - %d\n", y, x);
    //printf("keycode - %d\n", keycode);
    if(keycode == 53)
    	mlx_destroy_window(game->mlx, game->mlx_win.mlx_win);
    if(keycode >= 123 && keycode <= 126)
    {
        if(keycode == 123)
            check = move_person(game, "LEFT");
        if(keycode == 124)
            check = move_person(game, "RIGHT");
        if(keycode == 125)
            check = move_person(game, "DOWN");
        if(keycode == 126)
            check = move_person(game, "UP");
        if(check == 1)
        {
            game->map[y][x] = '0';
            moves++;
        //    printf("Coins restantes - %d\n", game->coins);
            printf("Movements - %d\n", moves);
        }
    }
	return (0);
}

void    anim_person(void *param)
{
	t_game	*game = (t_game *)param;

    if (game->sprites.person.framecount == game->sprites.person.anim_frame)
		game->sprites.person.img = game->sprites.person.idle_image_0;
	else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 2)
		game->sprites.person.img = game->sprites.person.idle_image_1;
    else if (game->sprites.person.framecount >= game->sprites.person.anim_frame * 3)
	{
		game->sprites.person.img = game->sprites.person.idle_image_2;
        game->sprites.person.framecount = 0;
	}
	game->sprites.person.framecount += 1;
}

int	ft_update (void *param)
{
	t_game	*game = (t_game *)param;
	static int	frame;

    anim_person(game);
    load_map(game);
    return (0);
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