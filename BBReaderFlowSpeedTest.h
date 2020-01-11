#pragma once
#include "BBReaderFlow.h"
#include <iostream>
#include <ctime>
class BBReaderFlowSpeedTest
{
public:
	BBReaderFlowSpeedTest();

	void test_speed();
private:
	std::string str;
	std::string filename;
};