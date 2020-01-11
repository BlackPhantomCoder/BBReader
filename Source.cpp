#include "BBReaderTest.h"
#include "BBReaderFlowTest.h"

int main() {
	BBReaderTest test;
	BBReaderFlowTest testFlow;
		
	
	test.test_all();
	testFlow.test_all();
}