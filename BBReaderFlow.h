#pragma once
#include "BBReader.h"
namespace Reader{
	//���� ����� ��������� BBReader, �������� ������� ����������� � ��
	class BBReaderFlow : public BBReader
	{
	public:
		BBReaderFlow(const std::string& filename, size_t container_size = 4096 * 2); // ����������� � ��������� �����
		void go_at_start();															 // �������� � ������ �����
		bool read_while_not(std::vector<char>& vec, char symbol);					 // ������ ���� �� ��������� symbol ��� ����� �����, ��� symbol �� ������, false, ���� �� ������ symbol
		bool read_while_not(std::vector<char>& vec, const std::string& word);		 // ������ ���� �� ��������� word ��� ����� �����, ��� word �� ������, false, ���� �� ������ word
		bool read_while_not(std::string& str, char symbol);							 // ������ ���� �� ��������� symbol ��� ����� �����, ��� symbol �� ������, false, ���� �� ������ symbol
		bool read_while_not(std::string& str, const std::string& word);				 // ������ ���� �� ��������� word ��� ����� �����, ��� word �� ������, false, ���� �� ������ word
		bool skip_while_not(char symbol);											 // ���������� ���� �� ��������� word ��� ����� �����, ��� symbol �� ������, false, ���� �� ������ symbol
		bool skip_while_not(const std::string& word);								 // ���������� ���� �� ��������� word ��� ����� �����, ��� word �� ������, false, ���� �� ������ word
		bool skip_byte();															 // ���������� 1 ����, false, ���� ����� �����
		bool skip_n_bytes(size_t n);												 // ���������� n ���� (���� � ����� ������ n ���� �� �� ����� �����), ���� ����� �����
	};
}

