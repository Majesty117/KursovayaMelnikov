#include "TSP.h"

void Input(vector<vector<int>>& SolutionArray, const string& filename) {
    fstream in(filename);
    int start, v;
    in >> start;
    in >> v;
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            in >> SolutionArray[i][j];
            if (i == j)
                SolutionArray[i][j] = INF; 
        }
    }
    in.close();
}

pair<vector<pair<int, int>>, int> SolutionGreedy(vector<vector<int>>& SolutionArray, int v, int start) {
    int mindist = 0;
    vector<pair<int, int>> route;
    vector<int> visited(v, 0);

    int current = start;
    while (true) {
        visited[current] = 1;
        pair<int, int> cur = { -1, INF };

        for (int i = 0; i < v; i++) {
            if (!visited[i] && SolutionArray[current][i] < cur.second) {
                cur = { i, SolutionArray[current][i] };
            }
        }

        if (cur.first == -1) {
            break;
        }

        route.push_back({ current, cur.second });
        mindist += cur.second;
        current = cur.first;
    }

    mindist += SolutionArray[current][start];
    route.push_back({ current, SolutionArray[current][start] });
    route.push_back({ start, INF });

    return { route, mindist };
}

void GraphvizGreedy(vector<vector<int>>& SolutionArray, int v, int start, const string& filename) {
    ofstream g(filename);

    pair<vector<pair<int, int>>, int> res = SolutionGreedy(SolutionArray, v, start);

    g << "digraph G {" << endl;

    int current = start;

    for (int i = 1; i < res.first.size(); ++i) {
        g << "    " << current << " -> " << res.first[i].first << " [label=\"" << res.first[i - 1].second << "\"];" << endl;
        current = res.first[i].first;
    }

    g << "}" << endl;

    cout << "after greedy alg mincost = " << res.second << endl;

    g.close();
}

void SolutionBAB(vector<vector<int>>& SolutionArray, vector<int>& visited, int v, int start, int curcountnodes, int curcost, int curnode, int& mincost, vector<pair<int, int>>& curPath, vector<pair<int, int>>& bestPath) {
    if (curcountnodes == v && SolutionArray[curnode][start] > 0) {
        if (curcost + SolutionArray[curnode][start] < mincost) {
            mincost = curcost + SolutionArray[curnode][start];
            bestPath = curPath;
            bestPath.push_back({ start, SolutionArray[curnode][start] });
        }
        return;
    }

    for (int next = 0; next < v; ++next) {
        if (!visited[next] && SolutionArray[curnode][next] > 0) {
            visited[next] = 1;
            curPath.push_back({ next, SolutionArray[curnode][next] });

            SolutionBAB(SolutionArray, visited, v, start, curcountnodes + 1,
                curcost + SolutionArray[curnode][next], next, mincost, curPath, bestPath);

            visited[next] = 0;
            curPath.pop_back();
        }
    }
}

void GraphvizBAB(vector<vector<int>>& SolutionArray, int v, int start, const string& filename) {
    ofstream g(filename);
    vector<pair<int, int>> curPath;
    vector<pair<int, int>> bestPath;
    vector<int> visited(v, 0);
    int mincost = INF;

    visited[start] = 1;
    curPath.push_back({ start, 0 });

    SolutionBAB(SolutionArray, visited, v, start, 1, 0, start, mincost, curPath, bestPath);

    g << "digraph G {" << endl;
    int current = start;

    for (int i = 1; i < bestPath.size(); ++i) {
        g << "    " << current << " -> " << bestPath[i].first << " [label=\"" << bestPath[i].second << "\"];" << endl;
        current = bestPath[i].first;
    }

    g << "}" << endl;

    cout << "after BAB mincost = " << mincost << endl;
    g.close();
}
