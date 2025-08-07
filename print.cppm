module;
// Allows usage of attribute((format)) with parameter pack
#pragma clang diagnostic ignored "-Wgcc-compat"
#pragma leco add_impl "non_literals"
#include <stdarg.h>
#include <stdio.h>

export module print;

void put_1(FILE * f, const auto &);
void put_1(FILE * f, bool c) { fprintf(f, c ? "true" : "false"); }
void put_1(FILE * f, char c) { putc(c, f); }
void put_1(FILE * f, float c) { fprintf(f, "%f", c); }
void put_1(FILE * f, double c) { fprintf(f, "%lf", c); }
void put_1(FILE * f, int c) { fprintf(f, "%d", c); }
void put_1(FILE * f, long c) { fprintf(f, "%ld", c); }
void put_1(FILE * f, unsigned long c) { fprintf(f, "%ld", c); }
void put_1(FILE * f, long double c) { fprintf(f, "%Lf", c); }
void put_1(FILE * f, long long c) { fprintf(f, "%lld", c); }
void put_1(FILE * f, unsigned long long c) { fprintf(f, "%lld", c); }
void put_1(FILE * f, unsigned c) { fprintf(f, "%d", c); }
void put_1(FILE * f, char * c) { fprintf(f, "%s", c); }
void put_1(FILE * f, const char * c) { fprintf(f, "%s", c); }
void put_1(FILE * f, void * c, unsigned len) { fwrite(c, 1, len, f); }
void put_1(FILE * f, const void * c, unsigned len) { fwrite(c, 1, len, f); }

export inline void fput(FILE * f, auto &&... args) {
  (put_1(f, args), ...);
}
export inline void fputln(FILE * f, auto &&... args) {
  fput(f, args..., '\n');
}
export __attribute__((format(printf, 2, 3))) void fputf(FILE * f, const char * msg, auto &&... args) {
  fprintf(f, msg, args...);
}
export __attribute__((format(printf, 2, 3))) void fputfn(FILE * f, const char * msg, auto &&... args) {
  fprintf(f, msg, args...);
  fputln(f);
}
export inline void fputa(FILE * f, auto &&... args) {
  ((fput(f, args), fput(f, ' ')), ...);
}

export inline void put(auto &&... args) { fput(stdout, args...); }
export inline void putln(auto &&... args) { fputln(stdout, args...); }
export __attribute__((format(printf, 1, 2))) void putf(const char * msg, auto &&... args) {
  fputf(stdout, msg, args...);
}
export __attribute__((format(printf, 1, 2))) void putfn(const char * msg, auto &&... args) {
  fputfn(stdout, msg, args...);
}
export inline void puta(auto &&... args) {
  ((put(args), put(' ')), ...);
}

export inline void err(auto &&... args) { fput(stderr, args...); }
export inline void errln(auto &&... args) { fputln(stderr, args...); }
export __attribute__((format(printf, 1, 2))) void errf(const char * msg, auto &&... args) {
  fputf(stderr, msg, args...);
}
export __attribute__((format(printf, 1, 2))) void errfn(const char * msg, auto &&... args) {
  fputfn(stderr, msg, args...);
}
export inline void erra(auto &&... args) {
  ((err(args), err(' ')), ...);
}

export struct death {};
export [[noreturn]] inline void die(auto &&... args) {
  errln(args...);
  throw death {};
}
export [[noreturn]] __attribute__((format(printf, 1, 2))) void dief(const char * msg, auto &&... args) {
  errfn(msg, args...);
  throw death {};
}
export [[noreturn]] inline void whilst(auto &&... args) {
  err("while ");
  errln(args...);
  throw;
}
export [[noreturn]] __attribute__((format(printf, 1, 2))) void whilstf(const char * msg, auto &&... args) {
  errfn(msg, args...);
  throw;
}
