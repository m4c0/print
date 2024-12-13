module;
#include <stdarg.h>
#include <stdio.h>

export module print;
import hai;
import jute;

void put_1(FILE * f, auto);
void put_1(FILE * f, char c) { putc(c, f); }
void put_1(FILE * f, int c) { fprintf(f, "%d", c); }
void put_1(FILE * f, long c) { fprintf(f, "%ld", c); }
void put_1(FILE * f, unsigned c) { fprintf(f, "%d", c); }
void put_1(FILE * f, const char * c) { fprintf(f, "%s", c); }
void put_1(FILE * f, jute::view c) { fwrite(c.begin(), 1, c.size(), f); }
void put_1(FILE * f, jute::heap c) { put_1(f, *c); }
void put_1(FILE * f, const hai::cstr & c) { fprintf(f, "%s", c.begin()); }

export inline void put(auto &&... args) {
  (put_1(stdout, args), ...);
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
