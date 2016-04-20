/*----------------------------------------------------------------------------**
**               █      █                                                     **
**               ████████                                                     **
**             ██        ██                                                   **
**            ███  █  █  ███        cowpath.h                                 **
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

#ifndef __libstdcow_include_cowpath_h__
#define __libstdcow_include_cowpath_h__


/*
    From pydoc os.path.isabs:
    Test whether a path is absolute

    cow_path_isabs:
    Return non zero if path is absolute, zero otherwise.
*/
int cow_path_isabs(const char *path);


/*
    From pydoc os.path.isabs:
    Expand ~ and ~user constructions.  If user or $HOME is unknown,
    do nothing.

    cow_path_expanduser:
    Return pointer is ALWAYS allocated with malloc(3), even if path
    is already expanded or cannot be expanded.

    Memory:
    The pointers are allocated with malloc(3) - Callers are responsible to
    free(3) them.
*/
char* cow_path_expanduser(const char *path);

/*
    From pydoc os.path.split:
    Split a pathname.  Returns tuple "(head, tail)" where "tail" is
    everything after the final slash.  Either part may be empty.

    cow_path_split:
    Instead of a tuple, this function will set the pointers
    (head_out and tail_out) - Empty parts will be NULL.

    Memory:
    The pointers are allocated with malloc(3) - Callers are responsible to
    free(3) them.
*/
void cow_path_split(const char *path,
                    char **head_out,
                    char **tail_out);


/*
    From pydoc os.path.splitext:
    Split the extension from a pathname.

    Extension is everything from the last dot to the end, ignoring
    leading dots.  Returns "(root, ext)"; ext may be empty.

    cow_path_splitext:
    Instead of a tuple this function will set the pointers (root_out, ext_out).
    ext_out may be NULL to indicate that it's empty.

    Memory:
    The pointers are allocated with malloc(3) - Callers are responsible to
    free(3) them.
*/
int cow_path_splitext(const char *path,
                      char **root_out,
                      char **ext_out);


#endif /* __libstdcow_include_cowpath_h__ */
