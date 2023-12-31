/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:33:57 by edcastro          #+#    #+#             */
/*   Updated: 2023/11/06 13:48:24 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>
# include "../library/.MLX42/include/MLX42/MLX42.h"
# include "../library/libft/inc/libft.h"

# define WIDTH				1920
# define HEIGHT				1080
# define BACKGROUND			0x22222200
# define COLOR_TEN			0x9e0142ff
# define COLOR_NINE			0xd53e4fff
# define COLOR_EIGHT		0xf46d43ff
# define COLOR_SEVEN		0xfdae61ff
# define COLOR_SIX			0xfee08bff
# define COLOR_FIVE			0xe6f598ff
# define COLOR_FOUR			0xabdda4ff
# define COLOR_THREE		0x66c2a5ff
# define COLOR_TWO			0x3288bdff
# define COLOR_ONE			0x5e4fa2ff
# define FORMAT				"Format:\n\t./fdf maps/filename.fdf"
# define MALLOC				"Malloc failed"
# define INVALID_MAP		"Map is invalid"
# define FILE_ERROR			"Unable to open file"

enum	e_boolean
{
	FALSE,
	TRUE
};

typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
	int		zcolor;
}				t_point3d;

typedef struct s_point2d
{
	double		x;
	double		y;
	double		z;
	int			rgba;
}			t_point2d;

typedef struct s_map
{
	int				rows;
	int				cols;
	int				high;
	int				low;
	enum e_boolean	use_zcolor;
	double			x_offset;
	double			y_offset;
	double			interval;
	double			alpha;
	double			beta;
	double			xrotate;
	double			yrotate;
	double			zrotate;
	double			zoom;
	double			zscale;
	t_point3d		**grid3d;
	t_point2d		**grid2d;
}					t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*image;
}				t_fdf;

// main
void		init_map(t_map *map);
// parse
void		parse_map(int fd, t_map *map);
void		get_dimensions(int fd, t_map *map);
// error
void		ft_free_tab(void **ptr, size_t len);
void		free_map(t_map *map);
void		handle_error(const char *message);
void		error_map(int fd, t_map *map, char *message);
// draw
void		project(t_map *map, int i, int j);
void		draw_image(void *param);
void		display_menu(mlx_t *mlx);
// rotate
void		rotate_x(double *y, double *z, double alpha);
void		rotate_y(double *x, double *z, double beta);
void		rotate_z(double *x, double *y, double gamma);
// hooks
void		ft_hook(void *param);
void		fdf_scrollhook(double xdelta, double ydelta, void *param);
void		ft_hook_rotate(void *param);
void		ft_hook_project(void *param);
// utils
void		make_upper(unsigned int i, char *c);
void		draw_reset(mlx_image_t *image);
int			valid_filename(const char *filename);
// color
int			get_color(t_point2d current, t_point2d a, t_point2d b);
void		set_zcolor(t_map *map);

#endif