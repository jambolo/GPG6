/********************************************************************************************************************

											FixedPointTest.cpp

										Copyright 2004, John J. Bolton
--------------------------------------------------------------------------------------------------------------

$Header: //depot/GPG6/Test/FixedPointTest.cpp#3 $

$NoKeywords: $

********************************************************************************************************************/

#include "FixedPointTest.h"
#include "../FixedPoint/FixedPoint.h"

#include "Math/Math.h"

typedef	FixedPoint<__int8,  0, __int8>	Fixed8_0_8;
typedef	FixedPoint<__int8,  1, __int8>	Fixed7_1_8;
typedef	FixedPoint<__int8,  2, __int8>	Fixed6_2_8;
typedef	FixedPoint<__int8,  4, __int8>	Fixed4_4_8;
typedef	FixedPoint<__int8,  6, __int8>	Fixed2_6_8;
typedef	FixedPoint<__int8,  7, __int8>	Fixed1_7_8;

typedef	FixedPoint<__int8,  0, __int16>	Fixed8_0_16;
typedef	FixedPoint<__int8,  1, __int16>	Fixed7_1_16;
typedef	FixedPoint<__int8,  2, __int16>	Fixed6_2_16;
typedef	FixedPoint<__int8,  4, __int16>	Fixed4_4_16;
typedef	FixedPoint<__int8,  6, __int16>	Fixed2_6_16;
typedef	FixedPoint<__int8,  7, __int16>	Fixed1_7_16;

typedef	FixedPoint<__int16,  0, __int16>	Fixed16_0_16;
typedef	FixedPoint<__int16,  1, __int16>	Fixed15_1_16;
typedef	FixedPoint<__int16,  2, __int16>	Fixed14_2_16;
typedef	FixedPoint<__int16,  4, __int16>	Fixed12_4_16;
typedef	FixedPoint<__int16,  8, __int16>	Fixed8_8_16;
typedef	FixedPoint<__int16, 14, __int16>	Fixed2_14_16;
typedef	FixedPoint<__int16, 15, __int16>	Fixed1_15_16;

typedef	FixedPoint<__int16,  0, __int32>	Fixed16_0_32;
typedef	FixedPoint<__int16,  1, __int32>	Fixed15_1_32;
typedef	FixedPoint<__int16,  2, __int32>	Fixed14_2_32;
typedef	FixedPoint<__int16,  4, __int32>	Fixed12_4_32;
typedef	FixedPoint<__int16,  8, __int32>	Fixed8_8_32;
typedef	FixedPoint<__int16, 14, __int32>	Fixed2_14_32;
typedef	FixedPoint<__int16, 15, __int32>	Fixed1_15_32;

typedef	FixedPoint<__int32,  0, __int32>	Fixed32_0_32;
typedef	FixedPoint<__int32,  1, __int32>	Fixed31_1_32;
typedef	FixedPoint<__int32,  2, __int32>	Fixed30_2_32;
typedef	FixedPoint<__int32,  4, __int32>	Fixed28_4_32;
typedef	FixedPoint<__int32,  8, __int32>	Fixed24_8_32;
typedef	FixedPoint<__int32, 16, __int32>	Fixed16_16_32;
typedef	FixedPoint<__int32, 30, __int32>	Fixed2_30_32;
typedef	FixedPoint<__int32, 31, __int32>	Fixed1_31_32;

typedef	FixedPoint<__int32,  0, __int64>	Fixed32_0_64;
typedef	FixedPoint<__int32,  1, __int64>	Fixed31_1_64;
typedef	FixedPoint<__int32,  2, __int64>	Fixed30_2_64;
typedef	FixedPoint<__int32,  4, __int64>	Fixed28_4_64;
typedef	FixedPoint<__int32,  8, __int64>	Fixed24_8_64;
typedef	FixedPoint<__int32, 16, __int64>	Fixed16_16_64;
typedef	FixedPoint<__int32, 30, __int64>	Fixed2_30_64;
typedef	FixedPoint<__int32, 31, __int64>	Fixed1_31_64;

typedef	FixedPoint<__int64,  0, __int64>	Fixed64_0_64;
typedef	FixedPoint<__int64,  1, __int64>	Fixed63_1_64;
typedef	FixedPoint<__int64,  2, __int64>	Fixed62_2_64;
typedef	FixedPoint<__int64,  4, __int64>	Fixed60_4_64;
typedef	FixedPoint<__int64,  8, __int64>	Fixed56_8_64;
typedef	FixedPoint<__int64, 16, __int64>	Fixed48_16_64;
typedef	FixedPoint<__int64, 32, __int64>	Fixed32_32_64;
typedef	FixedPoint<__int64, 62, __int64>	Fixed2_62_64;
typedef	FixedPoint<__int64, 63, __int64>	Fixed1_63_64;

typedef	FixedPoint<unsigned __int32,  0, unsigned __int32>	FixedU32_0_32;
typedef	FixedPoint<unsigned __int32,  1, unsigned __int32>	FixedU32_1_32;
typedef	FixedPoint<unsigned __int32,  2, unsigned __int32>	FixedU30_2_32;
typedef	FixedPoint<unsigned __int32,  4, unsigned __int32>	FixedU28_4_32;
typedef	FixedPoint<unsigned __int32,  8, unsigned __int32>	FixedU24_8_32;
typedef	FixedPoint<unsigned __int32, 16, unsigned __int32>	FixedU16_16_32;
typedef	FixedPoint<unsigned __int32, 30, unsigned __int32>	FixedU2_30_32;
typedef	FixedPoint<unsigned __int32, 31, unsigned __int32>	FixedU1_31_32;


typedef FixedPoint<__int32, 24, __int64>	Fixed8_24_64;













CPPUNIT_TEST_SUITE_REGISTRATION( FixedPointTest );

namespace
{
} // anonymous namespace


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void FixedPointTest::setUp()
{

}

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void FixedPointTest::tearDown()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

void FixedPointTest::TestConstructorT()
{
	for ( int i = -128; i < 128; ++i )
	{
		CPPUNIT_ASSERT_EQUAL( __int16(i << 8), Fixed8_8_16( __int16(i) ).m_value );
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestToDouble()
{
	for ( int i = -32768; i < 32768; ++i )
	{
		CPPUNIT_ASSERT_EQUAL( double(i)/256.0, Fixed8_8_16( double(i)/256.0 ).ToDouble() );
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestToInt()
{
	for ( int i = -32768; i < 32768; ++i )
	{
		CPPUNIT_ASSERT_EQUAL( i/256, Fixed8_8_16( double(i)/256.0 ).ToInt() );
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestConstructorIntInt()
{
	for ( int i = -127; i < 0; ++i )
	{
		for ( int j = -255; j < 0; ++j )
		{
			CPPUNIT_ASSERT_EQUAL( double(i) + double(j)/256.0, Fixed8_8_16( i, j ).ToDouble() );
		}
	}
	for ( int i = 0; i < 128; ++i )
	{
		for ( int j = 0; j < 256; ++j )
		{
			CPPUNIT_ASSERT_EQUAL( double(i) + double(j)/256.0, Fixed8_8_16( i, j ).ToDouble() );
		}
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestConstructorDouble()
{
	for ( double d = -128.0; d < 128.0; d += 1.0/256.0 )
	{
		CPPUNIT_ASSERT_EQUAL( d, Fixed8_8_16( d ).ToDouble() );
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestConstructorFixed()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorAddAssign()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorSubtractAssign()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorMultiplyAssign()
{
	int const		NUMBER_OF_ITERATIONS	= 113;
	int const		MIN_POWER				= -14;
	int const		MAX_POWER				= 7;
	double const	TOLERANCE				= 1e-6;

	for ( int i = 0; i < NUMBER_OF_ITERATIONS; ++i )
	{
		double			l2i	= Math::Lerp( float(MIN_POWER), float(MAX_POWER), float(i)/float(NUMBER_OF_ITERATIONS) );
		Fixed8_24_64	a( pow( 2.0, l2i ) );

		int const	MIN_J	= -MIN_POWER*NUMBER_OF_ITERATIONS/(MAX_POWER-MIN_POWER);
		int const	MAX_J	= (MAX_POWER-2*MIN_POWER)*NUMBER_OF_ITERATIONS/(MAX_POWER-MIN_POWER);

		for ( int j = std::max(MIN_J-i+1, 0); j < std::min(MAX_J-i, NUMBER_OF_ITERATIONS); ++j )
		{
			double			l2j	= Math::Lerp( float(MIN_POWER), float(MAX_POWER), float(j)/float(NUMBER_OF_ITERATIONS) );
			Fixed8_24_64	b( pow( 2.0, l2j ) );
			Fixed8_24_64	c;

			c = b;
			c *= a;
			CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE( "Error exceeded tolerance.", b.ToDouble()*a.ToDouble(), c.ToDouble(), TOLERANCE );

			c = b;
			c *= -a;
			CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE( "Error exceeded tolerance.", b.ToDouble()*-a.ToDouble(), c.ToDouble(), TOLERANCE );

			c = -b;
			c *= a;
			CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE( "Error exceeded tolerance.", -b.ToDouble()*a.ToDouble(), c.ToDouble(), TOLERANCE );

			c = -b;
			c *= -a;
			CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE( "Error exceeded tolerance.", -b.ToDouble()*-a.ToDouble(), c.ToDouble(), TOLERANCE );

			c = a;
			c *= b;
			CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE( "Error exceeded tolerance.", a.ToDouble()*b.ToDouble(), c.ToDouble(), TOLERANCE );

			c = a;
			c *= -b;
			CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE( "Error exceeded tolerance.", a.ToDouble()*-b.ToDouble(), c.ToDouble(), TOLERANCE );

			c = -a;
			c *= b;
			CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE( "Error exceeded tolerance.", -a.ToDouble()*b.ToDouble(), c.ToDouble(), TOLERANCE );

			c = -a;
			c *= -b;
			CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE( "Error exceeded tolerance.", -a.ToDouble()*-b.ToDouble(), c.ToDouble(), TOLERANCE );
		}
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorDivideAssign()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorAdd()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorSubtract()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorMultiply()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorDivide()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorNegate()
{
	for ( double d = -128.0+1.0/256.0; d < 128.0; d += 1.0/256.0 )
	{
		CPPUNIT_ASSERT_EQUAL( -d, (-Fixed8_8_16( d )).ToDouble() );
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorLessThan()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorGreaterThan()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorEqual()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorLessThanEqual()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorGreaterThanEqual()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/


void FixedPointTest::TestOperatorNotEqual()
{
}


