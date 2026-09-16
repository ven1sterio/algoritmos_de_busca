#include <bits/stdc++.h>
using namespace std;

#define ii pair<int, int>

int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};

void printGraph(vector<vector<char>>& graph){
    for(auto& row : graph){
        for(char c : row) cout << c << ' ';
        cout << '\n';
    }
    cout << "----------------------------\n";
}


bool found = false;
int N = 0, M = 0;
ii endPos = {-1, -1};

void DFS(vector<vector<char>>& graph, vector<vector<bool>>& vis, ii pos){
    if(found) return;

    int x = pos.first, y = pos.second;

    if(x == endPos.first && y == endPos.second){
        found = true;
        return;
    }

    for(int i = 0; i < 4; i++){
        if(found) return;

        int nx = x + dx[i], ny = y + dy[i];

        if(nx >= 0 && nx < N && ny >= 0 && ny < M && !vis[nx][ny]){
            graph[nx][ny] = '#';
            vis[nx][ny] = true;

            if(nx == endPos.first && ny == endPos.second){
                graph[nx][ny] = 'X';
                found = true;
            }

            printGraph(graph);
            DFS(graph, vis, {nx, ny});
        }
    }
    
}


int main(){
    cin >> N >> M;

    vector<vector<char>> graph(N, vector<char>(M, '*'));

    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<> randomX(0, N-1), randomY(0,M-1);

    int sx = randomX(gen), sy = randomY(gen);
    int ex = randomX(gen), ey = randomY(gen);

    vector<vector<bool>> vis(N, vector<bool>(M, false));
    endPos = {ex, ey};

    graph[sx][sy] = 'S';
    graph[ex][ey] = 'E';

    vis[sx][sy] = true;

    DFS(graph, vis, {sx,sy});


    cout << "\n\n " << sx << " " << sy << " " << ex << " " << ey;

    return 0;
}

