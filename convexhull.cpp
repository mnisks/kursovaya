#include "convexhull.h"

/**
 * @brief ���������� ���������� ��� �����
 *
 * ������������ ��� ��������, ��������� �� ����� �� ����� �����, ������� ���������� �� ������� �������
 * ��� ������ ������� �������.
 *
 * @param a ������ �����
 * @param b ������ �����
 * @param c ������ �����
 * @return int ����������:
 * - 0, ���� ����� �����������
 * - 1, ���� ������� �� ������� �������
 * - -1, ���� ������� ������ ������� �������
 */
int orientation(const Point& a, const Point& b, const Point& c) {
    int orientation = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (orientation == 0) return 0;
    return (orientation > 0) ? 1 : -1;
}

/**
 * @brief ��������� ����� �� �����
 *
 * ��������� ����� �� ���������� �����, ��� ������ ������ �������� ���������� ����� �����
 * � ������� "x y". ��������� ���� �� ������������ ������.
 *
 * @param filename ��� �������� �����
 * @return std::vector<Point> ������ ��������� �����
 * @throws std::runtime_error ���� ���� �� ������, ���� ��� ������ �����������
 */
std::vector<Point> readPoints(const std::string& filename) {
    std::ifstream input(filename);
    if (!input.is_open()) {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    std::vector<Point> points;
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Point p;
        if (!(iss >> p.x >> p.y)) {
            throw std::runtime_error("Error: Invalid data in file. Each line must contain two integers.");
        }
        points.push_back(p);
    }

    if (points.empty()) {
        throw std::runtime_error("Error: Input file is empty.");
    }

    return points;
}

/**
 * @brief ���������� ����� �������� �������� � ����
 *
 * ��������� ����� �������� �������� � ��������� ����, ������� ��������� ��������
 * (���������� ������ ����� � ����� ������).
 *
 * @param filename ��� ��������� �����
 * @param hull ������ ����� �������� ��������
 */
void writePoints(const std::string& filename, const std::vector<Point>& hull) {
    if (hull.size() < 3) {
        std::cerr << "Error: Convex hull must contain at least 3 points.\n";
        return;
    }

    std::ofstream output(filename);
    if (!output.is_open()) {
        std::cerr << "Error: Cannot open output file " << filename << "\n";
        return;
    }

    for (const Point& p : hull) {
        output << p.x << " " << p.y << "\n";
    }
    output << hull[0].x << " " << hull[0].y << "\n";

    output.close();
}

/**
 * @brief ���������� ������ ��� Gnuplot
 *
 * ������ ������ ��� Gnuplot, ������� ������������� �������� ����� � ����� �������� ��������.
 * ������ ������ ������ � ����� ������ ������: ����� � �����.
 *
 * @param scriptFile ��� ����� ��� �������
 * @param inputFile ��� ����� � ��������� �������
 * @param hullFile ��� ����� � ������� �������� ��������
 * @throws std::runtime_error ���� �� ������ ������� ���� ��� ������
 */
void generateGnuplotScript(const std::string& scriptFile,
    const std::string& inputFile,
    const std::string& hullFile) {
    std::ofstream gnuplotScript(scriptFile);
    if (!gnuplotScript.is_open()) {
        throw std::runtime_error("Error: Cannot open file " + scriptFile);
    }

    gnuplotScript << "set terminal png\n"
        << "set output 'convex_hull.png'\n"
        << "plot '" << inputFile << "' using 1:2 title 'Points' with points pointtype 7, \\\n"
        << "     '" << hullFile << "' using 1:2 title 'Convex Hull' with linespoints pointtype 5\n";
    gnuplotScript.close();
}

/**
 * @brief ��������� �������� �������� ��������� �����
 *
 * ��������� ���������������� �������� �������. ���������� ���������� �����
 * � ���������������� ���������� ������ � ������� ������ �������� ��������.
 *
 * @param points ������ �����, �� ������� �������� �������� ��������
 * @return std::vector<Point> ����� �������� �������� � ������� ������
 * @throws std::runtime_error ���� ���������� ����� ������ ���
 */
std::vector<Point> computeHull(std::vector<Point>& points) {
    if (points.size() < 3) {
        throw std::runtime_error("Error: At least 3 points are required to compute the convex hull.");
    }

    std::vector<Point> hull;
    std::sort(points.begin(), points.end());

    // ���������� ������ ����� ��������
    for (const Point& p : points) {
        while (hull.size() >= 2 && orientation(hull[hull.size() - 2], hull[hull.size() - 1], p) != -1) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    // ���������� ������� ����� ��������
    size_t lowerHullSize = hull.size();
    for (auto it = points.rbegin(); it != points.rend(); ++it) {
        while (hull.size() > lowerHullSize && orientation(hull[hull.size() - 2], hull[hull.size() - 1], *it) != -1) {
            hull.pop_back();
        }
        hull.push_back(*it);
    }

    // �������� ��������� ����� (����������� ������)
    hull.pop_back();
    return hull;
}