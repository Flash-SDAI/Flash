#include "stdafx.h"
#include "CppUnitTest.h"
#include "testcase.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FlashTestProject
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestLightDetection) {
			testcase test;
			Assert::AreEqual(test.lightDetection(50), test.HIGH);
			Assert::AreEqual(test.lightDetection(150), test.LOW);
		}

		TEST_METHOD(TestLightDetectionAndShortLights) {
			testcase test;
			Assert::AreEqual(test.lightDetection(50), test.HIGH);
			Assert::AreEqual(test.shortHeadLights(test.HIGH, test.LOW), test.HIGH);
			Assert::AreEqual(test.shortHeadLights(test.LOW, test.HIGH), test.HIGH);
			Assert::AreEqual(test.shortHeadLights(test.LOW, test.LOW), test.HIGH);
			Assert::AreEqual(test.shortHeadLights(test.HIGH, test.HIGH), test.HIGH);
		}

		TEST_METHOD(TestLightDetectionAndLongLights) {
			testcase test;
			Assert::AreEqual(test.lightDetection(50), test.HIGH);
			Assert::AreEqual(test.longHeadLights(test.HIGH, test.LOW), test.LOW);
			Assert::AreEqual(test.longHeadLights(test.LOW, test.HIGH), test.HIGH);
			Assert::AreEqual(test.longHeadLights(test.LOW, test.LOW), test.LOW);
			Assert::AreEqual(test.longHeadLights(test.HIGH, test.HIGH), test.HIGH);
		}

		TEST_METHOD(TestShortLights) {
			testcase test;
			Assert::AreEqual(test.shortHeadLights(test.HIGH, test.LOW), test.LOW);
			Assert::AreEqual(test.shortHeadLights(test.LOW, test.HIGH), test.HIGH);
			Assert::AreEqual(test.shortHeadLights(test.LOW, test.LOW), test.HIGH);
			Assert::AreEqual(test.shortHeadLights(test.HIGH, test.HIGH), test.LOW);
		}

		TEST_METHOD(TestLongLights) {
			testcase test;
			Assert::AreEqual(test.longHeadLights(test.HIGH, test.LOW), test.LOW);
			Assert::AreEqual(test.longHeadLights(test.LOW, test.HIGH), test.HIGH);
			Assert::AreEqual(test.longHeadLights(test.LOW, test.LOW), test.LOW);
			Assert::AreEqual(test.longHeadLights(test.HIGH, test.HIGH), test.LOW);
		}

		TEST_METHOD(TestTurnLights) {
			testcase test;
			Assert::AreEqual(test.rightTurnLights(test.HIGH), test.HIGH);
			Assert::AreEqual(test.rightTurnLights(test.LOW), test.LOW);
			Assert::AreEqual(test.leftTurnLights(test.HIGH), test.HIGH);
			Assert::AreEqual(test.leftTurnLights(test.LOW), test.LOW);
		}

		TEST_METHOD(TestTurnLightsWithEmergencyLights) {
			testcase test;
			for (int i = 0; i < 2; i++) {
				if (i == 0)
					Assert::AreEqual(test.emergencyLights(test.HIGH), test.LOW);
				if (i == 1)
					Assert::AreEqual(test.emergencyLights(test.HIGH), test.HIGH);
			}
			Assert::AreEqual(test.rightTurnLights(test.HIGH), test.LOW);
			Assert::AreEqual(test.rightTurnLights(test.LOW), test.LOW);
			Assert::AreEqual(test.leftTurnLights(test.HIGH), test.LOW);
			Assert::AreEqual(test.leftTurnLights(test.LOW), test.LOW);

			Assert::AreEqual(test.emergencyLights(test.LOW), test.LOW);
			Assert::AreEqual(test.rightTurnLights(test.HIGH), test.HIGH);
			Assert::AreEqual(test.rightTurnLights(test.LOW), test.LOW);
			Assert::AreEqual(test.leftTurnLights(test.HIGH), test.HIGH);
			Assert::AreEqual(test.leftTurnLights(test.LOW), test.LOW);
		}

		TEST_METHOD(TestEmergencyLights) {
			testcase test;
			for (int i = 0; i < 3; i++) {
				if (i == 0)
					Assert::AreEqual(test.emergencyLights(test.HIGH), test.LOW);
				if (i == 1)
					Assert::AreEqual(test.emergencyLights(test.HIGH), test.HIGH);
				if (i == 2)
					Assert::AreEqual(test.emergencyLights(test.LOW), test.LOW);
			}
		}

		TEST_METHOD(TestStopLights) {
			testcase test;
			Assert::AreEqual(test.stopLights(test.HIGH), test.HIGH);
			Assert::AreEqual(test.stopLights(test.LOW), test.LOW);
		}
	};
}