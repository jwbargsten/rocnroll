/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    status = CxxTest::Main<CxxTest::ErrorPrinter>( tmp, argc, argv );
    return status;
}
bool suite_MiscTest_init = false;
#include "approx.test.h"

static MiscTest suite_MiscTest;

static CxxTest::List Tests_MiscTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MiscTest( "approx.test.h", 5, "MiscTest", suite_MiscTest, Tests_MiscTest );

static class TestDescription_suite_MiscTest_testTieMean : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MiscTest_testTieMean() : CxxTest::RealTestDescription( Tests_MiscTest, suiteDescription_MiscTest, 8, "testTieMean" ) {}
 void runTest() { suite_MiscTest.testTieMean(); }
} testDescription_suite_MiscTest_testTieMean;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
