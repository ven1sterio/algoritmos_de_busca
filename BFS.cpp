#include <bits/stdc++.h>
using namespace std;

// pair de int é uma estrutra de dados que armazena 2 inteiros em uma única variável, bom para por exemplo posições numa matrix
// onde tem X e Y, primeiro valor pegase com .first e segundo valor com .second.

#define ii pair<int, int>

// movimentos que definem onde pode andar: esquerda, direita, cima e baixo.
int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};

// função que apenas mostra o quadrado na tela, só pra isso
void printGraph(vector<vector<char>>& graph){
    for(auto& row : graph){
        for(char c : row) cout << c << ' ';
        cout << '\n';
    }
    cout << "----------------------------\n";
}

void BFS(vector<vector<char>>& graph, ii start, ii end, int N, int M){

    // dp é um array para verificar se eu processo aquela "casa" denovo ou não, se for true eu não vou para ela denovo
    vector<vector<bool>> dp(N, vector<bool>(M, false));
    bool found = false;
    int depth = 0;

    graph[start.first][start.second] = 'S';
    graph[end.first][end.second] = 'E';

    // fila de processamento da busca por profundidade
    queue<ii> q;
    q.push(start);

    dp[start.first][start.second] = true;

    printGraph(graph);

    while(!q.empty() && !found){
        int levelSize = q.size();
        vector<ii> visitedThisLayer;

        // ele processa por niveis de profundidade, uma modificação do BFS original para saber quando 
        // pode imprimir o quadrado na tela, mas o funcionamento continua o mesmo.
        for(int k = 0; k < levelSize; k++){
            if(found) break;

            ii top = q.front();
            q.pop();

            int x = top.first, y = top.second;

            // se eu estou na posição final, encerro o algoritmo
            if(x == end.first && y == end.second){
                found = true;
                break;
            }

            // dou um loop e pego as novas posições
            for(int i = 0; i < 4; i++){
                int nx = x + dx[i], ny = y + dy[i];

                // ele apenas continua a execução daquele quadrado se aquele quadrado for uma posição válida, importante!
                if(nx >= 0 && nx < N && ny >= 0 && ny < M && !dp[nx][ny]){
                    dp[nx][ny] = true;
                    q.push({nx, ny});

                    // marca no graph visual (sem sobrescrever start/end)
                    if(graph[nx][ny] != 'S'){
                        graph[nx][ny] = '#';

                        // se eu estou na posição final, encerro o algoritmo
                        if(end.first == nx && end.second == ny){
                            graph[nx][ny] = 'X';
                            found = true;
                            break;
                        }
                    }
                }
            }
        }

        // apenas exibo o quadrado no final do algoritmo

        depth++;
        cout << "Camada " << depth << ":\n";
        printGraph(graph);
    }
}

int main(){

    // so é necessário informar as dimensões do quadrado ( ou retangulo ) que o algoritmo faz o resto
    // ex: 4 4, ou 100 50, ou 20 80, qualquer combinações de 2 valores que não seja muito grande, senão quebra.
    // cin é responsável por receber valores, igual o scanf em C, e cout responsavel por mostrar valores, igual o printf em C também.

    // recomendo testar com 10 10, fica bem de boa de ver o algoritmo em ação.
    
    int N, M;
    cin >> N >> M;

    vector<vector<char>> graph(N, vector<char>(M, '*'));

    // gera a posição inicial e final de forma aleatória
    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<> randomX(0, N-1), randomY(0,M-1);

    // sx = X inicial, sy = Y inicial, ex = X final, ey = Y final
    int sx = randomX(gen), sy = randomY(gen);
    int ex = randomX(gen), ey = randomY(gen);


    // inicia a busca por profundidade
    BFS(graph, {sx,sy}, {ex,ey}, N, M);


    // depois no final de tudo, mostra as posições escolhidas de forma aleatória para começar e finalziar o jogo.
    cout << "\n\n " << sx << " " << sy << " " << ex << " " << ey;
}