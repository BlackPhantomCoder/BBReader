#include "BBReaderTest.h"
BBReaderTest::BBReaderTest()
{
	std::ofstream out("output.txt", std::ios::binary);
	std::string str = "123456789";
	for (size_t i = 0; i < str.size(); ++i) {
		out << str[i];
	}
	out.close();

	BBReader reader("output.txt");
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
}
