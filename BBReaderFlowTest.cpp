#include "BBReaderFlowTest.h"

BBReaderFlowTest::BBReaderFlowTest()
{
	std::ofstream out("output.txt", std::ios::binary);
	std::string str = "123456789";
	for (size_t i = 0; i < str.size(); ++i) {
		out << str[i];
	}
	out.close();

	BBReaderFlow reader("output.txt");
	for (size_t i = 0; i < str.size(); ++i) {
		std::cout << reader.read_byte();
	}
	std::cout << std::endl;
	reader.go_at_n(0);
	std::vector<char> vec;
	size_t size = str.size();
	reader.read_n_bytes(vec, size);
	for (size_t i = 0; i < str.size(); ++i) {
		std::cout << vec[i];
	}
	std::cout << std::endl;

	reader.go_at_n(5);
	std::cout << reader.read_byte();
	if (!reader.go_for_n_back(5)) {
		std::cout << "no go back";
	}
	std::cout << reader.read_byte();
	std::cout << std::endl;
	vec.clear();
	reader.go_at_start();
	if (!reader.read_while_not(vec, '5')) {
		std::cout << "no read_while_not" << std::endl;
	}
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
	}
	std::cout << std::endl;
}
