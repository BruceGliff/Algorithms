#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <array>
#include <iomanip>

#define INT_MAX 2147483647

/* ALGORITHM */
/*
for_each u in G.V
    u.key = INF
    u.p = nil
r.key = 0
Q = G.V
while Q != 0
    u = extract_min(Q)
    for_each v in G.adj[u]
        if v in Q and w(u,v) < v.key
            v.p = u
            v.key = w(u,v)
//*/



//                                  vertex   list of connected vertexies with weight
using input_t = std::vector<std::pair<int, std::vector<std::pair<int, int>>>>;

void O_n2(input_t const &, std::ostream & os);
input_t parseInput(std::istream & is);
void outMatrix(std::vector<std::vector<int>> const &, std::ostream & os);
std::vector<std::pair<int, int>> parseEdges(std::istream & is);

int main(int argc, char ** argv) {
    input_t ArrayConnections;
    // Gets input data
    if (argc == 1)
        ArrayConnections = parseInput(std::cin);
    else {
        std::ifstream input{argv[1]};
        if (!input.is_open()) {
            std::cerr << "No input file: " << argv[1] << std::endl;
            return -1;
        }
        ArrayConnections = parseInput(input);
    }
    // Compute MST
    if (argc == 3) {
        if (!std::ofstream{std::string{argv[2]}}) {
            std::cerr << "Cannot open output path: " << argv[2] << std::endl;
            return -1;
        }
        O_n2(ArrayConnections, std::ofstream{std::string{argv[2]}});
    } else {
        O_n2(ArrayConnections, std::cout);
    }

    return 0;
}


void O_n2(input_t const & in, std::ostream & os) {
    size_t const n = in.size();
    // matrix of connections
    std::vector<std::vector<int>> conMatrix (n, std::vector<int>(n, INT_MAX));
    std::vector<std::vector<int>> conMatrixMST (n, std::vector<int>(n, INT_MAX));
    for (auto && x : in) {
        for (auto && y : x.second) {
            conMatrix[x.first - 1][y.first - 1] = y.second;
            conMatrix[y.first - 1][x.first - 1] = y.second;
        }
    }

    os << "Input\n";
    outMatrix(conMatrix, os);
    
    unsigned operations = 0;
    // algorithm
    std::vector<bool> used(n, false);
    std::vector<int> shortest (n, INT_MAX);
    std::vector<int> selected (n, -1);
    shortest[0] = 0;
    for (int i = 0; i != n; ++i) {
        int vertex = -1;
        for (int j = 0; j != n; ++j) { // extract_min
            ++operations;
            if (!used[j] && (vertex == -1 || shortest[j] < shortest[vertex]))
                vertex = j;
        }
        if (shortest[vertex] == INT_MAX) {
            std::cerr << "Did not find connected path!";
            return;
        }
    
        used[vertex] = true;
        if (selected[vertex] != -1) { // check if connection occures
            conMatrixMST[vertex][selected[vertex]] = shortest[vertex];
            conMatrixMST[selected[vertex]][vertex] = shortest[vertex];
        }
        for (int to_vertex = 0; to_vertex != n; ++to_vertex)
            if (conMatrix[vertex][to_vertex] < shortest[to_vertex]) { // if path shorter then keep it
                shortest[to_vertex] = conMatrix[vertex][to_vertex];
                selected[to_vertex] = vertex;
            }
    }
    os << "Output\n";
    outMatrix(conMatrixMST, os);
    os << "\nOperations: " << operations << std::endl;
}

input_t parseInput(std::istream & is) {
    int Vertex = 0;
    input_t ArrayConnections;
    while(1) {
        char input = is.peek();
        if (input == ' ') { // skip spaces
            is.get();
            continue;
        }
        if (!is.good()) { // input is over
            break;
        }
        if (input == ':') {
            // assume that Vertex has been already read
            is.get(); // skip ':'
            ArrayConnections.emplace_back(std::make_pair(Vertex, parseEdges(is)));
        } else {
            is >> Vertex;
        }
    }
    return ArrayConnections;
}

std::vector<std::pair<int, int>> parseEdges(std::istream & is) {
    std::vector<std::pair<int, int>> toReturn;

    char input = is.peek();
    while (input != ';') {
        if (input == ' ') {
            is.get();
            input = is.peek();
            continue;
        }
        int vertex = 0;
        int weight = 0;

        is >> vertex >> input >> weight >> input; // number bracket number bracket
        toReturn.emplace_back(std::make_pair(vertex, weight));
        input = is.peek();
    }

    is.get(); // skip ';'
    return toReturn;
}


void outMatrix(std::vector<std::vector<int>> const & mat, std::ostream & os) {
    for (auto && row : mat) {
        for (auto && y : row) {
            if (y == INT_MAX) {
                os << " --- ";
            } else {
                os << std::setfill('0') << std::setw(5) << y;
            }
            os << ' ';
        }
        os << "\n";
    }
}