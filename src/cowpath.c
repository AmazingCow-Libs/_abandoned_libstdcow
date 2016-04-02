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
