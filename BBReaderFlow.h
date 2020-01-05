#pragma once
#include "BBReader.h"
class BBReaderFlow : public BBReader
{
public:
	BBReaderFlow(const std::string& filename, size_t container_size = 2048);
	void go_at_start(); // �������� � ������ �����
	bool read_while_not(std::vector<char>& vec, char symbol);// ������ ���� �� ��������� symbol ��� ����� �����, ��� symbol �� ������
	bool read_while_not(std::vector<char>& vec, std::string word);// ������ ���� �� ��������� word ��� ����� �����, ��� word �� ������
	bool skip_while_not(char symbol);// ���������� ���� �� ��������� word ��� ����� �����, ��� symbol �� ������
	bool skip_while_not(std::string word);// ���������� ���� �� ��������� word ��� ����� �����, ��� word �� ������

	bool skip_byte();// ���������� 1 ���� (���� ����)
	bool skip_n_bytes(size_t n);// ���������� n ���� (���� � ����� ������ n ���� �� �� ����� �����)

private:

};

