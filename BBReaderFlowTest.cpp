#include "BBReaderFlowTest.h"

BBReaderFlowTest::BBReaderFlowTest()
{
	filename = "testreaderflow.txt";
	std::ofstream out(filename, std::ios::binary);
	str = "123456789";
	out << str;
	out.close();
}

void BBReaderFlowTest::test_all()
{
	go_at_start();
	read_while_not();
	skip_while_not();
	skip_byte();
	skip_n_bytes();
}

void BBReaderFlowTest::go_at_start()
{
	std::cout << "Testing go_at_start()...";
	Reader::BBReaderFlow reader(filename);
	reader.go_at_n(5);
	reader.go_at_start();
	std::cout << (reader.read_byte() == str[0]) << std::endl;
}

void BBReaderFlowTest::read_while_not()
{
	std::cout << "Testing read_while_not()... ";
	Reader::BBReaderFlow reader(filename);
	std::string buf;
	reader.read_while_not(buf, "7");
	bool result = true;
	for (size_t i = 0; i < 6; ++i) {
		if (str[i] != buf[i]) {
			result = false;
			break;
		}
	}
	std::cout << result << std::endl;
}

void BBReaderFlowTest::skip_while_not()
{
	std::cout << "Testing skip_while_not()... ";
	Reader::BBReaderFlow reader(filename);
	std::string buf;
	reader.read_while_not(buf, "7");
	std::cout << (reader.read_byte() == str[7]) << std::endl;
}

void BBReaderFlowTest::skip_byte()
{
	std::cout << "Testing skip_byte()... ";
	Reader::BBReaderFlow reader(filename);
	reader.skip_byte();
	std::cout << (reader.read_byte() == str[1])<< std::endl;
}

void BBReaderFlowTest::skip_n_bytes()
{
	std::cout << "Testing skip_n_bytes()... ";
	Reader::BBReaderFlow reader(filename);

	reader.skip_n_bytes(5);
	std::cout << (reader.read_byte() == str[5]) << std::endl;
}

