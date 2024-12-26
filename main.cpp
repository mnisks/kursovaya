#include "convexhull.h"

/**
 * @brief Основная функция программы
 *
 * Запрашивает у пользователя имена входного и выходного файлов,
 * выполняет чтение точек, построение выпуклой оболочки, запись результата
 * и генерацию графика с использованием Gnuplot.
 *
 * @return int Код завершения программы: 0 при успешной работе, 1 при ошибках
 */
int main() {
    std::string inputFile;  ///< Имя файла с исходными точками
    std::string outputFile; ///< Имя файла для сохранения выпуклой оболочки

    // Запрос имени входного файла у пользователя
    std::cout << "Enter the name of the input file: ";
    std::cin >> inputFile;

    // Запрос имени выходного файла у пользователя
    std::cout << "Enter the name of the output file: ";
    std::cin >> outputFile;

    try {
        // Чтение точек из входного файла
        std::vector<Point> points = readPoints(inputFile);

        // Построение выпуклой оболочки
        std::vector<Point> hull = computeHull(points);

        // Запись результата в выходной файл
        writePoints(outputFile, hull);

        // Генерация Gnuplot-скрипта для визуализации
        std::string scriptFile = "plot_convex_hull.gp";
        generateGnuplotScript(scriptFile, inputFile, outputFile);

        // Автоматический вызов Gnuplot для построения графика
        std::system(("gnuplot " + scriptFile).c_str());

        // Сообщение об успешной работе программы
        std::cout << "Convex hull saved to " << outputFile << "\n";
        std::cout << "Visualization saved as convex_hull.png\n";
    }
    catch (const std::exception& e) {
        // Обработка ошибок
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}