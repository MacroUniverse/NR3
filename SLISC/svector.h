#pragma once
#include "vector.h"

namespace slisc {

// contiguous slice vector class
template <class T>
class Svector
{
public:
	typedef T value_type;
	T *m_p;
	Long m_N;
	Svector();
	Svector(Long_I N);
	Svector(const T *ptr, Long_I N);

	// === Vbase<T> functions ===
	T* ptr(); // get pointer
	const T* ptr() const;
	Long size() const;
	// resize() is a bad idea, don't try to create it!
	T & operator[](Long_I i);
	const T & operator[](Long_I i) const;
	T & operator()(Long_I i);
	const T & operator()(Long_I i) const;
	T& end();
	const T& end() const;
	T& end(Long_I i);
	const T& end(Long_I i) const;
	Svector & operator=(const Svector &rhs);
	template <class Tv, SLS_IF(is_dense_vec<Tv>())>
	Svector & operator=(const Tv &rhs);
	Svector & operator=(const T &rhs); // for scalar

	// === other member functions ===
	// There is no bound checking, use with care
	void set_size(Long_I N);
	void set_ptr(const T *ptr);
	void set(const T *ptr, Long_I N);
	void next(); // m_ptr += m_N
	void last(); // m_ptr -= m_N
	void shift(Long_I N); // m_ptr += N;
	
	~Svector();
};

template <class T>
inline Svector<T>::Svector() {}

template <class T>
inline Svector<T>::Svector(Long_I N) : m_N(N) {}

template <class T>
inline Svector<T>::Svector(const T *ptr, Long_I N)
	: m_p((T *)ptr), m_N(N) {}

template<class T>
inline T * Svector<T>::ptr()
{
#ifdef SLS_CHECK_BOUNDS
	if (m_N == 0)
		SLS_ERR("using ptr() for empty container!");
#endif
	return m_p;
}

template<class T>
inline const T * Svector<T>::ptr() const
{
#ifdef SLS_CHECK_BOUNDS
	if (m_N == 0)
		SLS_ERR("using ptr() for empty container!");
#endif
	return m_p;
}

template<class T>
inline Long Svector<T>::size() const
{
	return m_N;
}

template<class T>
inline T & Svector<T>::operator[](Long_I i)
{
#ifdef SLS_CHECK_BOUNDS
	if (i < 0 || i >= m_N)
		SLS_ERR("Vbase subscript out of bounds");
#endif
	return m_p[i];
}

template<class T>
inline const T & Svector<T>::operator[](Long_I i) const
{
#ifdef SLS_CHECK_BOUNDS
	if (i < 0 || i >= m_N)
		SLS_ERR("Vbase subscript out of bounds");
#endif
	return m_p[i];
}

template<class T>
inline T & Svector<T>::operator()(Long_I i)
{
	return (*this)[i];
}

template<class T>
inline const T & Svector<T>::operator()(Long_I i) const
{
	return (*this)[i];
}

template<class T>
inline T & Svector<T>::end()
{
#ifdef SLS_CHECK_BOUNDS
	if (m_N == 0)
		SLS_ERR("tring to use end() on empty vector!");
#endif
	return m_p[m_N - 1];
}

template<class T>
inline const T & Svector<T>::end() const
{
#ifdef SLS_CHECK_BOUNDS
	if (m_N == 0)
		SLS_ERR("tring to use end() on empty vector!");
#endif
	return m_p[m_N - 1];
}

template<class T>
inline T & Svector<T>::end(Long_I i)
{
#ifdef SLS_CHECK_BOUNDS
	if (i <= 0 || i > m_N)
		SLS_ERR("index out of bound");
#endif
	return m_p[m_N - i];
}

template<class T>
inline const T & Svector<T>::end(Long_I i) const
{
#ifdef SLS_CHECK_BOUNDS
	if (i <= 0 || i > m_N)
		SLS_ERR("index out of bound");
#endif
	return m_p[m_N - i];
}

template <class T>
inline Svector<T> & Svector<T>::operator=(const Svector<T> &rhs)
{
	veccpy(m_p, rhs.ptr(), m_N);
	return *this;
}

template <class T> template <class Tv, SLS_IF0(is_dense_vec<Tv>())>
inline Svector<T> & Svector<T>::operator=(const Tv &rhs)
{
	veccpy(m_p, rhs.ptr(), m_N);
	return *this;
}

template <class T>
inline Svector<T> & Svector<T>::operator=(const T &rhs)
{
	vecset(m_p, rhs, m_N);
	return *this;
}

template<class T>
inline void Svector<T>::set_size(Long_I N)
{
#ifdef SLS_CHECK_SHAPE
	if (N <= 0) SLS_ERR("illegal N!");
#endif
	m_N = N;
}

template<class T>
inline void Svector<T>::set_ptr(const T * ptr)
{
	m_p = (T *)ptr;
}

template<class T>
inline void Svector<T>::set(const T * ptr, Long_I N)
{
	m_p = (T *)ptr; m_N = N;
}

template<class T>
inline void Svector<T>::next()
{
	m_p += m_N;
}

template<class T>
inline void Svector<T>::last()
{
	m_p -= m_N;
}

template<class T>
inline void Svector<T>::shift(Long_I N)
{
	m_p += N;
}

template<class T>
inline Svector<T>::~Svector()
{}
} // namespace slisc
