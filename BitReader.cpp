#include "BitReader.h"

BitReader::BitReader(const std::string& filename){
	t_nameof_file = filename;
	t_in.open(t_nameof_file, std::ios::binary);
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
			t_deb("go at END");
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
			t_deb("eof");
			return false;
		}
		else {
			return true;
		}
	}
}
void BitReader::go_end()
{
	t_in.clear();
	t_in.seekg(1, t_in.end);
}
char BitReader::get_byte() {
	char buf;
	size_t size = 1;
	if (get_n_bytes(&buf, size)) {
		return buf;
	}
	else {
		t_deb("get_error");
		return 0;
	}
}
bool BitReader::get_n_bytes(char* buf,size_t& size) {
	if (buf) {
		if (is_open()) {
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
				return false;
			}
			else {
				return true;
			}
		}
	}
	else {
		size = 0;

		t_deb("null pointer");
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
		t_deb("file isn't open");
		return false;
	}
}

bool BitReader::go_for_n_back(size_t n)
{
	if (is_open()) {
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
}
void BitReader::t_deb(const std::string& str) {
#ifdef DEBUG
	std::cout << str << std::endl;
#endif // DEBUG
}