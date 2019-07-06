#pragma once

#include <cmath>
#include <climits>	// for CHAR_BIT
#include <cassert>

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	T	Integer type used for storing the value. The type must have at least N bits.
//! @param	N	Number of bits to the right of the binary point
//! @param	T2	Integer type used during operations to avoid overflow. The size of this type must be
//!				at least the size of T. Ideally, it is twice as large as T.

template< typename T, int N, typename T2 = T >
class FixedPoint
{
public:

	typedef T	ValueType;										//!< The type used to store the value

	static int const	PRECISION	= N;						//!< Number of bits to the right of the binary point
	static int const	SIZE		= sizeof( T ) * CHAR_BIT;	//!< Size in bits of the type used to store the value
	static int const	SIZE_2		= sizeof( T2 ) * CHAR_BIT;	//!< Size in bits of the extended type

	//! @brief	Constructs a fixed point number from an integer value.
	//!
	//! @param	n	Integer value.
	FixedPoint( T n = 0 ) : m_value( n << PRECISION ) {}

	//! @brief Constructs a fixed point number from a floating point number
	//!
	//! @param	f	Floating point value
	FixedPoint( double f ) : m_value( T( floor( ldexp( f, PRECISION ) + 0.5 ) ) ) {}

	//! @brief	Constructs a fixed point number from a whole number and fraction value
	//!
	//! @param	whole		Whole part of the value
	//! @param	fraction	Fractional part of the value in units of 1/2**PRECISION (can be >= 1)
    //!
    //! @note   If the number is negative, then both parts must be negative
	FixedPoint( T whole, T fraction ) : m_value( ( whole << PRECISION ) + fraction ) {}

	//! @brief Constructs a fixed point number from a fixed point number with a different format
	//!
	//! @param	f	Fixed point value
	template < typename S, int M, typename S2 >
	explicit FixedPoint( FixedPoint<S, M, S2> const & f );

	//! Returns the value as a double
	double ToDouble() const
	{
		return ldexp( double(m_value), -PRECISION );
	}

	//! Returns the value as an integer, truncated to a whole number
	int ToInt() const
	{
		return int( m_value / ( T(1) << PRECISION ) );
	}

	//! @name Operators
	//@{
	FixedPoint operator +=( FixedPoint const & b );
	FixedPoint operator -=( FixedPoint const & b );
	FixedPoint operator *=( FixedPoint const & b );
	FixedPoint operator /=( FixedPoint const & b );
	FixedPoint operator -() const;
	//@}

	ValueType	m_value;						//!< Encoded value
};

template < typename T, int N, typename T2 >
template < typename S, int M, typename S2 >
FixedPoint< T, N, T2 >::FixedPoint( FixedPoint<S, M, S2> const & f )
{
	if ( PRECISION >= M )
	{
		m_value = T( f.m_value ) << ( PRECISION - M )
	}
	else
	{
		m_value = T( f.m_value / ( S(1) << ( M - PRECISION ) ) );
	}
}

template< typename T, int N, typename T2 >
FixedPoint< T, N, T2 > FixedPoint< T, N, T2 >::operator +=( FixedPoint const & b )
{
	m_value += b.m_value;
	return *this;
}

template< typename T, int N, typename T2 >
FixedPoint< T, N, T2 > FixedPoint< T, N, T2 >::operator -=( FixedPoint const & b )
{
	m_value -= b.m_value;
	return *this;
}

template< typename T, int N, typename T2 >
FixedPoint< T, N, T2 > FixedPoint< T, N, T2 >::operator *=( FixedPoint const & b )
{
	m_value = T( ( T2( m_value ) * T2( b.m_value ) ) / ( T2(1) << PRECISION ) );
	return *this;
}

template< typename T, int N, typename T2 >
FixedPoint< T, N, T2 > FixedPoint< T, N, T2 >::operator /=( FixedPoint const & b )
{
	m_value = T( ( T2( m_value ) << PRECISION ) / T2( b.m_value ) );
	return *this;
}

template< typename T, int N, typename T2 >
FixedPoint< T, N, T2 > FixedPoint< T, N, T2 >::operator -() const
{
	return FixedPoint( 0, -m_value );
}

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

// Binary operators

template< typename T, int N, typename T2 >
FixedPoint< T, N, T2 > operator +( FixedPoint< T, N, T2 > const & a, FixedPoint< T, N, T2 > const & b )
{
	return FixedPoint< T, N, T2 >( a ) += b;
}

template< typename T, int N, typename T2 >
FixedPoint< T, N, T2 > operator -( FixedPoint< T, N, T2 > const & a, FixedPoint< T, N, T2 > const & b )
{
	return FixedPoint< T, N, T2 >( a ) -= b;
}

template< typename T, int N, typename T2 >
FixedPoint< T, N, T2 > operator *( FixedPoint< T, N, T2 > const & a, FixedPoint< T, N, T2 > const & b )
{
	return FixedPoint< T, N, T2 >( a ) *= b;
}

template< typename T, int N, typename T2 >
FixedPoint< T, N, T2 > operator /( FixedPoint< T, N, T2 > const & a, FixedPoint< T, N, T2 > const & b )
{
	return FixedPoint< T, N, T2 >( a ) /= b;
}

template< typename T, int N, typename T2 >
bool operator <( FixedPoint< T, N, T2 > const & a, FixedPoint< T, N, T2 > const & b )
{
	return a.m_value < b.m_value;
}

template< typename T, int N, typename T2 >
bool operator >( FixedPoint< T, N, T2 > const & a, FixedPoint< T, N, T2 > const & b )
{
	return a.m_value > b.m_value;
}

template< typename T, int N, typename T2 >
bool operator ==( FixedPoint< T, N, T2 > const & a, FixedPoint< T, N, T2 > const & b )
{
	return a.m_value == b.m_value;
}

template< typename T, int N, typename T2 >
bool operator <=( FixedPoint< T, N, T2 > const & a, FixedPoint< T, N, T2 > const & b )
{
	return a.m_value <= b.m_value;
}

template< typename T, int N, typename T2 >
bool operator >=( FixedPoint< T, N, T2 > const & a, FixedPoint< T, N, T2 > const & b )
{
	return a.m_value >= b.m_value;
}

template< typename T, int N, typename T2 >
bool operator !=( FixedPoint< T, N, T2 > const & a, FixedPoint< T, N, T2 > const & b )
{
	return a.m_value != b.m_value;
}
