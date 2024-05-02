#ifndef S21_CAT
#define S21_CAT

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct options {
  bool n;
  bool b;
  bool s;
  bool t;
  bool e;
  bool v;
} flags;

struct char_train {
  int prev;
  int curr;
};

void file_checker(int file_count, char *file_path[], flags *flags_state);
int parse_flags(int argc, char *argv[], flags *flags_state);
void file_processer(flags *flags_state, FILE *file);
void process_flag_b(struct char_train buf, int *line_counter);
void process_flag_s(struct char_train buf, int *gap_counter,
                    bool *print_blocker_s);
void process_flag_n(struct char_train buf, int *line_counter,
                    bool *print_blocker_s);
void process_flag_e(struct char_train buf, bool *print_blocker_s);
void process_flag_t(struct char_train buf, bool *print_blocker_t);
void process_flag_v(struct char_train *buf);
void print_character(struct char_train *buf, bool print_blocker_s,
                     bool print_blocker_t);

#endif  // S21_CAT
