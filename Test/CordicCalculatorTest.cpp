#include "CordicCalculatorTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( CordicCalculatorTest );

namespace
{
	float Lerp( float a, float b, float t )
	{
		return a * (1.f - t) + b * t;
	}

	double const	TWO_PI	= 6.28318530717958647692529;

} // anonymous namespace


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void CordicCalculatorTest::setUp()
{
}

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void CordicCalculatorTest::tearDown()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void CordicCalculatorTest::TestRotate()
{
	// Tests the results of of rotating vectors evenly spaced in the range [-2pi,+2pi] by angles evenly
	// spaced in the range [-2pi,+2pi].

	int const		NUMBER_OF_ROTATIONS	= 67+1;
	int const		NUMBER_OF__VECTORS	= 61+1;
	double const	TOLERANCE			= 1e-5;

	for ( int i = 0; i < NUMBER_OF_ROTATIONS; ++i )
	{
		double a	= Lerp( -float(TWO_PI), +float(TWO_PI), float(i) / float(NUMBER_OF_ROTATIONS-1) );
		double sa	= sin( a );
		double ca	= cos( a );

		for ( int j = 0; j < NUMBER_OF__VECTORS; ++j )
		{
			double	a0	= Lerp( -float(TWO_PI), +float(TWO_PI), float(j) / float(NUMBER_OF__VECTORS-1) );
			double	x0	= cos( a0 );
			double	y0	= sin( a0 );

			Cordic::Fixed fx( x0 );
			Cordic::Fixed fy( y0 );
			Cordic::Rotate( fx, fy, a );

			double	xp	= x0 * ca - y0 * sa;
			double	yp	= x0 * sa + y0 * ca;

			double	expected	= _hypot( xp, yp );
			double	actual		= _hypot( fx.ToDouble(), fy.ToDouble() );

			CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE( "Error exceeded tolerance.", expected, actual, TOLERANCE );
		}
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void CordicCalculatorTest::TestSineCosine()
{
	int const		NUMBER_OF_ITERATIONS	= 3701+1;
	double const	TOLERANCE				= 1e-5;

	for ( int i = 0; i < NUMBER_OF_ITERATIONS; ++i )
	{
		double a	= Lerp( -float(TWO_PI), +float(TWO_PI), float(i) / float(NUMBER_OF_ITERATIONS-1) );

		Cordic::Fixed fs;
		Cordic::Fixed fc;
		Cordic::SineCosine( a, fs, fc );

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE( "Sine error exceeded tolerance.", sin( a ), fs.ToDouble(), TOLERANCE );
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE( "Cosine error exceeded tolerance.", cos( a ), fc.ToDouble(), TOLERANCE );
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void CordicCalculatorTest::TestArcTangent()
{
	int const		NUMBER_OF_ITERATIONS	= 3701+1;
	double const	TOLERANCE				= 1e-5;

	for ( int i = 0; i < NUMBER_OF_ITERATIONS; ++i )
	{
		double			slope	= Lerp( -32.0f, +32.0f, float(i) / float(NUMBER_OF_ITERATIONS-1) );
		Cordic::Fixed	fslope( slope );

		double	expected	= atan( slope );
		double	actual		= Cordic::ArcTangent( fslope ).ToDouble();

		CPPUNIT_ASSERT_DOUBLES_EQUAL( expected, actual, TOLERANCE );
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void CordicCalculatorTest::TestArcTangent2()
{
	int const		NUMBER_OF_ITERATIONS	= 61+1;
	double const	TOLERANCE				= 1e-5;

	for ( int i = 0; i < NUMBER_OF_ITERATIONS; ++i )
	{
		double			y	= Lerp( -32.0f, +32.0f, float(i) / float(NUMBER_OF_ITERATIONS-1) );
		Cordic::Fixed	fy(y);

		for ( int j = 0; j < NUMBER_OF_ITERATIONS; ++j )
		{
			double			x	= Lerp( -32.0f, +32.0f, float(j) / float(NUMBER_OF_ITERATIONS-1) );
			Cordic::Fixed	fx(x);

			double	expected	= atan2( y, x );
			double	actual		= Cordic::ArcTangent2( fy, fx ).ToDouble();

			CPPUNIT_ASSERT_DOUBLES_EQUAL( expected, actual, TOLERANCE );
		}
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void CordicCalculatorTest::TestLength()
{
	int const		NUMBER_OF_ITERATIONS	= 61+1;
	double const	TOLERANCE				= 1e-5;

	for ( int i = 0; i < NUMBER_OF_ITERATIONS; ++i )
	{
		double			y	= Lerp( -32.0f, +32.0f, float(i) / float(NUMBER_OF_ITERATIONS-1) );
		Cordic::Fixed	fy(y);

		for ( int j = 0; j < NUMBER_OF_ITERATIONS; ++j )
		{
			double			x	= Lerp( -32.0f, +32.0f, float(j) / float(NUMBER_OF_ITERATIONS-1) );
			Cordic::Fixed	fx(x);

			double	expected	= _hypot( x, y );
			double	actual		= Cordic::Length( fx, fy ).ToDouble();

			CPPUNIT_ASSERT_DOUBLES_EQUAL( expected, actual, TOLERANCE );
		}
	}
}
