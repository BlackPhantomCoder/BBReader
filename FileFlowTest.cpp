#include "FileFlowTest.h"
FileFlowTester::FileFlowTester(std::string filename, std::string text) :FileFlow(filename) {
	t_filename = filename;
	t_text = text;
	std::cout << "Creating test... ";
	t_out.open(t_filename, std::ios::binary);
	if (t_out.is_open()) {
		std::cout << "true" << std::endl;
		t_out << t_text;
		t_out.close();

		std::cout << "Opening... ";
		(open()) ? std::cout << "true" : std::cout << "false";
		std::cout << std::endl;
	}
	else {
		std::cout << "false" << std::endl;
	}
}
void FileFlowTester::test_all() {
	if (open()) {
		std::cout << "Testing" << std::endl;
		at_start();
		std::cout << "test_read_byte()" << std::endl;
		test_read_byte();
		at_start();
		std::cout << "test_read_n_bytes()" << std::endl;
		test_read_n_bytes();
		at_start();
		std::cout << "test_read_while()" << std::endl;
		test_read_while();
		std::cout << "test_go_back()" << std::endl;
		test_go_back();
		std::cout << "End Testing" << std::endl;
	}
}
void FileFlowTester::test_read_byte() {
	if (open()) {
		at_start();
		char buf;
		for (size_t i = 0; i < t_text.size(); ++i) {
			buf = read_byte();
			if (buf != t_text[i]) {
				std::cout << "read_byte error, element is " << i << std::endl;
			}
		}
	}
}
void FileFlowTester::test_read_n_bytes() {
	if (open()) {
		at_start();
		size_t n = t_text.size() / 4;
		std::vector<char> buf;
		read_n_bytes(buf, n);
		if (buf.size() == n) {
			for (size_t i = 0; i < buf.size(); ++i) {
				if (t_text[i] != buf[i]) {
					std::cout << "not success test_read_n_bytes()" << std::endl;
					break;
				}
			}
		}
		else {
			std::cout << "not success test_read_n_bytes()" << std::endl;
		}
	}
}
void FileFlowTester::test_read_while() {
	if (open()) {
		at_start();
		at_start();
		size_t n = t_text.size() / 4;
		std::vector<char> buf;
		read_while(buf, t_text[n]);
		if (buf.size() == n) {
			for (size_t i = 0; i < buf.size(); ++i) {
				if (t_text[i] != buf[i]) {
					std::cout << "not success test_read_while()" << std::endl;
					break;
				}
			}
		}
		else {
			std::cout << "not success test_read_while()" << std::endl;
		}
	}
}

void FileFlowTester::test_go_back()
{
	if (open()) {
		at_start();
		char buf = read_byte();
		go_back();
		if (buf == read_byte()) {
			std::cout << "success go_back()" << std::endl;
		}
		else {
			std::cout << "not success go_back()" << std::endl;
		}
	}
}



bool test(){
	FileFlowTester tester = FileFlowTester();
	tester.test_all();

	return true;
}
