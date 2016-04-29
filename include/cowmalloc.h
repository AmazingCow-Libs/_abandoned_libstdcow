/*----------------------------------------------------------------------------**
**               █      █                                                     **
**               ████████                                                     **
**             ██        ██                                                   **
**            ███  █  █  ███        cowmalloc.h                               **
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

#ifndef __libstdcow_include_cowmalloc_h__
#define __libstdcow_include_cowmalloc_h__

/* std */
#include  <stdlib.h>
/* stdcow */
#include "cowassert.h"


/*******************************************************************************
* malloc                                                                       *
*******************************************************************************/
#ifdef NDEBUG
    #define COW_MALLOC(_size_) malloc((_size_))

#else
    /* Function Prototypes */
    /** @brief DO NOT CALL IT DIRECTLY
        @warning DO NOT CALL IT DIRECTLY
        @see COW_MALLOC
    */
    void* _cow_malloc(size_t size);

    /* Macros Definitions */
    /**
    @brief
        "Safe" version of malloc(3). \n
        In non NDEBUG builds it will check the allocated memory and
        initialize it wil the 'C' char. \n
        In NDEBUG builds it's a placeholder for malloc(3).
    @param
        size - The size of memory to allocate.
    @return
        A chunk of memory like malloc(3).
    */
    #define COW_MALLOC(_size_) \
        _cow_malloc((_size_))

#endif /* NDEBUG */


/*******************************************************************************
* free                                                                         *
*******************************************************************************/
/**
@brief Safe version of free(3). \n
       It will free(3) the pointer and after will set it as NULL. \n
       In non NDEBUG builds it will check if the pointer is not already NULL.
@param
    ptr - The pointer the will be freed.
@see
    COW_SAFE_FREE_NULL
*/
#define COW_FREE_NULL(_ptr_)                                \
    do {                                                    \
        COW_ASSERT_ARGS((_ptr_) != NULL,                      \
                        "Trying to free a null ptr (0x%x)", \
                        &(_ptr_));                            \
        free((_ptr_));                                        \
        (_ptr_) = NULL;                                       \
    } while(0)


/**
@brief Safer version of free(3). \n
       It will free(3) the pointer and after will set it as NULL. \n
       COW_SAFE_FREE_NULL, will check if the pointer isn't already NULL,
       before trying to free it.
@param
    ptr - The pointer the will be freed.
@see
    COW_FREE_NULL
*/
#define COW_SAFE_FREE_NULL(_ptr_) \
    do {                          \
        if((_ptr_))                 \
        {                         \
            free((_ptr_));          \
            (_ptr_) = NULL;         \
        }                         \
    } while(0)


#endif /* __libstdcow_include_cowmalloc_h__ */
