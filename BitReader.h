#pragma once
#include "Logger.h"
#include <fstream>
#include <string>
class BitReader
{
public:
	BitReader();								// Создание без открытия
	BitReader(const std::string& filename);		// Создание с открытием
	~BitReader();								// Уничтожение с закрытием файла
	char get_byte();							// Читает байт, в случае ошибки - 0;
	bool get_n_bytes(char* buf, size_t& size);	// Читает n байт в buf, если false меняет size на количество записанных байт
	bool open(const std::string& filename);		// Открывает файл, возвращает false если если уже открыт
	void close();								// Закрывает файл
	bool go_at_n(size_t n);						// Перемещается на позицию n
	bool go_for_n_back(size_t n);				// Перемещается в файле на позицию n (0 - начало файла), если позиция дальше конца файла - перемещает в конец
	bool go_for_n(size_t n);					// Перемещается на n байт вперёд
	void go_end();								// Перемещение в конец файла
	bool is_eof();								// True если достигнут конец файла
	bool is_open();								// True если файл открыт
	
private:
	std::string t_nameof_file;					// Имя файла
	std::ifstream t_in;							// Файл
	void t_go_end_not_eof();					// Функция для перехода в конец, без ошибки в файле
};

