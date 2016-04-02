#ifndef COWLOG_H_INCLUDED
#define COWLOG_H_INCLUDED

/* std */
#include <stdio.h>


/* Function Prototypes */
_cow_log(FILE *f, int flush,
         const char *prefix, const char *fmt, ...);


/* Macro Definitions */
#define COW_LOG(_fmt_, ...)                  \
    _cow_log(stdout, 1,                      \
             "cowlog", _fmt_, ##__VA_ARGS__);



#ifdef _NDEBUG
    #define COW_DLOG (void)0

#else
    /* Macro Definitions */
    #define COW_DLOG(_fmt_, ...)                  \
        _cow_log(stdout, 1,                       \
                 "cowdebuglog", _fmt_, ##__VA_ARGS__);

#endif /* _NDEBUG */

#endif /* COWLOG_H_INCLUDED */
