#include "../../includes/cub.h"

void safe_free(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}