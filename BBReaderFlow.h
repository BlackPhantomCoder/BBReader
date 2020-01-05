#pragma once
#include "BBReader.h"
class BBReaderFlow : public BBReader
{
public:
	BBReaderFlow(const std::string& filename, size_t container_size = 2048);
	void go_at_start(); // вернутся в начало файла
	bool read_while_not(std::vector<char>& vec, char symbol);// читает пока не достигнут symbol или конец файла, сам symbol не читает
	bool read_while_not(std::vector<char>& vec, std::string word);// читает пока не достигнут word или конец файла, сам word не читает
	bool skip_while_not(char symbol);// пропускает пока не достигнут word или конец файла, сам symbol не читает
	bool skip_while_not(std::string word);// пропускает пока не достигнут word или конец файла, сам word не читает

	bool skip_byte();// пропускает 1 байт (если есть)
	bool skip_n_bytes(size_t n);// пропускает n байт (если в файле меньше n байт то до конца файла)

private:

};

