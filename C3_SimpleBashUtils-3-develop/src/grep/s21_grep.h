#ifndef S21_GREP
#define S21_GREP

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 10000

typedef struct {
  int e;  //+
  int c;  //+
  int i;  //+
  int v;  //+
  int l;  //+
  int n;  //+
  int h;  //+
  int s;  //+
  int o;  //+
  char comp_string[BUFFER];
  char line_from_file[BUFFER];
  char filename[BUFFER];
} Flags;

void parser(int argc, char **argv, Flags *flag);
void output(char **argv, Flags *flag, int *flag_printable_name);
void print_match_only(Flags *flag, regmatch_t *start, regex_t *reg);
void f_flag(Flags *flag);

#endif
