#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Blueprint player struct
typedef struct {
    char Name[9];
    int Health;
    int Damage;
    char Items[8][10];
} Players;

// Chooses which player goes
void PlayerInitialiser(Players* PNow, Players* PLater, int* isTurn) {
    // Player 1 'N Player 2
    Players P1 = {
        .Name = "Player 1",
        .Health = 2,
        .Damage = 1,
        .Items = {}
    };
    Players P2 = {
        .Name = "Player 2",
        .Health = 2,
        .Damage = 1,
        .Items = {}
    };
    // Checks who's turn it is, then changes the Struct based on that
    if (*isTurn == 1) {
        PNow = &P1;
        PLater = &P2;
        printf("Player 1\n");
        *isTurn = 0;
    }
    else {
        PNow = &P2;
        PLater = &P1;
        printf("Player 2\n");
        *isTurn = 1;
    }
}

// Removes item from array and moves all "above" items "downward". TEST THIS FUNC
void ArrDecimate(char *Arr) {
    for (int i = Arr[0]; i < (sizeof(Arr) - 1); i++) {
        printf("%s", Arr[6]);
        Arr[i] = Arr[i + 1];
        //printf("%s", Arr[i]);
    }
}

void PlayerItems(int *DamageInc, char (*ChambBullet), Players* PlayerSelect) {
    char ItemBuf[2];
    char *ItemChoice;
    char *fgetReturn;
    while (1) {
        printf("\n");
        // Asks player for input, stores it in fgetReturn
        printf("What do you Choose? ");
        fgetReturn = fgets(ItemBuf, sizeof(ItemBuf), stdin);
        // Print this if blank
        if (fgetReturn == NULL) {
            printf("Input must not be blank\n");
            continue;
        }
        else if (fgetReturn) {
            ItemBuf[strcspn(ItemBuf, "\n")] = '\0'; // Remove the trailing newline (if it exists)
        }
            ItemChoice = PlayerSelect->Items[atoi(ItemBuf)]; // Converts ItemChoice (string) to an int, then uses this as the index for the Structs .Items Array
            // If player chooses soda, show the chambered bullet
            if (strcmp(ItemChoice, "Soda") == 0) {
                printf("Soda\n");
                printf("%s", ChambBullet[rand() % 2]);
                break;
            }
            // If player chooses saw, double damage
            else if (strcmp(ItemChoice, "Saw") == 0) {
                printf("Saw\n");
                *DamageInc = 2;
                break;
            }
            // If item doesn't exist
            else {
                printf("Nothing here\n");
                continue;
            }
    }
    printf("PlayerItems Good");
}

// Player code
void PlayerGo(Players* CurPlayer, Players* OpPlayer, int *CurTurn, int *isRunning, char (*CurBullet)[6], int BulletCount) {
    char *fgetReturn;
    char ChoiceBuf[4];
    char *Choice;
    int *DamagePtr;
    char* PlayerCheck;
    char Actions[2][6] = {"Shoot", "Items"};
    char ShootActions[2][10] = {"ShootOpp", "ShootSelf"};
    int SelectFlag = 1;
    int i;
    PlayerInitialiser(CurPlayer, OpPlayer, CurTurn);
    while (SelectFlag == 1) {
        printf("\n");
        printf("What do you do?\n1: Shoot\n2: Items\n");
        fgetReturn = fgets(ChoiceBuf, sizeof(ChoiceBuf), stdin); // Stores input in fgetReturn
        // Print this if input blank
        if (fgetReturn == NULL) {
            printf("Input must not be blank\n");
        }
        else if (fgetReturn) {
            ChoiceBuf[strcspn(ChoiceBuf, "\n")] = '\0'; // Remove the trailing newline (if it exists)
            Choice = Actions[(atoi(ChoiceBuf)) - 1];  // Converts ChoiceBuf (string) to an int, then uses this as the index for the Structs .Items Array
            // Checks if user choice matches
            if (strcmp(Choice, "Shoot") == 0) {
                printf("\nShoot who?\n1: Opponent\n2: Self\n");
                // Asks player who they wanna shoot
                while (1) {
                    fgetReturn = fgets(ChoiceBuf, sizeof(ChoiceBuf), stdin);
                    // Print this if blank
                    if (fgetReturn == NULL) {
                        printf("Input must not be blank\n");
                        continue;
                    }
                    else if (fgetReturn) {
                            ChoiceBuf[strcspn(ChoiceBuf, "\n")] = '\0'; // Remove the trailing newline (if it exists)
                            Choice = ShootActions[(atoi(ChoiceBuf)) - 1];  // Converts ChoiceBuf (string) to an int, then uses this as the index for the Structs .Items Array
                            SelectFlag = 0; // Breaks out of nested loops
                            ++i; // Iterates bullet index after each loop
                            // Shoot opponent
                            if (strcmp(Choice, "ShootOpp") == 0 && strcmp(CurBullet[0], "Live") == 0) {
                                OpPlayer->Health -= CurPlayer->Damage;
                                printf("%s Damage taken: %d\n", OpPlayer->Name, CurPlayer->Damage);
                                ArrDecimate(CurBullet[6]); // This wants an array value, but ArrDecimate func also wants one, so IDK. FIX
                                printf("%s", CurBullet[6]);
                                break;
                            }
                            // Shoot self
                            else if (strcmp(Choice, "ShootSelf") == 0 && strcmp(CurBullet[0], "Live") == 0) {
                                CurPlayer->Health -= CurPlayer->Damage;
                                printf("%s Damage taken: %d\n", OpPlayer->Name, CurPlayer->Damage);
                                break;
                            }
                            // No blood spilt
                            else {
                                printf("*Click*\n");
                                break;
                            }
                        }
                }
            }
            // Starts item screen
            else if (strcmp(Choice, "Items") == 0) {
                PlayerItems(DamagePtr, *CurBullet, CurPlayer);
                break;
            }
            // Checks if player enters 9, if so, sets loop in main to 0, killing the loop and exiting the game
            else if ((atoi(ChoiceBuf)) == 9) {
                *isRunning = 0;
                printf("Goodbye");
                break;
            }
            // If choice doesn't exist
            else {
                printf("Nothing here\n");
                continue;
            }
        }
    }
    printf("PlayerGo func Good");
}

int main() {
    int Running = 1;
    int Turn;
    int *TurnPtr = &Turn;
    int *RunPtr = &Running;
    char Bullets[7][6];
    char (*BulletsPtr)[6] = Bullets;
    int BullLimit = 2; // Starts from 0 cause loader loop needs it for indexing
    int BulType;
    Players* CurPlayerPtr;
    Players* OpPlayerPtr;
    strcpy(Bullets[0], "\0"); // Sets up var for loader
    // Selects random player to go first
    srand(time(NULL));
    Turn = rand() % 2;
    // Game loop, checks if no bullets then runs game func until Running != 1
    while (Running == 1) {
        // If no bullets, then load the gun with rand lives and blanks
        if (Bullets[0][0] == '\0') {
            for (int i = 0; i < BullLimit; i++) {
                printf("\n");
                srand(time(NULL));
                BulType = rand() % 2;
                if (BulType == 0) {
                    strcpy(Bullets[i], "Blank\n");
                    printf("%s", Bullets[i]);
                }
                else {
                    strcpy(Bullets[i], "Live\n");
                    printf("%s", Bullets[i]);
                }
            }
            // Increases bullets & health for next round
            BullLimit++;
            CurPlayerPtr->Health++;
            OpPlayerPtr->Health++;
        }
        PlayerGo(CurPlayerPtr, OpPlayerPtr, TurnPtr, RunPtr, BulletsPtr, BullLimit);
        printf("Main good");
        printf("\n");
        // Test code, DELETE
        //for (int d = 0; d < BullLimit; d++) {
        //    printf("%s\n", Bullets[d]);
        //}
    }
    return 0;
}