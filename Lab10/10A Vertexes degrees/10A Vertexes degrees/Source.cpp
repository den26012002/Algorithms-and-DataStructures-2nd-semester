#include<fstream>
#include<vector>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

int main() {
	int n, m;
	fin >> n >> m;
	std::vector<int> powers(n);
	for (int i(0); i < m; ++i) {
		int v, u;
		fin >> v >> u;
		++powers[v - 1];
		++powers[u - 1];
	}
	for (int i(0); i < n; ++i) {
		fout << powers[i] << ' ';
	}
}