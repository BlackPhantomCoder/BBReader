#pragma once
#ifdef DEBUG
#include <iostream>
#endif


#include <fstream>
#include <string>
#include <vector>
/*
Поток взаимедействия с файлом, предоставляет интерфейс удобного взаимодействия с вашим файлом - 
через функции read и skip*/

class FileFlow
{
public:
	FileFlow(const std::string& filename);
	bool open(); // открывает файл, используется при вызове любого read
	void close(); // закрывает файл, используется при удалении потока
	void at_start(); // вернутся в начало файла
	bool is_eof(); // true если достигнут конец файла
	bool is_open();// true если файл открыт

	char read_byte(); // читает следующий байт, если он есть,если нет - 0 (использовать в связке с is_eof());
	void read_n_bytes(std::vector<char>& vec, size_t n);// читает n байт в vector vec (если в файле меньше - ...)
	void read_while(std::vector<char>& vec, char symbol);// читает пока не достигнут symbol или конец файла, сам symbol не читает

	void skip_byte();// пропускает 1 байт (если есть)
	void skip_n_bytes(size_t n);// пропускает n байт (если в файле меньше n байт то до конца файла)
	
	void go_at_n(size_t n); // перемещается в файле на позицию n (0 - начало файла), если позиция дальше конца файла - перемещает в конец
	void go_back(); // возвращается на 1 байт назад
	void go_back_n(size_t n); // возвращается на n байт назад
private:
	std::string t_nameof_file;
	std::ifstream t_in;
	bool t_is_open();
};