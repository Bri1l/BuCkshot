#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int Turn;
char *Choice;

struct Players {
    int Health;
    int Damage;
    char Items[8][10];
};

struct Players *CurPlayer, P1 = {
    .Health = 2,
    .Damage = 1,
    .Items[0] = "Nothing"
};

struct Players *CurPlayer, P2 = {
    .Health = 2,
    .Damage = 1,
    .Items[0] = "Nothing"
};

void PlayerGo(struct Players *CurPlayer) {
    if (Turn == 1) {
        CurPlayer = &P1;
    }
    else {
        CurPlayer == &P2;
    }
    printf("What do you do? ");
}

int main() {
    while (1):
        srand(time(NULL));
        Turn = rand() % 1;
        PlayerGo(); // Allow multiple structs
        printf("/n");
    return 0;
}