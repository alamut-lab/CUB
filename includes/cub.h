#ifndef CUB_H
# define CUB_H
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <X11/keysym.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define MAX_SECTION_ITEMS 254 // uint8_t max
# define MAX_SECTION_LINE_LEN 254 // uint8_t max
# define MAX_MAP_WIDTH 65534 // uint16_t max
# define MAX_MAP_HEIGHT 65534 // uint16_t max
# define N_DEF_SECTION 7 // all the section that are not maps
# define MAX_DEBUG_LINE 1024

# define HEX_COLOR_LEN 8

typedef struct	s_texture_def
{
	char		*name;
	char		*path;
	int32_t		color;
	bool		is_color;
}				t_texture_def;

typedef struct	s_wall_def
{
	uint8_t		tex_north;
	uint8_t		tex_west;
	uint8_t		tex_south;
	uint8_t		tex_east;
	char 		symbol;
} t_wall_def;

typedef struct	s_air_def
{
	uint8_t		tex_floor;
	uint8_t		tex_ceiling;
	char 		symbol;
}				t_air_def;

typedef struct	s_door_def
{
	uint8_t		tex_front;
	uint8_t		tex_back;
	uint8_t		tex_side;
	char 		symbol;
	bool		is_closed;
}				t_door_def;

typedef struct	s_monster_def
{
	uint8_t		hp;
	uint8_t		size_pc;
	uint8_t		tex;
	char		symbol;
}				t_monster_def;

typedef struct	s_obj_def
{
	uint8_t		tex;
	uint8_t		size_pc;
	char		symbol;
	uint8_t		pad;
}				t_obj_def;

typedef enum	e_dir
{
	DIR_NONE,
	DIR_NORTH,
	DIR_EAST,
	DIR_SOUTH,
	DIR_WEST
}				t_dir;

typedef struct	s_player_def
{
	t_dir		dir;
	uint8_t		tex;
	char		symbol;
}				t_player_def;

typedef struct s_img
{
	bool		is_color;
	uint32_t	hex_color;
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}	t_img;


typedef struct	s_data
{
	// definitions
	uint32_t		textures_section_id;
	uint8_t			textures_len;
	t_texture_def 	*textures_defs;

	uint32_t		walls_section_id;
	uint8_t			walls_len;
	t_wall_def		*walls_defs;

	uint32_t		airs_section_id;
	uint8_t			airs_len;
	t_air_def		*airs_defs;

	uint32_t		doors_section_id;
	uint8_t			doors_len;
	t_door_def 		*doors_defs;

	uint32_t		monsters_section_id;
	uint8_t			monsters_len;
	t_monster_def	*monsters_defs;

	uint32_t		objs_section_id;
	uint8_t			obj_len;
	t_obj_def		*obj_defs;

	uint32_t		players_section_id;
	uint8_t			player_len;
	t_player_def 	*player_defs;

	// player data
	uint16_t		player_row;
	uint16_t		player_col;
	t_dir			player_dir;

	// ids arrays
	char *all_ids;
	char *wall_ids;
	char *air_ids;
	char *door_ids;
	char *monster_ids;
	char *obj_ids;
	char *player_ids;

	uint16_t		door_rt_count;
	uint16_t		monster_rt_count;

	// mandatory map
	uint32_t	m_map_section_id;
	char		**m_map;
	uint16_t	m_max_width; 
	uint16_t	m_height;

	bool have_bonus;
	// bonus map
	uint32_t	b_map_section_id;
	char		**b_map;
	uint16_t	b_max_width;
	uint16_t	b_height;

	// t_img s
	t_img		*img_tab;
}				t_data;

typedef enum	e_perr
{
	PERR_NONE = 0,
	PERR_OVERFLOW,
	PERR_SEGMENT_TOO_LONG,
	PERR_INVALID_CHAR,
	PERR_UNFINISHED_LINE,
	PERR_INVALID_ID,
	PERR_SECTION_TITLE,
	PERR_OPEN_BRACE,
	PERR_CLOSE_BRACE,
	PERR_NO_CONTENT,
	PERR_MAX_CONTENT,
	PERR_UNEXPECTED_EOF,
	PERR_UNEXPECTED_EOL,
	PERR_UNEXPECTED_REST_OF_LINE,
	PERR_INVALID_HEX_COLOR,
	PERR_BAD_SEPARATOR,
	PERR_BAD_KEYWORD,
	PERR_INVALID_LINE_FORMAT,
	PERR_NO_BOOL_FOUND,
	PERR_NO_DIR_FOUND,
	INVALIDE_TEXT_TYPE,
	PERR_INVALID_PATH,
	PERR_TEXT_NOT_RECOGNIZED,
	PERR_PLAYER_NOT_FOUND,
	PERR_UNEVEN_MAPS,
	PERR_BAD_HEX_PREFIX,
	PERR_BAD_HEX_COLOR_LEN,
	PERR_BAD_FILEPATH,
	PERR_NO_TEX_MATCH,
	PERR_INVALID_PERCENT,
	PERR_TOO_LARGE_NUMBER,
	PERR_NO_NUMBER,
	PERR_MAP_SIZE_TOO_LARGE,
	PERR_REPETED_SYM,
	PERR_INVALIDE_SYMBOL,
	PERR_TOO_MANY_PLAYER,
	PERR_UNCLOSED_MAP,
	PERR_UNEXPECTED_SPACE,
	PERR_MAP_MISMATCH,
	PERR_MLX_ERROR,
	PERR_MALLOC_ERR
}				t_perr;

typedef struct	s_index
{
	size_t			line;
	size_t			col;
	t_perr			err;
}				t_index;

typedef struct		s_parsing
{
	char			**file_content;
	t_data			*data;
	t_index			idx;
}					t_parsing;

//get_map.c
char **get_file(char *filename);
void	free_str_tab(char **tab);
void	print_str_tab(char **tab);

bool parse_file(char *filename, t_data *d);

// parsing_utils.c
bool is_char_fmt(char c);
bool is_space_fmt(char c);
bool skip_space_tab(char *s, t_index *i, bool expect_eol);
bool skip_char_fmt(char *s, t_index *i);
bool skip_separator(char *s, t_index *i, char sep);
bool skip_keyword(char *s, t_index *i, char *keyword);
bool is_hex_digit(char c);
bool isalpha_up(int c);
bool skip_hex_color(char *s, t_index *i, int32_t *dest);
bool skip_file_path(char *s, t_index *i, char **dest);
bool skip_tex_name(char *s, t_index *i, char **dest);
bool skip_and_get_symbol(char *s, t_index *i, char *dest);
ssize_t find_tex_from_str(char *s, size_t n, t_parsing *p);
bool	skip_uint16_value(char *s, t_index *i, uint16_t *out);
bool	skip_uint8_value(char *s, t_index *i, uint8_t *out);
bool	skip_percent_value(char *s, t_index *i, uint8_t *out);

// CHECK SECTION
bool check_texture_section(t_parsing *p, size_t len);
bool check_wall_section(t_parsing *p, size_t len);
bool check_air_section(t_parsing *p, size_t len);
bool check_door_section(t_parsing *p, size_t len);
bool check_monster_section(t_parsing *p, size_t len);
bool check_object_section(t_parsing *p, size_t len);
bool check_player_section(t_parsing *p, size_t len);
bool check_mandatory_map_section(t_parsing *p, size_t len);
bool check_bonus_map_section(t_parsing *p, size_t len);

bool check_section(char *name, bool (*func)(t_parsing*, size_t), t_parsing *p);

bool validate_map(t_data *d, t_index *i);

// check IDS
bool get_ids(t_parsing *p);

// parsing_free_def.c
void free_ids(t_data *d);
void free_textures_def(t_texture_def **tex, size_t len);
void free_all_def(t_data *d);
void free_preprocessing_data(t_data *d);

// parsing_print_def.c
void print_parsing(t_data *d);
void print_textures_def(t_texture_def *tex, size_t len);
void print_walls_def(t_wall_def *w, size_t len, t_texture_def *tex);
void print_airs_def(t_air_def *a, size_t len, t_texture_def *tex);
void print_doors_def(t_door_def *d, size_t len, t_texture_def *tex);
void print_monsters_def(t_monster_def *m, size_t len, t_texture_def *tex);
void print_objects_def(t_obj_def *o, size_t len, t_texture_def *tex);
void print_players_def(t_player_def *o, size_t len, t_texture_def *tex);
void print_perr(t_index *i);

/*SYSTEM*/

void safe_free(void **ptr);

/*MLX*/

# define WINDOW_WIDTH 2000
# define WINDOW_HEIGHT 1000

typedef struct s_screen
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}	t_screen;

void free_screen(t_screen *s);
bool	init_mlx(t_screen *screen, char *title);
void free_img_tab(void *mlx, t_img *img, size_t lim);
bool get_all_tex(t_data *data, t_screen *s);
void draw_tex_lib(t_screen *s, t_data *d);
/*BLOB*/

// helper struct

typedef struct	s_xy_double
{
	double		x;
	double		y;
}				t_xy_double;

typedef struct	s_xy_uint32
{
	uint32_t	x;
	uint32_t	y;
}				t_xy_uint32;

/*RUNTIME STRUCT*/

typedef struct	s_world
{
	void *blob_raw;

}				t_world;


typedef struct	s_player_rt
{
	t_xy_double	pos;
	t_xy_double	dir;
	t_xy_double	plane;
	uint8_t		tex_id;
}				t_player_rt;

/*BLOB*/

typedef struct	s_blob_seg // size = 16 // 4 unit on 1 cache line
{
	uint32_t	start;
	uint32_t	end;
	uint32_t	used;
	union {
		struct {
			uint16_t width;
			uint16_t height;
		} map_data;
		uint32_t	count;
	};
}				t_blob_seg;

typedef struct  __attribute__((aligned(64))) s_blob_hdr // size = 192 // 1 unit on 3 cache line
{
	t_blob_seg	map;
	t_blob_seg	door_rt;
	t_blob_seg	mstr_rt;
	t_blob_seg	wall_def;

	t_blob_seg	air_def;
	t_blob_seg	door_def;
	t_blob_seg	mstr_def;
	t_blob_seg	obj_def;

	t_blob_seg	tex_def;
	t_blob_seg	pixels_data;
	uint32_t	end_offset;
	uint32_t	pad[7];
}				t_blob_hdr;



/*
put flag 	flags |= CELL_HAS_DOOR;
rm flag  	flags &= ~CELL_HAS_DOOR;
test flag	if (flags & CELL_HAS_DOOR)
*/

# define CELL_HAS_WALL			(1u << 0)
# define CELL_HAS_AIR			(1u << 1)
# define CELL_HAS_DOOR			(1u << 2)
# define CELL_HAS_OBJ			(1u << 3)
# define CELL_HAS_MSTR			(1u << 3)
# define MAP_SOA_LAYERS			3

typedef struct	s_map_soa
{
	uint8_t		*flags;
	uint8_t		*block_id; // wall and air
	uint8_t		*occ_id; // door and obj
}				t_map_soa;

# define MONSTER_MOVE			(1u << 0)
# define MONSTER_ATTACK			(1u << 1)
# define MONSTER_DEAD			(1u << 2)
# define MONSTER_HAS_PLAYER_POS	(1u << 3)
# define MONSTER_IS_ACTIVE		(1u << 4)

typedef struct	s_monster_rt
{
	uint8_t		flags;
	uint8_t		def_id;
	uint8_t		current_hp;
	uint8_t		pad1;
	t_xy_double	pos;
	t_xy_double	dir;
	t_xy_double	last_player_pos;
	uint32_t	map_id;
	uint32_t	pad2;
}				t_monster_rt;

# define DOOR_CLOSING			(1u << 0)
# define DOOR_OPENING			(1u << 1)
# define DOOR_IS_OPEN			(1u << 2)

typedef struct	s_door_rt
{
	uint8_t		flags;
	uint8_t		def_id;
	uint8_t		open_ratio_255;
	uint8_t		pad;
	uint32_t	map_id;
}				t_door_rt;

/*DEFS*/

/*if off_px_from_blob == 0 then color hex_code*/
// typedef struct	s_bdef_tex
// {
// 	uint16_t	width;
// 	uint16_t	height;
// 	uint32_t	size;
// 	uint32_t	off_px_from_blob;
// 	uint32_t	color;
// }				t_bdef_tex;

typedef struct	s_bdef_wall
{
	uint8_t tex_north;
	uint8_t tex_south;
	uint8_t tex_west;
	uint8_t tex_east;
}				t_bdef_wall;

typedef struct	s_bdef_air
{
	uint8_t tex_floor;
	uint8_t tex_ceiling;
}				t_bdef_air;

typedef struct	s_bdef_door
{
	uint8_t tex_front;
	uint8_t tex_back;
	uint8_t tex_side;
	uint8_t	padding;
}				t_bdef_door;

typedef struct	s_bdef_monster
{
	uint8_t	tex;
	uint8_t	initial_hp;
	uint8_t size_pc;
	uint8_t	padding;
}				t_bdef_monster;

typedef struct	s_bdef_obj
{
	uint8_t	tex;
	uint8_t size_pc;
}				t_bdef_obj;

// if width == 0 and height == 0 then get color
typedef struct	s_bdef_tex
{
	uint16_t	width;
	uint16_t	height;
	union
	{
		uint32_t	offset;
		uint32_t	color;
	};
}				t_bdef_tex;

/* typedef struct	s_blob
{
	t_blob_hdr	*header;

	uint8_t		wall_count;
	t_bdef_wall	*wall_def;

	uint8_t		air_count;
	t_bdef_air	*air_def;

	uint8_t		door_count;
	t_bdef_air	*air_def;
}				t_blob; */

/*BUILD BLOB*/

typedef struct s_tmp_header
{
	size_t	header_size;
	
	size_t	door_rt_size;
	size_t	monster_rt_size;
	size_t	map_soa_size;

	size_t	wall_size;
	size_t	air_size;
	size_t	door_size;
	size_t	monster_size;
	size_t	obj_size;
	size_t	tex_size;
	size_t	px_size;
}	t_tmp_header;

typedef enum	e_block_type
{
	T_WALL,
	T_AIR,
	T_DOOR,
	T_OBJ,
	T_MSTR,
	T_PLAYER
}				t_block_type;

typedef struct	s_tmp_cell
{
	size_t l;
	size_t c;
	size_t soa_idx;
	size_t mstr_idx;
	size_t door_idx;
	char m;
	char b;
}				t_tmp_cell;

bool get_alloc_size(t_tmp_header *hdr, size_t *out);
bool build_blob(t_data *d, void **blob);

bool fill_tmp_hdr(t_data *d, t_tmp_header *hdr);
bool build_hdr(t_data *d, void *blob, t_tmp_header *tmp);

void build_rt(t_data *d, void *blob);
void build_bdef(t_data *d, void *blob);

void print_blob(void *blob);

// build_helpers
int16_t get_block_id(char sym, t_data *d, t_block_type type);
int16_t get_def_id(char *ids, char sym);


// blob_helpers
t_blob_hdr     *get_blob_hdr(void *blob);

uint16_t        get_map_height(t_blob_hdr *hdr);
uint16_t        get_map_width(t_blob_hdr *hdr);
uint16_t        get_map_size(t_blob_hdr *hdr);

uint8_t        *get_map_flags(void *blob);
uint8_t        *get_map_block_ids(void *blob);
uint8_t        *get_map_bonus_ids(void *blob);

t_map_soa       get_map_soa(void *blob);

t_monster_rt   *get_monster_rt(void *blob);
t_door_rt	   *get_door_rt(void *blob);

t_bdef_wall    *get_wall_bdef(void *blob);
t_bdef_air     *get_air_bdef(void *blob);
t_bdef_door    *get_door_bdef(void *blob);
t_bdef_monster *get_mstr_bdef(void *blob);
t_bdef_obj     *get_obj_bdef(void *blob);
t_bdef_tex		*get_tex_bdef(void *blob);
#endif