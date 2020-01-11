#pragma once
#include <iostream>
#include "BBReader.h"
class BBReaderTest
{
public:
	BBReaderTest();
	void test_all();	
	void test_open();
	void test_close();			
	void test_go_at_n();			
	void test_go_for_n_back();		
	void test_go_for_n();		
	void test_go_at_end();		
	void test_is_eof();			
	void test_is_open();			
	void test_read_byte();			
	void test_read_n_bytes();
private:
	std::string t_filename;
	std::string  t_text;
};

