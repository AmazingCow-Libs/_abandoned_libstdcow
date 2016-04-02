
/* Header */
#include "cowlog.h"
/* std */
#include <stdlib.h>
#include <stdarg.h>

/* Function Prototypes */
_cow_log(FILE *f, int flush,
         const char *prefix, const char *fmt, ...)
{
    const int k_buffer_size = 1024;
    char buffer[k_buffer_size];

    /* Reset the buffer */
    memset(buffer, 0, k_buffer_size);

    /* Build the buffer with the variadic args list */
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buffer, k_buffer_size, fmt, ap);
    va_end(ap);

    fprintf(f, "[%s]: %s\n", prefix, buffer);
    if(flush)
        fflush(f);
}
