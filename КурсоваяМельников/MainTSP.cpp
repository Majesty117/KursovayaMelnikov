#include "TSP.h"

int main() {
    fstream in("input.txt");
    int v, start;
    in >> start;
    in >> v;

    vector<vector<int>> SolutionArray(v, vector<int>(v, 0));

    Input(SolutionArray, "input.txt");

    GraphvizBAB(SolutionArray, v, start, "graphBranchAndBounds.dot");

    GraphvizGreedy(SolutionArray, v, start, "graphGreedy.dot");

    return 0;
}
