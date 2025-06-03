#include <iostream>
#include <Windows.h>
#include "Libraries/CustomFunctions.h"

#pragma comment(lib, "user32")

// This function set the console to a specific color
void setColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

//This function goes to a precise position of the console
void gotoxy(int x, int y){
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void setFontSize_Function(){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 24;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void fullscreen_Function(){
    Sleep(300);

    keybd_event(VK_F11, 0, 0, 0);
    Sleep(50);
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
}