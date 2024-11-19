module;
#include <stdarg.h>
#include <stdio.h>

export module print;
import hai;
import jute;

void put_1(auto);
void put_1(char c) { putc(c, stdout); }
void put_1(int c) { printf("%d", c); }
void put_1(long c) { printf("%ld", c); }
void put_1(unsigned c) { printf("%d", c); }
void put_1(const char * c) { printf("%s", c); }
void put_1(jute::view c) { fwrite(c.begin(), 1, c.size(), stdout); }
void put_1(jute::heap c) { put_1(*c); }
void put_1(const hai::cstr & c) { printf("%s", c.begin()); }

export inline void put(auto &&... args) {
  (put_1(args), ...);
}
export inline void putln(auto &&... args) {
  put(args..., '\n');
}
export __attribute__((format(printf, 1, 2))) void putf(const char * msg, ...) {
  va_list arg;
  va_start(arg, msg);
  vprintf(msg, arg);
  va_end(arg);
}
export __attribute__((format(printf, 1, 2))) void putfn(const char * msg, ...) {
  va_list arg;
  va_start(arg, msg);
  vprintf(msg, arg);
  va_end(arg);
  printf("\n");
}
