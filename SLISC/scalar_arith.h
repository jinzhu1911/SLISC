// scalar utilities
#pragma once
#include <cmath>
#include <algorithm>
#include "global.h"
#include "complex_arith.h"

namespace slisc {

// these are slightly different from Numerical Recipes
template<class T1, class T2>
constexpr const auto &MIN(const T1 &a, const T2 &b)
{ return a < b ? a : b; }

template<class T1, class T2>
constexpr const auto &MAX(const T1 &a, const T2 &b)
{ return a < b ? b : a; }

template<class T>
constexpr const T SQR(const T &a) { return a * a; }

template<class T, SLS_IF(is_arithmetic<T>::value)>
constexpr const T ABS2(const T &a) { return a * a; }

template<class T>
constexpr const T ABS2(const complex<T> &a) { return SQR(abs(a)); }

constexpr Float SIGN(Float_I s)
{ return s > 0.f ? 1.f : (s < 0.f ? -1.f : 0.f); }

constexpr Doub SIGN(Doub_I s)
{ return s > 0. ? 1. : (s < 0. ? -1. : 0.); }

constexpr Float SIGN(Float_I &a, Float_I &b)
{ return 0.f <= b ? (0.f <= a ? a : -a) : (0.f <= a ? -a : a); }

constexpr Doub SIGN(Doub_I &a, Doub_I &b)
{ return 0. <= b ? (0. <= a ? a : -a) : (0. <= a ? -a : a); }

constexpr Doub SIGN(Doub_I &a, Float_I &b)
{ return 0.f <= b ? (0. <= a ? a : -a) : (0. <= a ? -a : a); }

constexpr Float SIGN(Float_I &a, Doub_I &b)
{ return 0. <= b ? (0.f <= a ? a : -a) : (0.f <= a ? -a : a); }

template<class T>
inline void SWAP(T &a, T &b)
{ error("use std::swap() instead!"); }

// check if two scalars have the same types and values
// const-ness and reference are ignored
template <class T1, class T2>
constexpr Bool is_equiv(const T1 &s1, const T2 &s2)
{
	if constexpr (is_same<T1, T2>()) {
		return s1 == s2;
	}
	return false;
}

// convert bool and character to Int, others unchanged
inline Int to_num(Bool_I x) { return (Int)x; }
inline Int to_num(Char_I x) { return (Int)x; }
inline Int to_num(Uchar_I x) { return (Int)x; }
template <class T>
inline const T &to_num(const T &x) { return x; }

// integer functions
// check if an integer is odd
inline Bool isodd(Int_I n) { return n & 1; }
inline Bool isodd(Long_I n) { return n & 1; }

// return true if n is power of 2 or 0
inline Bool ispow2(Int_I n) { return (n&(n-1)) == 0; }
inline Bool ispow2(Long_I n) { return (n&(n-1)) == 0; }

// return the positive modulus (use "%" when i >= 0)
inline Int mod(Int_I i, Int_I n) { return (i % n + n) % n; }
inline Long mod(Long_I i, Long_I n) { return (i % n + n) % n; }

// matrix double index to single index conversion

inline Long csub2ind(Long_I Nr, Long_I i, Long_I j)
{ return i + Nr*j; } // column major

inline Long rsub2ind(Long_I Nc, Long_I i, Long_I j)
{ return Nc*i + j; } // row major

// floating point functions

using std::swap; using std::abs; using std::real; using std::imag;
using std::sqrt; using std::sin; using std::cos; using std::tan;
using std::exp; using std::log; using std::log10;
using std::expm1; using std::log1p; using std::hypot;
using std::sinh; using std::cosh; using std::tanh;

inline Float cot(Float_I x) { return 1.f / tan(x); }
inline Doub cot(Doub_I x) { return 1. / tan(x); }

inline Float sinc(Float_I x) { return x == 0.f ? 1.f : sin(x) / x; }
inline Doub sinc(Doub_I x) { return x == 0. ? 1. : sin(x) / x; }
}
