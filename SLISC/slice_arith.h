// slicing arithmetics
#pragma once
#include "svector.h"
#include "dvector.h"
#include "scmat.h"
#include "Dcmat.h"

namespace slisc {

// slice a row from a row-major matrix
template <class Tmat, class T = contain_type<Tmat>,
	SLS_IF(is_dense_mat<Tmat>() && is_rmajor<Tmat>())>
void slice_row(Svector<T> &slice, const Tmat &a, Long_I row)
{
#ifdef SLS_CHECK_BOUNDS
	if (row < 0 || row >= a.nrows())
		SLS_ERR("out of bound!");
#endif
	Long Nc = a.ncols();
	slice.set(a.ptr() + row * Nc, Nc);
}

// note that `slice1 = slice2` will copy data instead of copying slice object
template <class Tmat, class T = contain_type<Tmat>,
	SLS_IF(is_dense_mat<Tmat>() && is_rmajor<Tmat>())>
Svector<T> slice_row(const Tmat &a, Long_I row)
{
	Svector<T> slice;
	slice_row(slice, a, row);
	return slice;
}

// slice a row from a col-major matrix
template <class Tmat, class T = contain_type<Tmat>,
	SLS_IF(is_dense_mat<Tmat>() && is_cmajor<Tmat>())>
void slice_row(Dvector<T> &slice, const Tmat &a, Long_I row)
{
	Long Nr = a.nrows(), Nc = a.ncols();
#ifdef SLS_CHECK_BOUNDS
	if (row < 0 || row >= Nr)
		SLS_ERR("out of bound!");
#endif
	
	slice.set(a.ptr() + row, Nc, Nr);
}

template <class Tmat, class T = contain_type<Tmat>,
	SLS_IF(is_dense_mat<Tmat>() && is_cmajor<Tmat>())>
Dvector<T> slice_row(const Tmat &a, Long_I row)
{
	Dvector<T> slice;
	slice_row(slice, a, row);
	return slice;
}

// slice a row from a col-major 3d array
template <class Tmat, class T = contain_type<Tmat>,
	SLS_IF(is_dense_mat3<Tmat>() && is_cmajor<Tmat>())>
void slice_row(Dvector<T> &slice, const Tmat &a, Long_I row, Long_I k = 0)
{
	Long Nr = a.dim1(), Nc = a.dim2();
#ifdef SLS_CHECK_BOUNDS
	if (row < 0 || row >= Nr)
		SLS_ERR("out of bound!");
#endif
	
	slice.set(a.ptr() + Nr*Nc*k + row, Nc, Nr);
}

template <class Tmat, class T = contain_type<Tmat>,
	SLS_IF(is_dense_mat3<Tmat>() && is_cmajor<Tmat>())>
Dvector<T> slice_row(const Tmat &a, Long_I row, Long_I k = 0)
{
	Dvector<T> slice;
	slice_row(slice, a, row, k);
	return slice;
}

// slice a col from a col-major matrix
template <class Tmat, class T = contain_type<Tmat>, SLS_IF(
	is_dense_mat<Tmat>() && is_cmajor<Tmat>())>
void slice_col(Svector<T> &slice, const Tmat &a, Long_I col)
{
#ifdef SLS_CHECK_BOUNDS
	if (col < 0 || col >= a.ncols())
		SLS_ERR("out of bound!");
#endif
	Long Nr = a.nrows();
	slice.set(a.ptr() + col * Nr, Nr);
}

// note that `slice1 = slice2` will copy data instead of copying slice object
template <class Tmat, class T = contain_type<Tmat>,
	SLS_IF(is_dense_mat<Tmat>() && is_cmajor<Tmat>())>
Svector<T> slice_col(const Tmat &a, Long_I col)
{
	Svector<T> slice;
	slice_col(slice, a, col);
	return slice;
}

// slice a col from a row-major matrix
template <class Tmat, class T = contain_type<Tmat>, SLS_IF(
	is_dense_mat<Tmat>() && is_rmajor<Tmat>())>
void slice_col(Dvector<T> &slice, const Tmat &a, Long_I col)
{
	Long Nr = a.nrows(), Nc = a.ncols();
#ifdef SLS_CHECK_BOUNDS
	if (col < 0 || col >= Nc)
		SLS_ERR("out of bound!");
#endif
	slice.set(a.ptr() + col, Nc, Nr);
}

// note that `slice1 = slice2` will copy data instead of copying slice object
template <class Tmat, class T = contain_type<Tmat>,
	SLS_IF(is_dense_mat<Tmat>() && is_rmajor<Tmat>())>
Dvector<T> slice_col(const Tmat &a, Long_I col)
{
	Dvector<T> slice;
	slice_col(slice, a, col);
	return slice;
}

// slice a col from a col-major 3d array
template <class Tmat, class T = contain_type<Tmat>, SLS_IF(
	is_dense_mat3<Tmat>() && is_cmajor<Tmat>())>
void slice_col(Svector<T> &slice, const Tmat &a, Long_I col, Long_I k = 0)
{
	Long Nr = a.dim1(), Nc = a.dim2();
#ifdef SLS_CHECK_BOUNDS
	if (col < 0 || col >= Nc)
		SLS_ERR("out of bound!");
#endif
	slice.set(a.ptr() + Nr*Nc*k + Nr*col, Nc);
}

template <class Tmat, class T = contain_type<Tmat>, SLS_IF(
	is_dense_mat3<Tmat>() && is_cmajor<Tmat>())>
Svector<T> slice_col(const Tmat &a, Long_I col, Long_I k = 0)
{
	Svector<T> slice;
	slice_col(slice, a, col, k);
	return slice;
}

// slice a Dmat from a mat
// only works for column major for now
template <class Tsmat, class Tmat, SLS_IF(
	is_slice_mat<Tsmat>() && is_cmajor<Tsmat>() &&
	is_dense_mat<Tmat>() && is_cmajor<Tmat>() &&
	is_same_contain_type<Tsmat, Tmat>())>
void slice_mat(Tsmat &slice, const Tmat &a,
	Long_I i, Long_I Nr, Long_I j, Long_I Nc)
{
	Tsmat slice_mat(&a(i, j), Nr, Nc, a.nrows());
}

// slice a3(i,j,:)
template <class Tmat3, class T = contain_type<Tmat3>,
	SLS_IF(is_Cmat3d<Tmat3>())>
void slice_dim3(Dvector<T> &slice, const Tmat3 &a,
	Long_I i, Long_I j)
{
	Long N1N2 = a.dim1()*a.dim2();
	slice.set(a.ptr() + i + a.dim1()*j, a.dim3(), a.dim1()*a.dim2());
}

template <class Tmat3, class T = contain_type<Tmat3>,
	SLS_IF(is_Cmat3d<Tmat3>())>
Dvector<T> slice_dim3(const Tmat3 &a,
		Long_I i, Long_I j)
{
	Dvector<T> slice;
	slice_dim3(slice, a, i, j);
	return slice;
}

// slice a3(:,:,k)
// only supports Cmat<> and Cmat3<> for now
template <class T, SLS_IF(is_scalar<T>())>
void slice_mat12(Scmat<T> &a, const Cmat3d<T> &a3, Long_I k)
{
#ifdef SLS_CHECK_BOUNDS
	if (k < 0 || k >= a3.dim3())
		SLS_ERR("out of bound!");
#endif
	a.set_size(a3.dim1(), a3.dim2());
	a.set_ptr(a3.ptr() + a.size() * k);
}

template <class T, SLS_IF(is_scalar<T>())>
Scmat<T> slice_mat12(const Cmat3d<T> &a3, Long_I k)
{
	Scmat<T> slice;
	slice_mat12(slice, a3, k);
	return slice;
}

// slice a4(:,:,k,i4)
// only supports Cmat<> and Cmat3<> for now
template <class T, SLS_IF(is_scalar<T>())>
void slice_mat12(Scmat<T> &a, const Cmat4d<T> &a4, Long_I k, Long_I l)
{
#ifdef SLS_CHECK_BOUNDS
	if (k < 0 || k >= a4.dim3())
		SLS_ERR("out of bound!");
#endif
	a.set_size(a4.dim1(), a4.dim2());
	a.set_ptr(a4.ptr() + a.size() * (a4.dim3()*l  + k));
}

template <class T, SLS_IF(is_scalar<T>())>
Scmat<T> slice_mat12(const Cmat4d<T> &a4, Long_I k, Long_I l)
{
	Scmat<T> slice;
	slice_mat12(slice, a4, k, l);
	return slice;
}

} // namespace slisc