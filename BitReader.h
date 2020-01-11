#pragma once
#include "Logger.h"
#include <fstream>
#include <string>
class BitReader
{
public:
	BitReader();								// �������� ��� ��������
	BitReader(const std::string& filename);		// �������� � ���������
	~BitReader();								// ����������� � ��������� �����
	char get_byte();							// ������ ����, � ������ ������ - 0;
	bool get_n_bytes(char* buf, size_t& size);	// ������ n ���� � buf, ���� false ������ size �� ���������� ���������� ����
	bool open(const std::string& filename);		// ��������� ����, ���������� false ���� ���� ��� ������
	void close();								// ��������� ����
	bool go_at_n(size_t n);						// ������������ �� ������� n
	bool go_for_n_back(size_t n);				// ������������ � ����� �� ������� n (0 - ������ �����), ���� ������� ������ ����� ����� - ���������� � �����
	bool go_for_n(size_t n);					// ������������ �� n ���� �����
	void go_end();								// ����������� � ����� �����
	bool is_eof();								// True ���� ��������� ����� �����
	bool is_open();								// True ���� ���� ������
	
private:
	std::string t_nameof_file;					// ��� �����
	std::ifstream t_in;							// ����
	void t_go_end_not_eof();					// ������� ��� �������� � �����, ��� ������ � �����
};

