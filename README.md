# libstdcow

**Made with <3 by [Amazing Cow](http://www.amazingcow.com).**


<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Project website:

[opensource.amazingcow.com/libs/libstdcow](http:/opensource.amazingcow/libs/libstdcow)



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Description:

The ```libstdcow``` objective is to create a ease to use C library with 
the common day-to-day programming tasks made easy.

We bring the inspiration from some other languages _standard libraries_, 
primarily python, but some Objective-C (Cocoa|Foundation) and some C# (.NET),
can appears here and there.


### Motivation:

Our main motivation for ```libstdcow``` is to ease some operations from C.   
We love the power, speed and flexibility of C but we think that some stuff
shall be easier to accomplish.   

For example, we **love** the ```os.path``` module from python - It's very easy
to get what you want without much fuzz. We would love have the same kind of 
stuff in C. So we decide to write it.   
Take a look:

In python:
```python
    import os.path;
    
    print os.path.expanduser("~/Desktop"); #Prints /home/you/Desktop
    print os.path.abspath(".");            #Prints /full/path/to/your/cwd
    print os.path.split("/usr/local");     #Prints /usr, local
    print os.path.splitext("Music.ogg");   #Prints Music, ogg
```

In C with ```libstdcow```:
``` c
    #include "cowpath.h";

    char *expanded = cow_path_expanduser("~/Desktop");
    COW_DLOG("%s", expanded); /* COW_DLOG is active only in debug */
    COW_FREE_NULL(expanded); /* cow_path_expanduser will ALWAYS use malloc */

    char *absolute = cow_path_abspath(".");
    COW_DLOG("%s", absolute); /* Think as printf for debug builds */
    COW_FREE_NULL(absolute); /* cow_path_abspath will ALWAYS use malloc */

    char *head, *tail;
    cow_path_split("/usr/local", &head, &tail);
    COW_DLOG("%s - %s", head, tail);
    COW_SAFE_FREE_NULL(head); /* It will free only if the pointer isn't NULL */
    COW_SAFE_FREE_NULL(tail); /* and will set the pointer as NULL too.       */

    char *root, *ext;
    cow_path_splitext("Music.ogg", &root, &ext);
    COW_DLOG("%s - %s", root, ext);
    COW_SAFE_FREE_NULL(root); 
    COW_SAFE_FREE_NULL(ext ); 
```

<br>

As usual, you are **very welcomed** to **share** and **hack** it.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Documentation:

We strive to make our source code fully documented.   
While there are a myriad of comments, one might find useful take a look at:

* [Doxygen Docs](http://opensource.amazingcow.com/libs/libstdcow/doxygen/)
* [Project Website](http://opensource.amazingcow.com/libs/libstdcow/)
* [A list of blog posts about the project](http://opensource.amazingcow.com/libs/libstdcow/posts/)



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Dependencies:

There is no dependency for ```libstdcow```.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## License:

This software is released under GPLv3.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## TODO:

Check the TODO file for general things.

This projects uses the COWTODO tags.   
So install [cowtodo](https://github.com/AmazingCow-Tools/COWTODO/) and run:

``` bash
$ cd path/for/the/project
$ cowtodo 
```

That's gonna give you all things to do :D.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## BUGS:

We strive to make all our code the most bug-free as possible - But we know 
that few of them can pass without we notice ;).

Please if you find any bug report to [bugs_opensource@amazingcow.com]() 
with the name of this project and/or create an issue here in Github.



<!-- ####################################################################### -->
<!-- ####################################################################### -->

## Others:
Check our repos and take a look at our [open source site](http://opensource.amazingcow.com).
