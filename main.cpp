#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;


void printMaze(vector<string>& maze) {
    for (int i = 0;i < maze.size(); i++) {
        cout << maze[i] << endl;
    }
}

pair<int, int> findStart(vector<string>&maze) {
    for (int i = 0;i < maze.size();i++) {
        for (int j = 0;j < maze[i].size();j++) {
            if (maze[i][j] == 'S') {
                return{ i,j };
            }

        }
    }
    return{ -1,-1 };

}

int dr[] = { -1, 1, 0, 0 };  // row changes
int dc[] = { 0, 0, -1, 1 };  // col changes
void bfs(vector<string>& maze, pair<int, int> start) {
    int rows = maze.size();
    int cols = maze[0].size();

    queue<pair<int,int>> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<pair<int, int>>> cameFrom(rows, vector<pair<int, int>>(cols, { -1,-1 }));

    q.push(start);
    visited[start.first][start.second] = true;
    
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        int row = current.first;
        int col = current.second;

        if (maze[row][col] == 'E') {
            cout << "path Found!" << endl;
            pair<int, int> current = { row, col };
            while (maze[current.first][current.second] != 'S') {
                maze[current.first][current.second] = '*';
                current = cameFrom[current.first][current.second];
            }
            printMaze(maze);
            break;
        }
        for (int d = 0; d < 4; d++) {
            int newRow = row + dr[d];
            int newCol = col + dc[d];

            if (newRow >= 0 && newCol >= 0 && newRow < rows && newCol < cols && !visited[newRow][newCol] && maze[newRow][newCol] != '#') {
                visited[newRow][newCol] = true;
                cameFrom[newRow][newCol] = { row,col };
                q.push({ newRow,newCol });

            }
        }
    }

    
}


int main() {
    vector<string> maze = {
    "###########",
    "#S        #",
    "######### #",
    "#         #",
    "# #########",
    "#         #",
    "######### #",
    "#         #",
    "# #########",
    "#        E#",
    "###########"
    };
        printMaze(maze);
		pair<int, int> start = findStart(maze);
        cout << "Start found at row: " << start.first << " col: " << start.second << endl;
        bfs(maze, start);
    

}
