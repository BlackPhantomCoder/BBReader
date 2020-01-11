#pragma once
#include "BBReader.h"
namespace Reader{
	//Этот класс наследует BBReader, основные функции реализованы в нём
	class BBReaderFlow : public BBReader
	{
	public:
		BBReaderFlow(const std::string& filename, size_t container_size = 4096 * 2); // Конструктор с созданием файла
		void go_at_start();															 // Вернутся в начало файла
		bool read_while_not(std::vector<char>& vec, char symbol);					 // Читает пока не достигнут symbol или конец файла, сам symbol не читает, false, если не найден symbol
		bool read_while_not(std::vector<char>& vec, const std::string& word);		 // Читает пока не достигнут word или конец файла, сам word не читает, false, если не найден word
		bool read_while_not(std::string& str, char symbol);							 // Читает пока не достигнут symbol или конец файла, сам symbol не читает, false, если не найден symbol
		bool read_while_not(std::string& str, const std::string& word);				 // Читает пока не достигнут word или конец файла, сам word не читает, false, если не найден word
		bool skip_while_not(char symbol);											 // Пропускает пока не достигнут word или конец файла, сам symbol не читает, false, если не найден symbol
		bool skip_while_not(const std::string& word);								 // Пропускает пока не достигнут word или конец файла, сам word не читает, false, если не найден word
		bool skip_byte();															 // Пропускает 1 байт, false, если конец файла
		bool skip_n_bytes(size_t n);												 // Пропускает n байт (если в файле меньше n байт то до конца файла), если конец файла
	};
}

