#include "Cordic.h"

#include "Constants.h"

#include <algorithm>

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

namespace
{

	__int32 const	FIXED_TWO_PI	= __int32( 6.28318530717958647692529 * Cordic::Fixed(1).m_value + 0.5 );
	__int32 const	FIXED_PI		= __int32( 3.14159265358979323846264 * Cordic::Fixed(1).m_value + 0.5 );
	__int32 const	FIXED_PI_OVER_2	= __int32( 1.57079632679489661923132 * Cordic::Fixed(1).m_value + 0.5 );

	void Normalize( __int32 & x, __int32 & y, __int32 & a );
	void RotationMode( __int32 x, __int32 y, __int32 a, __int32 * rx, __int32 * ry );
	void VectoringMode( __int32 x, __int32 y, __int32 a, __int32 * rl, __int32 * ra );

} // anonymous namespace


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param  x, y    Vector to rotate (the rotated vector is returned)
//! @param  a       Angle of rotation (in radians)

void Cordic::Rotate( Fixed & x, Fixed & y, Fixed a )
{
	Normalize( x.m_value, y.m_value, a.m_value );

	// Use the rotation mode to rotate the vector

	RotationMode( x.m_value, y.m_value, a.m_value, &x.m_value, &y.m_value );

	// Scale the vector by C because the rotator scales it by 1/C

	x *= C;
	y *= C;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param  a       Input angle of rotation (in radians)
//! @param  s       Returned sine value
//! @param  c       Returned cosine value

void Cordic::SineCosine( Fixed a, Fixed & s, Fixed & c )
{
	c = C;
	s = 0;

	Normalize( c.m_value, s.m_value, a.m_value );

	RotationMode( c.m_value, s.m_value, a.m_value, &c.m_value, &s.m_value );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param  m   Input tangent
//!
//! @return     arctan of the input value (in radians)

Cordic::Fixed Cordic::ArcTangent( Fixed m )
{
	Fixed	a;
	__int32	l;

	VectoringMode( Fixed(1).m_value, m.m_value, 0, &l, &a.m_value );

	return a;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! This function returns the arc tangent of the given tangent represented by y/x.
//! @param  x,y   tangent components
//!
//! @return     arctan of the input value (in radians)

Cordic::Fixed Cordic::ArcTangent2( Fixed y, Fixed x )
{
	Fixed	a	= 0;

	// Adjust for the range outside of [-pi/2,pi/2]

	if ( x < Fixed(0) )
	{
		if  ( y > Fixed(0) )
		{
			a = Fixed( 0, FIXED_PI );
		}
		else
		{
			a = Fixed( 0, -FIXED_PI );
		}
		x = -x;
		y = -y;
	}

	__int32	l;
	VectoringMode( x.m_value, y.m_value, a.m_value, &l, &a.m_value );

	return a;
}




/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Cordic::Fixed Cordic::Length( Fixed x, Fixed y )
{
	// Put the vector into the range [-pi/2,pi/2]. This doesn't affect its length.

	x.m_value = abs( x.m_value );

	__int32	a;
	Fixed	l;

	VectoringMode( x.m_value, y.m_value, 0, &l.m_value, &a );

	// Return the length (scaled by C because the rotator scales it by 1/C)
	return l * C;
}




namespace
{


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void Normalize( __int32 & x, __int32 & y, __int32 & a )
{
	// Rotate by 2pi, pi, and pi/2 until the desired angle is in the range (-pi/2, pi/2)

	while ( a >= FIXED_TWO_PI )
	{
		a -= FIXED_TWO_PI;
	}

	while ( a <= -FIXED_TWO_PI )
	{
		a += FIXED_TWO_PI;
	}

	if ( a >= FIXED_PI )
	{
		x = -x;
		y = -y;
		a -= FIXED_PI;
	}

	if ( a <= -FIXED_PI )
	{
		x = -x;
		y = -y;
		a += FIXED_PI;
	}

	if ( a >= FIXED_PI_OVER_2 )
	{
		y = -y;
		std::swap( x, y );
		a -= FIXED_PI_OVER_2;
	}

	if ( a <= -FIXED_PI_OVER_2 )
	{
		x = -x;
		std::swap( x, y );
		a += FIXED_PI_OVER_2;
	}
}

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

// These functions are used to optimize the functions below, eliminating conditional execution. They are shown in
// generic form here but can be replaced by one or two assembly instructions on some processors.

// Returns n if d == 0, and -n if d == -1
inline __int32 CONDITIONAL_NEG( __int32 n, __int32 d )
{
    return ( n ^ d ) - d;
}

// IMPORTANT: The following function assumes that the compiler implements the shift operator on signed types using
// an arithmetic shift. In C/C++, the precise behavior of the >> operator on signed integer types is defined by the
// compiler implementaion. The compiler may or may not shift in the value of the sign bit. For example, the result
// of (-1) >> 1 may be 0x7fffffff or 0xffffffff, depending on the compiler. 

// Returns 0 if n >= 0, and -1 if n < 0
inline __int32 S( __int32 n )
{
    return n >> ( sizeof(__int32) * 8 - 1 );
}

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void RotationMode( __int32 x, __int32 y, __int32 a, __int32 * rx, __int32 * ry )
{
	for ( int i = 0; i < NUMBER_OF_ITERATIONS; ++i )
	{
		__int32	d	= S( a );	// ( a >= 0 ) ? 0 : -1;
		__int32	xi	= x;
		__int32	yi	= y;

		x = x - CONDITIONAL_NEG( yi >> i, d );
		y = y + CONDITIONAL_NEG( xi >> i, d );
		a -= CONDITIONAL_NEG( angles[i].m_value, d );
	}

	*rx = x;
	*ry = y;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void VectoringMode( __int32 x, __int32 y, __int32 a, __int32 * rl, __int32 * ra )
{
	for ( int i = 0; i < NUMBER_OF_ITERATIONS; ++i )
	{
		__int32	d	= S( y );	// ( y >= 0 ) ? 0 : -1;
		__int32	xi	= x;
		__int32	yi	= y;

		x = x + CONDITIONAL_NEG( yi >> i, d );
		y = y - CONDITIONAL_NEG( xi >> i, d );
		a += CONDITIONAL_NEG( angles[i].m_value, d );
	}

	*rl = x;
	*ra = a;
}


} // anonymous namespace