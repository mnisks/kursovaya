#include "convexhull.h"

/**
 * @brief Определяет ориентацию трёх точек
 *
 * Используется для проверки, находятся ли точки на одной линии, поворот происходит по часовой стрелке
 * или против часовой стрелки.
 *
 * @param a Первая точка
 * @param b Вторая точка
 * @param c Третья точка
 * @return int Возвращает:
 * - 0, если точки коллинеарны
 * - 1, если поворот по часовой стрелке
 * - -1, если поворот против часовой стрелки
 */
int orientation(const Point& a, const Point& b, const Point& c) {
    int orientation = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (orientation == 0) return 0;
    return (orientation > 0) ? 1 : -1;
}

/**
 * @brief Считывает точки из файла
 *
 * Считывает точки из текстового файла, где каждая строка содержит координаты одной точки
 * в формате "x y". Проверяет файл на корректность данных.
 *
 * @param filename Имя входного файла
 * @return std::vector<Point> Вектор считанных точек
 * @throws std::runtime_error Если файл не найден, пуст или данные некорректны
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
 * @brief Записывает точки выпуклой оболочки в файл
 *
 * Сохраняет точки выпуклой оболочки в текстовый файл, включая замыкание оболочки
 * (повторение первой точки в конце списка).
 *
 * @param filename Имя выходного файла
 * @param hull Вектор точек выпуклой оболочки
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
 * @brief Генерирует скрипт для Gnuplot
 *
 * Создаёт скрипт для Gnuplot, который визуализирует исходные точки и точки выпуклой оболочки.
 * Скрипт строит график с двумя типами данных: точки и линии.
 *
 * @param scriptFile Имя файла для скрипта
 * @param inputFile Имя файла с исходными точками
 * @param hullFile Имя файла с точками выпуклой оболочки
 * @throws std::runtime_error Если не удаётся открыть файл для записи
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
 * @brief Вычисляет выпуклую оболочку множества точек
 *
 * Реализует модифицированный алгоритм Грэхема. Использует сортировку точек
 * и последовательное построение нижней и верхней частей выпуклой оболочки.
 *
 * @param points Вектор точек, из которых строится выпуклая оболочка
 * @return std::vector<Point> Точки выпуклой оболочки в порядке обхода
 * @throws std::runtime_error Если количество точек меньше трёх
 */
std::vector<Point> computeHull(std::vector<Point>& points) {
    if (points.size() < 3) {
        throw std::runtime_error("Error: At least 3 points are required to compute the convex hull.");
    }

    std::vector<Point> hull;
    std::sort(points.begin(), points.end());

    // Построение нижней части оболочки
    for (const Point& p : points) {
        while (hull.size() >= 2 && orientation(hull[hull.size() - 2], hull[hull.size() - 1], p) != -1) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    // Построение верхней части оболочки
    size_t lowerHullSize = hull.size();
    for (auto it = points.rbegin(); it != points.rend(); ++it) {
        while (hull.size() > lowerHullSize && orientation(hull[hull.size() - 2], hull[hull.size() - 1], *it) != -1) {
            hull.pop_back();
        }
        hull.push_back(*it);
    }

    // Удаление последней точки (дублирующей первую)
    hull.pop_back();
    return hull;
}