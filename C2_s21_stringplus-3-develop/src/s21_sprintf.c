#include "s21_string.h"

void init_format(FORMAT *FFormat) {
  FFormat->width = FFormat->accuracy = -1;
  FFormat->flag_error = FFormat->flag_sharp = FFormat->flag_zero =
      FFormat->flag_minus = FFormat->flag_space = FFormat->flag_plus = 0;
}

void process_format(const char **format, va_list *argList, FORMAT *FFormat) {
  if (is_flag(**format))
    while (is_flag(**format)) s21_set_flag(FFormat, (*format)++);
  if (is_digit(**format) || **format == '*')
    *format = s21_str_to_int(*format, &FFormat->width, argList);
  if (**format == '.')
    *format = s21_str_to_int(++(*format), &FFormat->accuracy, argList);
  if (is_len(**format)) FFormat->len = *((*format)++);
  if (is_spec(**format)) FFormat->spec = *((*format)++);
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list argList;
  va_start(argList, format);
  s21_size_t i = 0, error = 0;
  // char *str_start = str;
  str = s21_strcpy(str, "");
  while (*format && error == 0) {
    FORMAT FFormat = {};
    init_format(&FFormat);
    if (*format == '%') {
      format++;
      process_format(&format, &argList, &FFormat);
      str = s21_format_param_to_str(str, &i, &FFormat, &argList);
      error = FFormat.flag_error;
    } else {
      str[i++] = *format++;
      str[i] = '\0';
    }
  }
  va_end(argList);
  return error == 0 ? (int)s21_strlen(str) : -1;
}

void s21_set_flag(FORMAT *FFormat, const char *format) {
  switch (*format) {
    case '-':
      FFormat->flag_minus = 1;
      break;
    case '+':
      FFormat->flag_plus = 1;
      break;
    case ' ':
      FFormat->flag_space = 1;
      break;
    case '#':
      FFormat->flag_sharp = 1;
      break;
    case '0':
      FFormat->flag_zero = 1;
      break;
  }
}

void handle_specifier(char spec, char *temp_str, va_list *argList,
                      FORMAT *FFormat) {
  switch (spec) {
    case 'd':
    case 'i':
      s21_string_of_d(temp_str, argList, FFormat);
      break;
    case 'o':
      s21_string_of_o(temp_str, argList, FFormat);
      break;
    case 'u':
      s21_string_of_u(temp_str, argList, FFormat);
      break;
    case 'x':
    case 'X':
      s21_string_of_xX(temp_str, argList, FFormat);
      break;
    case 'f':
      s21_string_of_f(temp_str, argList, FFormat);
      break;
    case 'c':
      s21_string_of_c(temp_str, argList, FFormat);
      break;
    case 's':
      s21_string_of_s(temp_str, argList, FFormat);
      break;
  }
}

char *s21_format_param_to_str(char *str, s21_size_t *str_len, FORMAT *FFormat,
                              va_list *argList) {
  char *temp_str = calloc(1000 + FFormat->width + 2, sizeof(char));
  if (temp_str) {
    handle_specifier(FFormat->spec, temp_str, argList, FFormat);
    s21_strcat(str, temp_str);
    free(temp_str);
    *str_len = s21_strlen(str);
  }
  return str;
}

char *s21_string_of_f(char *str, va_list *argList, FORMAT *FFormat) {
  long double ld_number = 0.0;
  double d_number = 0.0;
  double f_number = 0.0;

  switch (FFormat->len) {
    case 'l':
      d_number = (double)va_arg(*argList, double);
      s21_lf_to_str(str, d_number, FFormat);
      break;
    case 'L':
      ld_number = va_arg(*argList, long double);
      s21_lf_to_str(str, ld_number, FFormat);
      break;
    default:
      d_number = va_arg(*argList, double);
      f_number = d_number;
      s21_lf_to_str(str, f_number, FFormat);
  }
  s21_sign_flag(str, FFormat);
  s21_lf_width_flag(str, FFormat);
  return str;
}

char *s21_lf_to_str(char *str, long double number, FORMAT *FFormat) {
  if (FFormat->accuracy < 0) FFormat->accuracy = 6;
  s21_ld_to_a(str, number, FFormat);
  return str;
}

char *s21_string_of_s(char *str, va_list *argList, FORMAT *FFormat) {
  wchar_t *pw = S21_NULL;
  char *p = S21_NULL;

  switch (FFormat->len) {
    case 'l':
      pw = va_arg(*argList, wchar_t *);
      if (!pw) {
        if (FFormat->accuracy < 6)
          s21_strncat(str, "(null)", FFormat->accuracy);
        else
          s21_strcat(str, "(null)");
      } else {
        wch_to_str(str, pw, FFormat->accuracy > -1 ? FFormat->accuracy : 0);
      }
      break;
    default:
      p = va_arg(*argList, char *);
      if (!p) {
        if (FFormat->accuracy < 6)
          s21_strncat(str, "(null)", FFormat->accuracy);
        else
          s21_strcat(str, "(null)");
      } else {
        if (FFormat->accuracy > -1)
          s21_strncat(str, p, FFormat->accuracy);
        else
          s21_strcat(str, p);
      }
  }
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_string_of_c(char *str, va_list *argList, FORMAT *FFormat) {
  wchar_t wchar = 0;
  wchar_t wchar_s[10] = {0};
  switch (FFormat->len) {
    case 'l':
      wchar = va_arg(*argList, wchar_t);
      wchar_s[0] = wchar;
      wch_to_str(str, wchar_s, 0);
      break;
    default:
      str[0] = va_arg(*argList, int);
      str[1] = '\0';
  }
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_string_of_u(char *str, va_list *argList, FORMAT *FFormat) {
  unsigned short us_number;
  unsigned long ul_number;
  unsigned int u_number;

  switch (FFormat->len) {
    case 'h':
      us_number = (unsigned short)va_arg(*argList, unsigned int);
      s21_ll_to_str(str, us_number);
      break;
    case 'l':
      ul_number = (unsigned long)va_arg(*argList, unsigned long);
      s21_ul_to_str(str, ul_number);
      break;
    default:
      u_number = (unsigned int)va_arg(*argList, unsigned int);
      s21_ll_to_str(str, u_number);
  }

  s21_ll_accuracy(str, FFormat);
  s21_sign_flag(str, FFormat);
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_string_of_d(char *str, va_list *argList, FORMAT *FFormat) {
  long int ld_number;
  short int sd_number;
  int number;

  switch (FFormat->len) {
    case 'h':
      sd_number = (short int)va_arg(*argList, int);
      s21_ll_to_str(str, sd_number);
      break;
    case 'l':
      ld_number = (long int)va_arg(*argList, long int);
      s21_ll_to_str(str, ld_number);
      break;
    default:
      number = va_arg(*argList, int);
      s21_ll_to_str(str, number);
  }
  s21_ll_accuracy(str, FFormat);
  s21_sign_flag(str, FFormat);
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_string_of_o(char *str, va_list *argList, FORMAT *FFormat) {
  unsigned long int ld_number;
  unsigned short int sd_number;
  unsigned int number;

  switch (FFormat->len) {
    case 'h':
      sd_number = (unsigned short int)va_arg(*argList, unsigned int);
      s21_ol_to_str(str, sd_number, FFormat->flag_sharp);
      break;
    case 'l':
      ld_number = (unsigned long int)va_arg(*argList, unsigned long int);
      s21_ol_to_str(str, ld_number, FFormat->flag_sharp);
      break;
    default:
      number = va_arg(*argList, unsigned int);
      s21_ol_to_str(str, number, FFormat->flag_sharp);
  }
  s21_ll_accuracy(str, FFormat);
  s21_sign_flag(str, FFormat);
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_string_of_xX(char *str, va_list *argList, FORMAT *FFormat) {
  unsigned long int ld_number;
  unsigned short int sd_number;
  unsigned int number;

  switch (FFormat->len) {
    case 'h':
      sd_number = (short unsigned int)va_arg(*argList, unsigned int);
      s21_hl_to_str(str, sd_number, FFormat);
      break;
    case 'l':
      ld_number = (long unsigned int)va_arg(*argList, unsigned long int);
      s21_hl_to_str(str, ld_number, FFormat);
      break;
    default:
      number = (unsigned int)va_arg(*argList, unsigned int);
      s21_hl_to_str(str, number, FFormat);
  }
  s21_ll_accuracy(str, FFormat);
  s21_sign_flag(str, FFormat);
  s21_ll_width_flag(str, FFormat);

  return str;
}

char *s21_lf_width_flag(char *str, FORMAT *FFormat) {
  int str_len = (int)s21_strlen(str);
  if (FFormat->width > str_len) {
    int padding_size = FFormat->width - str_len;
    char padding_char = FFormat->flag_zero ? '0' : ' ';
    char *new_str = calloc(FFormat->width + 1, sizeof(char));
    if (new_str) {
      if (FFormat->flag_minus) {
        s21_memcpy(new_str, str, str_len);
        s21_memset(new_str + str_len, padding_char, padding_size);
      } else {
        s21_memset(new_str, padding_char, padding_size);
        s21_memcpy(new_str + padding_size, str, str_len);
      }
      new_str[FFormat->width] = '\0';
      s21_strcpy(str, new_str);
      free(new_str);
    }
  }
  return str;
}

char *s21_ll_width_flag(char *str, FORMAT *FFormat) {
  char *ptr;
  ptr = str;
  int str_len = (int)s21_strlen(ptr);
  if (FFormat->width > str_len) {
    int padding_size = FFormat->width - str_len;
    char padding_char = ' ';
    char *new_str = calloc(FFormat->width + 1, sizeof(char));
    if (new_str) {
      if (FFormat->flag_minus) {
        s21_memcpy(new_str, ptr, str_len);
        s21_memset(new_str + str_len, padding_char, padding_size);
      } else {
        s21_memset(new_str, padding_char, padding_size);
        s21_memcpy(new_str + padding_size, ptr, str_len);
      }
      new_str[FFormat->width] = '\0';
      s21_strcpy(ptr, new_str);
      free(new_str);
    }
  }
  return str;
}

char *wch_to_str(char *str, wchar_t *wstr, s21_size_t len) {
  s21_size_t str_len = s21_strlen(str);
  int cnt = len;
  char *p = str + str_len;

  while (*wstr != '\0' && (cnt-- > 0 || len == 0)) {
    *(p++) = (char)*(wstr++);
  }
  *p = '\0';
  return str;
}

char *s21_sign_flag(char *str, FORMAT *FFormat) {
  if (is_digit(*str) || *str == 'i') {
    char num_str[2] = "";
    char *p = S21_NULL;
    p = num_str;
    if (FFormat->flag_plus)
      *(p++) = '+';
    else if (FFormat->flag_space)
      *(p++) = ' ';
    *p = '\0';
    s21_reverse_str(str);
    s21_strcat(str, num_str);
    s21_reverse_str(str);
  }
  return str;
}

char *s21_ll_accuracy(char *str, FORMAT *FFormat) {
  char *num_str = calloc(1000 + FFormat->width + 2, sizeof(char));
  if (num_str) {
    s21_size_t str_len = s21_strlen(str);
    int shift;
    char *p = S21_NULL;
    char *s = S21_NULL;
    p = num_str;
    s = str;

    int sign = *s == '-' ? -1 : 0;
    if (FFormat->flag_zero == 1)
      FFormat->accuracy = (FFormat->accuracy > FFormat->width)
                              ? FFormat->accuracy
                              : FFormat->width;

    FFormat->accuracy = FFormat->accuracy > (int)str_len + sign
                            ? FFormat->accuracy
                            : (int)str_len + sign;
    shift = FFormat->spec == 'x' && FFormat->flag_sharp == 1 ? 32 : 0;

    s21_reverse_str(str);
    for (int i = 0; i < FFormat->accuracy; i++) {
      if (i < (int)str_len + sign)
        *(p++) = *(s++);
      else
        *(p++) = '0';
    }

    if (FFormat->flag_sharp == 1 && FFormat->spec == (char)('X' + shift)) {
      *(p++) = (char)('X' + shift);
      *(p++) = '0';
    }

    if (sign < 0) *(p++) = '-';
    *p = '\0';
    s21_reverse_str(num_str);
    s21_strcpy(str, num_str);
    free(num_str);
  }
  return str;
}

char *s21_ll_to_str(char *str, long long number) {
  char *p = S21_NULL;
  int flag = 1, sign;

  sign = number < 0 ? -1 : 1;
  number *= sign;
  p = str;

  while (flag) {
    int digit;
    if (number >= 10) {
      digit = (int)(number % 10);
      number = (number - digit) / 10;
    } else {
      digit = (int)number;
      flag = 0;
    }
    *(p++) = (char)(digit + '0');
  }

  if (sign < 0) {
    *(p++) = '-';
  }
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

char *s21_ul_to_str(char *str, unsigned long long number) {
  char *p = S21_NULL;
  int flag = 1;

  p = str;

  while (flag) {
    int digit;
    if (number >= 10) {
      digit = (int)(number % 10);
      number = (number - digit) / 10;
    } else {
      digit = (int)number;
      flag = 0;
    }
    *(p++) = (char)(digit + '0');
  }
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

char *s21_ol_to_str(char *str, unsigned long long number, int prefix) {
  char *p = S21_NULL;
  int flag = 1;

  p = str;

  while (flag) {
    unsigned int digit;
    if (number > 7) {
      digit = number % 8;
      number = (number - digit) / 8;
    } else {
      digit = number;
      flag = 0;
    }
    *(p++) = (char)(digit + '0');
  }

  if (prefix == 1) *(p++) = '0';
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

char *s21_hl_to_str(char *str, unsigned long long number, FORMAT *FFormat) {
  char *p = S21_NULL;
  int flag = 1, shift;

  p = str;

  shift = FFormat->spec == 'x' ? 32 : 0;

  while (flag) {
    unsigned int digit;
    if (number > 15) {
      digit = number % 16;
      number = (number - digit) / 16;
    } else {
      digit = number;
      flag = 0;
    }
    if (digit < 10)
      *(p++) = (char)(digit + '0');
    else
      *(p++) = (char)(digit + 'A' + shift - 10);
  }
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

char *s21_str_to_int(const char *format, int *number, va_list *argList) {
  *number = 0;
  while (is_digit(*format)) {
    *number = *format - '0' + *number * 10;
    format++;
  }
  if (*format == '*') {
    *number = va_arg(*argList, int);
    format++;
  }
  return (char *)format;
}

char *s21_reverse_str(char *str) {
  s21_size_t str_len = s21_strlen(str);
  char ch;
  for (s21_size_t i = 0; i < str_len / 2; i++) {
    ch = str[i];
    str[i] = str[str_len - 1 - i];
    str[str_len - 1 - i] = ch;
  }
  return str;
}

long double s21_round(long double x, int accuracy) {
  long double right = 0.0;
  long double x1 = modfl(fabsl(x), &right);
  int mul = 0;
  int sign = signbit(x) == 0 ? 1 : -1;
  for (int i = 0; i < accuracy; i++) mul--;

  if (roundl(x1 / powl(10, mul)) > truncl(x1 / powl(10, mul))) {
    x = x + (5 * powl(10, mul - 1)) * sign;
  }
  if (accuracy <= 6 && x1 > 0) {
    x = x / powl(10, mul);
    x = truncl(x) * powl(10, mul);
  }
  return x;
}

char *s21_ld_to_a(char *str, long double number, FORMAT *FFormat) {
  char num1_str[1000] = "", *p1 = S21_NULL;
  p1 = num1_str;
  char num2_str[1000] = "", *p2 = S21_NULL;
  p2 = num2_str;
  long double mantis, right = 0.0L, pow = 1.0L, pow_t = 1.0L;
  int sign;
  sign = signbit(number) == 0 ? 1 : -1;

  if (fpclassify(number) < 4) {
    d_class_to_str(num1_str, number, FFormat->accuracy);
    if (sign < 0 && fpclassify(number) != 1) s21_strcat(str, "-");
    s21_strcat(str, num1_str);
    FFormat->flag_zero = 0;
  } else {
    number = s21_round(number, FFormat->accuracy);
    mantis = modfl(fabsl(number), &right);

    while (truncl(right / pow) > 0) {
      int digit;
      digit = (int)truncl(fmodl(truncl(right), pow * (long double)10L) / (pow));
      *(p1++) = (char)(digit + '0');
      pow *= 10L;
    }

    if (sign < 0) *(p1++) = '-';
    *p1 = '\0';

    for (int i = 0; i < FFormat->accuracy; i++) pow_t *= 10;

    mantis = roundl(mantis * pow_t);
    pow = 1.0L;
    while (pow < pow_t) {
      int digit;
      digit =
          (int)truncl(fmodl(truncl(mantis), pow * (long double)10L) / (pow));
      *(p2++) = (char)(digit + '0');
      pow *= 10L;
    }
    *p2 = '\0';
    s21_reverse_str(num1_str);
    if (s21_strlen(num1_str) == 0) s21_strcat(str, "0");
    s21_strcat(str, num1_str);
    if (FFormat->accuracy > 0 || FFormat->flag_sharp == 1) s21_strcat(str, ".");
    if (FFormat->accuracy > 0) {
      s21_reverse_str(num2_str);
      s21_strcat(str, num2_str);
    }
  }
  return str;
}

char *d_class_to_str(char *str, long double x, int accuracy) {
  switch (fpclassify(x)) {
    case FP_INFINITE:
      s21_strcat(str, "inf");
      break;
    case FP_ZERO:
      s21_strcat(str, "0");
      if (accuracy > 0) {
        s21_strcat(str, ".");
        while (accuracy--) s21_strcat(str, "0");
      }
      break;
  }
  return str;
}
