Documentation of changes made to original library in order to make it integrate into inviwo

Shared library fixes for unix. Necessary when compiling with -fvisibility=hidden (i.e. not exposing classes and functions by default).
Added __attribute__ ((visibility ("default"))) to export functions when building shared libraries on UNIX.



