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
CxxTest::StaticSuiteDescription suiteDescription_MiscTest( "approx.test.h", 7, "MiscTest", suite_MiscTest, Tests_MiscTest );

static class TestDescription_suite_MiscTest_testTieMean1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MiscTest_testTieMean1() : CxxTest::RealTestDescription( Tests_MiscTest, suiteDescription_MiscTest, 10, "testTieMean1" ) {}
 void runTest() { suite_MiscTest.testTieMean1(); }
} testDescription_suite_MiscTest_testTieMean1;

static class TestDescription_suite_MiscTest_testTieMean2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MiscTest_testTieMean2() : CxxTest::RealTestDescription( Tests_MiscTest, suiteDescription_MiscTest, 29, "testTieMean2" ) {}
 void runTest() { suite_MiscTest.testTieMean2(); }
} testDescription_suite_MiscTest_testTieMean2;

static class TestDescription_suite_MiscTest_testTieMean3 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MiscTest_testTieMean3() : CxxTest::RealTestDescription( Tests_MiscTest, suiteDescription_MiscTest, 48, "testTieMean3" ) {}
 void runTest() { suite_MiscTest.testTieMean3(); }
} testDescription_suite_MiscTest_testTieMean3;

static class TestDescription_suite_MiscTest_testTieMean4 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MiscTest_testTieMean4() : CxxTest::RealTestDescription( Tests_MiscTest, suiteDescription_MiscTest, 67, "testTieMean4" ) {}
 void runTest() { suite_MiscTest.testTieMean4(); }
} testDescription_suite_MiscTest_testTieMean4;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
