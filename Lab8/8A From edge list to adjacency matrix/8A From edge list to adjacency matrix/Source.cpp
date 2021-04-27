#include<fstream>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

const int MAX_N = 105;

int main() {
	int n, m;
	fin >> n >> m;
	int matrix[MAX_N][MAX_N];
	for (int i(0); i < n; ++i) {
		for (int j(0); j < n; ++j) {
			matrix[i][j] = 0;
		}
	}
	for (int i(0); i < m; ++i) {
		int v, u;
		fin >> v >> u;
		matrix[v - 1][u - 1] = 1;
	}
	for (int i(0); i < n; ++i) {
		for (int j(0); j < n; ++j) {
			fout << matrix[i][j] << ' ';
		}
		fout << '\n';
	}
}