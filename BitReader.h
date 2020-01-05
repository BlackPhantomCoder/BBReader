#pragma once
#pragma once
#define DEBUG 1
#ifdef DEBUG
#include <iostream>
#endif

#include <fstream>
#include <string>
#include <vector>
#include <list>
class BitReader
{
public:
	BitReader(const std::string& filename);
	char get_byte();
	bool get_n_bytes(char* buf, size_t& size);

	void close(); // закрывает файл, используется при удалении потока
	bool go_at_n(size_t n);
	bool go_for_n_back(size_t n);// перемещается в файле на позицию n (0 - начало файла), если позиция дальше конца файла - перемещает в конец
	bool go_for_n(size_t n);// перемещается на n байт вперёд
	void go_end();

	bool is_eof(); // true если достигнут конец файла
	bool is_open();// true если файл открыт
	void t_deb(const std::string& str);
private:
	std::string t_nameof_file;
	std::ifstream t_in;
};

