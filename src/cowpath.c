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
#include "cowlog.h"
/* std */
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

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

    /*
     Create a local copy of dir and filename strings
     because the man of: dirname(3) and basename(3) says..

     These  functions  may  return  pointers  to statically
     allocated memory which may be overwritten by subsequent calls.
     Alternatively, they  may return  a  pointer to some part of path,
     so that the string referred to by path should not be modified or
     freed until the pointer  returned  by the function is no
     longer required.
    */
    char dirname_cpy [PATH_MAX];
    char basename_cpy[PATH_MAX];

    strcpy(dirname_cpy, path);
    strcpy(basename_cpy, path);

    char *dirname_str  = dirname (dirname_cpy);  /* Get the dir  component */
    char *basename_str = basename(basename_cpy); /* Get the file component */


    /* Check if we have a dot (.) */
    char *dot_ptr = strrchr(basename_str, '.');
    int   dot_pos = (dot_ptr - basename_str);


    /* Calculate the string sizes */
    int dirname_size  = -1;
    int basename_size = -1;
    int ext_size      = -1;

    /* COWTODO: COMMENT */
    dirname_size = (strcmp(dirname_str, ".") == 0) ? 0 : strlen(dirname_str);

    if(dot_ptr) /* We HAVE a dot (.) */
    {
        basename_size = dot_pos;                           /* Up to the dot */
        ext_size      = strlen(basename_str) - dot_pos -1; /* Do not include the dot */
    }
    else  /* We HAVE NOT a dot (.) */
    {
        basename_size = strlen(basename_str); /* The whole basename */
        ext_size      = -1;                   /* Dummy value */
    }


    /* Calculate the size of filename_out string
       It must take in account the size of dirname, because we must
       return the complete path excluding only the extension */
    int filename_out_size = (dirname_size)
                             ? dirname_size + basename_size + 1 /* The slash char */
                             : basename_size;

    int copy_offset = 0;

    /* Init the filename_out string
       1 - Copy the dirname.
       2 -
       3 - Copy the "real" filename.
       4 - Add a null char. */
    *filename_out = COW_MALLOC(sizeof(char) * filename_out_size + 1);
    if(dirname_size != 0)
    {
        /* 1 */
        memcpy(*filename_out, dirname_str, dirname_size);
        /* 2 */
        memcpy(*filename_out + dirname_size, "/", 1);

        copy_offset = dirname_size + 1;
    }

    /* 3 */
    memcpy(*filename_out + copy_offset, /* Offset the dirname */
            basename_str,
            basename_size);
    /* 3 */
    (*filename_out)[filename_out_size] = '\0';


    /* We haven't a dot (.) - We're done here... */
    if(!dot_ptr)
        return -1;

    /* We have a dot (.) */
    /* Init the ext_out string */
    *ext_out = COW_MALLOC(sizeof(char ) * ext_size + 1);
    memcpy(*ext_out, (dot_ptr + 1), ext_size);
    (*ext_out)[ext_size] = '\0';


    return strrchr(path, '.') - path;
}
