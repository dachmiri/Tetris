// 208539080 Maria Dach
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


enum direction {vertical, horizontal}typedef direction;
void GameLogic(char c);
void printMatrix();
void signal_handler(int sig);
int xPos = 10;
int yPos = 0;
direction dir = horizontal;
int main(){

    signal(SIGUSR2,signal_handler);

}

void GameLogic(char c) {
    // Move left
    if (c == 'a'){
        if(dir == horizontal){
            if ((xPos) + 1 > 19){
                // can't move
            }
            else {
                xPos +=1;
            }
        }
        else {
            if ((xPos) > 19){
                // can't move
            }
            else {
                xPos +=1;
            }
        }
    }
    // Move right
    if (c == 'd'){
        if(dir == horizontal){
            if ((xPos) - 1 < 0){
                // can't move
            }
            else {
                xPos -=1;
            }
        }
        else {
            if ((xPos) < 0){
                // can't move
            }
            else {
                xPos -=1;
            }
        }
    }
    // Move down
    if (c == 's'){
        (yPos) = (yPos) + 1;
        if (((dir) == vertical && (yPos) + 1 > 20) || ((dir) == horizontal && (yPos) > 20))
        {
            yPos = 0;
            xPos = 10;
            dir = horizontal;
        }
    }
    // rotate
    if(c == 'w'){
        if((dir) == horizontal) {
            if ((yPos) < 19 && yPos > 0){
                dir = vertical;
            }
        }
        else {
            if ((xPos) < 19 && (xPos) >0)
            {
                dir = horizontal;
            }
        }
    }

}

void printMatrix(){
    system("clear");
    for (int i = 0; i < 21; i++){
        printf("*");
        for (int j = 0; j < 20; j++){
            if(dir == horizontal){
                if(j > xPos - 2 && j < xPos +2 && i == yPos){
                    printf("-");
                }
                else{
                    printf(" ");
                }
            }
            else{
                if(i > yPos - 2 && i < yPos +2 && j == xPos){
                    printf("-");
                }
                else{
                    printf(" ");
                }
            }
        }
        printf("*\n");
    }
    printf("**********************");
    printf("\n");
}

void signal_handler(int sig){
    signal(SIGUSR2,signal_handler);
    char c;
    read(1, &c, 1);
    GameLogic(c);
    printMatrix();
}