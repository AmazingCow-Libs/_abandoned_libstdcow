#ifndef COWPATH_H_INCLUDED
#define COWPATH_H_INCLUDED

/*
    From pydoc os.path.splitext
    Split the extension from a pathname.

    Extension is everything from the last dot to the end, ignoring
    leading dots.  Returns "(root, ext)"; ext may be empty.
*/
int cow_splitext(const char *path,
                 char **filename_out,
                 char **ext_out);


#endif // COWPATH_H_INCLUDED
