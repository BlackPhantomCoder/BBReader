#pragma once
#define DEBUG 1
#ifdef DEBUG
#include <iostream>
#endif

#include "BitReader.h"
#include <fstream>
#include <string>
#include <vector>
#include <list>
class BBReader
{
public:
	BBReader(const std::string& filename, size_t container_size = 2048);
	~BBReader();
	void close(); // ��������� ����, ������������ ��� �������� ������
	bool go_at_n(size_t n);
	bool go_for_n_back(size_t n);// ������������ � ����� �� ������� n (0 - ������ �����), ���� ������� ������ ����� ����� - ���������� � �����
	bool go_for_n(size_t n);// ������������ �� n ���� �����
	void go_at_end();

	bool is_eof(); // true ���� ��������� ����� �����
	bool is_open();// true ���� ���� ������

	char read_byte(); // ������ ��������� ����, ���� �� ����,���� ��� - 0 (������������ � ������ � is_eof());
	bool read_n_bytes(std::vector<char>& vec, size_t n);

private:
	BitReader* file;
	std::list<char> t_container;
	size_t t_container_size;
	void t_clear_container();
	bool t_fill_container(size_t n);
	char* read_buffer;
};


