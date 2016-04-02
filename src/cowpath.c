/*----------------------------------------------------------------------------**
**               █      █                                                     **
**               ████████                                                     **
**             ██        ██                                                   **
**            ███  █  █  ███        cowpath.c                                 **
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
#include "cowpath.h"
/* stdcow */
#include "cowassert.h"
#include "cowmalloc.h"
/* std */
#include <limits.h>
#include <stdlib.h>
#include <string.h>


/* Heavily inspired on python's os.path.splitext */
/*
   ~/image1.jpg         -> filename_out(image)     - ext_out(jpg)
   ~/image2             -> filename_out(image)     - ext_out(NULL)
   ~/image3.jpg.zip     -> filename_out(image.jpg) - ext_out(.zip)
   ~/(only the dirname) -> filename_out(~/ (same)) - ext_out(NULL)
*/
int cow_splitext(const char *path,
                 char **filename_out,
                 char **ext_out)
{
    COW_ASSERT(path != NULL, "path cannot be NULL");

    /* Reset the output args */
    *filename_out = NULL;
    *ext_out      = NULL;

    char *filename = path;

    /* Check if we have a dot (.) and calculate the string sizes */
    char *dot_ptr   = strrchr(filename, '.');
    int   dot_pos   = (dot_ptr - filename);

    int fout_size = (dot_ptr) ? dot_pos : (strlen(filename));
    int eout_size = (dot_ptr) ? strlen(filename) - dot_pos -1 : 0;

    /* Init the filename_out string */
    *filename_out = COW_MALLOC(sizeof(char) * fout_size + 1);
    memcpy(*filename_out, filename, fout_size);
    (*filename_out)[fout_size] = '\0';


    /* We haven't a dot (.) - We're done here... */
    if(!dot_ptr)
        return -1;

    /* We have a dot (.) */
    /* Init the ext_out string */
    *ext_out = COW_MALLOC(sizeof(char ) * eout_size + 1);
    memcpy(*ext_out, (dot_ptr + 1), eout_size);
    (*ext_out)[eout_size] = '\0';


    return (dot_ptr - filename);
}
