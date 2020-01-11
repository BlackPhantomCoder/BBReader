#include "BBReaderTest.h"
#include "BBReaderFlowTest.h"
#include "BBReaderFlowSpeedTest.h"
int main() {
	BBReaderTest test;
	BBReaderFlowTest testFlow;
	BBReaderFlowSpeedTest testFlowSpeed;
	
	test.test_all();
	testFlow.test_all();
	testFlowSpeed.test_speed();
}