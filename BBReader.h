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
	BBReader(size_t container_size = 2048);								 // Создание без открытия файла
	BBReader(const std::string& filename, size_t container_size = 2048); // Создание c открытием файла
	~BBReader();														 // Уничтожение с закрытием файла
	bool open(const std::string& filename, size_t container_size = 2048);// Открытие файла, возвращает false если уже открыт, если есть
	void close();														 // Pакрывает файл
	bool go_at_n(size_t n);												 //	Перемещает на позицию n, false если нет n байт - перемещает в конец
	bool go_for_n_back(size_t n);										 // Возвращает на n байт назад, false если нет n байт - перемещает в начало
	bool go_for_n(size_t n);											 // Возвращает на n байт вперёд, false если нет n байт - перемещает в конец
	void go_at_end();													 // Перемещает в конец файла
	bool is_eof();														 // True если достигнут конец файла
	bool is_open();														 // True если файл открыт
	char read_byte();													 // Читает следующий байт, если он есть,если нет - 0
	bool read_n_bytes(std::vector<char>& vec, size_t n);				 // Читает n байт, если нет n - читает до конца, изменяет n и возвращает false
	bool read_n_bytes(std::string& str, size_t n);						 // Читает n байт, если нет n - читает до конца, изменяет n и возвращает false

private:
	char* read_buffer;													 // Буффер для чтения из файла 
	struct my_str {														 // Структура контейнера
		my_str();														 // Конструктор
		char get_front();												 // Возвращает первый байт и удалёет его из контейнера
		void reserve(size_t size);										 // Резервирование n мест для хранения
		void push_back(char symbol);									 // Вставка в конец контейнера 1го символа
		void push_back_n(const char* symbols, size_t size);				 // Вставка в конец контейнера n символов
		void clear();													 // Очистка контейнера
		size_t size();													 // Возвращает рамер контейнера
		void erase_begin(size_t n);										 // Удаляет n элементов в начале
		void erase_end(size_t n);										 // Удаляет n элементов в конце
		bool empty();													 // True если контейнер пуст
		void insert_front_n(size_t n, char symbol);						 // Вставляет в начало элемент
	private:
		std::string t_str;												 // Реализация контейнера
		size_t t_first;													 // Оптимизация реализации
	} t_container;														 // Контейнер
	BitReader* file;													 // Файл
	size_t t_container_size;											 // Размер контейнера из 
	void t_clear_container();											 // Очистка контейнера
	bool t_fill_container(size_t n);									 // Заполнение контейнера на n символов
};


