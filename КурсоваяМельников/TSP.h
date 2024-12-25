#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

const int INF = 1e9;

void Input(vector<vector<int>>& SolutionArray, const string& filename);

pair<vector<pair<int, int>>, int> SolutionGreedy(vector<vector<int>>& SolutionArray, int v, int start);

void GraphvizGreedy(vector<vector<int>>& SolutionArray, int v, int start, const string& filename);

void GraphvizBAB(vector<vector<int>>& SolutionArray, int v, int start, const string& filename);

void SolutionBAB(vector<vector<int>>& SolutionArray, vector<int>& visited, int v, int start, int curcountnodes, int curcost, int curnode, int& mincost, vector<pair<int, int>>& curPath, vector<pair<int, int>>& bestPath);
