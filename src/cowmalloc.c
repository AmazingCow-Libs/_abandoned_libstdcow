/* Header */
#include "cowmalloc.h"
/* std */
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
* malloc                                                                       *
*******************************************************************************/
void* _cow_malloc(size_t size)
{
    void *mem = NULL;
    mem = malloc(size);

    COW_ASSERT_ARGS(mem != NULL, "Failed to alloc memory - size(%d)", size);

    memset(mem, 'C', size);

    return mem;
}
