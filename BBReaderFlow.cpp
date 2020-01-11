#include "BBReaderFlow.h"
Reader::BBReaderFlow::BBReaderFlow(const std::string& filename, size_t container_size) : BBReader(filename, container_size)
{

}

void Reader::BBReaderFlow::go_at_start()
{
	go_at_n(0);
}

bool Reader::BBReaderFlow::read_while_not(std::vector<char>& vec, char symbol)
{
	if (is_open()) {
		char next = read_byte();
		while (next != symbol && !is_eof()) {
			vec.push_back(next);
			next = read_byte();
		}
	}
	return !is_eof();
}

bool Reader::BBReaderFlow::read_while_not(std::vector<char>& vec, const std::string& word)
{
	if (is_open()) {
		std::string buf;
		bool skip;
		for (size_t i = 0; i < word.size(); i++) {
			buf += read_byte();
		}
		while (!is_eof() && buf != word) {
			skip = true;
			for (size_t i = 0; i < word.size(); i++) {
				if (buf[buf.size() - 1] == word[i]) {
					skip = false;
					break;
				}
			}
			if (!skip) {
				vec.push_back(buf[0]);
				for (size_t i = 0; i < buf.size() - 1; i++) {
					buf[i] = buf[i + 1];
				}
				buf[buf.size() - 1] = read_byte();
			}
			else {
				vec.reserve(buf.size());
				for (size_t i = 0; i < buf.size(); i++) {
					vec.push_back (buf[i]);
				}
				buf.clear();
				if (!read_n_bytes(buf, word.size())) {
					return false;
				}
			}
		}
	}
	return !is_eof();
}

bool Reader::BBReaderFlow::read_while_not(std::string& str, char symbol)
{
	if (is_open()) {
		char next = read_byte();
		while (next != symbol && !is_eof()) {
			str += next;
			next = read_byte();
		}
	}
	return !is_eof();
}

bool Reader::BBReaderFlow::read_while_not(std::string& str, const std::string& word)
{
	if (is_open()) {
		std::string buf;
		bool skip;
		for (size_t i = 0; i < word.size(); i++) {
			buf += read_byte();
		}
		while (!is_eof() && buf != word) {
			skip = true;
			for (size_t i = 0; i < word.size(); i++) {
				if (buf[buf.size() - 1] == word[i]) {
					skip = false;
					break;
				}
			}
			if (!skip) {
				str += buf[0];
				for (size_t i = 0; i < buf.size() - 1; i++) {
					buf[i] = buf[i + 1];
				}
				buf[buf.size() - 1] = read_byte();
			}
			else {
				str.reserve(buf.size());
				for (size_t i = 0; i < buf.size(); i++) {
					str += buf[i];
				}
				buf.clear();
				if (!read_n_bytes(buf, word.size())) {
					return false;
				}
			}
		}
	}
	return !is_eof();
}

bool Reader::BBReaderFlow::skip_while_not(char symbol)
{
	if (is_open()) {
		char next = read_byte();
		while (next != symbol && !is_eof()) {
			next = read_byte();
		}
	}
	return !is_eof();
}

bool Reader::BBReaderFlow::skip_while_not(const std::string& word)
{
	if (is_open()) {
		std::string buf;
		bool skip;
		for (size_t i = 0; i < word.size(); i++) {
			buf += read_byte();
		}
		while (!is_eof() && buf != word) {
			skip = true;
			for (size_t i = 0; i < word.size(); i++) {
				if (buf[buf.size() - 1] == word[i]) {
					skip = false;
					break;
				}
			}
			if (!skip) {
				for (size_t i = 0; i < buf.size() - 1; i++) {
					buf[i] = buf[i + 1];
				}
				buf[buf.size() - 1] = read_byte();
			}
			else {
				buf.clear();
				if (!read_n_bytes(buf, word.size())) {
					return false;
				}
			}
		}
	}
	return !is_eof();
}

bool Reader::BBReaderFlow::skip_byte()
{
	return go_for_n(1);
}

bool Reader::BBReaderFlow::skip_n_bytes(size_t n)
{
	return go_for_n(n);
}
