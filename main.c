#include "so_long.h"
#include <fcntl.h>

int	main()
{
    int fd;
    int x = 0;
    fd = open("map1.ber", O_RDWR);
    if(fd == -1)
    {
      perror("Error: ");
      exit(0);
      return(-1);
   }
//    char *map;
   // call_map(fd);
   // printf("%s\n", call_map(fd));
    load_mlx(fd);
}