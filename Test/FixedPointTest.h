/********************************************************************************************************************

											FixedPointTest.h

										Copyright 2004, John J. Bolton
--------------------------------------------------------------------------------------------------------------

$Header: //depot/GPG6/Test/FixedPointTest.h#2 $

$NoKeywords: $

********************************************************************************************************************/

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class FixedPointTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( FixedPointTest );
	CPPUNIT_TEST( TestConstructorT );
	CPPUNIT_TEST( TestToDouble );
	CPPUNIT_TEST( TestToInt );
	CPPUNIT_TEST( TestConstructorIntInt );
	CPPUNIT_TEST( TestConstructorDouble );
	CPPUNIT_TEST( TestConstructorFixed );
	CPPUNIT_TEST( TestOperatorAddAssign );
	CPPUNIT_TEST( TestOperatorSubtractAssign );
	CPPUNIT_TEST( TestOperatorMultiplyAssign );
	CPPUNIT_TEST( TestOperatorDivideAssign );
	CPPUNIT_TEST( TestOperatorAdd );
	CPPUNIT_TEST( TestOperatorSubtract );
	CPPUNIT_TEST( TestOperatorMultiply );
	CPPUNIT_TEST( TestOperatorDivide );
	CPPUNIT_TEST( TestOperatorNegate );
	CPPUNIT_TEST( TestOperatorLessThan );
	CPPUNIT_TEST( TestOperatorGreaterThan );
	CPPUNIT_TEST( TestOperatorEqual );
	CPPUNIT_TEST( TestOperatorLessThanEqual );
	CPPUNIT_TEST( TestOperatorGreaterThanEqual );
	CPPUNIT_TEST( TestOperatorNotEqual );
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp();
	void tearDown();

	void TestToDouble();
	void TestToInt();
	void TestConstructorT();
	void TestConstructorIntInt();
	void TestConstructorDouble();
	void TestConstructorFixed();
	void TestOperatorAddAssign();
	void TestOperatorSubtractAssign();
	void TestOperatorMultiplyAssign();
	void TestOperatorDivideAssign();
	void TestOperatorAdd();
	void TestOperatorSubtract();
	void TestOperatorMultiply();
	void TestOperatorDivide();
	void TestOperatorNegate();
	void TestOperatorLessThan();
	void TestOperatorGreaterThan();
	void TestOperatorEqual();
	void TestOperatorLessThanEqual();
	void TestOperatorGreaterThanEqual();
	void TestOperatorNotEqual();
};
