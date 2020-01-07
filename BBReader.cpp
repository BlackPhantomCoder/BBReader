#include "BBReader.h"

BBReader::BBReader(const std::string& filename, size_t container_size)
{
	file = new BitReader(filename);
	t_container_size = container_size;
	read_buffer = new char[container_size];
	t_container.reserve(container_size * 2);
}
BBReader::~BBReader()
{
	if (file) {
		if (file->is_open()) {
			file->close();
		}
		delete file;
		t_container.clear();
	}
	delete[] read_buffer;
}
void BBReader::close() {
	if (is_open()) {
		file->close();
		t_container.clear();
	}
}
bool BBReader::go_at_n(size_t n) {
	if (is_open()) {
		if (!file->go_at_n(n)) {
			file->t_deb("go at END");
			return false;
		}
		t_container.clear();
		return true;
	}
	else {
		return false;
	}
}
bool BBReader::go_for_n_back(size_t n) {
	if (is_open()) {
		if (n < t_container.size()) {
			if (!file->is_eof()) {
				if (file->go_for_n_back(t_container.size())) {
					for (size_t i = 0; i < n; ++i) {
						t_container.insert_front_n(i, file->get_byte());
					}
				}
				else {
					file->t_deb("fail back");
				}
			}
			else {
				file->t_deb("eof?");
				//file->go_end();
				file->go_for_n_back(t_container.size() + n);
				for (size_t i = 0; i < n; ++i) {
					t_container.insert_front_n(i, file->get_byte());
				}
				file->go_end();
				return false;
			}
		}
		else {
			if (!file->go_for_n_back(t_container.size() + n)) {
				file->t_deb("fail!");
				return false;
			}
			t_container.clear();
		}
		return true;
	}
	else {
		return false;
	}
}
bool BBReader::go_for_n(size_t n) {
	if (is_open()) {
		if (n > t_container.size()) {
			if (is_open()) {
				if (!file->go_for_n((n - t_container.size()))) {
					file->t_deb("go at end (for)");
					return false;
				}
			}
			t_clear_container();
		}
		else {
			if (n = t_container.size()) {
				t_clear_container();
			}
			else {
				t_container.erase_begin(n);
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void BBReader::go_at_end()
{
	if (is_open()) {
		file->go_end();
		t_container.clear();
	}
}

bool BBReader::is_eof() {
	if(is_open()){
		return file->is_eof() && t_container.empty();
	}
	else {
		return false;
	}
}
bool BBReader::is_open() {
	if (file) {
		return file->is_open();
	}
	else {
		return false;
	}
}

char BBReader::read_byte() {
	if (is_open()) {
		char result = 0;
		if (t_container.empty()) {
			if (t_fill_container(1)) {
				result = t_container.get_front();
			}
		}
		else {
			result = t_container.get_front();
		}
		return result;
	}
}
bool BBReader::read_n_bytes(std::vector<char>& vec, size_t n) {
	if (is_open()) {
		if (t_container.empty() || n > t_container.size()) {
			if (t_fill_container(n - t_container.size())) {
				for (size_t i = 0; i < n; ++i) {
					vec.push_back(t_container.get_front());
				}
			}
			else {
				while (!t_container.empty()) {
					vec.push_back(t_container.get_front());
				}
				file->t_deb("fill_container error -> maybe eof");
				return false;
			}
		}
		else {
			for (size_t i = 0; i < n; ++i) {
				vec.push_back(t_container.get_front());
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void BBReader::t_clear_container() {
	t_container.clear();
}
bool BBReader::t_fill_container(size_t n) {
	bool filled = false;
	if (is_open()) {
		size_t start_size = t_container.size();
		size_t cycles = n / t_container_size + 1;
		filled = true;
		size_t size = t_container_size;
		for (size_t i = 0; i < cycles; ++i) {
			if(!file->get_n_bytes(read_buffer, size)){
				t_container.push_back_n(read_buffer, size);
				if (!(size >= start_size + n)) {
					filled = false;
					file->t_deb("trying to read more bits than file consitsts");
				}
				break;
			}
			else {
				t_container.push_back_n(read_buffer, size);
			}
		}
	}
	return filled;
}
BBReader::my_str::my_str() {
	t_first = 0;
}
char BBReader::my_str::get_front() {
	if (t_str.size() > t_first) {
		t_first++;
		if (t_str.size() == t_first) {
			char buf = t_str[t_first - 1];
			clear();
			return buf;
		}
		else {
			return t_str[t_first - 1];
		}
	}
	else {
		t_deb("error get_front");
		if (t_str.size() > 0) {
			clear();
		}
		return 0;
	}
}
void BBReader::my_str::reserve(size_t size) {
	t_str.reserve(size);
}
void BBReader::my_str::push_back(char symbol) {
	t_str.push_back(symbol);
}
void BBReader::my_str::push_back_n(const char* symbols, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		t_str.push_back(symbols[i]);
	}
}
void BBReader::my_str::clear() {
	t_first = 0;
	t_str.clear();
}
size_t BBReader::my_str::size() {
	return t_str.size() - t_first;
}
void BBReader::my_str::erase_begin(size_t n) {
	if (t_str.size() >= t_first + n) {
		if (t_str.size() == t_first + n) {
			clear();
		}
		else {
			t_first += n;
		}
	}
	else {
		if (t_str.size() > 0) {
			t_str.clear();
		}
		t_first = 0;
		t_deb("error erase_begin");
	}
}
void BBReader::my_str::erase_end(size_t n) {
	if (n + t_first < t_str.size()) {
		t_str.erase(t_str.end(), t_str.end() + n);
	}
	else {
		t_deb("error erase_end");
		clear();
	}
}
bool BBReader::my_str::empty() {
	return t_str.empty();
}
void BBReader::my_str::insert_front_n(size_t n, char symbol) {
	if (t_first > 0) {
		t_str.erase(t_str.begin(), t_str.begin() + t_first);
		t_first = 0;
	}
	t_str.insert(t_str.begin() + n, symbol);
}

void BBReader::my_str::t_deb(std::string str)
{
#ifdef DEBUG
	std::cout << str <<std::endl;
#endif
}
