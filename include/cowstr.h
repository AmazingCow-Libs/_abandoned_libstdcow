/*----------------------------------------------------------------------------**
**               █      █                                                     **
**               ████████                                                     **
**             ██        ██                                                   **
**            ███  █  █  ███        cowstr.h                                  **
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

#ifndef __libstdcow_include_cowstr_h__
#define __libstdcow_include_cowstr_h__

/*******************************************************************************
* find                                                                         *
*******************************************************************************/
/**
@brief
    Finds the target char c in the string - From left to right.
@param
    str - A non NULL pointer to string.
@param
    c - A char that will be searched in the string.
@returns
    The index of char in the string or -1 if it was not found.
@warning
    This function will not check the validity of str pointer. \n
    If the pointer could be NULL is better use the cow_str_find_safe.
@see
    cow_str_find_safe, cow_str_rfind, cow_str_rfind_safe
*/
int cow_str_find(const char *str, char c);

/**
@brief
    Finds the target char c in the string - From left to right. \n
    This function will handle the NULL str pointer, so is safe pass
    pointer that could be NULL to it.
@param
    str - A pointer to string.
@param
    c - A char that will be searched in the string.
@returns
    The index of char in the string or -1 if it was not found. \n
    If the str pointer is NULL it will return -1.
@see
    cow_str_find, cow_str_rfind, cow_str_rfind_safe
*/
int cow_str_find_safe(const char *str, char c);


/*******************************************************************************
* rfind                                                                        *
*******************************************************************************/
/**
@brief
    Finds the target char c in the string - From right to left.
@param
    str - A non NULL pointer to string.
@param
    c - A char that will be searched in the string.
@returns
    The index of char in the string or -1 if it was not found.
@warning
    This function will not check the validity of str pointer. \n
    If the pointer could be NULL is better use the cow_str_rfind_safe.
@see
    cow_str_find, cow_str_find_safe, cow_str_rfind_safe
*/
int cow_str_rfind(const char *str, char c);

/**
@brief
    Finds the target char c in the string - From right to left. \n
    This function will handle the NULL str pointer, so is safe pass
    pointer that could be NULL to it.
@param
    str - A pointer to string.
@param
    c - A char that will be searched in the string.
@returns
    The index of char in the string or -1 if it was not found. \n
    If the str pointer is NULL it will return -1.
@see
    cow_str_find, cow_str_find_safe, cow_str_rfind
*/
int cow_str_rfind_safe(const char *str, char c);


/*******************************************************************************
* count                                                                        *
*******************************************************************************/
/**
@brief
    Counts how many times the target char c is in the string \n
@param
    str - A pointer to string.
@param
    c - A char that will be searched in the string.
@returns
    How many times c was found in str. \n
@warning
    This function will not check the validity of str pointer. \n
    If the pointer could be NULL is better use the cow_str_count_safe.
@see
    cow_str_count_safe.
*/
int cow_str_count(const char *str, char c);

/**
@brief
    Counts how many times the target char c is in the string \n
    This function will handle the NULL str pointer, so is safe pass
    pointer that could be NULL to it.
@param
    str - A pointer to string.
@param
    c - A char that will be searched in the string.
@returns
    How many times c was found in str. \n
    If the str pointer is NULL it will return 0.
@see
    cow_str_count.
*/
int cow_str_count_safe(const char *str, char c);


#endif /* __libstdcow_include_cowstr_h__ */
