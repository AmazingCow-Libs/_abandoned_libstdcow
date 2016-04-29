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


/**
@brief
    From pydoc os.path.isabs: \n
    Test whether a path is absolute
@param
    path - Non NULL pointer to a string.
@returns
    Non zero value if path is absolute, zero value otherwise.
*/
int cow_path_isabs(const char *path);


/**
@brief
    From pydoc os.path.expanduser: \n
    Expand ~ and ~user constructions. If user or $HOME is unknown,
    do nothing.
@param
    path - Non NULL pointer to a string.
@returns
    A pointer to string allocated with malloc(3). \n
    If path could be expanded the return pointer will contains the expanded
    path, otherwise it will contains the original path given as argument.
@warning
    The return pointer is ALWAYS allocated with malloc(3), even if path
    is already expanded or cannot be expanded. \n
    Users are responsible to free(3) it.
*/
char* cow_path_expanduser(const char *path);


/**
@brief
    From pydoc os.path.abspath: \n
    Return an absolute path.
@param
    path - Non NULL pointer to a string.
@returns
    A pointer to string allocated with malloc(3). \n
    The absolute path.
@warning
    The return pointer is ALWAYS allocated with malloc(3), even if path
    is already absolute. \n
    Users are responsible to free(3) it.
*/
char* cow_path_abspath(const char *path);


/**
@brief
    Canonize the path, i.e. expanduser + abspath + normpath in
    one call.
@param
    path - Non NULL pointer to a string.
@returns
    A pointer to string allocated with malloc(3). \n
    The canonized path.
@warning
    The return pointer is ALWAYS allocated with malloc(3), even if path
    is already canonized. \n
    Users are responsible to free(3) it.
*/
char* cow_path_canonizepath(const char *path);


/**
@brief
    From pydoc os.path.normpath: \n
    Normalize path, eliminating double slashes, etc.
@param
    path - Non NULL pointer to a string.
@returns
    A pointer to string allocated with malloc(3). \n
    The normalized path.
@warning
    The return pointer is ALWAYS allocated with malloc(3), even if path
    is already normalized. \n
    Users are responsible to free(3) it.
@bug
    This function DOES NOT behave like python's one. \n
    It isn't aware of leading double or triple slashes.
*/
char* cow_path_normpath(const char *path);


/**
@brief
    From pydoc os.path.split: \n
    Split a pathname. Returns tuple "(head, tail)" where "tail" is
    everything after the final slash. Either part may be empty. \n
    \n
    cow_path_split: \n
    Instead of a tuple, this function will set the pointers
    (head_out and tail_out) - Empty parts will be NULL.
@param
    path     - Non NULL pointer to a string.
@param
    head_out - A pointer to a pointer to string - It will may be set
               if path has a head component. \n
               If set it will be allocated with malloc(3), otherwise will be NULL.
@param
    tail_out - A pointer to a pointer to string - It will may be set
               if path has a tail component. \n
               If set it will be allocated with malloc(3), otherwise will be NULL.
@warning
    The head_out and tail_out if exists, are allocated with malloc(3), users
    are responsible to free(3) them.
@see
    COW_SAFE_FREE_NULL
*/
void cow_path_split(const char *path,
                    char **head_out,
                    char **tail_out);


/**
@brief
    From pydoc os.path.splitext: \n
    Split the extension from a pathname. \n
    \n
    Extension is everything from the last dot to the end, ignoring
    leading dots. Returns "(root, ext)"; ext may be empty.
    \n
    cow_path_splitext:
    Instead of a tuple this function will set the pointers (root_out, ext_out).
    ext_out may be NULL to indicate that it's empty.
@param
    path     - Non NULL pointer to a string.
@param
    root_out - A pointer to a pointer to string - It will may be set
               if path has a root component. \n
               It will be allocated with malloc(3).
@param
    ext_out - A pointer to a pointer to string - It will may be set
              if path has a ext component. \n
              If set it will be allocated with malloc(3), otherwise will be NULL.
@warning
    The ext_out if exists, is allocated with malloc(3), users
    are responsible to free(3) them.
@see
    COW_SAFE_FREE_NULL
*/
int cow_path_splitext(const char *path,
                      char **root_out,
                      char **ext_out);


#endif /* __libstdcow_include_cowpath_h__ */
