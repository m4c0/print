module;
#pragma leco add_impl "non_literals"
#include <stdarg.h>
#include <stdio.h>

export module print;

void put_1(FILE * f, const auto &);
void put_1(FILE * f, char c) { putc(c, f); }
void put_1(FILE * f, float c) { fprintf(f, "%f", c); }
void put_1(FILE * f, double c) { fprintf(f, "%lf", c); }
void put_1(FILE * f, int c) { fprintf(f, "%d", c); }
void put_1(FILE * f, long c) { fprintf(f, "%ld", c); }
void put_1(FILE * f, unsigned long c) { fprintf(f, "%ld", c); }
void put_1(FILE * f, long long c) { fprintf(f, "%lld", c); }
void put_1(FILE * f, unsigned long long c) { fprintf(f, "%lld", c); }
void put_1(FILE * f, unsigned c) { fprintf(f, "%d", c); }
void put_1(FILE * f, char * c) { fprintf(f, "%s", c); }
void put_1(FILE * f, const char * c) { fprintf(f, "%s", c); }
void put_1(FILE * f, void * c, unsigned len) { fwrite(c, 1, len, f); }
void put_1(FILE * f, const void * c, unsigned len) { fwrite(c, 1, len, f); }

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

export inline void err(auto &&... args) {
  (put_1(stdout, args), ...);
}
export inline void errln(auto &&... args) {
  err(args..., '\n');
}
export __attribute__((format(printf, 1, 2))) void errf(const char * msg, ...) {
  va_list arg;
  va_start(arg, msg);
  fprintf(stderr, "\n");
  va_end(arg);
}
export __attribute__((format(printf, 1, 2))) void errfn(const char * msg, ...) {
  va_list arg;
  va_start(arg, msg);
  vfprintf(stderr, msg, arg);
  va_end(arg);
  fprintf(stderr, "\n");
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
