#include "FileFlow.h"
FileFlow::FileFlow(const std::string& filename) {
	t_nameof_file = filename;
}
bool FileFlow::open() {
	if (!t_is_open()) {
		t_in.clear();
		t_in.open(t_nameof_file, std::ios::binary);
	}
	return t_in.is_open();
}
void FileFlow::close() {
	t_in.close();
}
void FileFlow::at_start() {
	if(t_is_open()) t_in.seekg(0, t_in.beg);
}
char FileFlow::read_byte() {
	if (t_is_open()) {
		return t_in.get();
	}
	else {
		return 0;
	}
}
void FileFlow::read_n_bytes(std::vector<char>& vec, size_t n)
{
	if (t_is_open()) {
		char* buf = new char[n];
		std::streampos pos = t_in.tellg();
		t_in.read(buf, n);
		if (t_in.fail()) {
			t_in.clear();
			t_in.seekg(pos);
			while (!t_in.eof()) {
				vec.push_back(t_in.get());
			}
			#ifdef DEBUG
				std::cout << "trying to read more bits than file consitsts" << std::endl;
			#endif // DEBUG
		}
		else {
			vec.reserve(n);
			for (size_t i = 0; i < n; i++) {
				vec.push_back(buf[i]);
			}
		}
		delete[] buf;
	}
}
void FileFlow::read_while(std::vector<char>& vec, char symbol){
	if (t_is_open()) {
		char next = read_byte();
		while (next != symbol && !t_in.eof() && !t_in.fail()) {
			vec.push_back(next);
			next = read_byte();
		}
		#ifdef DEBUG
			if(t_in.fail())std::cout << "symbol not found" << std::endl;
		#endif // DEBUG
	}
}
bool FileFlow::is_eof() {
	if (t_in.is_open()) {
		return  t_in.eof();
	}
	else {
		#ifdef DEBUG
			std::cout << "file isn't open" << std::endl;
		#endif // DEBUG
		return true;
	}
}
bool FileFlow::is_open() {
	return t_is_open();
}
void FileFlow::skip_byte() {
	if (t_in.is_open()) {
		read_byte();
	}
	#ifdef DEBUG
		if (t_in.fail())std::cout << "reached eof" << std::endl;
	#endif // DEBUG
}
void FileFlow::skip_n_bytes(size_t n) {
	if (t_in.is_open()) {
		t_in.seekg(n, t_in.cur);
	}
	#ifdef DEBUG
		if (t_in.fail())std::cout << "reached eof" << std::endl;
	#endif // DEBUG
}

void FileFlow::go_at_n(size_t n)
{
	if (t_in.is_open()) {
		t_in.seekg(n, t_in.beg);
	}
	#ifdef DEBUG
		if (t_in.fail())std::cout << "reached eof" << std::endl;
	#endif // DEBUG
}

void FileFlow::go_back()
{
	go_back_n(1);
}

void FileFlow::go_back_n(size_t n)
{
	if (t_in.is_open()) {
		std::streampos pos = t_in.tellg();
		pos -= n;
		t_in.seekg(pos, t_in.beg);
	}
	#ifdef DEBUG
		if (t_in.fail())std::cout << "reached eof" << std::endl;
	#endif // DEBUG
}

bool FileFlow::t_is_open()
{
	if (t_in.is_open()) {
		return true;
	}
	else {
		#ifdef DEBUG
			std::cout << "file isn't open" << std::endl;
		#endif // DEBUG
		return false;
	}
}
