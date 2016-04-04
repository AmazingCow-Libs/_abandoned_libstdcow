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
#include "cowlog.h"
#include "cowmalloc.h"
/* std */
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

/*******************************************************************************
* NOTES                                                                        *
********************************************************************************
* dirname(3) | basename (3)
*    These  functions  may  return  pointers  to statically
*    allocated memory which may be overwritten by subsequent calls.
*    Alternatively, they  may return  a  pointer to some part of path,
*    so that the string referred to by path should not be modified or
*    freed until the pointer  returned  by the function is no
*    longer required.
*
*
********************************************************************************
*******************************************************************************/


void cow_path_split(const char *path,
                    char **head_out,
                    char **tail_out)
{
    COW_ASSERT(path != NULL, "path cannot be NULL");

    /* Reset the pointers */
    *head_out = NULL;
    *tail_out = NULL;

    int path_str_size = strlen(path);

    /* Empty path - NULL components */
    if(path_str_size == 0)
        return;

    /* If the path ends in a slash (/) the tail is empty
       and head is the path itself */
    if(path[path_str_size -1] == '/')
    {
        int offset = (path_str_size == 1) ? 0 : 1;

        *head_out = COW_MALLOC(sizeof(char) * path_str_size + 1);
        memcpy(*head_out, path, path_str_size);
        (*head_out)[path_str_size - offset] = '\0';

        return;
    }


    /* Create a local copy of strings */
    /* Checkout the notes about dirname(3) and basename(3) */
    char dirname_local_copy [PATH_MAX];
    char basename_local_copy[PATH_MAX];

    strcpy(dirname_local_copy,  path);
    strcpy(basename_local_copy, path);

    /* */
    char *dirname_str  = dirname (dirname_local_copy);
    char *basename_str = basename(basename_local_copy);

    /* Init the head */
    /* Special case for when the there is no slashes */
    if(strcmp(dirname_str, ".") != 0 || strcmp(basename_str, path) != 0)
    {
        *head_out = COW_MALLOC(sizeof(char) * strlen(dirname_str)  + 1);
        strcpy(*head_out, dirname_str);
    }


    /* Init the tail */
    *tail_out = COW_MALLOC(sizeof(char) * strlen(basename_str) + 1);
    strcpy(*tail_out, basename_str);
}

int find_safe(const char *str, char c)
{
    if(!str)
        return -1;

    char *p = strchr(str, c);
    return (p) ? (p - str) : -1;
}

int rfind_safe(const char *str, char c)
{
    if(!str)
        return -1;

    char *p = strrchr(str, c);
    return (p) ? (p - str) : -1;
}

int cow_path_splitext(const char *path,
                      char **root_out,
                      char **ext_out)
{
    COW_ASSERT(path != NULL, "path cannot be NULL");

    char *head_dummy;
    char *tail;

    cow_path_split(path, &head_dummy, &tail);
    COW_SAFE_FREE_NULL(head_dummy); /* We never need head */

    /* Reset the output args */
    *root_out = NULL;
    *ext_out  = NULL;

    int first_dot_pos =  find_safe(tail, '.');
    int last_dot_pos  = rfind_safe(tail, '.');

    /* The path is only a directory part
       or the path doesn't  contains a dot (.)  */
    if(!tail
       || (first_dot_pos == 0 && first_dot_pos == last_dot_pos)
       || (last_dot_pos == -1))
    {
        COW_SAFE_FREE_NULL(tail);

        *root_out = COW_MALLOC(sizeof(char) * strlen(path) + 1);
        strcpy(*root_out, path);

        return -1;
    }
    COW_SAFE_FREE_NULL(tail) /* We don't need tail anymore */


    /* The path contains a filename with a dot
       let's find it on path */
    int dot_pos = rfind_safe(path, '.');

    /* Init the root_out */
    *root_out = COW_MALLOC(sizeof(char) * dot_pos + 1);
    memcpy(*root_out, path, dot_pos);
    (*root_out)[dot_pos] = '\0';

    /* Init the ext_out */
    *ext_out = COW_MALLOC(sizeof(char) * (strlen(path) - dot_pos) + 1);
    memcpy(*ext_out,
            path + dot_pos,         /* Offset the path to dot */
            strlen(path) - dot_pos);

    (*ext_out)[strlen(path) - dot_pos] = '\0';

    return dot_pos;
}
