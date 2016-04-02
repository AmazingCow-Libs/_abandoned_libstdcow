/*----------------------------------------------------------------------------**
**               █      █                                                     **
**               ████████                                                     **
**             ██        ██                                                   **
**            ███  █  █  ███        main.c                                    **
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

/*
*  THIS IS SHOW CASE PROGRAM - MOST USERS WILL NOT NEEDED THIS, BUT TO
*  PREVENT THE HASSLE OF DELETE IT WE ADD A (HOPEFULLY) GUARD TO PREVENT
*  ACCIDENTAL USAGE.
*/

#ifdef AMAZINGCOW_LIBSTDCOW_SHOWCASE_TEST_ENABLED

#include "stdcow.h"
#include "cowmalloc.h"
#include "cowlog.h"

#include <stdio.h>
#include <assert.h>
#include <limits.h>

int main(int argc, const char * argv[])
{
    /*
    char *str = "...####Mateus####...";
    char *tstr1 = cow_ltrim(str, '.');
    char *tstr2 = cow_ltrim(str, '#');
    char *tstr3 = cow_ltrim(tstr1, '#');

    COW_LOG("%s", str);
    COW_LOG("%s", tstr1);
    COW_LOG("%s", tstr2);
    COW_LOG("%s", tstr3);

    COW_FREE_NULL(tstr1);
    COW_FREE_NULL(tstr2);
    COW_FREE_NULL(tstr3);
    */

    /*
    char *str = "...####Mateus####...";
    char *tstr1 = COW_MALLOC(sizeof(char) * 20);
    char *tstr2 = COW_MALLOC(sizeof(char) * 20);
    char *tstr3 = COW_MALLOC(sizeof(char) * 20);


    cow_ltrim_out(str,   tstr1, '.');
    cow_ltrim_out(str,   tstr2, '#');
    cow_ltrim_out(tstr1, tstr3, '#');

    COW_LOG("%s", str);
    COW_LOG("%s", tstr1);
    COW_LOG("%s", tstr2);
    COW_LOG("%s", tstr3);

    COW_FREE_NULL(tstr1);
    COW_FREE_NULL(tstr2);
    COW_FREE_NULL(tstr3);
    */

    /*
    char *str = "..##12##..";
    COW_LOG("%s", str);

    char *tstr1 = cow_rtrim(str, '.');
    COW_LOG("%s", tstr1);

    char *tstr2 = cow_rtrim(str, '#');
    COW_LOG("%s", tstr2);

    char *tstr3 = cow_rtrim(tstr1, '#');
    COW_LOG("%s", tstr3);

    COW_FREE_NULL(tstr1);
    COW_FREE_NULL(tstr2);
    COW_FREE_NULL(tstr3);
    */

    /*
    char *str = "...####Mateus####...";
    char *tstr1 = COW_MALLOC(sizeof(char) * 20);
    char *tstr2 = COW_MALLOC(sizeof(char) * 20);
    char *tstr3 = COW_MALLOC(sizeof(char) * 20);


    cow_rtrim_out(str,   tstr1, '.');
    cow_rtrim_out(str,   tstr2, '#');
    cow_rtrim_out(tstr1, tstr3, '#');

    COW_LOG("%s", str);
    COW_LOG("%s", tstr1);
    COW_LOG("%s", tstr2);
    COW_LOG("%s", tstr3);

    COW_FREE_NULL(tstr1);
    COW_FREE_NULL(tstr2);
    COW_FREE_NULL(tstr3);
    */


    char *str = "..##12##..";
    COW_LOG("%s", str);

    char *tstr1 = cow_trim(str, '.');
    COW_LOG("%s", tstr1);

    char *tstr2 = cow_trim(str, '#');
    COW_LOG("%s", tstr2);

    char *tstr3 = cow_trim(tstr1, '#');
    COW_LOG("%s", tstr3);

    COW_FREE_NULL(tstr1);
    COW_FREE_NULL(tstr2);
    COW_FREE_NULL(tstr3);

    /*
    char *str = "...####Mateus####...";
    char *tstr1 = COW_MALLOC(sizeof(char) * 20);
    char *tstr2 = COW_MALLOC(sizeof(char) * 20);
    char *tstr3 = COW_MALLOC(sizeof(char) * 20);


    cow_rtrim_out(str,   tstr1, '.');
    cow_rtrim_out(str,   tstr2, '#');
    cow_rtrim_out(tstr1, tstr3, '#');

    COW_LOG("%s", str);
    COW_LOG("%s", tstr1);
    COW_LOG("%s", tstr2);
    COW_LOG("%s", tstr3);

    COW_FREE_NULL(tstr1);
    COW_FREE_NULL(tstr2);
    COW_FREE_NULL(tstr3);
    */
    return 0;
}

#endif /* AMAZINGCOW_LIBSTDCOW_SHOWCASE_TEST_ENABLED */
