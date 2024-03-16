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

// Enumerator for levels of ptr indirection
typedef enum {
    SINGLE_INDIRECTION,
    DOUBLE_INDIRECTION
} IndirectionLevel;

// Chooses which player goes
void PlayerInitialiser(Players* pP1, Players* pP2, int* pTurn, IndirectionLevel level) {
    // Checks who's turn it is, then changes the Struct based on that.
    // Health is handled elsewhere cause of stack popping
    if (*pTurn == 1) {
        if (level == SINGLE_INDIRECTION) {
            // Player 1
            strcpy(pP1->Name, "Player 1");
            pP1->Damage = 1;
            memset(pP1->Items, 0, sizeof(pP1->Items));

            // Player 2
            strcpy(pP2->Name, "Player 2");
            pP2->Damage = 1;
            memset(pP2->Items, 0, sizeof(pP2->Items));
        }
        else if (level == DOUBLE_INDIRECTION) {
            strcpy(pP1->Name, "Player 1");
            pP1->Damage = 1;
            memset(pP1->Items, 0, sizeof(pP1->Items));

            // Player 2
            strcpy(pP2->Name, "Player 2");
            pP2->Damage = 1;
            memset(pP2->Items, 0, sizeof(pP2->Items));
        }
        *pTurn = 0;
    }
    else {
        if (level == SINGLE_INDIRECTION) {
           // Player 2
            strcpy(pP1->Name, "Player 2");
            pP1->Damage = 1;
            memset(pP1->Items, 0, sizeof(pP1->Items));
            
            // Player 1
            strcpy(pP2->Name, "Player 1");
            pP2->Damage = 1;
            memset(pP2->Items, 0, sizeof(pP2->Items));
        }
        else if (level == DOUBLE_INDIRECTION) {
            strcpy(pP1->Name, "Player 2");
            pP1->Damage = 1;
            memset(pP1->Items, 0, sizeof(pP1->Items));

            // Player 1
            strcpy(pP2->Name, "Player 1");
            pP2->Damage = 1;
            memset(pP2->Items, 0, sizeof(pP2->Items));
        }
        *pTurn = 1;
    }
}

void PlayerItems(int *ppDamage, char (*ChambBullet), Players* pppCurPlayer) {
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
            ItemChoice = pppCurPlayer->Items[atoi(ItemBuf)]; // Converts ItemChoice (string) to an int, then uses this as the index for the Structs .Items Array
            // If player chooses soda, show the chambered bullet
            if (strcmp(ItemChoice, "Soda") == 0) {
                printf("Soda\n");
                printf("%s", ChambBullet[rand() % 2]);
                break;
            }
            // If player chooses saw, double damage
            else if (strcmp(ItemChoice, "Saw") == 0) {
                printf("Saw\n");
                *ppDamage = 2;
                break;
            }
            // If item doesn't exist
            else {
                printf("Nothing here\n");
                continue;
            }
        //for (int i = ArrPos; i < (*Arr[6] - 1); i++) {
        //printf("%s", Arr[6]);
        //*Arr[i] = Arr[i + 1];
        //printf("%s", Arr[i]);
        }
    printf("PlayerItems Good");
    }

// Player code
void PlayerGo(Players* pCurPlayer, Players* pOpPlayer, int* ppTurn, int* ppRunning, char (*ppBullet)[6], int BullLimit) {
    char *fgetReturn;
    char ChoiceBuf[4];
    char *Choice;
    int *pDamage;
    char* PlayerCheck;
    char Actions[2][6] = {"Shoot", "Items"};
    char ShootActions[2][10] = {"ShootOpp", "ShootSelf"};
    int SelectFlag = 1;
    int i;
    Players** ppCurPlayer = NULL;
    Players** ppOpPlayer = NULL;
    PlayerInitialiser(pCurPlayer, pOpPlayer, ppTurn, DOUBLE_INDIRECTION);
    while (SelectFlag == 1) {
        printf("%s", pCurPlayer->Name);
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
                            if (strcmp(Choice, "ShootOpp") == 0 && strcmp(ppBullet[0], "Live") == 0) {
                                pOpPlayer->Health -= pCurPlayer->Damage;
                                printf("%s Damage taken: %d\n", pOpPlayer->Name, pCurPlayer->Damage); // Check if these need dereferencing
                                break;
                            }
                            // Shoot self
                            else if (strcmp(Choice, "ShootSelf") == 0 && strcmp(ppBullet[0], "Live") == 0) {
                                pCurPlayer->Health -= pCurPlayer->Damage;
                                printf("%s Damage taken: %d\n", pOpPlayer->Name, pCurPlayer->Damage);
                                break;
                            }
                            // No blood spilt
                            else {
                                printf("*Click*\n");
                                break;
                            }
                        for (int i = 0; i < (*ppBullet[6] - 1); i++) {
                            *ppBullet[i] = *ppBullet[i + 1];
                            printf("%s", *ppBullet[i]);
                        }
                    }
                }
            }
            // Starts item screen
            else if (strcmp(Choice, "Items") == 0) {
                PlayerItems(pDamage, *ppBullet, pCurPlayer);
                break;
            }
            // Checks if player enters 9, if so, sets loop in main to 0, killing the loop and exiting the game
            else if ((atoi(ChoiceBuf)) == 9) {
                *ppRunning = 0;
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
    //printf("PlayerGo func Good");
}

int main() {
    int MaxHealth = 2;
    int Running = 1;
    int Turn;
    int *pTurn = &Turn;
    int *pRunning = &Running;
    char Bullets[8][6];
    char (*pBullets)[6] = Bullets;
    int BullLimit = 2; // Starts from 0 cause loader loop needs it for indexing
    int BulType;
    time_t CurTime;
    Players P1;
    Players P2;
    PlayerInitialiser(&P1, &P2, pTurn, SINGLE_INDIRECTION);
    strcpy(Bullets[0], "\0"); // Sets up var for loader
    // Selects random player to go first
    srand(time(NULL));
    Turn = rand() % 2;
    // Game loop, checks if no bullets then runs game func until Running != 1
    while (Running == 1) {
        // If no bullets, then load the gun with rand lives and blanks
        if (Bullets[0][0] == '\0') {
            CurTime = time(NULL);
            for (int i = 0; i < BullLimit; i++) {
                printf("\n\n");
                srand(CurTime);
                BulType = rand() % 2;
                if (BulType == 0) {
                    strcpy(Bullets[i], "Blank");
                    printf("%s", Bullets[i]);
                    CurTime += 54; // reseeds the time to stop repeat choices
                }
                else {
                    strcpy(Bullets[i], "Live");
                    printf("%s", Bullets[i]);
                    CurTime += 54;
                }
            }
            // Increases bullets & health for next round
            if (BullLimit < 8) {
                BullLimit++;
            }
            if (P1.Health < 6) {
                P1.Health = MaxHealth++;
                P2.Health = P1.Health;
            }
        }
        PlayerGo(&P1, &P2, pTurn, pRunning, pBullets, BullLimit);
        // Test code, DELETE
        //for (int d = 0; d < BullLimit; d++) {
        //    printf("%s\n", Bullets[d]);
        //}
    }
    return 0;
}