module;
#include <stdio.h>

module print;
import hai;
import jute;

template<> void put_1(FILE * f, const jute::view & c) { put_1(f, c.begin(), c.size()); }
template<> void put_1(FILE * f, const jute::heap & c) { put_1(f, *c); }
template<> void put_1(FILE * f, const hai::cstr & c) { put_1(f, c.begin()); }

