#include<fstream>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

const int MAX_N = 105;

int main() {
	int n;
	fin >> n;
	int matrix[MAX_N][MAX_N];
	for (int i(0); i < n; ++i) {
		for (int j(0); j < n; ++j) {
			fin >> matrix[i][j];
		}
	}

	bool ans = true;
	for (int i(0); i < n; ++i) {
		for (int j(i); j < n; ++j) {
			if (i == j && matrix[i][j] == 1) {
				ans = false;
				break;
			}
			else if (matrix[i][j] != matrix[j][i]) {
				ans = false;
				break;
			}
		}
	}
	fout << (ans ? "YES" : "NO");

	return 0;
}