#include "convexhull.h"

/**
 * @brief �������� ������� ���������
 *
 * ����������� � ������������ ����� �������� � ��������� ������,
 * ��������� ������ �����, ���������� �������� ��������, ������ ����������
 * � ��������� ������� � �������������� Gnuplot.
 *
 * @return int ��� ���������� ���������: 0 ��� �������� ������, 1 ��� �������
 */
int main() {
    std::string inputFile;  ///< ��� ����� � ��������� �������
    std::string outputFile; ///< ��� ����� ��� ���������� �������� ��������

    // ������ ����� �������� ����� � ������������
    std::cout << "Enter the name of the input file: ";
    std::cin >> inputFile;

    // ������ ����� ��������� ����� � ������������
    std::cout << "Enter the name of the output file: ";
    std::cin >> outputFile;

    try {
        // ������ ����� �� �������� �����
        std::vector<Point> points = readPoints(inputFile);

        // ���������� �������� ��������
        std::vector<Point> hull = computeHull(points);

        // ������ ���������� � �������� ����
        writePoints(outputFile, hull);

        // ��������� Gnuplot-������� ��� ������������
        std::string scriptFile = "plot_convex_hull.gp";
        generateGnuplotScript(scriptFile, inputFile, outputFile);

        // �������������� ����� Gnuplot ��� ���������� �������
        std::system(("gnuplot " + scriptFile).c_str());

        // ��������� �� �������� ������ ���������
        std::cout << "Convex hull saved to " << outputFile << "\n";
        std::cout << "Visualization saved as convex_hull.png\n";
    }
    catch (const std::exception& e) {
        // ��������� ������
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}