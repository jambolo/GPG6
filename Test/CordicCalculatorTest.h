#pragma once

#include "../Cordic/Cordic.h"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class CordicCalculatorTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CordicCalculatorTest );
	CPPUNIT_TEST( TestRotate );
	CPPUNIT_TEST( TestSineCosine );
	CPPUNIT_TEST( TestArcTangent );
	CPPUNIT_TEST( TestArcTangent2 );
	CPPUNIT_TEST( TestLength );
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp();
	void tearDown();

	void TestRotate();
	void TestSineCosine();
	void TestArcTangent();
	void TestArcTangent2();
	void TestLength();

private:

};
