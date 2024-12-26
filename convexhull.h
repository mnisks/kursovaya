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
 * @brief ��������� ��� ������������� ����� �� ���������
 *
 * ������ ���������� ����� (x, y) � ��������� �������� ��������� ��� ����������.
 */
struct Point {
    int x; ///< ���������� X
    int y; ///< ���������� Y

    /**
     * @brief �������� ��������� �����
     *
     * ���������� ����� �� ����������� X, ��� ������ X ���������� �� Y.
     * @param other ������ ����� ��� ���������
     * @return true, ���� ������� ����� ������ ������
     */
    bool operator<(const Point& other) const {
        return (x < other.x) || (x == other.x && y < other.y);
    }
};

/**
 * @brief ������� ��� ������ ����� �� ���������� �����
 *
 * ��������� ����� � ������� "x y" �� ���������� ����� � ��������� �� � ������.
 * @param filename ��� �����, ����������� �����
 * @return std::vector<Point> ������ ��������� �����
 * @throws std::runtime_error ���� ���� �� ������ ��� ������ ������ �����������
 */
std::vector<Point> readPoints(const std::string& filename);

/**
 * @brief ������� ��� ������ ����� �������� �������� � ����
 *
 * ��������� ����� �������� �������� � ��������� ����, �� ����� ����� �� ������.
 * @param filename ��� ����� ��� ������
 * @param hull ������ ����� �������� ��������
 */
void writePoints(const std::string& filename, const std::vector<Point>& hull);

/**
 * @brief ��������� ������� Gnuplot ��� ������������ �������� ��������
 *
 * ������ ������ ��� Gnuplot, ������� ������������� �������� ����� � ����������� �������� ��������.
 * @param scriptFile ��� ����� ��� �������
 * @param inputFile ��� ����� � ��������� �������
 * @param hullFile ��� ����� � ������� �������� ��������
 */
void generateGnuplotScript(const std::string& scriptFile,
    const std::string& inputFile,
    const std::string& hullFile);

/**
 * @brief ������� ��� ���������� �������� ��������
 *
 * ���������� ���������������� �������� ������� ��� ���������� �������� �������� ��������� �����.
 * @param points ������ �����, �� ������� �������� �������� ��������
 * @return std::vector<Point> ����� �������� �������� � ������� ������
 * @throws std::runtime_error ���� ���������� ����� ������ ���
 */
std::vector<Point> computeHull(std::vector<Point>& points);

#endif

