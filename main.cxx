#include <iostream>
using namespace std;

// code map
char map[5][5] = {
    {'P', '.', '#', '.', '.'},
    {'.', '#', '.', '.', '.'},
    {'.', '.', 'O', '#', '.'},
    {'#', '.', '.', '#', '.'},
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

// hàm map
void DrawMap() {
		for (int i=0;i<5;i++) {
			for (int n=0;n<5;n++) {
				cout<<map[i][n]<<" ";
			}
			cout<<endl;
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
			cout<<"vượt biên rồi!"<<endl;
		} else if (map[nextRow][nextCol]=='#') {
			cout<<"đụng tường rồi!"<<endl;
		} else {
			map[P.row][P.col]='.';
			P.row=nextRow;
			P.col=nextCol;
			map[P.row][P.col]='P';
		}
	}

int main() {

	player P;
	
	// bắt đầu trò chơi
		while ((P.row!=4||P.col!=4) && (P.row!=2||P.col!=2)) {
				
			// tạo map
			DrawMap();
				
			//hướng di chuyển
			char huong=input();
			
			// vật lý va chạm
			update(P,huong);
			
		}
	if (P.row==2 && P.col==2) {
		cout<<"\n---bạn đã thua---";
	} else if (P.row==4 && P.col==4) {
		cout<<"\n---bạn đã thắng---";
	}
	
	return 0;
}
// kết thúc trò chơi
