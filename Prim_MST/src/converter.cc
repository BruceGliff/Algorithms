#include <iostream>
#include <string>


int main(int argc, char ** argv) {
    // program is to convert from matrix to input format
    // launch smth like this: ./a.out {number of vertecies} < matrixInput.txt > rowOutput.txr
    if (argc == 1) {
        std::cout << "no number of vertecies!\n";
        return 0;
    }

    int n = std::stoi(argv[1]);

    for (int i = 0; i != n; ++i) {
        std::cout << i + 1 << ":";
        int v = 0;
        for (int j = 0; j != n; ++j) {
            std::cin >> v;
            if (!v)
                continue;
            std::cout << j+1 << '(' << v << ')';
        }
        std::cout << ';';
    }

}