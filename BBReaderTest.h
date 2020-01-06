#pragma once
#include "BBReader.h"
class BBReaderTest
{
public:
	BBReaderTest();
	void test_all();

	void test_close(); // закрывает файл, используется при удалении потока
	void test_go_at_n();
	void test_go_for_n_back();// перемещается в файле на позицию n (0 - начало файла), если позиция дальше конца файла - перемещает в конец
	void test_go_for_n();// перемещается на n байт вперёд
	void test_go_at_end();

	void test_is_eof(); // true если достигнут конец файла
	void test_is_open();// true если файл открыт

	void test_read_byte(); // читает следующий байт, если он есть,если нет - 0 (использовать в связке с is_eof());
	void test_read_n_bytes();
private:
	std::string t_filename;
	std::string  t_text;
};

