#include "so_long.h"
#include <fcntl.h>


static char	*ft_n_zero(void)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static char	*ft_n_neg(int n)
{
	char			*str;
	long			spot;
	int				decomp;
	unsigned int	x;

	x = n * -1;
	decomp = x;
	spot = 0;
	while (decomp)
	{
		decomp /= 10;
		spot++;
	}
	str = (char *)malloc((spot + 2) * sizeof(char));
	if (!str)
		return (0);
	str[spot + 1] = '\0';
	while (x)
	{
		str[spot] = x % 10 + '0';
		x /= 10;
		spot--;
	}
	str[spot] = '-';
	return (str);
}

static char	*ft_n_pos(int n)
{
	char	*str;
	long	spot;
	int		decomp;

	decomp = n;
	spot = 0;
	while (decomp)
	{
		decomp /= 10;
		spot++;
	}
	str = (char *)malloc((spot + 1) * sizeof(char));
	if (!str)
		return (0);
	str[spot] = '\0';
	while (n)
	{
		str[spot - 1] = n % 10 + '0';
		n /= 10;
		spot--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	if (n == 0)
		return (ft_n_zero());
	else if (n > 0)
		return (ft_n_pos(n));
	else
		return (ft_n_neg(n));
}


void    close_game(char **mapstr, int x)
{
    printf("Linha inválida %d\n", x + 1);
    free(mapstr);
    exit(0);
}

int    check_map(char *line, int x, int vectors[2])
{
    int i;

    i = 0;
    if(vectors[0] == vectors[1])
        return(0);
    if(x == 0 || x == (vectors[0] - 1))
    {
        while(line[i] == '1')
            i++;
        if(i == vectors[1])
            return(1);
        else
            return(0);
    }
    else
    {
        while(line[i] != '\n')
            i++;
        if(!(i == vectors[1]))
            return(0);
        if(line[0] == '1' && line[vectors[1] - 1] == '1')
            return(1);
        else
            return(0);
    }
}

void    gen_map(char **mapstr, int vectors[2])
{
    int x;
    int y;
    int fd;

    fd = open("map1.ber", O_RDWR);
    x = 0;
    while(x < vectors[0])
    {
        *(mapstr + x) = get_next_line(fd);
        if(!(check_map(*(mapstr + x), x, vectors)))
            close_game(&*mapstr, x);
        x++;
    }
    *(mapstr + x) = NULL;
}

char    **alloc_strmap(int vectors[2])
{
    int i;
    char **map_str;
    i = 0;
    map_str = malloc(sizeof(char *) * vectors[0] + 1);
    gen_map(&*map_str, vectors);
    return(map_str);
}

char    **file_map(int fd, void *mlx_program)
{
    t_game *game = (t_game *)mlx_program;
    int vectors[2];
    int number_columns;
    char c;
    int linecheck;
    char **map_str;

    vectors[0] = 1;
    vectors[1] = 1;
    while(1)
    {
        linecheck = read(fd, &c, 1);
        if(linecheck == 0)
            break;
        if(linecheck == -1)
            break;
        if(c == '\n')
            vectors[0]++;
        else
            vectors[1]++;
        if(c == 'C')
            game->coins++;
        if(c == 'E')
            game->exit++;
        if(c == 'P')
            game->start++;
    }
    vectors[1]--;
    game->mlx_win.vector.y = vectors[0];
    game->mlx_win.vector.x = vectors[1] / vectors[0];
    if(!(game->exit == 1 && game->start == 1 && game->coins > 0))
    {
        printf("Jogo Invalido\n");
        exit(0);
    }
    // printf("%d - %d\n",  game->mlx_win.vector.y,  game->mlx_win.vector.x);
    close(fd);
    vectors[1] = vectors[1] / vectors[0];
    //printf("numero de linhas - %d\n", number_lines);
    map_str = alloc_strmap(vectors);
    return (map_str);
}

void    gen_tiles(void *mlx_program)
{
    t_game *game = (t_game *)mlx_program;

    game->sprites.person.anim_frame = 10;
    game->sprites.person.framecount = 0;
    game->sprites.coin.anim_frame = 20;
    game->sprites.coin.framecount = 0;

    game->sprites.box.img = mlx_xpm_file_to_image(game->mlx, "./sprites/box/tile-box-64px.xpm", &game->sprites.box.img_width, &game->sprites.box.img_height);
    game->sprites.tiles.img = mlx_xpm_file_to_image(game->mlx, "./sprites/tile/tile-64px.xpm", &game->sprites.tiles.img_width, &game->sprites.tiles.img_height);
    game->sprites.coin.img = mlx_xpm_file_to_image(game->mlx, "./sprites/collectable/diamond.xpm", &game->sprites.coin.img_width, &game->sprites.coin.img_height);
    game->sprites.coin.img_0 = mlx_xpm_file_to_image(game->mlx, "./sprites/collectable/diamond.xpm", &game->sprites.coin.img_width, &game->sprites.coin.img_height);
    game->sprites.coin.img_1 = mlx_xpm_file_to_image(game->mlx, "./sprites/collectable/diamond-2.xpm", &game->sprites.coin.img_width, &game->sprites.coin.img_height);
    game->sprites.exit.img = mlx_xpm_file_to_image(game->mlx, "./sprites/exit/exit-closed.xpm", &game->sprites.exit.img_width, &game->sprites.exit.img_height);
    game->sprites.exit.exit_open = mlx_xpm_file_to_image(game->mlx, "./sprites/exit/exit-open.xpm", &game->sprites.exit.img_width, &game->sprites.exit.img_height);
    game->sprites.person.img = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/1.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.idle_image_0 = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/2.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.idle_image_1 = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/3.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.idle_image_2 = mlx_xpm_file_to_image(game->mlx, "./sprites/stand/4.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);

    game->sprites.person.anim_end.img_1 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_1.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.anim_end.img_2 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_2.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.anim_end.img_3 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_3.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.anim_end.img_4 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_4.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.anim_end.img_5 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_5.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.anim_end.img_6 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_6.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.anim_end.img_7 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_7.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.anim_end.img_8 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_8.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.anim_end.img_9 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_9.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.anim_end.img_10 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_10.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.anim_end.img_11 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_11.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
    game->sprites.person.anim_end.img_12 = mlx_xpm_file_to_image(game->mlx, "./sprites/finish/endgame_12.xpm", &game->sprites.person.img_width, &game->sprites.person.img_height);
}

void    load_map(void *mlx_program)
{
    t_game *game = (t_game *)mlx_program;
    char    *line;
    int x;
    int y;
    int increment_x;
    int increment_y;

    increment_x = game->sprites.tiles.img_width;
    increment_y = game->sprites.tiles.img_height;
    x = 0;
    y = 0;
    //printf("%f\n", anim);
    mlx_clear_window(game->mlx, game->mlx_win.mlx_win);
    //printf("%d - %d", x, y);
    //printf("%s\n", game->sprites.person.path);

        while(game->map[y][x])
        {
            if(game->map[y][x] == '1')
            {
               mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.box.img, x * increment_x, y * increment_y);
               x++;
            }
            if(game->map[y][x] == '0')
            {
                mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.tiles.img, x * increment_x, y * increment_y);
                x++;
            }
            if(game->map[y][x] == 'C')
            {
                mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.tiles.img, x * increment_x, y * increment_y);
                mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.coin.img, x * increment_x, y * increment_y);
                x++;
            }
            if(game->map[y][x] == 'E')
            {
                if(game->coins <= 0)
                    mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.exit.exit_open, x * increment_x, y * increment_y);
                else
                    mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.exit.img, x * increment_x, y * increment_y);
                x++;
            }
            if(game->map[y][x] == 'P')
            {
                if(game->move == 1)
                    printf("posicao - %f - x = %d\n", x * (increment_x * game->sprites.person.anim_rum), x);
                if(game->move == 1)
                {
                    game->sprites.person.anim_rum += 0.10;
                    // printf("%f\n", game->sprites.person.anim_rum);
                }
                mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.tiles.img, x * increment_x, y * increment_y);
                mlx_put_image_to_window(game->mlx, game->mlx_win.mlx_win, game->sprites.person.img, x * (increment_x * game->sprites.person.anim_rum), y * increment_y);
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
        if(game->sprites.person.anim_rum < 1)
            load_map(game);
        
        game->move = 0;
        mlx_string_put(game->mlx, game->mlx_win.mlx_win, 64, 64, 555, game->movements);
        if(game->game_status == 1)
            mlx_string_put(game->mlx, game->mlx_win.mlx_win, (game->mlx_win.vector.x / 2) - 50, (game->mlx_win.vector.y / 2) - 50, 555, "GANHOU!!!");
}

int    check_tile(void *mlx_program, int y, int x)
{
    t_game *game = (t_game *)mlx_program;

    if(game->map[y][x] == 'C')
        game->coins--;
    if(game->map[y][x] == 'E' && game->coins == 0)
    {
        game->map[y][x] = 'P';
        return(2);
    }
    game->map[y][x] = 'P';
    return(1);
}

int move_person(void *mlx_program, char direction)
{
    t_game *game = (t_game *)mlx_program;
    int y;
    int x;

    y = game->sprites.person.position.y;
    x = game->sprites.person.position.x;
    if(direction == 'A')
    {
        if(game->map[y][x - 1] != '1')
            return (check_tile(game, y, x - 1));
        else
            return (0);
    }
    if(direction == 'D')
    {
        if(game->map[y][x + 1] != '1')
            return (check_tile(game, y, x + 1));
        else
            return (0);
    }
    if(direction == 'S')
    {
        if(game->map[y + 1][x] != '1')
            return (check_tile(game, y + 1, x));
        else
            return (0);
    }
    if(direction == 'W')
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
    {
            mlx_destroy_window(game->mlx, game->mlx_win.mlx_win);
            free(game->map);
            exit(0);
    }
        if(keycode == 0)
            check = move_person(game, 'A');
        if(keycode == 2)
            check = move_person(game, 'D');
        if(keycode == 1)
            check = move_person(game, 'S');
        if(keycode == 13)
            check = move_person(game, 'W');
        if(check == 1)
        {
            game->map[y][x] = '0';
            moves++;
        game->move = 1;
        game->sprites.person.anim_rum = 0;
        game->movements = ft_itoa(moves);
        // printf("Coins restantes - %d - %d\n", game->coins, check);
        printf("Movements - %d\n", moves);
        }
        if(check == 2)
        {
            game->map[y][x] = '0';
            game->game_status = 1;
        }

	return (0);
}

void    anim_person(void *param)
{
	t_game	*game = (t_game *)param;

    if (game->game_status == 1)
    {
        if (game->sprites.person.framecount == game->sprites.person.anim_frame)
            game->sprites.person.img = game->sprites.person.anim_end.img_1;
        else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 2)
            game->sprites.person.img = game->sprites.person.anim_end.img_2;
        else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 3)
            game->sprites.person.img = game->sprites.person.anim_end.img_3;
        else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 4)
            game->sprites.person.img = game->sprites.person.anim_end.img_4;
        else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 5)
            game->sprites.person.img = game->sprites.person.anim_end.img_5;
        else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 6)
            game->sprites.person.img = game->sprites.person.anim_end.img_6;
        else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 7)
            game->sprites.person.img = game->sprites.person.anim_end.img_7;
        else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 8)
            game->sprites.person.img = game->sprites.person.anim_end.img_8;
        else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 9)
            game->sprites.person.img = game->sprites.person.anim_end.img_9;
        else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 10)
            game->sprites.person.img = game->sprites.person.anim_end.img_10;
        else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 11)
            game->sprites.person.img = game->sprites.person.anim_end.img_11;
        else if (game->sprites.person.framecount >= game->sprites.person.anim_frame * 12)
            game->sprites.person.img = game->sprites.person.anim_end.img_12;
    }
    else
    {
        if (game->sprites.person.framecount == game->sprites.person.anim_frame)
            game->sprites.person.img = game->sprites.person.idle_image_0;
        else if (game->sprites.person.framecount == game->sprites.person.anim_frame * 2)
            game->sprites.person.img = game->sprites.person.idle_image_1;
        else if (game->sprites.person.framecount >= game->sprites.person.anim_frame * 3)
        {
            game->sprites.person.img = game->sprites.person.idle_image_2;
            game->sprites.person.framecount = 0;
        }
    }
	game->sprites.person.framecount += 1;
}

void    anim_coin(void *param)
{
	t_game	*game = (t_game *)param;

    if (game->sprites.coin.framecount == game->sprites.coin.anim_frame)
		game->sprites.coin.img = game->sprites.coin.img_0;
	else if (game->sprites.coin.framecount == game->sprites.coin.anim_frame * 3)
    {
		game->sprites.coin.img = game->sprites.coin.img_1;
        game->sprites.coin.framecount = 0;
    }
	game->sprites.coin.framecount += 1;
}

int	ft_update (void *param)
{
	t_game	*game = (t_game *)param;
	static int	frame;

    anim_person(game);
    anim_coin(game);
    load_map(game);
    return (0);
}

void    load_mlx(int map)
{
    char    *line;
    t_game   game;
    game.sprites.person.anim_rum = 1;
    game.movements = "0";
    game.game_status = 0;
    game.move = 0;
    game.coins = 0;
    game.start = 0;
    game.exit = 0;
	game.mlx = mlx_init();
    game.map = file_map(map, &game);
    gen_tiles(&game);

    // printf("%d - %d - %d\n", game.coins, game.start, game.exit);
    // if((game.mlx_win.vector.x * game.sprites.tiles.img_width) > 1920)
    //     game.mlx_win.vector.x = width_resize(&game);
    // else
    game.mlx_win.vector.x = game.mlx_win.vector.x * game.sprites.tiles.img_width;
    game.mlx_win.vector.y = game.mlx_win.vector.y * game.sprites.tiles.img_height;
    // printf("%d - %d\n", game.sprites.box.img_width, game.sprites.box.img_height);
    // printf("%d - %d\n", game.mlx_win.vector.x, game.sprites.box.img_width);
    game.mlx_win.mlx_win = mlx_new_window(game.mlx, game.mlx_win.vector.x, game.mlx_win.vector.y, "SO_LONG JGIACOMO");
    mlx_key_hook(game.mlx_win.mlx_win, press_key, &game);
    mlx_loop_hook(game.mlx, *ft_update, &game);
    load_map(&game);
    mlx_loop(game.mlx);
}

