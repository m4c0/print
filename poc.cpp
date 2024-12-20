#pragma leco tool

import hai;
import jute;
import print;

int main() try {
  using namespace jute::literals;

  put("\e[33m");
  put("i'm a view"_s);
  putln("\e[0m");
  putf("i'm a basic %sf", "print");
  putfn("%c", '!');
  putln("value ", 6969, '!', " view"_s, " cstr"_s.cstr());

  try {
    die("a painful death");
  } catch (...) {
    whilst("testing this");
  }
} catch (death) {
}
