#include<fstream>
#include<vector>
#include<string>

std::ifstream fin("search1.in");
std::ofstream fout("search1.out");

int main() {
	std::string p, t;
	fin >> p >> t;
	std::vector<int> ansPoses;
	for (int i(0); i < t.size(); ++i) {
		bool wasEntry = true;
		for (int j(0); j < p.size(); ++j) {
			if (i + j >= t.size() || p[j] != t[i + j]) {
				wasEntry = false;
				break;
			}
		}
		if (wasEntry) {
			ansPoses.push_back(i + 1);
		}
	}
	fout << ansPoses.size() << '\n';
	for (int i(0); i < ansPoses.size(); ++i) {
		fout << ansPoses[i] << ' ';
	}


	return 0;
}