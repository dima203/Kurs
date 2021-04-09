/*
    Файл с функциями меню (вывод меню для различных действий)
*/

#include "menu.h"
#include <iomanip>
#include <iostream>


// Вывод меню действий
void print_menu()
{
    std::cout << std::endl;
    std::cout << "=====================MENU=====================" << std::endl;
    std::cout << std::endl;
    std::cout 
    << "1" << '\t' << "вывод всех поездов" << std::endl
    << "2" << '\t' << "добавление нового поезда" << std::endl
    << "3" << '\t' << "удаление поезда" << std::endl
    << "4" << '\t' << "сортировка поездов" << std::endl
    << "0" << '\t' << "выход из программы" << std::endl;
    std::cout << std::endl;
}


// Вывод меню типов сортировки 
void print_sort_menu()
{
    std::cout << std::endl;
    std::cout << "==================SORT MENU===================" << std::endl;
    std::cout << std::endl;
    std::cout 
    << "1" << '\t' << "сортировка по номеру" << std::endl
    << "2" << '\t' << "сортировка по конечной станции" << std::endl
    << "3" << '\t' << "сортировка по времени отправления" << std::endl
    << "4" << '\t' << "сортировка по времени в пути" << std::endl
    << "5" << '\t' << "сортировка по количеству остановок" << std::endl
    << "0" << '\t' << "отмена" << std::endl;  
    std::cout << std::endl;
}


// Вывод меню флагов сортировки
void print_reverse_menu()
{
    std::cout << std::endl;
    std::cout << "===================REVERSE====================" << std::endl;
    std::cout << std::endl;
    std::cout 
    << "0" << '\t' << "прямая сортировка (от меньшего к большему)" << std::endl
    << "1" << '\t' << "обратная сортировка (от большего к меньшему)" << std::endl;
    std::cout << std::endl;
}


// Вывод меню флагов записи в файл
void print_file_menu()
{
    std::cout << std::endl;
    std::cout << "=====================FILE=====================" << std::endl;
    std::cout << std::endl;
    std::cout 
    << "0" << '\t' << "без записи в файл" << std::endl
    << "1" << '\t' << "с записью в файл" << std::endl;
    std::cout << std::endl;
}


// Вывод меню типов удаления
void print_delete_menu()
{
    std::cout << std::endl;
    std::cout << "====================DELETE====================" << std::endl;
    std::cout << std::endl;
    std::cout 
    << "1" << '\t' << "удаление записи по номеру" << std::endl
    << "2" << '\t' << "удаление записей по названию станции" << std::endl
    << "3" << '\t' << "удаление записей по времени отправления" << std::endl
    << "4" << '\t' << "удаление записей по времени в пути" << std::endl
    << "5" << '\t' << "удаление записей по количеству остановок" << std::endl
    << "0" << '\t' << "отмена" << std::endl;   
    std::cout << std::endl;
} 