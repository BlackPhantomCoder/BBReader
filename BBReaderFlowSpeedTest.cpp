#include "BBReaderFlowSpeedTest.h"

BBReaderFlowSpeedTest::BBReaderFlowSpeedTest()
{
	filename = "testspeed.txt";
	std::ofstream out(filename, std::ios::binary);
	str.insert(str.begin(), 1024 * 1024 * 300, '9');
	out << str;
	out.close();
}

void BBReaderFlowSpeedTest::test_speed()
{
	Reader::BBReaderFlow reader(filename);
	std::string buf;
	buf.reserve(1024 * 1024 * 300);
	double start = clock();

	reader.read_n_bytes(buf, 1024 * 1024 * 300);

	double end = clock();

	if (buf == str) {
		std::cout << "success " << double((end - start)/CLOCKS_PER_SEC)  << " sec"<< std::endl;
	}
	else {
		std::cout << " not success "<< std::endl;
	}

}
