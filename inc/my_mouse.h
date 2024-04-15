#ifndef __MY_MOUSE_
#define __MY_MOUSE_

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/stat.h>

#define HELP "Usage: ./my_mouse [file]\n"

int my_mouse(const char* file);

#endif