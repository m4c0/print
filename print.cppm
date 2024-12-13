module;
#include <stdarg.h>
#include <stdio.h>

export module print;
import hai;
import jute;

constexpr void put_1(FILE * f, auto); // cexpr fires warnings if undefined
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

export struct death {};
export [[noreturn]] inline void die(auto &&... args) {
  (put_1(stderr, args), ...);
  put_1(stderr, "\n");
  throw death {};
}
export [[noreturn]] __attribute__((format(printf, 1, 2))) void dief(const char * msg, ...) {
  va_list arg;
  va_start(arg, msg);
  vfprintf(stderr, msg, arg);
  va_end(arg);
  throw death {};
}
export [[noreturn]] inline void whilst(auto &&... args) {
  put_1(stderr, "while ");
  (put_1(stderr, args), ...);
  put_1(stderr, "\n");
  throw;
}
export [[noreturn]] __attribute__((format(printf, 1, 2))) void whilstf(const char * msg, ...) {
  va_list arg;
  va_start(arg, msg);
  vfprintf(stderr, msg, arg);
  va_end(arg);
  throw;
}
