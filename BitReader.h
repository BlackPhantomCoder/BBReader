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

	void close(); // ��������� ����, ������������ ��� �������� ������
	bool go_at_n(size_t n);
	bool go_for_n_back(size_t n);// ������������ � ����� �� ������� n (0 - ������ �����), ���� ������� ������ ����� ����� - ���������� � �����
	bool go_for_n(size_t n);// ������������ �� n ���� �����
	void go_end();

	bool is_eof(); // true ���� ��������� ����� �����
	bool is_open();// true ���� ���� ������
	void t_deb(const std::string& str);
private:
	std::string t_nameof_file;
	std::ifstream t_in;
};

