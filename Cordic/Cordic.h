#pragma once

#include "../FixedPoint/FixedPoint.h"

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

class Cordic
{

public:

	//! Number of fractional bits
	static int const	PRECISION	= 24;

	//! 8.24 fixed point using 64-bit for intermediate values
	typedef FixedPoint< __int32, PRECISION, __int64 >	Fixed;

	//! Rotates a vector by the given angle
	static void Rotate( Fixed & x, Fixed & y, Fixed a );

	//! Returns the sine and cosine of an angle
	static void SineCosine( Fixed a, Fixed & s, Fixed & c );

	//! Returns the arc tangent of a slope in the range [-pi,pi)
	static Fixed ArcTangent( Fixed m );

	//! Returns the arc tangent of a slope in the range [-pi,pi) given the X and Y components
	static Fixed ArcTangent2( Fixed y, Fixed x );

	//! Returns the length of a vector given the X and Y components
	static Fixed Length( Fixed x, Fixed y );
};
