/*----------------------------------------------------------------------------**
**               █      █                                                     **
**               ████████                                                     **
**             ██        ██                                                   **
**            ███  █  █  ███        stdcow.c                                  **
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
#include "stdcow.h"
/* libstdcow */
#include "cowassert.h"
#include "cowmalloc.h"
/* std */
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>


/*******************************************************************************
* ato(X) Functions                                                             *
*******************************************************************************/
int cow_atoi(const char *str)
{
    int  sign  = 1; /* Assume positive */
    int  value = 0;
    char c;

    /* Check if we have an sign char */
    if(*str == '-')
    {
        sign = -1;
        ++str;
    }
    else if(*str == '+')
    {
        /* sign is already positive ignore it */
        ++str;
    }

    /* Test for hexdecimal string first */
    if(*str == '0' && toupper(*(str + 1)) == 'X')
    {
        str += 2;
        c = *str;

        while(c != '\0')
        {
            c = toupper(c);

            COW_ASSERT_ARGS((c >= '0' && c <= '9') ||
                            (c >= 'A' && c <= 'F'),
                            "Invalid character found '%c'", c);

            if(c >= '0' && c <= '9')
                value = (value * 16) + (c - '0');
            else if(c >= 'A' && c <= 'F')
                value = (value * 16) + ((c - 'A') + 10);

            c = *(++str);
        }

        return value * sign;
    }

    /* Test for decimal string */
    c = *str;
    while(c != '\0')
    {
        COW_ASSERT_ARGS((c >= '0' && c <= '9'),
                         "Invalid character found '%c'", c);

        if(c >= '0' && c <= '9')
            value = (value * 10) + (c - '0');

        c = *(++str);
    }

    return value * sign;
}

int cow_atoi_checked(const char *str, int *value_ptr)
{
    COW_ASSERT_ARGS(value_ptr != NULL, "value must be non NULL");

    int  sign  = 1; /* Assume positive */
    int  value = 0;
    char c;

    /* Check if we have an sign char */
    if(*str == '-')
    {
        sign = -1;
        ++str;
    }
    else if(*str == '+')
    {
        /* sign is already positive ignore it */
        ++str;
    }

    /* Test for hexdecimal string first */
    if(*str == '0' && toupper(*(str + 1)) == 'X')
    {
        str += 2;
        c = *str;

        while(c != '\0')
        {
            c = toupper(c);

            if(c >= '0' && c <= '9')
                value = (value * 16) + (c - '0');
            else if(c >= 'A' && c <= 'F')
                value = (value * 16) + ((c - 'A') + 10);
            else
                return 0; /* False */

            c = *(++str);
        }

        *value_ptr = value * sign;
        return 1; /* True */
    }

    /* Test for decimal string */
    c = *str;
    while(c != '\0')
    {
        COW_ASSERT_ARGS((c >= '0' && c <= '9'),
                         "Invalid character found '%c'", c);

        if(c >= '0' && c <= '9')
            value = (value * 10) + (c - '0');
        else
            return 0; /* False */

        c = *(++str);
    }

    *value_ptr = value * sign;
    return 1; /* True */
}



/*******************************************************************************
* (X)toa Functions                                                             *
*******************************************************************************/
const char* cow_itoa(int i)
{
    /* COWTODO: This is a very, very ugly way to
       get how many digits the INT_MAX has, but
       for now it is what we have */
    /* COWHACK: Change to a performatic way */
    static int d = 0;
    static int v = INT_MAX;
    if(d == 0)
        while((v /= 10)) ++d;

    char *str = COW_MALLOC(sizeof(char) * d + 2); /* Sign + NULL char */
    sprintf(str, "%d", i);

    return str;
}

void cow_itoa_out(int i, const char *str_ptr)
{
    /* COWTODO: Should we check if length of str_ptr is enough?? */

    COW_ASSERT(str_ptr != NULL, "str_ptr cannot be null");
    sprintf((char *)str_ptr, "%d", i);
}
