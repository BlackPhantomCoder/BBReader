#pragma once
#define DEBUG 1
#ifdef DEBUG
#include <iostream>
#endif

#include "BitReader.h"
#include <fstream>
#include <string>
#include <vector>
#include <list>
class BBReader
{
public:
	BBReader(const std::string& filename, size_t container_size = 2048);
	~BBReader();
	void close(); // закрывает файл, используется при удалении потока
	bool go_at_n(size_t n);
	bool go_for_n_back(size_t n);// перемещается в файле на позицию n (0 - начало файла), если позиция дальше конца файла - перемещает в конец
	bool go_for_n(size_t n);// перемещается на n байт вперёд
	void go_at_end();

	bool is_eof(); // true если достигнут конец файла
	bool is_open();// true если файл открыт

	char read_byte(); // читает следующий байт, если он есть,если нет - 0 (использовать в связке с is_eof());
	bool read_n_bytes(std::vector<char>& vec, size_t n);

private:
	BitReader* file;
	std::list<char> t_container;
	size_t t_container_size;
	void t_clear_container();
	bool t_fill_container(size_t n);
	char* read_buffer;
};


