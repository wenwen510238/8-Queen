#include <bits/stdc++.h>

#define N 15 //N-Queen
#define Col 14 //N-1
using namespace std;

typedef pair<int, vector< vector<int> > > P;
typedef tuple<int, int, vector< vector<int> > > T;

bool IDS(int [N][N], int, int&, int&);
bool UCS(int [N][N]);
bool GBFS(int [N][N]);
bool Astar(int [N][N]);
int RBFS(int [N][N], int, int&, int&, int);
bool Check(int [N][N], int, int);
void Solution(int [N][N]);
int heuristic(int [N][N], int);

int main(){
	int board[N][N],tmp_board[N][N],n,Movement,Space,pos_row,pos_col;
	memset(board,0,sizeof(board));
	cout<<"initial pos_row(0-14) : ";
	cin>>pos_row;
	cout<<"initial pos_col(0-14) : ";
	cin>>pos_col;
	board[pos_row][pos_col]=1;
	cout<<"Choose a algorithm"<<endl;
    cout << "1:IDS  2:UCS  3:GBFS  4:A*  5:RBFS" << endl;
    while(cin>>n && n>=1 && n<=5){
    	for(int i = 0; i < N; i++){
    		for(int j = 0; j < N; j++)
            	tmp_board[i][j] = board[i][j];
    	}
    	Movement=0;
    	Space=1;
        if(n == 1){
            printf("IDS:\n");
            if(IDS(tmp_board, 0, Movement, Space) == false)  printf("No Solution!\n");
        }
        else if(n == 2){
            printf("\nUCS:\n");
            if(UCS(tmp_board) == false)    printf("No Solution!\n");
        }
        else if(n == 3){
            printf("\nGBFS:\n");
            if(GBFS(tmp_board) == false)   printf("No Solution!\n");
        }
        else if(n == 4){
            printf("\nA*:\n");
            if(Astar(tmp_board) == false)  printf("No Solution!\n");
        }
        else if(n == 5){
            printf("\nRBFS:\n");
            if(RBFS(board, 0, Movement, Space, 1e9) != 0)   printf("No Solution!\n");
        }
        cout<<"Choose a algorithm"<<endl;
        cout << "1:IDS  2:UCS  3:GBFS  4:A*  5:RBFS" << endl;
    }
    system("pause");
    return 0;
}

size_t hashing(int H,int col,vector<vector<int>> board) {
	string result;
	for (size_t i = 0; i < board.size(); ++i) {
		for (size_t j = 0; j < board[i].size(); ++j) {
			string tmp;
            tmp = to_string(board[i][j]);
			result += tmp;
		}
	}
	result += to_string(H);
	result += to_string(col);
	return hash<string>{}(result);
}

void Solution(int board[N][N])  {
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            cout<<board[i][j]<<"    ";
        cout<<endl<<endl;
    }
    cout<<endl<<endl;
}

bool Check(int board[N][N], int row, int col){
    int i, j;
    for (i = 0; i < N; i++)//檢查row那一列有沒有放過皇后
        if (board[row][i])  return false;
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)//檢查斜的(左上方)有沒有放過
        if (board[i][j])    return false;
    for (i = row, j = col; i < N && j < N; i++, j++)//檢查斜的(右下方)有沒有放過
        if (board[i][j])    return false;
    for (i = row, j = col; j >= 0 && i < N; i++, j--)//檢查斜的(左下方)有沒有放過
        if (board[i][j])    return false;
    for (i = row, j = col; j < N && i >= 0; i--, j++)//檢查斜的(右上方)有沒有放過
        if (board[i][j])    return false;
    return true;
}

bool IDS(int board[N][N], int col, int& moves, int& space){
    if (col >= N){
    	cout<<"Movements : "<<moves<<endl;
    	cout<<"Space : "<<space<<endl;
    	Solution(board);
        return true;
    }
    for(int i = 0; i < N; i++){
        if(board[i][col] == 1){
            moves++;
            if (IDS(board, col + 1, moves, space))  return true;
        }
    }
    for (int i = 0; i < N; i++){
        space++;
        if (Check(board, i, col)){
            moves++;
            board[i][col] = 1;
            if (IDS(board, col + 1, moves, space))  return true;
            board[i][col] = 0;
        }
    }
    return false;
}

bool UCS(int chessboard[N][N]){//看G(已經成功放幾個皇后了)
    vector< vector<int> > state(N, vector<int>(N));
    vector< vector<int> > tmp_board;
    priority_queue< P, vector <P>, less<P> > Queue;
    int moves = 0, space = 1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            state[i][j] = chessboard[i][j];
    }
    Queue.push(P(0, state));
    while(!Queue.empty()){
        P temp = Queue.top();
        Queue.pop();
        int board[N][N],col;
        col = temp.first;
        tmp_board = temp.second;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++)
                board[i][j] = tmp_board[i][j];
        }
        moves++;
        int flag = 0;
        for(int i = 0; i < N; i++){
            if(board[i][col] == 1){
                space++;
                if(col == Col){
                    cout<<"Movements : "<<moves<<endl;
                    cout<<"Space : "<<space<<endl;
                    Solution(board);
                    return true;
                }
                else    Queue.push(P(col + 1, tmp_board));
                flag=1;
            }
        }
        if(flag == 0){
            for (int i = 0; i < N; i++){
                if (Check(board, i, col)){
                    space++;
                    board[i][col] = 1;
                    for(int i = 0; i < N; i++){
                        for(int j = 0; j < N; j++)
                            tmp_board[i][j] = board[i][j];
                    }
                    if(col == Col){
                        moves++;
                        cout<<"Movements : "<<moves<<endl;
                        cout<<"Space : "<<space<<endl;
                        Solution(board);
                        return true;
                    }
                    else    Queue.push(P(col + 1, tmp_board));
                    board[i][col] = 0;
                }
            }
        }
    }
    return false;
}

int Heuristic(int board[N][N], int col){//回傳幾個點不能放皇后
    int Count = 0;
    for (int i = col+1; i < N; i++){
        for (int j = 0; j < N; j++){
            if(board[j][i] != 1){
                board[j][i] = 1;
                if (!Check(board, j, i))
                    Count++;
                board[j][i] = 0;
            }
        }
    }
    return Count;
}


bool GBFS(int chessboard[N][N]){//看h(剩下column中的所有點還有幾個可以放)
    vector< vector<int> > state(N, vector<int>(N));
    vector< vector<int> > tmp_board;
    priority_queue< T, vector <T>, greater<T> > Queue;
    int moves = 0, space = 1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            state[i][j] = chessboard[i][j];
    }
    Queue.push(T(0, 0, state));
    while(!Queue.empty()){
        T temp = Queue.top();
        Queue.pop();
        int board[N][N];
        tmp_board = get<2>(temp);
        int col = get<1>(temp);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++)
                board[i][j] = tmp_board[i][j];
        }
        moves++;
        int flag = 0;

        for(int i = 0; i < N; i++){
            if(board[i][col] == 1){
                space++;
                if(col == Col){
                    cout<<"Movements : "<<moves<<endl;
                    cout<<"Space : "<<space<<endl;
                    Solution(board);
                    return true;
                }
                else    Queue.push(T(Heuristic(board, col), col + 1, tmp_board));
                flag=1;
            }
        }
        if(flag == 0){
            for (int i = 0; i < N; i++){
                if (Check(board, i, col)){
                    space++;
                    board[i][col] = 1;
                    for(int i = 0; i < N; i++){
                        for(int j = 0; j < N; j++)
                            tmp_board[i][j] = board[i][j];
                    }
                    if(col == Col){
                        moves++;
                        cout<<"Movements : "<<moves<<endl;
                        cout<<"Space : "<<space<<endl;
                        Solution(board);
                        return true;
                    }
                    else    Queue.push(T(Heuristic(board, col), col + 1, tmp_board));

                    board[i][col] = 0;
                }
            }
        }
    }
    return false;
}

bool Astar(int chessboard[N][N]){//看G+H
    vector< vector<int> > state(N, vector<int>(N));
    vector< vector<int> > tmp_board;
    priority_queue< T, vector <T>, greater<T> > Queue;
    int moves = 0, space = 1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            state[i][j] = chessboard[i][j];
    }
    Queue.push(T(0, 0, state));
    while(!Queue.empty()){
        T temp = Queue.top();
        Queue.pop();
        int board[N][N];
        tmp_board = get<2>(temp);
        int col = get<1>(temp);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++)
                board[i][j] = tmp_board[i][j];
        }
        moves++;
        int flag = 0;

        for(int i = 0; i < N; i++){
            if(board[i][col] == 1){
                space++;
                if(col == Col){
                    cout<<"Movements : "<<moves<<endl;
                    cout<<"Space : "<<space<<endl;
                    Solution(board);
                    return true;
                }
                else    Queue.push(T(Heuristic(board, col) + col + 1, col + 1, tmp_board));
                cout << "flag" << endl;
                flag=1;
            }
        }
        if(flag == 0){
            for (int i = 0; i < N; i++){
                if (Check(board, i, col)){
                    space++;
                    board[i][col] = 1;
                    for(int i = 0; i < N; i++){
                        for(int j = 0; j < N; j++)
                            tmp_board[i][j] = board[i][j];
                    }
                    if(col == Col){
                        moves++;
                        cout<<"Movements : "<<moves<<endl;
                        cout<<"Space : "<<space<<endl;
                        Solution(board);
                        return true;
                    }
                    else    Queue.push(T(Heuristic(board, col) + col + 1, col + 1, tmp_board));
                    board[i][col] = 0;
                }
            }
        }
    }
    return false;
}

int RBFS(int chessboard[N][N], int col, int& moves, int& space, int limit){
    vector< vector<int> > state(N, vector<int>(N));
    static priority_queue< T, vector <T>, greater<T> > Queue;
    static unordered_map<size_t, vector<vector<int>>> visited;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            state[i][j] = chessboard[i][j];
    }
    int flag = 0;
    for(int i = 0; i < N; i++){
        if(chessboard[i][col] == 1){
            space++;
            if(col == Col){
                space-=Queue.size();
                while(!Queue.empty())
                    Queue.pop();
                visited.clear();
                cout<<"Movements : "<<moves<<endl;
                cout<<"Space : "<<space<<endl;
                Solution(chessboard);
                return true;
            }
            else{
                size_t tmpKey = hashing(Heuristic(chessboard, col), col + 1, state);
                if (visited.find(tmpKey) == visited.end()){
                    Queue.push(T(Heuristic(chessboard, col), col + 1, state));
                    visited[tmpKey] = state;
                }
            }
            if(col == 0)    Queue.push(T(Heuristic(chessboard, col), col + 1, state));
            flag=1;
        }
    }

    if(flag == 0){
        for (int i = 0; i < N; i++){
            if (Check(chessboard, i, col)){
                space++;
                chessboard[i][col] = 1;
                for(int i = 0; i < N; i++){
                    for(int j = 0; j < N; j++)
                        state[i][j] = chessboard[i][j];
                }
                if(col == Col){
                    space-=Queue.size();
                    while(!Queue.empty())
                        Queue.pop();
                    visited.clear();
                    moves++;
                    cout<<"Movements : "<<moves<<endl;
                    cout<<"Space : "<<space<<endl;
                    Solution(chessboard);
                    return 0;
                }
                else{
                    size_t tmpKey = hashing(Heuristic(chessboard, col), col + 1, state);
                    if (visited.find(tmpKey) == visited.end()){
                        Queue.push(T(Heuristic(chessboard, col), col + 1, state));
                        visited[tmpKey] = state;
                    }
                }
                chessboard[i][col] = 0;
            }
        }
    }

    while(!Queue.empty()){
        T tem = Queue.top();
        if(get<0>(tem) == 1e9){
            Queue.pop();
            continue;
        }
        if(get<0>(tem) > limit) return get<0>(tem);
        else{
            Queue.pop();
            T tem2 = Queue.top();
            int w[N][N];
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++)
                    w[i][j] = get<2>(tem)[i][j];
            }
            moves++;
            get<0>(tem) = RBFS(w, get<1>(tem), moves, space, min(limit, get<0>(tem2)));
            if(get<0>(tem) == 0)    return 0;
            size_t tmpKey = hashing(get<0>(tem),get<1>(tem),get<2>(tem));
            if (visited.find(tmpKey) == visited.end()){
                Queue.push(tem);
                visited[tmpKey] = (get<0>(tem),get<1>(tem),get<2>(tem));
            }
        }
    }
    return 1e9;
}
