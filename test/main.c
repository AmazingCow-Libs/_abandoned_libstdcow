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
#include <stdio.h>
#include <assert.h>
#include <limits.h>

int main(int argc, const char * argv[])
{
//    int value  = cow_atoi("-0xFF");
//    int value2 = cow_atoi("400");
//    int value3;
//    cow_atoi_checked("0xaAa", &value3);
//
//    printf("value : %d\n", value);
//    printf("value2: %d\n", value2);
//    printf("value3: %d\n", value3);


    const char str1[2];
    cow_itoa_out(-245, str1);

    const char *str2 = cow_itoa(234);

    printf("str1 %s", str1);
    printf("str2 %s", str2);

    COW_FREE_NULL(str2);

    return 0;
}

#endif /* AMAZINGCOW_LIBSTDCOW_SHOWCASE_TEST_ENABLED */
