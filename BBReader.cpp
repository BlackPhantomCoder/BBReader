#include "BBReader.h"

BBReader::BBReader(const std::string& filename, size_t container_size)
{
	file = new BitReader(filename);
	t_container_size = container_size;

}
void BBReader::close() {
	file->close();
}
bool BBReader::go_at_n(size_t n) {
	if (is_open()) {
		if (!file->go_at_n(n)) {
			file->t_deb("go at END");
			return false;
		}
	}
	t_clear_container();
	return true;
}
bool BBReader::go_for_n_back(size_t n) {
	if (is_open()) {
		if (n < t_container.size()) {
			if (!file->is_eof()) {
				if (file->go_for_n_back(t_container.size())) {
					for (size_t i = 0; i < n; ++i) {
						std::list<char>::iterator it = t_container.begin();
						for (size_t j = 0; j < i; ++j) {
							it++;
						}
						t_container.insert(it, file->get_byte());
					}
					if (file->go_for_n(t_container.size()));
				}
				else {
					file->t_deb("fail back");
				}
			}
			else {
				file->t_deb("eof?");
				file->go_end();
				file->go_for_n_back(t_container.size() + n);
				for (size_t i = 0; i < n; ++i) {
					std::list<char>::iterator it = t_container.begin();
					for (size_t j = 0; j < i; ++j) {
						it++;
					}
					t_container.insert(it, file->get_byte());
				}
				file->go_end();
				return false;
			}
		}
		else {
			if (file->is_eof()) {
				file->go_end();
			}
			if (!file->go_for_n_back(t_container.size() + n)) {
				file->t_deb("fail!");
				return false;
			}
			t_container.clear();
		}
	}
	return true;
}
bool BBReader::go_for_n(size_t n) {
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
			t_container.clear();
		}
		else {
			std::list<char>::iterator last_pos = t_container.begin();
			for (size_t i = 0; i < n; ++i) {
				last_pos++;
			}
			t_container.erase(t_container.begin(), last_pos);
			
		}
	}
	return true;
}

void BBReader::go_at_end()
{
	file->go_end();
}

bool BBReader::is_eof() {
	return file->is_eof() && t_container.empty();
}
bool BBReader::is_open() {
	return file->is_open();
}

char BBReader::read_byte() {
	char result = 0;
	if (t_container.empty()) {
		if (t_fill_container(1)) {
			result = t_container.front();
			t_container.pop_front();
		}
	}
	else {
		result = t_container.front();
		t_container.pop_front();
	}
	return result;
}
bool BBReader::read_n_bytes(std::vector<char>& vec, size_t n) {
	if (t_container.empty() || n > t_container.size()) {
		if (t_fill_container(n - t_container.size())) {
			for (size_t i = 0; i < n; ++i) {
				vec.push_back(t_container.front());
				t_container.pop_front();
			}
		}
		else {
			while (!t_container.empty()) {
				vec.push_back(t_container.front());
				t_container.pop_front();
			}
			file->t_deb("fill_container error -> maybe eof");
			return false;
		}
	}
	else {
		for (size_t i = 0; i < n; ++i) {
			vec.push_back(t_container.front());
			t_container.pop_front();
		}
	}
	return true;
}

void BBReader::t_clear_container() {
	t_container.clear();
}
bool BBReader::t_fill_container(size_t n) {
	bool filled = false;
	if (is_open()) {
		size_t start_size = t_container.size();

		size_t size = n / t_container_size + 1;
		char* buf = new char[t_container_size];
		filled = true;
		for (size_t i = 0; i < size; ++i) {
			size_t size = t_container_size;
			if(!file->get_n_bytes(buf, size)){
				for(size_t i = 0;i < size; i++){
					t_container.push_back(buf[i]);
				}
				if (!(size >= start_size + n)) {
					filled = false;
					file->t_deb("trying to read more bits than file consitsts");
				}
				break;
			}
			else {
				for (size_t j = 0; j < t_container_size; ++j) {
					t_container.push_back(buf[j]);
				}
			}
		}
		delete[] buf;
	}
	return filled;
}