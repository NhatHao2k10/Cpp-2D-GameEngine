#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

const int Map_size=10;
bool isRunning=true;
int currentlevel=1;
string message=" ";

// Map
char map[Map_size][Map_size];

// struct nhân vật
struct player {
	int row=0;
	int col=0;
};

// hàm input
char input() {
	char huong;
	cout<<"phím (W/A/S/D): ";
	cin>>huong;
	return huong;
}

// hàm map 
void DrawMap() {
		
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
void GenerateMap(int level) {
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
	map[Map_size-1][Map_size-1]='E';
	message = "\n===MAP " + to_string(level) + "!===\n";
}

	// hàm update
	void update (player &P, char huong) {
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
		} else if (map[nextRow][nextCol]=='E') {
			currentlevel++;
			
			if (currentlevel<=2) {
				GenerateMap(currentlevel);
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
	
	srand(time(0));

	player P;
	
	GenerateMap(currentlevel);
	
	// bắt đầu trò chơi
		while (isRunning) {
				
			// tạo map
			DrawMap();
				
			//hướng di chuyển
			char huong=input();
			
			// vật lý va chạm
			update(P,huong);
			
		}
		DrawMap();
	
	return 0;
}
// kết thúc trò chơi
