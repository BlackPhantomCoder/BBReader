#pragma once
#ifdef DEBUG
#include <iostream>
#endif


#include <fstream>
#include <string>
#include <vector>
/*
����� �������������� � ������, ������������� ��������� �������� �������������� � ����� ������ - 
����� ������� read � skip*/

class FileFlow
{
public:
	FileFlow(const std::string& filename);
	bool open(); // ��������� ����, ������������ ��� ������ ������ read
	void close(); // ��������� ����, ������������ ��� �������� ������
	void at_start(); // �������� � ������ �����
	bool is_eof(); // true ���� ��������� ����� �����
	bool is_open();// true ���� ���� ������

	char read_byte(); // ������ ��������� ����, ���� �� ����,���� ��� - 0 (������������ � ������ � is_eof());
	void read_n_bytes(std::vector<char>& vec, size_t n);// ������ n ���� � vector vec (���� � ����� ������ - ...)
	void read_while(std::vector<char>& vec, char symbol);// ������ ���� �� ��������� symbol ��� ����� �����, ��� symbol �� ������

	void skip_byte();// ���������� 1 ���� (���� ����)
	void skip_n_bytes(size_t n);// ���������� n ���� (���� � ����� ������ n ���� �� �� ����� �����)
	
	void go_at_n(size_t n); // ������������ � ����� �� ������� n (0 - ������ �����), ���� ������� ������ ����� ����� - ���������� � �����
	void go_back(); // ������������ �� 1 ���� �����
	void go_back_n(size_t n); // ������������ �� n ���� �����
private:
	std::string t_nameof_file;
	std::ifstream t_in;
	bool t_is_open();
};