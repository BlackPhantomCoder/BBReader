#include "BitReader.h"


BitReader::BitReader() {

}
BitReader::BitReader(const std::string& filename){
	t_nameof_file = filename;
	t_in.open(t_nameof_file, std::ios::binary);
}
BitReader::~BitReader()
{
	t_in.close();
}
bool BitReader::open(const std::string& filename)
{
	t_nameof_file = filename;
	if(!t_in.is_open()) {
		t_in.open(t_nameof_file, std::ios::binary);
	}
	else {
		LOG("file already open");
	}
	return t_in.is_open();
}
void BitReader::close() {
	t_in.close();
}
bool BitReader::go_at_n(size_t n)
{
	if (is_open()) {
		t_in.clear();
		t_in.seekg(n, t_in.beg);
		if (t_in.fail() || t_in.eof()) {
			t_in.clear();
			t_in.seekg(0, t_in.end);
			LOG("go at END");
			return false;
		}
		else {
			return true;
		}
	}
}
bool BitReader::go_for_n(size_t n)
{
	if (is_open()) {
		t_in.seekg(n,t_in.cur);
		if (t_in.bad()) {
			t_in.clear();
			t_in.seekg(0, t_in.end);
			LOG("eof");
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}
void BitReader::go_end()
{
	t_in.clear();
	t_in.seekg(0, t_in.end);
	t_in.get();
}
char BitReader::get_byte() {
	char buf;
	size_t size = 1;
	if (get_n_bytes(&buf, size)) {
		return buf;
	}
	else {
		LOG("get_error");
		return 0;
	}
}
bool BitReader::get_n_bytes(char* buf,size_t& size) {
	if (buf) {
		if (is_open()) {
			if (t_in.eof()) {
				size = 0;
				return false;
			}
			std::streampos pos = t_in.tellg();
			t_in.read(buf, size);
			if (t_in.fail()) {
				t_in.clear();
				t_in.seekg(pos, t_in.beg);
				size = 0;
				while (!t_in.eof()) {
					t_in.read(&buf[size], 1);
					size++;
				}
				size--;
				return false;
			}
			else {
				return true;
			}
		}
	}
	else {
		size = 0;
		LOG("bull pointer");
		return false;
	}
}
bool BitReader::is_eof() {
	if (is_open()) {
		return t_in.eof() && t_in.fail();
	}
	else {
		return true;
	}
}
bool BitReader::is_open() {

	if (t_in.is_open()) {
		return true;
	}
	else {
		LOG("file isn't open");
		return false;
	}
}

bool BitReader::go_for_n_back(size_t n)
{
	if (is_open()) {
		if (t_in.eof()) {
			t_go_end_not_eof();
		}
		std::streampos pos = t_in.tellg();
		pos -= n;
		t_in.clear();
		t_in.seekg(pos, t_in.beg);
		if (t_in.fail()) {
			t_in.clear();
			t_in.seekg(0, t_in.beg);
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}
void BitReader::t_go_end_not_eof()
{
	if(is_open()) {
		t_in.clear();
		t_in.seekg(0, t_in.end);
	}
}
