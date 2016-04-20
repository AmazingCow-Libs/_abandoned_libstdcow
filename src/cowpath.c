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
/* std */
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <pwd.h>
/* stdcow */
#include "cowassert.h"
#include "cowlog.h"
#include "cowmalloc.h"
#include "cowstr.h"

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



/*******************************************************************************
* Function implementations                                                     *
*******************************************************************************/
int cow_path_isabs(const char *path)
{
    COW_ASSERT(path != NULL, "path cannot be NULL");
    return path[0] == '/';
}


char* cow_path_expanduser(const char *path)
{
    COW_ASSERT(path != NULL, "path cannot be NULL");

    char *expanded_path = NULL;

    /* Not start with tilde so do not expand it. */
    if(path[0] != '~')
    {
        expanded_path = COW_MALLOC(sizeof(char) * strlen(path) + 1);
        strcpy(expanded_path, path);

        return expanded_path;
    }

    /*
        Basically we have two options here for path:
            #1 - Start with [tilde] and may have tralling components.
            #2 - Start with [tilde][user] and may have tralling components.

        We must note that the #1 is the same of #2 with the [user] implied
        for the current proccess.

        For example:
            #1 - ~/Desktop
          ` #2 - ~n2omatt/Desktop
        Is the same for this function if the current user is n2omatt.

        So we have all these possibilities:
            [1] ~
            [2] ~/
            [3] ~/path
            [4] ~/path/
            [5] ~user
            [6] ~user/
            [7] ~user/path
            [8] ~user/path/
    */

    int slash_index = cow_str_find_safe(path, '/');
    if(slash_index == -1)
        slash_index = strlen(path);

    char *user_home = NULL;

    /* Check if fall in the [1-4] of above category */
    if(slash_index == 0 || slash_index == 1)
    {
        user_home = getenv("HOME");
    }

    /* We are at category [5-8] - Get the user from given path */
    if(!user_home)
    {
        /* We don't +1 in malloc because we're skipping the first char */
        char *user_name = COW_MALLOC(sizeof(char) * slash_index);
        memcpy(user_name, path+1, slash_index -1);
        user_name[slash_index -1] = '\0';

        struct passwd *pwd = getpwnam(user_name);
        if(pwd) /* User exists */
            user_home = pwd->pw_dir;

        COW_SAFE_FREE_NULL(user_name);
    }

    /* Here if user_home is NULL means that the HOME is not set
       or desired user doesn't exists - Return the same value from path. */
    if(!user_home)
    {
        expanded_path = COW_MALLOC(sizeof(char) * strlen(path) + 1);
        strcpy(expanded_path, path);

        return expanded_path;
    }

    /* Easy the typing */
    int user_home_len      = strlen(user_home);
    int path_wo_user_start = slash_index;
    int path_wo_user_len   = strlen(path) - path_wo_user_start;
    int expanded_path_len  = user_home_len + path_wo_user_len + 1;

    /* Buffer long enough to /home/user/ + /whatever/comes/afer/ */
    expanded_path = COW_MALLOC(sizeof(char) * expanded_path_len);

    /* Copy the user home */
    memcpy(expanded_path,
           user_home,
           user_home_len);
    /* Copy the rest of path - It will come with the leading slash */
    memcpy(expanded_path + user_home_len,
           path + path_wo_user_start,
           path_wo_user_len);
    /* Null char */
    expanded_path[expanded_path_len -1] = '\0';


    return expanded_path;
}


char* cow_path_abspath(const char *path)
{
    COW_ASSERT(path != NULL, "path cannot be NULL");

    /* Already is absolute */
    if(cow_path_isabs(path))
    {
        char *fullpath = cow_path_normpath(path);
        return fullpath;
    }

    /* Let the getcwd allocate the memory */
    char *cwd = getcwd(NULL, 0);

    int start_offset = (path[0] == '/') ? 1 : 0;
    int end_offset   = (path[strlen(path) -1] == '/') ? 1 : 0;

    /* Easy typing... */
    int cwd_len      = strlen(cwd);
    int path_len     = strlen(path);
    int fullpath_len = cwd_len + path_len + 1; /* 1 for the slash */
    /* Size without the slashes in path */
    fullpath_len -= (start_offset + end_offset);

    char *fullpath = COW_MALLOC(sizeof(char) * fullpath_len + 1);

    /* head of path */
    memcpy(fullpath, cwd, cwd_len);
    /* slash */
    memcpy(fullpath + cwd_len, "/", 1);
    /* tail of path */
    memcpy(fullpath + cwd_len + 1, /* Skip the slash added above      */
           path + start_offset,    /* Skip the leading slash in path  */
           path_len - end_offset); /* Skip the trailing slash in path */

    fullpath[fullpath_len] = '\0';

    COW_FREE_NULL(cwd);

    /* Normalize the path */
    char *normalized_fullpath = cow_path_normpath(fullpath);
    COW_FREE_NULL(fullpath);

    return normalized_fullpath;
}


char* cow_path_normpath(const char *path)
{
    COW_ASSERT(path != NULL, "path cannot be NULL");

    /* Empty string - Dot path */
    if(strlen(path) == 0)
        return strdup(".");

    int slash_count = cow_str_count(path, '/');
    int path_started_with_slash = (path[0] == '/');

    /* There is no slashes - Return the path itself */
    if(slash_count == 0)
        return strdup(path);

    char comps_arr[slash_count][PATH_MAX / slash_count];
    int  comp_index = 0;

    /* Reset all the compoments - Prevent junk on them */
    for(int i = 0; i < slash_count; ++i)
        memset(comps_arr[i], 0, PATH_MAX / slash_count);


    char *search_path = strdup(path);
    char *strtok_str  = search_path; /* Used only to ease the while loop */
    char *token       = NULL;        /* The path piece */

    while((token = strtok(strtok_str, "/")))
    {
        strtok_str = NULL;
        if(strcmp(token, ".") == 0)
        {
            /* Do nothing */
        }
        else if(strcmp(token, "..") == 0)
        {
            /* Go back in the comps_arr */
            --comp_index;
            if(comp_index < 0) /* Make it remain on bounds */
                comp_index = 0;

            /* But if we already on top we must let the .. */
            if(comp_index == 0)
                strcpy(comps_arr[comp_index++], token);
            /* Reset the value so strcat can operate correctly */
            else
                comps_arr[comp_index][0] = '\0';
        }
        else
        {
            strcpy(comps_arr[comp_index++], token);
        }
    }
    COW_FREE_NULL(search_path);


    /* The comp_index didn't increase, it means that all components
       were "gobacked" by the "../" or the path has only "./" or
       there is no compoment at all (only a slash)
    */
    if(comp_index == 0 && !path_started_with_slash)
        return strdup(".");
    else if(comp_index == 0 && path_started_with_slash)
        return strdup("/");


    /* The comp_index is the count relevant path pieces. i.e. the path
       pieces that aren't "gobacked" by the "../" or is the "./"
       Now we need join them up into one string
    */
    int normalized_path_len = (path_started_with_slash) ? 1 : 0;

    /* Find the length of all path pieces together */
    for(int i = 0; i < comp_index; ++i)
        normalized_path_len  += strlen(comps_arr[i]) + 1; /* +1 for the slashes */

    /* Join them */
    char *normalized_path = COW_MALLOC(sizeof(char) * normalized_path_len + 1);
    memset(normalized_path, 0, normalized_path_len); /* Prevent junk */

    if(path_started_with_slash)
        strcat(normalized_path, "/");

    for(int i = 0; i < comp_index; ++i)
    {
        strcat(normalized_path , comps_arr[i]);
        if(i != comp_index -1) /* As in python, don't put trailling slash */
            strcat(normalized_path , "/");
    }

    return normalized_path;
}


char* cow_path_canonizepath(const char *path)
{
    char *expanded = cow_path_expanduser(path);
    char *abs      = cow_path_abspath(expanded);

    COW_FREE_NULL(expanded);
    return abs;
}


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

    int first_dot_pos = cow_str_find_safe (tail, '.');
    int last_dot_pos  = cow_str_rfind_safe(tail, '.');

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
    COW_SAFE_FREE_NULL(tail); /* We don't need tail anymore */


    /* The path contains a filename with a dot
       let's find it on path */
    int dot_pos = cow_str_rfind_safe(path, '.');

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
