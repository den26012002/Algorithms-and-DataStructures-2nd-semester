#include<fstream>
#include<vector>

std::ifstream fin("knight2.in");
std::ofstream fout("knight2.out");

struct Position {
	int x, y;
};

Position operator+(const Position& pos1, const Position& pos2) {
	return Position{ pos1.x + pos2.x, pos1.y + pos2.y };
}

const Position BACK_MOVES[4] = { {-2, -1}, {-2, 1},  {-1, -2}, {1, -2} };

bool isCorrect(Position pos, int n, int m) {
	return (pos.x < m && pos.x >= 0 && pos.y < n && pos.y >= 0);
}

int main() {
	int n, m;
	fin >> n >> m;
	std::vector<std::vector<int>> board(n, std::vector<int>(m, 0));
	board[0][0] = 1;
	for (int i(0); i < n + m; ++i) {
		for (int j(0); j <= i; ++j) {
			Position pos{ i - j, j };
			if (!isCorrect(pos, n, m)) {
				continue;
			}
			for (int k(0); k < 4; ++k) {
				Position from = pos + BACK_MOVES[k];
				if (isCorrect(from, n, m)) {
					board[pos.y][pos.x] += board[from.y][from.x];
				}
			}
		}
	}
	fout << board[n - 1][m - 1];

	return 0;
}