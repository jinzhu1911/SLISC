// copy data from one container to another
// includes container shape checking
// all `container = container` should be implemented using copy
#pragma once

#include "meta.h"
#include "dcmat.h"
#include "jcmat3d.h"

namespace slisc {
//  === pointer interface ===

template<class T, class T1, SLS_IF(is_promo<T, T1>())>
inline void vecset(T *v, const T1 &val, Long_I n)
{
	T val0 = (T)val;
	for (T *p = v; p < v + n; ++p)
		*p = val0;
}

template<class T, class T1, SLS_IF(is_promo<T, T1>())>
inline void vecset(T *v, const T1 &val, Long_I n, Long_I step)
{
	T val0 = (T)val;
	for (T *p = v; p < v + n*step; p += step)
		*p = val0;
}

template<class T>
inline void veccpy(T *v, const T *v1, Long_I n)
{
	memcpy(v, v1, n * sizeof(T));
}

template<class T, class T1, SLS_IF(is_promo<T,T1>())>
inline void veccpy(T *v, const T1 *v1, Long_I n)
{
	for (Long i = 0; i < n; ++i)
		v[i] = v1[i];
}

template<class T, class T1, SLS_IF(is_promo<T, T1>())>
inline void veccpy(T *v, const T1 *v1, Long_I step1, Long_I n)
{
	for (T *p = v; p < v + n; ++p) {
		*p = *v1;
		v1 += step1;
	}
}

template<class T, class T1, SLS_IF(is_promo<T, T1>())>
inline void veccpy(T *v, Long_I step, const T1 *v1, Long_I n)
{
	for (T *p = v; p < v + n*step; p += step) {
		*p = *v1;
		++v1;
	}
}

template<class T, class T1, SLS_IF(is_promo<T, T1>())>
inline void veccpy(T *v, Long_I step, const T1 *v1, Long_I step1, Long_I n)
{
	T *end = v + n * step;
	for (; v < end; v += step) {
		*v = *v1;
		v1 += step1;
	}
}

template<class T, class T1, SLS_IF(is_promo<T, T1>())>
inline void matcpy(T *v, Long_I lda, const T1 *v1, Long_I lda1, Long_I Nr, Long_I Nc)
{
	for (Long j = 0; j < Nr; ++j) {
		veccpy(v, v1, Nc);
		v += lda; v1 += lda1;
	}
}

// copy matrix with different majors
// N1 is the leading dimension of `v`
// leading dimension is equal to the number of elements in major dimension

// equivalent to the following code

//for (j = 0; j < N1; ++j)
//	for (i = 0; i < N2; ++i)
//		v[j + N1 * i] = v1[j * N2 + i];

template<class T, class T1, SLS_IF(is_promo<T, T1>())>
inline void matcpy_2_major(T *a, const T1 *a1, Long_I N1, Long_I N2)
{
	Long k1 = 0;
	for (Long i2 = 0; i2 < N2; ++i2) {
		Long k = i2;
		for (Long i1 = 0; i1 < N1; ++i1) {
			a[k] = a1[k1];
			k += N1; ++k1;
		}
	}
}

// === container interface ===
// must use pointer version

// contiguous copy
template <class T, class T1, SLS_IF(
	is_dense_vec<T>() && is_dense_vec<T1>() ||
	is_dense<T>() && is_dense<T1>() &&
	is_same_major<T, T1>())>
inline void copy(T &v, const T1 &v1)
{
#ifdef SLS_CHECK_SHAPE
	if (!shape_cmp(v, v1))
		SLS_ERR("wrong shape!");
#endif
	veccpy(v.ptr(), v1.ptr(), v.size());
}

// from Dvector<> to Dvector<>
template <class T, class T1, SLS_IF(
	is_Dvector<T>() && is_Dvector<T1>() &&
	is_promo<contain_type<T>, contain_type<T1>>())>
inline void copy(T &v, const T1 &v1)
{
#ifdef SLS_CHECK_SHAPE
	if (!shape_cmp(v, v1))
		SLS_ERR("wrong shape!");
#endif
	veccpy(v.ptr(), v.step(), v1.ptr(), v1.step(), v.size());
}

// from dense vector to Dvector<>
template <class T, class T1, SLS_IF(
	is_dense_vec<T>() && is_Dvector<T1>() &&
	is_promo<contain_type<T>, contain_type<T1>>())>
inline void copy(T &v, const T1 &v1)
{
#ifdef SLS_CHECK_SHAPE
	if (!shape_cmp(v, v1))
		SLS_ERR("wrong shape!");
#endif
	veccpy(v.ptr(), v1.ptr(), v1.step(), v1.size());
}

// from Dvector<> to dense vector
template <class T, class T1, SLS_IF(
	is_Dvector<T>() && is_dense_vec<T1>() &&
	is_promo<contain_type<T>, contain_type<T1>>())>
inline void copy(T &v, const T1 &v1)
{
#ifdef SLS_CHECK_SHAPE
	if (!shape_cmp(v, v1))
		SLS_ERR("wrong shape!");
#endif
	veccpy(v.ptr(), v.step(), v1.ptr(), v1.size());
}

// copy dense matrix with different major
template <class T, class T1, SLS_IF(
	is_dense_mat<T>() && is_dense_mat<T1>() &&
	is_diff_major<T, T1>())>
inline void copy(T &a, const T1 &a1)
{
#ifdef SLS_CHECK_SHAPE
	if (!shape_cmp(a, a1))
		SLS_ERR("wrong shape!");
#endif
	if constexpr (is_cmajor<T>())
		matcpy_2_major(a.ptr(), a1.ptr(), a.n2(), a.n1());
	else
		matcpy_2_major(a.ptr(), a1.ptr(), a.n1(), a.n2());
}

// from Dmat<> to Dmat<>
// from cDmat<> to Dcmat<>
template <class T, class T1, SLS_IF(
	is_Dmat<T>() && is_Dmat<T1>() ||
	is_Dcmat<T>() && is_Dcmat<T1>())>
inline void copy(T &a, const T1 &a1)
{
#ifdef SLS_CHECK_SHAPE
	if (!shape_cmp(a, a1))
		SLS_ERR("wrong shape!");
#endif
	matcpy(a.ptr(), a.lda(), a1.ptr(), a1.lda(), a.n1(), a.n2());
}

// from Jcmat3<> to Jcmat3<>
template <class T, class T1, SLS_IF(
	is_promo<T, T1>())>
inline void copy(Jcmat3d<T> &a, const Jcmat3d<T1> &a1)
{
#ifdef SLS_CHECK_SHAPE
	if (!shape_cmp(a, a1))
		SLS_ERR("wrong shape!");
#endif

	// slow
	for (Long k = 0; k < a.n3(); ++k)
		for (Long j = 0; j < a.n2(); ++j)
			for (Long i = 0; i < a.n1(); ++i)
				a(i, j, k) = a1(i, j, k);
}

// for sparse containers

template <class T, class T1, SLS_IF(is_promo<T,T1>())>
void copy(MatCoo<T> &v, const MatCoo<T1> &v1)
{
#ifdef SLS_CHECK_SHAPE
	if (!shape_cmp(v, v1))
		SLS_ERR("wrong shape!");
	if (v.capacity() < v1.nnz())
		SLS_ERR("not enough capacity!");
#endif
	if constexpr (is_same<T,T1>())
	if (v.ptr() == v1.ptr())
		SLS_ERR("self assignment is forbidden!");
	Long Nnz = v1.nnz();
	v.resize(Nnz);
	veccpy(v.ptr(), v1.ptr(), Nnz);
	veccpy(v.row_ptr(), v1.row_ptr(), Nnz);
	veccpy(v.col_ptr(), v1.col_ptr(), Nnz);
}

template <class T, class T1, SLS_IF(is_promo<T, T1>())>
void copy(MatCoo<T> &v, const CmatObd<T1> &v1)
{
#ifdef SLS_CHECK_SHAPE
	if (!shape_cmp(v, v1))
		SLS_ERR("wrong shape!");
	if (v.capacity() < v1.nnz())
		SLS_ERR("not enough capacity!");
#endif
	Long Nnz = v1.nnz(), N0 = v1.n0(), N1 = N0 - 1;
	Long N = v1.n1();
	Long k = 0;
	for (Long blk = 0; blk < v1.nblk(); ++blk) {
		for (Long j = 0; j < N0; ++j) {
			for (Long i = 0; i < N0; ++i) {
				Long shift = blk * N1 - 1;
				Long ii = shift + i, jj = shift + j;
				if (!(i == N1 && j == N1 || ii < 0 || jj < 0 || ii == N || jj == N))
					v.push(v1(k), ii, jj);
				++k;
			}
		}
	}
}

} // namespace slisc
