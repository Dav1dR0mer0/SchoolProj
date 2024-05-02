#include "cat.h"

void file_checker(int file_count, char *file_path[], flags *flags_state) {
  FILE *current_file = NULL;
  if (file_count != 0) {
    while (file_count > 0) {
      current_file = fopen(*file_path, "r");
      if (current_file == NULL) {
        fprintf(stderr, "No such file or directory\n");
      } else {
        file_processer(flags_state, current_file);
      }
      ++file_path;
      --file_count;
    }
    fclose(current_file);
  } else {
    fprintf(stderr, "cat: no such file or directory\n");
  }
}

int parse_flags(int argc, char *argv[], flags *flags_state) {
  int opt = 0;
  int option_index = 0;
  struct option long_options[] = {{"number", no_argument, 0, 'n'},
                                  {"number-nonblank", no_argument, 0, 'b'},
                                  {"squeeze-blank", no_argument, 0, 's'},
                                  {0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, "beEnstTv", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'E':
        flags_state->e = true;
        flags_state->v = false;
        break;
      case 'T':
        flags_state->t = true;
        flags_state->v = false;
        break;
      case 'n':
        flags_state->n = true;
        if (flags_state->b) flags_state->n = false;
        break;
      case 'b':
        flags_state->b = true;
        flags_state->n = false;
        break;
      case 's':
        flags_state->s = true;
        break;
      case 't':
        flags_state->t = true;
        flags_state->v = true;
        break;
      case 'e':
        flags_state->e = true;
        flags_state->v = true;
        break;
      case 'v':
        flags_state->v = true;
        break;
      case '?':
      default:
        fprintf(
            stderr,
            "cat: illegal option -- p\n usage: cat [-belnstuv] [file ...]\n");
        break;
    }
  }
  return optind;
}

void file_processer(flags *flags_state, FILE *file) {
  struct char_train buf = {10, 0};
  int ch;
  bool print_blocker_s = false;
  bool print_blocker_t = false;
  int line_counter = 1;
  int gap_counter = 0;

  while ((ch = fgetc(file)) != EOF) {
    buf.curr = ch;
    if (flags_state->b == true) {
      process_flag_b(buf, &line_counter);
    }
    if (flags_state->s == true) {
      process_flag_s(buf, &gap_counter, &print_blocker_s);
    }
    if (flags_state->n == true) {
      process_flag_n(buf, &line_counter, &print_blocker_s);
    }
    if (flags_state->e == true) {
      process_flag_e(buf, &print_blocker_s);
    }
    if (flags_state->t == true) {
      process_flag_t(buf, &print_blocker_t);
    }
    if (flags_state->v == true) {
      process_flag_v(&buf);
    }
    buf.prev = ch;
    print_character(&buf, print_blocker_s, print_blocker_t);
  }
}

void process_flag_b(struct char_train buf, int *line_counter) {
  if ((buf.prev == '\n') && (buf.curr != '\n')) {
    printf("%6d\t", (*line_counter)++);
  }
}

void process_flag_s(struct char_train buf, int *gap_counter,
                    bool *print_blocker_s) {
  if ((buf.prev == 10) && (buf.curr == 10)) {
    (*gap_counter)++;
  } else {
    *gap_counter = 0;
  }
  *print_blocker_s = (*gap_counter >= 2);
}

void process_flag_n(struct char_train buf, int *line_counter,
                    bool *print_blocker_s) {
  if (buf.prev == 10 && (*print_blocker_s == false)) {
    printf("%6d\t", (*line_counter)++);
  }
}

void process_flag_e(struct char_train buf, bool *print_blocker_s) {
  if ((buf.curr == 10) && (*print_blocker_s == false)) {
    printf("$");
  }
}

void process_flag_t(struct char_train buf, bool *print_blocker_t) {
  if (buf.curr == '\t') {
    printf("^I");
    *print_blocker_t = true;
  } else {
    *print_blocker_t = false;
  }
}

void process_flag_v(struct char_train *buf) {
  if ((buf->curr >= 0 && buf->curr <= 32) &&
      (buf->curr != ' ' && buf->curr != '\n' && buf->curr != '\r' &&
       buf->curr != '\t')) {
    buf->curr += 64;
    printf("^");
  }
  if (buf->curr == 127) {
    buf->curr -= 64;
    printf("^");
  }
}

void print_character(struct char_train *buf, bool print_blocker_s,
                     bool print_blocker_t) {
  if ((print_blocker_s == false) && (print_blocker_t == false)) {
    printf("%c", buf->curr);
  }
}