/*----------------------------------------------------------------------------**
**               █      █                                                     **
**               ████████                                                     **
**             ██        ██                                                   **
**            ███  █  █  ███        cowassert.c                               **
**            █ █        █ █        libstdcow                                 **
**             ████████████                                                   **
**           █              █       Copyright (c) 2016                        **
**          █     █    █     █      AmazingCow - www.AmazingCow.com           **
**          █     █    █     █                                                **
**           █              █       N2OMatt - n2omatt@amazingcow.com          **
**             ████████████         www.amazingcow.com/n2omatt                **
**                                                                            **
**                  This software is licensed as GPLv3                        **
**                 CHECK THE COPYING FILE TO MORE DETAILS                     **
**                                                                            **
**    Permission is granted to anyone to use this software for any purpose,   **
**   including commercial applications, and to alter it and redistribute it   **
**               freely, subject to the following restrictions:               **
**                                                                            **
**     0. You **CANNOT** change the type of the license.                      **
**     1. The origin of this software must not be misrepresented;             **
**        you must not claim that you wrote the original software.            **
**     2. If you use this software in a product, an acknowledgment in the     **
**        product IS HIGHLY APPRECIATED, both in source and binary forms.     **
**        (See opensource.AmazingCow.com/acknowledgment.html for details).    **
**        If you will not acknowledge, just send us a email. We'll be         **
**        *VERY* happy to see our work being used by other people. :)         **
**        The email is: acknowledgment_opensource@AmazingCow.com              **
**     3. Altered source versions must be plainly marked as such,             **
**        and must not be misrepresented as being the original software.      **
**     4. This notice may not be removed or altered from any source           **
**        distribution.                                                       **
**     5. Most important, you must have fun. ;)                               **
**                                                                            **
**      Visit opensource.amazingcow.com for more open-source projects.        **
**                                                                            **
**                                  Enjoy :)                                  **
**----------------------------------------------------------------------------*/

/* Header */
#include "cowassert.h"
/* std */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* Function Definitions */
_cow_assert_print(const char  *expr,
                  const char  *file,
                  unsigned int line,
                  const char  *func,
                  const char  *msg)
{
    _cow_assert_print_args(expr, file, line, func, msg);
}

_cow_assert_print_args(const char  *expr,
                       const char  *file,
                       unsigned int line,
                       const char  *func,
                       const char   *msg,
                       ...)
{
    const int k_buffer_size = 1024;
    char buffer[k_buffer_size];

    /* Reset the buffer */
    memset(buffer, 0, k_buffer_size);

    /* Build the buffer with the variadic args list */
    va_list ap;
    va_start(ap, msg);
    vsnprintf(buffer, k_buffer_size, msg, ap);
    va_end(ap);

    /* Print the message and abort */
    fprintf(stderr,
"cowassert: assertion failed on: \n \
  file       : %s \n \
  line       : %d \n \
  function   : %s \n \
  expression : %s \n \
  message    : %s \n",
        file, line, func, expr, buffer);

    abort();
}

