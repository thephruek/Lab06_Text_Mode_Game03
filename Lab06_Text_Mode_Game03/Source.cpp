#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void erase_ship(int x, int y)
{
    gotoxy(x, y);
    setcolor(2, 0);
    printf("      ");
}
void draw_ship(int x, int y)
{
    setcolor(2, 4);
    gotoxy(x, y); printf("<-0->");
}
void erase_bullet(int xb, int yb)
{
    gotoxy(xb, yb);
    setcolor(2, 0);
    printf(" ");
}
void draw_bullet(int xb, int yb)
{
    setcolor(9, 0);
    gotoxy(xb, yb); printf("|");
}
void draw_star(int xs, int ys)
{
    setcolor(14, 0);
    gotoxy(xs, ys);
    printf("*");
}
void right(int sc)
{
    setcolor(3, 0);
    gotoxy(65, 0);
    printf("Score : %d", sc);
}
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
int main()
{
    int i, score = 0;
    srand(time(NULL));
    int gun[5] = { 0 }, ax[5] = { 0 }, ay[5] = { 0 };
    int bullet = 0;
    char dir = 's';
    setcursor(0);
    char ch = '.';
    int x = 38, y = 20;
    int xb = x, yb = y;
    int star = 0, starx[20] = { 0 }, stary[20] = { 0 };
    draw_ship(x, y);
    right(score);
    do {

        for (; star < 20;)
        {
            int num1, num2, num3 = 0;
            num1 = (rand() % 61) + 10;
            num2 = (rand() % 4) + 2;
            for (int i = 0; i < 20; i++)
            {
                if (num1 == starx[i] && num2 == stary[i]) {
                    num3 = 1;
                    break;
                }
            }
            if (num3 == 0) {
                starx[star] = num1;
                stary[star] = num2;
                draw_star(starx[star], stary[star]);
                star++;
            }
        }
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'a' && x > 0) { 
                erase_ship(x, y); 
                draw_ship(--x, y); }
            if (ch == 'd' && x < 75) { 
                erase_ship(x, y); 
                draw_ship(++x, y); }

            if (ch == ' ') {
                
                for (int i = 0; i < 5; i++) {
                    if (gun[i] == 0) {
                        gun[i] = 1;
                        ax[i] = x + 2;
                        ay[i] = y - 1;
                        break;
                    }
                }
            }
            fflush(stdin);
        }

        for (int i = 0; i < 1; i++) {
            if (gun[i] == 1 && ay[i] > 0) {
                erase_bullet(ax[i], ay[i]);  
                draw_bullet(ax[i], --ay[i]);
            }
            if (gun[i] == 1 && ay[i] == 0) {
                erase_bullet(ax[i], ay[i]);
                gun[i] = 0;
            }
            for (int j = 0; j < 20; j++) {
                if (gun[i] == 1 && ax[i] == starx[j] && ay[i] == stary[j]) {
                    erase_bullet(ax[i], ay[i]);
                    ax[i] = 0;
                    ay[i] = 0;
                    gun[i] = 0;
                    starx[j] = 0;
                    stary[j] = 0;
                    star--;
                    Beep(400, 100);
                    right(++score);
                }
            }
        }

        Sleep(100);
    } while (ch != 'x');
    return 0;
}