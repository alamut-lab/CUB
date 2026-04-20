#include "../../includes/cub.h"

/* typedef enum	e_block_type
{
	T_WALL,
	T_AIR,
	T_DOOR,
	T_OBJ
}				t_block_type;

int16_t get_block_id(char sym, t_data *d, t_block_type type)
{
	int16_t i;
	char	*arr;

	if (type == T_WALL)
		arr = d->wall_ids;
	else if (type == T_AIR)
		arr = d->air_ids;
	else if (type == T_DOOR)
		arr = d->door_ids;
	else if (type == T_OBJ)
		arr = d->obj_ids;
	else
		return (-1);
	i = 0;
	while(arr[i])
	{
		if (arr[i] == sym)
			return(i);
		i++;
	}
	return (-1);
}

int8_t build_block_id(t_data *d, char m_sym, char b_sym, uint8_t *flag)
{
	int16_t res;

	res = get_block_id(m_sym, d, T_WALL);
	if (res >= 0)
	{
		*flag |= CELL_HAS_WALL;
		return ((int8_t)res);
	}
	res = get_block_id(m_sym, d, T_AIR);
	if (res >= 0)
	{
		*flag |= CELL_HAS_AIR;
		return ((int8_t)res);
	}
	if (b_sym)
	{
		res = get_block_id(b_sym, d, T_AIR);
		if (res >= 0)
		{
			*flag |= CELL_HAS_AIR;
			return ((int8_t)res);
		}
	}
	*flag |= CELL_HAS_AIR;
	return (0); // dft
}

int8_t build_bonus_id(t_data *d, char m_sym, uint8_t *flag)
{
	int16_t res;

	res = get_block_id(m_sym, d, T_DOOR);
	if (res >= 0)
	{
		*flag |= CELL_HAS_DOOR;
		return(res);
	}
	res = get_block_id(m_sym, d, T_OBJ);
	if (res >= 0)
	{
		*flag |= CELL_HAS_OBJ;
		return (res);
	}
	return (-1);
}

bool build_cell_soa(t_map_soa *m, size_t l, size_t c, t_data *d)
{
	int16_t block;
	int16_t bonus;

	if (d->have_bonus)
	{
		block = build_block_id(d, d->m_map[l][c], d->b_map[l][c], &m->flags[l * d->m_max_width + c]);
		if (block < 0 && !(m->flags[l * d->m_max_width + c] & CELL_HAS_WALL) && !(m->flags[l * d->m_max_width + c] & CELL_HAS_AIR))
		{
			bonus = build_bonus_id(d, d->m_map[l][c], &m->flags[l * d->m_max_width + c]);
			if (bonus < 0)
				return (false);
			
		}
	}


}

bool build_map_soa(t_data *data, void *blob)
{
	size_t	l;
	size_t	c;
	t_map_soa m;

	m = get_map_soa(blob);
	l = 0;
	while ()

} */

bool build(t_data *data, void *blob, t_tmp_header *tmp_header)
{
	if (!build_hdr(data, blob, tmp_header))
		return (printf("ERR 1\n"), false);
	// build_cells(data, blob);
	// build_walls(data, blob);
	// build_airs(data, blob);
	// build_doors(data, blob);
	// build_tex(data, blob);
	// build_px(data, blob);
	return (true);
}

void print_hdr_seg_map(t_blob_seg *map)
{
	printf("start : %u\n", map->start);
	printf("end   : %u\n", map->end);
	printf("used  : %u\n", map->used);
	printf("width : %u\n", map->map_data.width);
	printf("height: %u\n", map->map_data.height);
}

void print_hdr_seg_normal(t_blob_seg *s)
{
	printf("start : %u\n", s->start);
	printf("end   : %u\n", s->end);
	printf("used  : %u\n", s->used);
	printf("count : %u\n", s->count);
}

void print_hdr(t_blob_hdr *h)
{
	printf("--------------------------\n");
	printf("BLOB HEADER :\n");
	printf("--------------------------\n");
	printf("map:\n");
	print_hdr_seg_map(&h->map);
	printf("--------------------------\n");
	printf("door_rt:\n");
	printf("sizeof struct -> %zd\n", sizeof(t_door_rt));
	print_hdr_seg_normal(&h->door_rt);
	printf("--------------------------\n");
	printf("mstr_rt:\n");
	printf("sizeof struct -> %zd\n", sizeof(t_monster_rt));
	print_hdr_seg_normal(&h->mstr_rt);
	printf("--------------------------\n");
	printf("wall_def:\n");
	printf("sizeof struct -> %zd\n", sizeof(t_bdef_wall));
	print_hdr_seg_normal(&h->wall_def);
	printf("--------------------------\n");
	printf("air_def:\n");
	printf("sizeof struct -> %zd\n", sizeof(t_bdef_air));
	print_hdr_seg_normal(&h->air_def);
	printf("--------------------------\n");
	printf("door_def:\n");
	printf("sizeof struct -> %zd\n", sizeof(t_bdef_door));
	print_hdr_seg_normal(&h->door_def);
	printf("--------------------------\n");
	printf("mstr_def:\n");
	printf("sizeof struct -> %zd\n", sizeof(t_bdef_monster));
	print_hdr_seg_normal(&h->mstr_def);
	printf("--------------------------\n");
	printf("obj_def:\n");
	printf("sizeof struct -> %zd\n", sizeof(t_bdef_obj));
	print_hdr_seg_normal(&h->obj_def);
	printf("--------------------------\n");
	printf("tex_def:\n");
	printf("sizeof struct -> %zd\n", sizeof(t_bdef_tex));
	print_hdr_seg_normal(&h->tex_def);
	printf("--------------------------\n");
	printf("pixels_data:\n");
	print_hdr_seg_normal(&h->pixels_data);
	printf("--------------------------\n");
	printf("end offset = %u\n", h->end_offset);
	printf("--------------------------\n");
}

bool build_blob(t_data *d, void **blob)
{
	size_t	alloc_size;
	t_tmp_header tmp_header;
	if (!fill_tmp_hdr(d, &tmp_header) || !get_alloc_size(&tmp_header, &alloc_size))
		return (false);
	*blob = ft_calloc(1, alloc_size);
	if (!*blob)
		return (false);
	if (!build(d, *blob, &tmp_header))
		return (free(*blob), false);
	print_hdr(*blob);
	return (true);
}