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
bool suite_MeasureTest_init = false;
#include "measure.test.h"

static MeasureTest suite_MeasureTest;

static CxxTest::List Tests_MeasureTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MeasureTest( "measure.test.h", 12, "MeasureTest", suite_MeasureTest, Tests_MeasureTest );

static class TestDescription_suite_MeasureTest_testAUC : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MeasureTest_testAUC() : CxxTest::RealTestDescription( Tests_MeasureTest, suiteDescription_MeasureTest, 15, "testAUC" ) {}
 void runTest() { suite_MeasureTest.testAUC(); }
} testDescription_suite_MeasureTest_testAUC;

static class TestDescription_suite_MeasureTest_testTPRFPR : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MeasureTest_testTPRFPR() : CxxTest::RealTestDescription( Tests_MeasureTest, suiteDescription_MeasureTest, 46, "testTPRFPR" ) {}
 void runTest() { suite_MeasureTest.testTPRFPR(); }
} testDescription_suite_MeasureTest_testTPRFPR;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
