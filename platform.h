#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <stdio.h>
#endif


#endif // PLATFORM_H_INCLUDED
