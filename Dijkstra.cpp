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

int N = 0, M = 0;

int main(){
    cin >> N >> M;

    vector<vector<char>> graph(N, vector<char>(M, '*'));
    vector<vector<int>> cost(N, vector<int>(M));

    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<> randomX(0, N-1), randomY(0, M-1);
    uniform_int_distribution<> randomCost(1, 9);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cost[i][j] = randomCost(gen);
        }
    }

    int sx = randomX(gen), sy = randomY(gen);
    int ex = randomX(gen), ey = randomY(gen);

    ii start = {sx, sy};
    ii endPos = {ex, ey};

    graph[sx][sy] = 'S';
    graph[ex][ey] = 'E';

    cost[sx][sy] = 0;

    for(int i = 0; i < N; i++){
        cout << '\n';

        for(int j = 0; j < M; j++){
            cout << cost[i][j] << " ";
        }
    }

    cout << "\n\nGrafo inicial:\n";
    printGraph(graph);

    vector<vector<int>> dist(N, vector<int>(M, INT_MAX));
    vector<vector<ii>> parent(N, vector<ii>(M, {-1,-1}));
    vector<vector<bool>> vis(N, vector<bool>(M, false));

    priority_queue<pair<int, ii>, vector<pair<int, ii>>, greater<>> pq;

    dist[sx][sy] = 0;
    pq.push({0, start});

    bool found = false;

    while(!pq.empty()){
        pair<int, ii> top = pq.top();

        int d = top.first;
        ii pos = top.second;

        pq.pop();

        int x = pos.first, y = pos.second;

        if(vis[x][y]) continue;
        vis[x][y] = true;

        if(x == ex && y == ey){
            found = true;
            break;
        }

        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];

            if(nx >= 0 && nx < N && ny >= 0 && ny < M && !vis[nx][ny]){
                int newDist = d + cost[nx][ny];

                if(newDist < dist[nx][ny]){
                    dist[nx][ny] = newDist;
                    parent[nx][ny] = {x, y};
                    pq.push({newDist, {nx, ny}});
                }
            }
        }
    }

    if(!found){
        cout << "Sem caminho possivel!\n";
        return 0;
    }

    // reconstroi o caminho a partir do fim
    ii cur = endPos;
    
    while(cur != start){
        int x = cur.first, y = cur.second;
        if(graph[x][y] != 'E') graph[x][y] = '#';
        cur = parent[x][y];
    }

    graph[sx][sy] = 'S';
    graph[ex][ey] = 'E';

    cout << "Caminho encontrado! Custo total: " << dist[ex][ey] << "\n";
    printGraph(graph);

    return 0;
}