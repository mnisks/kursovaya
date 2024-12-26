#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>

/**
 * @struct Point
 * @brief Структура для представления точки на плоскости
 *
 * Хранит координаты точки (x, y) и реализует оператор сравнения для сортировки.
 */
struct Point {
    int x; ///< Координата X
    int y; ///< Координата Y

    /**
     * @brief Оператор сравнения точек
     *
     * Сравнивает точки по координатам X, при равных X сравнивает по Y.
     * @param other Другая точка для сравнения
     * @return true, если текущая точка меньше другой
     */
    bool operator<(const Point& other) const {
        return (x < other.x) || (x == other.x && y < other.y);
    }
};

/**
 * @brief Функция для чтения точек из текстового файла
 *
 * Считывает точки в формате "x y" из указанного файла и сохраняет их в вектор.
 * @param filename Имя файла, содержащего точки
 * @return std::vector<Point> Вектор считанных точек
 * @throws std::runtime_error Если файл не найден или формат данных некорректен
 */
std::vector<Point> readPoints(const std::string& filename);

/**
 * @brief Функция для записи точек выпуклой оболочки в файл
 *
 * Сохраняет точки выпуклой оболочки в текстовый файл, по одной точке на строке.
 * @param filename Имя файла для записи
 * @param hull Вектор точек выпуклой оболочки
 */
void writePoints(const std::string& filename, const std::vector<Point>& hull);

/**
 * @brief Генерация скрипта Gnuplot для визуализации выпуклой оболочки
 *
 * Создаёт скрипт для Gnuplot, который визуализирует исходные точки и построенную выпуклую оболочку.
 * @param scriptFile Имя файла для скрипта
 * @param inputFile Имя файла с исходными точками
 * @param hullFile Имя файла с точками выпуклой оболочки
 */
void generateGnuplotScript(const std::string& scriptFile,
    const std::string& inputFile,
    const std::string& hullFile);

/**
 * @brief Функция для вычисления выпуклой оболочки
 *
 * Использует модифицированный алгоритм Грэхема для вычисления выпуклой оболочки множества точек.
 * @param points Вектор точек, из которых строится выпуклая оболочка
 * @return std::vector<Point> Точки выпуклой оболочки в порядке обхода
 * @throws std::runtime_error Если количество точек меньше трёх
 */
std::vector<Point> computeHull(std::vector<Point>& points);

#endif

