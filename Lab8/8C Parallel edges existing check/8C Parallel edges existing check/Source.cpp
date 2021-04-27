#include<fstream>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

const int MAX_N = 105;

int main() {
	int n, m;
	fin >> n >> m;
	bool matrix[MAX_N][MAX_N];
	for (int i(0); i < n; ++i) {
		for (int j(0); j < n; ++j) {
			matrix[i][j] = false;
		}
	}
	
	bool ans = false;
	for (int i(0); i < m; ++i) {
		int v, u;
		fin >> v >> u;
		--v, --u;
		if (matrix[v][u]) {
			ans = true;
			break;
		}
		matrix[v][u] = true;
		matrix[u][v] = true;
	}
	fout << (ans ? "YES" : "NO");

	return 0;
}