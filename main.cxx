#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <queue>
using namespace std;

const int Map_size=11;
bool isRunning=true;
int currentlevel=1;
string message=" ";
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
int dist[Map_size][Map_size];

// struct nhân vật
struct player {
	int row=0;
	int col=0;
};

// struct quái
struct Quai {
	int r, c;
};
	
struct Point {
    int r, c;
};

bool isValid(char map[][Map_size],int r,int c) {
	if (r>=0||r<Map_size||c>=0||c<Map_size){
   	 if (map[r][c] != '#' && map[r][c] != 'O' && map[r][c] != 'X') {
        
    	}
	}
}

// AI
void AIquai (char map[][Map_size],player P) {
	for (int r=0; r<Map_size; r++) {
		for (int c=0; c<Map_size; c++) {
			dist[r][c]=-1;
		}
	}
	
	queue<pair<int, int>> q;
	q.push({P.row, P.col});
	dist[P.row][P.col]=0;
	
	while (!q.empty()) {
		pair<int, int> curr=q.front();
		q.pop();
		
		int r=curr.first;
		int c=curr.second;
		
		for (int i=0;i<4;i++) {
			int newR=r+dr[i];
			int newC=c+dc[i];
			
			if (isValid(map,newR,newC)&&dist[newR][newC]==-1) {
				dist[newR][newC]=dist[r][c]+1;
				q.push({newR, newC});
			}
		}
	}
}

bool CheckPath(char map[][Map_size], int startR, int startC) {
    
    bool visited[Map_size][Map_size] = {false};
    queue<Point> q;
    q.push({0, 0});

    // Đưa điểm bắt đầu vào hàng đợi
    q.push({startR, startC});
    visited[startR][startC] = true;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        // 1. Kiểm tra nếu đã chạm tới đích 'E'
        if (map[current.r][current.c] == 'E') {
            return true; // Có đường đi thành công!
        }

        // 2. Thử loang ra 4 hướng xung quanh
        for (int i = 0; i < 4; i++) {
            int newR = current.r + dr[i];
            int newC = current.c + dc[i];

            // Kiểm tra: Nằm trong map + Chưa đi qua + Không phải tường/bẫy
            if (newR >= 0 && newR < Map_size && newC >= 0 && newC < Map_size) {
                if (!visited[newR][newC] && map[newR][newC] != '#' && map[newR][newC] != 'O' && map[newR][newC] != 'X') {
                    visited[newR][newC] = true;
                    q.push({newR, newC});
                    
                }
            }
        }
    }
    return false; // Đi hết map rồi mà không tới được 'E' -> Tắc đường!
}

// hàm input
char input() {
	char huong;
	cout<<"phím (W/A/S/D): ";
	cin>>huong;
	return huong;
}

void spamMod(char map[][Map_size],Quai &X) {

	do {
		X.r=rand() %Map_size;
		X.c=rand() %Map_size;
	} while (map[X.r][X.c]!='.');
	map[X.r][X.c]='X';
}
	
// hàm map 
void DrawMap(char map[][Map_size]) {
		
		system("clear");
		for (int i=0;i<Map_size;i++) {
			for (int j=0;j<Map_size;j++) {
				cout<<map[i][j]<<" ";
			}
			cout<<endl;
		}
		if (message!=" ") {
			cout<<">>"<<message<<"<<"<<endl;
		}
}
	
// hàm tạo map
void GenerateMap(char map[][Map_size],int level) {
	for (int i=0;i<Map_size;i++) {
		for (int j=0;j<Map_size;j++) {
			
			int rate=rand() %100;
			if (rate<15) {
				map[i][j]='#';
			} else if (rate<20) {
				map[i][j]='O';
			} else {
				map[i][j]='.';
			}
			
		}
	}
	map[0][0]='P';
	map[Map_size/2][Map_size/2]='E';
	message = "\n===MAP " + to_string(level) + "!===\n";
}

	// hàm update
	void update (player &P, char huong,char map[][Map_size]) {
		int nextRow=P.row;
		int nextCol=P.col;
		
		if (huong=='W'||huong=='w') nextRow--;
		else if (huong=='S'||huong=='s') nextRow++;
		else if (huong=='A'||huong=='a') nextCol--;
		else if (huong=='D'||huong=='d') nextCol++;
		
		if (nextRow<0||nextRow>=Map_size||nextCol<0||nextCol>=Map_size) {
			message="vượt biên rồi!";
		} else if (map[nextRow][nextCol]=='#') {
			message="đụng tường rồi!";
		} else if (map[nextRow][nextCol]=='O') {
			message="===bạn đã thua===";
			isRunning=false;
		} else if (map[nextRow][nextCol]=='X') {
			message="===YOU DIED===";
			isRunning=false;
		} else if (map[nextRow][nextCol]=='E') {
			currentlevel++;
			
			if (currentlevel<=2) {
				GenerateMap(map,currentlevel);
				P.row=0;
				P.col=0;
			} else {
				message="bạn đã hoàn thành game";
				isRunning=false;
			}
		} else {
			message=" ";
			map[P.row][P.col]='.';
			P.row=nextRow;
			P.col=nextCol;
			map[P.row][P.col]='P';
		}
	}

int main() {
	
	// Map
	char map[Map_size][Map_size];
	
	srand(time(0));

	player P;
	Quai X;
	
	do {
    GenerateMap(map, currentlevel);
	} while (!CheckPath(map, 0, 0)); // Nếu map bị tắc, bắt nó Generate lại ngay!
	
	spamMod(map,X);
	
	// bắt đầu trò chơi
		while (isRunning) {
				
			// tạo map
			DrawMap(map);
				
			//hướng di chuyển
			char huong=input();
			
			// vật lý va chạm
			update(P,huong,map);
			
			AIquai(map,P);
		}
		DrawMap(map);
	
	return 0;
}
// kết thúc trò chơi
