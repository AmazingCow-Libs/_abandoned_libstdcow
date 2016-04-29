/*----------------------------------------------------------------------------**
**               █      █                                                     **
**               ████████                                                     **
**             ██        ██                                                   **
**            ███  █  █  ███        cowassert.h                               **
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

#ifndef __libstdcow_include_cowassert_h__
#define __libstdcow_include_cowassert_h__


/*******************************************************************************
* Notes                                                                        *
*******************************************************************************/
/*
    COW_VERIFY macro was heavily insipred on the amazing course by
    Kenny Kerr - @kennykerr - PluralSight Modern C++ Libraries.
*/

/*******************************************************************************
* Macros                                                                       *
*******************************************************************************/
/* NDEBUG is defined - We're on RELEASE mode. */
#ifdef NDEBUG
    #define COW_ASSERT(_cond_, _msg_) do {} while(0)
    #define COW_ASSERT_ARGS(_cond_, _msg_, ...) do {} while(0)

    #define COW_VERIFY(_expr_) ((_expr_))


/* NDEBUG is not defined - We're on DEBUG mode. */
#else
    /* Functions prototypes */
    /** @brief This function is only declared for !NDEBUG, this is what
        COW_ASSERT will call.
        @warning DO NOT CALL IT DIRECTLY.
        @see COW_ASSERT
    */
    void _cow_assert_print(const char   *expr,
                           const char   *file,
                           unsigned int line,
                           const char   *func,
                           const char   *msg);

    /** @brief This function is only declared for !NDEBUG, this is what
        COW_ASSERT_ARGS will call.
        @warning DO NOT CALL IT DIRECTLY.
        @see COW_ASSERT_ARGS
    */
    void _cow_assert_print_args(const char   *expr,
                                const char   *file,
                                unsigned int line,
                                const char   *func,
                                const char   *msg,
                                ...);

    /* Macro definition */
    /**
        @brief
            A more informative assert than the standard assert.
        @param
            cond - The condition that will be asserted.
        @param
            msg - The message the will be printed along the other info.
        @see
            COW_ASSERT_ARGS, COW_VERIFY
    */
    #define COW_ASSERT(_cond_, _msg_) \
        ((_cond_))                    \
        ? (void) 0                    \
        : _cow_assert_print(#_cond_,  \
                            __FILE__, \
                            __LINE__, \
                            __func__, \
                            (_msg_));

    /**
        @brief
            A more informative assert than the standard assert.
        @param
            cond - The condition that will be asserted.
        @param
            msg - The message the will be printed along the other info. \n
                  This can be used like a printf(3) format string.
        @param
            ... - variadic arguments list that will be used to build the final
                  message. \n
                  This is used like the printf(3) var args list.
        @see
            COW_ASSERT, COW_VERIFY
    */
    #define COW_ASSERT_ARGS(_cond_, _msg_, ...) \
        ((_cond_))                              \
        ? (void) 0                              \
        : _cow_assert_print_args(#_cond_,       \
                                 __FILE__,      \
                                 __LINE__,      \
                                 __func__,      \
                                 (_msg_),       \
                                 ##__VA_ARGS__)

    /**
        @brief
            Assert like macro that will behave like the assert in
            non NDEBUG builds, but unlike the assert it WILL continue
            doing the check in NDEBUG builds. \n
            This is util in cases that we want an assert in debug, but
            want that the expression being kept in the release builds.
        @param
            expr - The expression that will evaluated and will trigger the
                   assert if false in debug build. \n
                   Notice that it will be kept regardless if the build mode,
                   but will only trigger the assert in non NDEBUG builds.
        @see
            COW_ASSERT, COW_ASSERT_ARGS
    */
    #define COW_VERIFY(_expr_)                                \
        COW_ASSERT_ARGS((_expr_),                             \
                        "COW_VERIFY Failed - expression(%s)", \
                        #_expr_)

#endif /* NDEBUG */


#endif /* defined(__libstdcow_include_cowassert_h__) */
