#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define S21_NULL ((void *)0)
typedef long unsigned s21_size_t;

// s21_sprint defines BEGIN
#define OUTPUT_BUF_SIZE 1024
#define BUF_FLUSH -1
#define NULL_STRING "(null)"
#define PARAMS_INIT \
  { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#define CONVERT_UNSIGNED 2
#define FTOA_BUFFER_SIZE 32U
#define DEFAULT_FLOAT_PRECISION 6U
// s21_sprint defines END

typedef struct Format {
  int flag_minus;
  int flag_plus;
  int flag_space;
  int flag_sharp;
  int flag_zero;
  int flag_error;
  int width;
  int accuracy;
  char len;
  char spec;
} FORMAT;

#define is_flag(ch) \
  ((ch) == '-' || (ch) == '+' || (ch) == ' ' || (ch) == '#' || (ch) == '0')

#define is_len(ch) ((ch) == 'h' || (ch) == 'l' || (ch) == 'L')

#define is_digit(ch) ((ch) >= '0' && (ch) <= '9')

#define is_octal_digit(ch) ((ch) >= '0' && (ch) <= '7')

#define is_hex_digit(ch)                                                      \
  (((ch) >= '0' && (ch) <= '9') || (ch) == 'a' || (ch) == 'b' ||              \
   (ch) == 'c' || (ch) == 'd' || (ch) == 'e' || (ch) == 'f' || (ch) == 'A' || \
   (ch) == 'B' || (ch) == 'C' || (ch) == 'D' || (ch) == 'E' || (ch) == 'F')

#define is_spec(ch)                                                           \
  ((ch) == 'c' || (ch) == 'd' || (ch) == 'i' || (ch) == 'f' || (ch) == 's' || \
   (ch) == 'u' || (ch) == '%' || (ch) == 'g' || (ch) == 'G' || (ch) == 'e' || \
   (ch) == 'E' || (ch) == 'x' || (ch) == 'X' || (ch) == 'o' || (ch) == 'n' || \
   (ch) == 'p')

#define EPS 1E-6

/*---------------------------------Part 1---------------------------------*/
s21_size_t s21_strspn(const char *str, const char *delim);
s21_size_t s21_strcspn(const char *str, const char *delim);
void *s21_strchr(const char *str, int c);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strtok(char *restrict str, const char *restrict sep);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strcat(char *destination, const char *source);
char *s21_strcpy(char *destination, const char *source);
void *s21_memset(void *ptr, int value, s21_size_t n);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *s1, const void *s2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

char *s21_strerror(int errnum);

int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

/*---------------------------------SPRINTF---------------------------------*/
int s21_sprintf(char *str, const char *format, ...);
void s21_set_flag(FORMAT *FFormat, const char *format);
char *s21_format_param_to_str(char *str, s21_size_t *str_len, FORMAT *FFormat,
                              va_list *argList);
char *s21_str_to_int(const char *format, int *number, va_list *argList);
char *s21_reverse_str(char *str);

char *s21_string_of_perc(char *str, FORMAT *FFormat);
char *s21_string_of_f(char *str, va_list *argList, FORMAT *FFormat);
char *s21_string_of_s(char *str, va_list *argList, FORMAT *FFormat);
char *s21_string_of_c(char *str, va_list *argList, FORMAT *FFormat);
char *s21_string_of_u(char *str, va_list *argList, FORMAT *FFormat);
char *s21_string_of_d(char *str, va_list *argList, FORMAT *FFormat);
char *s21_string_of_o(char *str, va_list *argList, FORMAT *FFormat);
char *s21_string_of_xX(char *str, va_list *argList, FORMAT *FFormat);
char *s21_lf_to_str(char *str, long double number, FORMAT *FFormat);
char *s21_leE_to_str(char *str, long double number, FORMAT *FFormat);

char *wch_to_str(char *str, wchar_t *wstr, s21_size_t len);
char *s21_lf_width_flag(char *str, FORMAT *FFormat);
char *s21_ll_width_flag(char *str, FORMAT *FFormat);
char *s21_sign_flag(char *str, FORMAT *FFormat);
char *s21_ll_accuracy(char *str, FORMAT *FFormat);
char *s21_ll_to_str(char *str, long long number);
char *s21_ul_to_str(char *str, unsigned long long number);
char *s21_ol_to_str(char *str, unsigned long long number, int prefix);
char *s21_hl_to_str(char *str, unsigned long long number, FORMAT *FFormat);
char *s21_ld_to_a(char *str, long double number, FORMAT *FFormat);
char *d_class_to_str(char *str, long double x, int accuracy);
long double s21_round(long double x, int accuracy);
/*---------------------------------Part 5---------------------------------*/
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
char *s21_strdup(const char *s);

#endif  // SRC_S21_STRING_H_
