#pragma once
#include "FileFlow.h"
#include <fstream>
#include <iostream>
class FileFlowTester :private FileFlow {
public:
	FileFlowTester(std::string filename = "test.txt", std::string text = "This is my code");

	void test_all();

	void test_read_byte();
	void test_read_n_bytes();
	void test_read_while();
	void test_go_back();
private:
	std::ofstream t_out;
	std::string t_filename;
	std::string  t_text;
};

bool test();
