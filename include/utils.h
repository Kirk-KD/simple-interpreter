#ifndef UTILS_H
#define UTILS_H

#include <algorithm>

template<class C, typename T>
inline bool contains(C&& c, T e) { return std::find(std::begin(c), std::end(c), e) != end(c); };

#endif