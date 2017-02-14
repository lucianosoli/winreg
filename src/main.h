#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#endif

#include "registry.h"

void read_file(FILE *fd, char *tmp, int n, long offset);
void print_hex(char *s, int count);
void print_display_strings(char *s, int count);
void print_hex_car(char c);
