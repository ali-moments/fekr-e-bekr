#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
using namespace std;

bool debug = false;
int PCSelected[4]={9,9,9,9};
int PLSelected[4];

bool isIn(int *array, int size, int value){
    for(int i=0; i<size; i++) if(array[i] == value) return true;
    return false;
}

void generateNRandomNumber(int array[], int length, int min, int max){
    int temp;
    for (int i=0; i<length; i++){
        temp = (rand() % max) + min;
        if(isIn(array, i, temp)){
            i--;
            continue;
        } else array[i] = temp;
    }
}

void clrscr(){
    system("cls");
    system("color b0");
    cout << "\033[3;106;30m";
}

void error(int ec=85){
    clrscr();
    cout << "there is a problem..." << endl;
    exit(ec);
}

int getColor(string text){
    int temp;
    do{
        cout << text;
        cin >> temp;
        if(temp<0 || temp>7) cout << "[!] enter number between 0 to 7." << endl;
    }while(temp<0 || temp>7);
    return temp;
}

int selectDifficulty(){
    clrscr();
    int ans;
    cout << "\n\t1) Easy (Default)\n\t2) Normal\n\t3) Hard" << endl;
    cout << "select game difficulty: ";
    cin >> ans;
    switch(ans){
        case 3:
            cout << "Selected: Hard" << endl;
            getch();
            return 5;
        case 2:
            cout << "Selected: Normal" << endl;
            getch();
            return 8;
        case 99:
            cout << "" << endl;
            cout << "answer: ";
            for(auto i: PCSelected) cout << i;
            cout << endl;
            debug = true;
            getch();
            return 99;
        default:
            cout << "Selected: Easy" << endl;
            getch();
            return 12;
    }
}

string color(int code, string text=" "){
    switch(code){
        case 0: // Red
            return "\033[2;41;30m" + text + "\033[0m\033[3;106;30m";
        case 1: // Orange
            return "\033[1;101;30m" + text + "\033[0m\033[3;106;30m";
        case 2: // Green
            return "\033[2;42;30m" + text + "\033[0m\033[3;106;30m";
        case 3: // Blue
            return "\033[2;104;30m" + text + "\033[0m\033[3;106;30m";
        case 4: // Yellow
            return "\033[2;43;30m" + text + "\033[0m\033[3;106;30m";
        case 5: // Black
            return "\033[1;40;37m" + text + "\033[0m\033[3;106;30m";
        case 6: // White
            return "\033[2;47;30m" + text + "\033[0m\033[3;106;30m";
        case 7: // Gray
            return "\033[2;100;30m" + text + "\033[0m\033[3;106;30m";
        default: // Reset
            return "\033[0m" + text;
    }
}

string getnumber(int number){
    switch (number){
        case 0:
            return "first";
        case 1:
            return "second";
        case 2:
            return "third";
        case 3:
            return "fourth";
        default:
            return "";
    }
}

void resetValues(int *arr, int size, int value){
    for(int i=0; i<size; i++) PLSelected[i] = 9;
}

void getPlayerGuess(){
    int temp, count = 0;
    clrscr();
    cout << "you should enter each color one by one; and colors should be a number from 0 to 7:" << endl;
    cout << "\t0: red " << color(0) << "\t1: orange " << color(1) << endl;
    cout << "\t2: green " << color(2) << "\t3: blue " << color(3) << endl;
    cout << "\t4: yellow " << color(4) << "\t5: black " << color(5) << endl;
    cout << "\t6: white " << color(6) << "\t7: gray " << color(7, " \n") << endl;
    resetValues(PLSelected, 4, 9);
    while(count < 4){
        temp = getColor("Enter " + getnumber(count) + " color: ");
        if(!isIn(PLSelected, 4, temp)){
            PLSelected[count] = temp;
            count++;
        } else cout << "[!] do not enter repeated colors." << endl;
    }
}

bool checkcolors(){
    for(int i=0; i<4; i++) if(PCSelected[i] != PLSelected[i]) return false;
    return true;
}

void printGameBoard(int remainingAttempts, int colscore, int locscore, int col[4], int loc[4]){
    clrscr();
    string XS[4];
    for(int i=0; i<4; i++){
        if(PCSelected[i]==PLSelected[i] && loc[i]==1) XS[i]=color(PCSelected[i]);
        else XS[i]="X";
    }

    string hints[4];
    for(int i=0; i<4; i++){
        if(loc[i]==1 && col[i]==1) hints[i]=color(2);
        else if(col[i]==1) hints[i]=color(4);
        else hints[i]=color(0);
    }

    cout << "---------------\n|";
    for(auto i: XS) cout << "  " << i;
    cout << " |" << endl;
    cout << "---------------" << endl;
    cout << "|";
    for(auto i: hints) cout << i;
    cout << "|";
    for(auto i: PLSelected) cout << color(i, "  ");
    cout << "|" << endl;
    cout << "---------------" << endl;
    cout << "|SE:" << colscore << "+" << locscore << "|RA: ";
    if(remainingAttempts<=3) printf("\033[2;40;31m%2d\033[0m|\n", remainingAttempts-1);
    else printf("%2d|\n", remainingAttempts-1);
    cout << "---------------" << endl;
}

int main(){
    srand((unsigned)time(NULL));
    system("color b0");
    generateNRandomNumber(PCSelected, 4, 0, 7);
    int colors[4] = {0};
    int locations[4] = {0};
    int difficulty = selectDifficulty();
    int colorScore;
    int locationScore;

    while(difficulty > 0){
        getPlayerGuess();
        colorScore = 0;
        locationScore = 0;
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(PLSelected[i] == PCSelected[j]){
                    colors[i]=1;
                    colorScore++;
                }
                if(PLSelected[i] == PCSelected[j] && i==j){
                    locations[i]=1;
                    locationScore++;
                }
            }
        }
        printGameBoard(difficulty, colorScore, locationScore, colors, locations);
        if(debug) debug_print(PCSelected, PLSelected, colors, locations);
        getch();
        if(checkcolors()) break;
        difficulty--;
    }

    if(checkcolors()) cout << "you win!" << endl;
    else cout << "you lose!" << endl;
    getchar();
    return 0;
}
