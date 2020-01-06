#include "BBReaderTest.h"
BBReaderTest::BBReaderTest()
{
	std::cout << std::boolalpha;
	t_filename = "output.txt";
	std::ofstream out(t_filename, std::ios::binary);
	t_text = "123456789";
	for (size_t i = 0; i < t_text.size(); ++i) {
		out << t_text[i];
	}
	out.close();
}

void BBReaderTest::test_all()
{
	test_close();
	test_go_at_n();
	test_go_for_n_back();
	test_go_for_n();
	test_go_at_end();
	test_is_eof();
	test_is_open();
	test_read_byte();
	test_read_n_bytes();
}

void BBReaderTest::test_read_byte()
{
	std::cout << "Testing read_byte() ... ";
	BBReader reader(t_filename);
	bool result = true;
	for (size_t i = 0; i < t_text.size(); ++i) {
		if (!(reader.read_byte() == t_text[i])) {
			result = false;
			break;
		}
	}
	std::cout << result << std::endl;
}

void BBReaderTest::test_read_n_bytes()
{
	std::cout << "Testing read_n_bytes() ... ";
	BBReader reader(t_filename);
	std::vector<char> buf;
	reader.read_n_bytes(buf, t_text.size());
	bool result = true;
	for (size_t i = 0; i < t_text.size(); ++i) {
		if (!(buf[i] == t_text[i])) {
			result = false;
			break;
		}
	}
	std::cout << result << std::endl;
}

void BBReaderTest::test_close()
{
	std::cout << "Testing close() ... ";
	BBReader reader(t_filename);
	reader.close();
	std::cout << !reader.is_open() << std::endl;
}

void BBReaderTest::test_go_at_n()
{
	std::cout << "Testing go_at_n() ... ";
	BBReader reader(t_filename);
	reader.go_for_n(2);
	std::cout << (reader.read_byte() == t_text[2]) << std::endl;
}

void BBReaderTest::test_go_for_n_back()
{
	std::cout << "Testing go_for_n_back() ... ";
	BBReader reader(t_filename);
	reader.go_at_end();
	reader.go_for_n_back(1);
	std::cout << (reader.read_byte() == t_text[t_text.size() - 1]) << std::endl;
}

void BBReaderTest::test_go_for_n()
{
	std::cout << "Testing go_for_n() ... ";
	BBReader reader(t_filename);
	reader.go_for_n(2);
	std::cout << (reader.read_byte() == t_text[2]) << std::endl;
}

void BBReaderTest::test_go_at_end()
{
	std::cout << "Testing go_at_end() ... ";
	BBReader reader(t_filename);
	reader.go_at_end();
	std::cout << reader.is_eof() << std::endl;
}

void BBReaderTest::test_is_eof()
{
	std::cout << "Testing is_eof() ... ";
	BBReader reader(t_filename);
	if (!reader.is_eof()) {
		for (size_t i = 0; i < t_text.size(); ++i) {
			reader.read_byte();
		}
		std::cout << reader.is_eof() << std::endl;
	}
	else {
		std::cout << " false" << std::endl;
	}
}

void BBReaderTest::test_is_open()
{
	std::cout << "Testing is_open() ... ";
	BBReader reader(t_filename);
	std::cout << reader.is_open() << std::endl;
}
