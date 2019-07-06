#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

int main()
{
	CPPUNIT_NS::TextTestRunner				runner;

	// Add the tests
	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );

	// Run the tests
	return runner.run( "", true );
}
