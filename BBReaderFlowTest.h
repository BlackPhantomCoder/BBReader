#pragma once
#include "BBReaderFlow.h"
#include <iostream>
class BBReaderFlowTest
{
public:
	BBReaderFlowTest();

	void test_all();
	void go_at_start();															
	void read_while_not();					
	void skip_while_not();	
	void skip_byte();														
	void skip_n_bytes();
private:
	std::string str;
	std::string filename;
};

