#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <iostream>
using namespace std;

char grid[3][3];
int mode = 1;
int offsetX = (1920 - 300) / 2;
int offsetY = (1080 - 300) / 2;
int prevMode = -1;  // tracks last selected mode



char playerX[20] = "Player X";
char playerO[20] = "Player O";

int winsX = 0;
int winsO = 0;


void initGrid() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            grid[i][j] = ' ';
}
void drawResetButton() {
    setfillstyle(SOLID_FILL, RED);
    bar(10, 10, 130, 60);  // red rectangle top-left

    setcolor(WHITE);
    rectangle(10, 10, 130, 60);  // white border

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(35, 25, "RESET");
}
bool isResetClicked(int x, int y) {
    return (x >= 10 && x <= 130 && y >= 10 && y <= 60);
}


void drawBoard() {
    cleardevice();
    setlinestyle(SOLID_LINE, 0, 3);
    setcolor(BLUE);
    line(offsetX + 100, offsetY + 0, offsetX + 100, offsetY + 300);
    line(offsetX + 200, offsetY + 0, offsetX + 200, offsetY + 300);
    line(offsetX + 0, offsetY + 100, offsetX + 300, offsetY + 100);
    line(offsetX + 0, offsetY + 200, offsetX + 300, offsetY + 200);

    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(grid[i][j] != ' ') {
                char ch[2] = {grid[i][j], '\0'};
                if(grid[i][j] == 'X')
                    setcolor(LIGHTCYAN);
                else if(grid[i][j] == 'O')
                    setcolor(LIGHTRED);
                outtextxy(offsetX + 30 + j*100, offsetY + 30 + i*100, ch);
            }
        }
    }
}

char checkWin() {
    for(int i=0;i<3;i++) {
        if(grid[i][0]==grid[i][1] && grid[i][1]==grid[i][2] && grid[i][0]!=' ')
            return grid[i][0];
        if(grid[0][i]==grid[1][i] && grid[1][i]==grid[2][i] && grid[0][i]!=' ')
            return grid[0][i];
    }
    if(grid[0][0]==grid[1][1] && grid[1][1]==grid[2][2] && grid[0][0]!=' ')
        return grid[0][0];
    if(grid[0][2]==grid[1][1] && grid[1][1]==grid[2][0] && grid[0][2]!=' ')
        return grid[0][2];
    return ' ';
}

bool isDraw() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(grid[i][j]==' ')
                return false;
    return true;
}

bool moveleft(){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(grid[i][j]==' ')
                return true;
    return false;
}

int scoreAI(){
    for (int row=0;row<3;row++)
        if (grid[row][0]==grid[row][1] && grid[row][1]==grid[row][2]) {
            if (grid[row][0]=='O') return +10;
            else if (grid[row][0]=='X') return -10;
        }
    for (int col=0;col<3;col++)
        if (grid[0][col]==grid[1][col] && grid[1][col]==grid[2][col]) {
            if (grid[0][col]=='O') return +10;
            else if (grid[0][col]=='X') return -10;
        }
    if (grid[0][0]==grid[1][1] && grid[1][1]==grid[2][2]) {
        if (grid[0][0]=='O') return +10;
        else if (grid[0][0]=='X') return -10;
    }
    if (grid[0][2]==grid[1][1] && grid[1][1]==grid[2][0]) {
        if (grid[0][2]=='O') return +10;
        else if (grid[0][2]=='X') return -10;
    }
    return 0;
}

int minimax(bool isMax){
    int score = scoreAI();
    if(score==10 || score ==-10)
        return score;
    if(!moveleft())
        return 0;
    if(isMax){
        int best = -1000;
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                if (grid[i][j]==' ') {
                    grid[i][j]='O';
                    best = max(best, minimax(false));
                    grid[i][j]=' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                if (grid[i][j]==' ') {
                    grid[i][j]='X';
                    best = min(best, minimax(true));
                    grid[i][j]=' ';
                }
            }
        }
        return best;
    }
}

void bestMove() {
    int bestVal = -1000;
    int moveRow = -1, moveCol = -1;
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (grid[i][j]==' ') {
                grid[i][j]='O';
                int moveVal = minimax(false);
                grid[i][j]=' ';
                if (moveVal > bestVal) {
                    moveRow = i;
                    moveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    if(moveRow != -1 && moveCol != -1)
        grid[moveRow][moveCol]='O';
}

// Input text inside graphics window
// it gonna be like this getInput(playerXName, "Enter Player X Name:", offsetX + 30, offsetY + 30);
// this below line thle ali line 
void getInput(char* input, const char* label, int x, int y) {
    setcolor(WHITE);
    
    // Make a writable char array from label to avoid const error
    char labelCopy[100];
    strcpy(labelCopy, label);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2.5);
    outtextxy(x, y, labelCopy);

    rectangle(x, y + 30, x + 200, y + 60);
    setcolor(YELLOW);

    int i = 0;
    char ch;
    while (true) {
        if (kbhit()) { //kbhit is a function in conio.h 	which tells 1 when keyboard key entered and 0 when non
            ch = getch();
            if (ch == 13) break; // Enter
            else if (ch == 8 && i > 0) { // Backspace
                i--;
                input[i] = '\0';
            } else if (i < 29 && ch >= 32 && ch <= 126) { // Printable characters
                input[i++] = ch;
                input[i] = '\0';
            }
            // Clear inside input box
            setfillstyle(SOLID_FILL, BLACK);
            bar(x + 2, y + 32, x + 198, y + 58);
            outtextxy(x + 5, y + 35, input);
        }
    }
}


// Ask mode + name input
int menu() {
    cleardevice();
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
	setcolor(WHITE);
    char msg[] = "Select Mode:";
    outtextxy(offsetX + 30 , offsetY + 50, msg);
    setcolor(WHITE);
    rectangle(offsetX -5 , offsetY + 100, offsetX + 275, offsetY + 150);
    setcolor(GREEN);
    outtextxy(offsetX + 5, offsetY + 110, "Player vs Player");

    setcolor(WHITE);
    rectangle(offsetX + 25, offsetY + 170, offsetX + 235, offsetY + 220);
    setcolor(RED);
    outtextxy(offsetX + 35, offsetY + 180, "Player vs AI");

    int selected = 0;
while (1) {
    if (ismouseclick(WM_LBUTTONDOWN)) {
        int x, y;
        getmouseclick(WM_LBUTTONDOWN, x, y);

        // Player vs Player
        if (x >= offsetX - 5 && x <= offsetX + 275 &&
            y >= offsetY + 100 && y <= offsetY + 150)
            selected = 1;

        // Player vs AI
        else if (x >= offsetX + 25 && x <= offsetX + 235 &&
                 y >= offsetY + 170 && y <= offsetY + 220)
            selected = 2;

        if (selected) break;
    }
    delay(50);
}


    cleardevice();
    if (selected != prevMode) {
    if(selected == 1) {
        getInput(playerX, "Enter Player X:", offsetX, offsetY + 50);
        getInput(playerO, "Enter Player O:", offsetX, offsetY + 120);
    } else {
        getInput(playerX, "Enter Your Name:", offsetX, offsetY + 50);
        strcpy(playerO, "Computer");
    }
    prevMode = selected;
}

}
 

// Win screen with names
bool endMenu(char winner) {
    cleardevice();
    drawResetButton(); 
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);

if (winner == 'X') {
    winsX++;
} else if (winner == 'O') {
    winsO++;
}


setfillstyle(SOLID_FILL, BLACK);
bar(offsetX - 260, offsetY + 90, offsetX - 10, offsetY + 180);


char scoreDisplay[100];
setcolor(WHITE);

// Player X
sprintf(scoreDisplay, "%s Wins: %d", playerX, winsX);
outtextxy(offsetX - 250, offsetY + 100, scoreDisplay);

// Player O
sprintf(scoreDisplay, "%s Wins: %d", playerO, winsO);
outtextxy(offsetX - 250, offsetY + 150, scoreDisplay);


//    if(winner=='D') {
//        setcolor(YELLOW);
//        outtextxy(offsetX + 60, offsetY + 50, "It's a Draw!");
//    }
//    else {
//        char msg[50];
//        if(winner=='X'){
//        	 winsX++; 
//            setcolor(LIGHTCYAN);
//            sprintf(msg, "%s Wins!	(Wins: %d)", playerX,winsX); //%s is a place holder for a string 
//			//It tells sprintf() to insert the string stored in playerX at that position. or store player name to msg
//        } else {
//        	winsO++;
//            setcolor(LIGHTRED);
//            sprintf(msg, "%s Wins!	(Wins: %d)", playerO,winsO);
//        }
//        outtextxy(offsetX + 35, offsetY + 50, msg);
//    }

    setcolor(WHITE);
    rectangle(offsetX + 50, offsetY + 100, offsetX + 250, offsetY + 150);
    setcolor(LIGHTGREEN);
    outtextxy(offsetX + 60, offsetY + 110, "New Game");

    setcolor(WHITE);
    rectangle(offsetX +110 , offsetY + 170, offsetX + 200, offsetY + 220);
    setcolor(LIGHTRED);
    outtextxy(offsetX + 120, offsetY + 180, "Quit");

    while(1) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int x,y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if(x>=offsetX && x<=offsetX + 260 && y>=offsetY + 100 && y<=offsetY + 150)
                return true;
            else if(x>=offsetX && x<=offsetX + 260 && y>=offsetY + 170 && y<=offsetY + 220)
                return false;
        }
        delay(50);
    }
}




int main() {

    int gd=DETECT, gm;
    initgraph(&gd, &gm, NULL);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
    cleardevice();
    while(true) {
        mode = menu(); 
        initGrid();
     

        char turn = 'X';
        char winner = ' ';
        bool running = true;

        while(running) {
        	   
            drawBoard();
            drawResetButton();
            if(mode == 1 || turn == 'X') {
                while (!ismouseclick(WM_LBUTTONDOWN)) delay(50);
                int x,y;
                getmouseclick(WM_LBUTTONDOWN, x, y);
                
     if (isResetClicked(x, y)) {
   		 winsX = 0;
   			winsO = 0;	    
}

                int row = -1, col = -1;
                if (y > offsetY && y < offsetY + 300 && x > offsetX && x < offsetX + 300) {
                    row = (y - offsetY) / 100;
                    col = (x - offsetX) / 100;
                }
                if (row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col]==' ') {
                    grid[row][col] = turn;
                    winner = checkWin();
                    if(winner != ' ' || isDraw()) running = false;
                    else turn = (turn=='X') ? 'O' : 'X';
                }
            } else if(mode == 2 && turn == 'O') {
                delay(500);
                bestMove();
                winner = checkWin();
                if(winner != ' ' || isDraw()) running = false;
                else turn = 'X';
            }
        }

        drawBoard();
        if(isDraw() && winner==' ') winner='D';
        if(!endMenu(winner)) break;
    }

    closegraph();
    return 0;
}

