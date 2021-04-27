#include<fstream>
#include<string>
#include<vector>

std::ifstream fin("prefix.in");
std::ofstream fout("prefix.out");

int main() {
	std::string s;
	fin >> s;
	std::vector<int> pi(s.size(), 0);
	int k;
	for (int i(1); i < s.size(); ++i) {
		k = pi[i - 1];
		while (k > 0 && s[i] != s[k]) {
			k = pi[k - 1];
		}
		if (s[i] == s[k]) {
			++k;
		}
		pi[i] = k;
	}
	for (int i(0); i < s.size(); ++i) {
		fout << pi[i] << ' ';
	}

	return 0;
}