#include "so_long.h"

int get_map(t_data *data, int collumn_count, int line_count)
{
if ((check_map_borders(data->map, collumn_count, line_count)) != 1
		|| (check_map_requirements(data->map, 0, 0, 0, data) != 1)
		|| (so_long_solver(data) != 1))
		return (-1);
return (0);
}