/*----------------------------------------------------------------------------**
**               █      █                                                     **
**               ████████                                                     **
**             ██        ██                                                   **
**            ███  █  █  ███        cowstr.c                                  **
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
#include "cowstr.h"
/* std */
#include <string.h>


/* find */
int cow_str_find(const char *str, char c)
{
    char *p = strchr(str, c);
    return (p) ? (p - str) : -1;
}
int cow_str_find_safe(const char *str, char c)
{
    if(!str) return -1;
    return cow_str_find(str, c);
}

/* rfind */
int cow_str_rfind(const char *str, char c)
{
    char *p = strrchr(str, c);
    return (p) ? (p - str) : -1;
}

int cow_str_rfind_safe(const char *str, char c)
{
    if(!str) return -1;
    return cow_str_find(str, c);
}

/* count */
int cow_str_count(const char *str, char c)
{
    int count = 0;
    for(char *p = (char *)str; *p != '\0'; ++p)
    {
        if(*p == c) ++count;
    }
    return count;
}
int cow_str_count_safe(const char *str, char c)
{
    if(!str) return 0;
    return cow_str_count(str, c);
}
