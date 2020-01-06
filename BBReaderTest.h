#pragma once
#include "BBReader.h"
class BBReaderTest
{
public:
	BBReaderTest();
	void test_all();

	void test_close(); // ��������� ����, ������������ ��� �������� ������
	void test_go_at_n();
	void test_go_for_n_back();// ������������ � ����� �� ������� n (0 - ������ �����), ���� ������� ������ ����� ����� - ���������� � �����
	void test_go_for_n();// ������������ �� n ���� �����
	void test_go_at_end();

	void test_is_eof(); // true ���� ��������� ����� �����
	void test_is_open();// true ���� ���� ������

	void test_read_byte(); // ������ ��������� ����, ���� �� ����,���� ��� - 0 (������������ � ������ � is_eof());
	void test_read_n_bytes();
private:
	std::string t_filename;
	std::string  t_text;
};

