#include <iostream>
#include <string>
using namespace std;

bool isRunning=true;
int currentlevel=1;
string message=" ";

// Map 1
char map[5][5] = {
    {'P', '.', '#', '.', '.'},
    {'.', '#', '.', '.', '.'},
    {'.', '.', 'O', '#', '.'},
    {'#', '.', '.', '#', '.'},
    {'.', '.', '.', '.', 'E'}
	};

// Map 2
char map2[5][5] = {
    {'P', '.', '.', '.', '.'},
    {'#', '#', '#', '.', '.'},
    {'.', '.', '.', '.', '#'},
    {'.', '#', '#', '.', '.'},
    {'.', '.', '.', '.', 'E'}
};

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

// hàm map 1
void DrawMap1() {
		
		system("clear");
		for (int i=0;i<5;i++) {
			for (int n=0;n<5;n++) {
				cout<<map[i][n]<<" ";
			}
			cout<<endl;
		}
		if (message!=" ") {
			cout<<">>"<<message<<"<<"<<endl;
		}
}
	
//hàm map 2
void DrawMap2(int level) {

	if (level==2) {
		for (int i=0;i<5;i++) {
				for (int j=0;j<5;j++) {
					map[i][j]=map2[i][j];
				}
			}
			message="\n=== CHÚC MỪNG! BẠN ĐÃ QUA MAP 2! ===\n";
	}
}

	// hàm update
	void update (player &P, char huong) {
		int nextRow=P.row;
		int nextCol=P.col;
		
		if (huong=='W'||huong=='w') nextRow--;
		else if (huong=='S'||huong=='s') nextRow++;
		else if (huong=='A'||huong=='a') nextCol--;
		else if (huong=='D'||huong=='d') nextCol++;
		
		if (nextRow<0||nextRow>=5||nextCol<0||nextCol>=5) {
			message="vượt biên rồi!";
		} else if (map[nextRow][nextCol]=='#') {
			message="đụng tường rồi!";
		} else if (map[nextRow][nextCol]=='O') {
			message="===bạn đã thua===";
			isRunning=false;
		} else if (map[nextRow][nextCol]=='E') {
			currentlevel++;
			
			if (currentlevel<=2) {
				DrawMap2(currentlevel);
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

	player P;
	
	// bắt đầu trò chơi
		while (isRunning) {
				
			// tạo map
			DrawMap1();
				
			//hướng di chuyển
			char huong=input();
			
			// vật lý va chạm
			update(P,huong);
			
		}
		DrawMap1();
	
	return 0;
}
// kết thúc trò chơi
