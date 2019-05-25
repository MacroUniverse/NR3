// discontiguous slice vector class
#pragma once
#include "vector.h"

namespace slisc {
template <class T>
class Dvector
{
public:
	typedef T value_type;
	T *m_p;
	Long m_N;
	Long m_step;
	Dvector();
	Dvector(const T *ptr, Long_I N, Long_I step);

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
	Dvector & operator=(const Dvector &rhs);
	template <class T1>
	Dvector & operator=(const Dvector<T1> &rhs);
	Dvector & operator=(const T &rhs); // for scalar

	// === other member functions ===
	// There is no bound checking, use with care
	void set_size(Long_I N);
	void set_ptr(const T *ptr);
	void set(const T *ptr, Long_I N);
	void next(); // m_ptr += m_N
	void last(); // m_ptr -= m_N
	void shift(Long_I N); // m_ptr += N;
	
	~Dvector();
};

template <class T>
inline Dvector<T>::Dvector() {}

template <class T>
inline Dvector<T>::Dvector(const T *ptr, Long_I N, Long_I step)
	: m_p((T *)ptr), m_N(N), m_step(step) {}

template<class T>
inline T * Dvector<T>::ptr()
{
	return ;
}

template<class T>
inline const T * Dvector<T>::ptr() const
{
	return ;
}

template<class T>
inline Long Dvector<T>::size() const
{
	return m_N;
}

template<class T>
inline T & Dvector<T>::operator[](Long_I i)
{
#ifdef SLS_CHECK_BOUNDS
	if (i < 0 || i >= m_N)
		SLS_ERR("Vbase subscript out of bounds");
#endif
	return m_p[m_step*i];
}

template<class T>
inline const T & Dvector<T>::operator[](Long_I i) const
{
#ifdef SLS_CHECK_BOUNDS
	if (i < 0 || i >= m_N)
		SLS_ERR("Vbase subscript out of bounds");
#endif
	return m_p[m_step*i];
}

template<class T>
inline T & Dvector<T>::operator()(Long_I i)
{ return (*this)[i]; }

template<class T>
inline const T & Dvector<T>::operator()(Long_I i) const
{ return (*this)[i]; }

template<class T>
inline T & Dvector<T>::end()
{
#ifdef SLS_CHECK_BOUNDS
	if (m_N == 0)
		SLS_ERR("tring to use end() on empty vector!");
#endif
	return m_p[m_step*m_N - 1];
}

template<class T>
inline const T & Dvector<T>::end() const
{
#ifdef SLS_CHECK_BOUNDS
	if (m_N == 0)
		SLS_ERR("tring to use end() on empty vector!");
#endif
	return m_p[m_step*m_N - 1];
}

template<class T>
inline T & Dvector<T>::end(Long_I i)
{
}

template<class T>
inline const T & Dvector<T>::end(Long_I i) const
{
}

template <class T>
inline Dvector<T> & Dvector<T>::operator=(const Dvector<T> &rhs)
{
}

template <class T>
inline Dvector<T> & Dvector<T>::operator=(const T &rhs)
{
}

template <class T> template <class T1>
inline Dvector<T> & Dvector<T>::operator=(const Dvector<T1> &rhs)
{
}

template<class T>
inline void Dvector<T>::set_size(Long_I N)
{
#ifdef SLS_CHECK_SHAPE
	if (N <= 0) SLS_ERR("illegal N!");
#endif
	m_N = N;
}

template<class T>
inline void Dvector<T>::set_ptr(const T * ptr)
{
	m_p = (T *)ptr;
}

template<class T>
inline void Dvector<T>::set(const T * ptr, Long_I N)
{
	m_p = (T *)ptr; m_N = N;
}

template<class T>
inline void Dvector<T>::next()
{
	m_p += m_N;
}

template<class T>
inline void Dvector<T>::last()
{
	m_p -= m_N;
}

template<class T>
inline void Dvector<T>::shift(Long_I N)
{
	m_p += N;
}

template<class T>
inline Dvector<T>::~Dvector()
{}
} // namespace slisc
