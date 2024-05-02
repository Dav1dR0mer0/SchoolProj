
#include "cat.h"

int main(int argc, char* argv[]) {
  flags flags_state = {0};
  parse_flags(argc, argv, &flags_state);
  file_checker(argc - optind, argv + optind, &flags_state);

  return 0;
}
