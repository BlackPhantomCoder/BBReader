#pragma once
#include "Logger.h"
#include "BitReader.h"
#include <fstream>
#include <string>
#include <vector>
#include <iterator> 
class BBReader
{
public:
	BBReader(size_t container_size = 2048);								 // �������� ��� �������� �����
	BBReader(const std::string& filename, size_t container_size = 2048); // �������� c ��������� �����
	~BBReader();														 // ����������� � ��������� �����
	bool open(const std::string& filename, size_t container_size = 2048);// �������� �����, ���������� false ���� ��� ������, ���� ����
	void close();														 // P�������� ����
	bool go_at_n(size_t n);												 //	���������� �� ������� n, false ���� ��� n ���� - ���������� � �����
	bool go_for_n_back(size_t n);										 // ���������� �� n ���� �����, false ���� ��� n ���� - ���������� � ������
	bool go_for_n(size_t n);											 // ���������� �� n ���� �����, false ���� ��� n ���� - ���������� � �����
	void go_at_end();													 // ���������� � ����� �����
	bool is_eof();														 // True ���� ��������� ����� �����
	bool is_open();														 // True ���� ���� ������
	char read_byte();													 // ������ ��������� ����, ���� �� ����,���� ��� - 0
	bool read_n_bytes(std::vector<char>& vec, size_t n);				 // ������ n ����, ���� ��� n - ������ �� �����, �������� n � ���������� false
	bool read_n_bytes(std::string& str, size_t n);						 // ������ n ����, ���� ��� n - ������ �� �����, �������� n � ���������� false

private:
	char* read_buffer;													 // ������ ��� ������ �� ����� 
	struct my_str {														 // ��������� ����������
		my_str();														 // �����������
		char get_front();												 // ���������� ������ ���� � ������ ��� �� ����������
		void reserve(size_t size);										 // �������������� n ���� ��� ��������
		void push_back(char symbol);									 // ������� � ����� ���������� 1�� �������
		void push_back_n(const char* symbols, size_t size);				 // ������� � ����� ���������� n ��������
		void clear();													 // ������� ����������
		size_t size();													 // ���������� ����� ����������
		void erase_begin(size_t n);										 // ������� n ��������� � ������
		void erase_end(size_t n);										 // ������� n ��������� � �����
		bool empty();													 // True ���� ��������� ����
		void insert_front_n(size_t n, char symbol);						 // ��������� � ������ �������
	private:
		std::string t_str;												 // ���������� ����������
		size_t t_first;													 // ����������� ����������
	} t_container;														 // ���������
	BitReader* file;													 // ����
	size_t t_container_size;											 // ������ ���������� �� 
	void t_clear_container();											 // ������� ����������
	bool t_fill_container(size_t n);									 // ���������� ���������� �� n ��������
};


