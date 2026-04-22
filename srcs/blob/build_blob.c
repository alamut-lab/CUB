#include "../../includes/cub.h"

bool build(t_data *data, void *blob, t_tmp_header *tmp_header)
{
	if (!build_hdr(data, blob, tmp_header))
		return (printf("ERR 1\n"), false);
	build_rt(data, blob);
	build_bdef(data, blob);
	// build_walls(data, blob);
	// build_airs(data, blob);
	// build_doors(data, blob);

	// build_tex(data, blob);
	// build_px(data, blob);
	return (true);
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
	return (true);
}