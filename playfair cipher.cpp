#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void generateKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]);
void formatPlaintext(char plaintext[], char formattedText[]);
void encryptPair(char keyMatrix[SIZE][SIZE], char *pair);
void playfairEncrypt(char plaintext[], char key[], char ciphertext[]);

int main() {
    char key[100], plaintext[100], formattedText[100], ciphertext[100];

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0; 

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; 

    playfairEncrypt(plaintext, key, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
void generateKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]) {
    int used[26] = {0};
    int i, j, k = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            keyMatrix[i][j] = 0;
        }
    }
    for (i = 0; i < strlen(key); i++) {
        if (key[i] == 'j') key[i] = 'i'; 
        if (!used[toupper(key[i]) - 'A'] && isalpha(key[i])) {
            keyMatrix[k / SIZE][k % SIZE] = toupper(key[i]);
            used[toupper(key[i]) - 'A'] = 1;
            k++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (!used[i] && i != 'J' - 'A') {
            keyMatrix[k / SIZE][k % SIZE] = 'A' + i;
            k++;
        }
    }
}
void formatPlaintext(char plaintext[], char formattedText[]) {
    int i, j = 0;
    char prevChar = '\0';

    for (i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            char currentChar = tolower(plaintext[i]);
            if (currentChar == 'j') currentChar = 'i'; 
            if (currentChar == prevChar) {
                formattedText[j++] = currentChar;
                formattedText[j++] = 'x';
            } else {
                formattedText[j++] = currentChar;
            }
            prevChar = currentChar;
        }
    }

    if (j % 2 != 0) formattedText[j++] = 'x'; 
    formattedText[j] = '\0';
}
void encryptPair(char keyMatrix[SIZE][SIZE], char *pair) {
    int i1, j1, i2, j2;
    int found = 0;
    for (i1 = 0; i1 < SIZE; i1++) {
        for (j1 = 0; j1 < SIZE; j1++) {
            if (keyMatrix[i1][j1] == toupper(pair[0])) {
                found = 1;
                break;
            }
        }
        if (found) break;
    }

    found = 0;
    for (i2 = 0; i2 < SIZE; i2++) {
        for (j2 = 0; j2 < SIZE; j2++) {
            if (keyMatrix[i2][j2] == toupper(pair[1])) {
                found = 1;
                break;
            }
        }
        if (found) break;
    }

    if (i1 == i2) {
        pair[0] = keyMatrix[i1][(j1 + 1) % SIZE];
        pair[1] = keyMatrix[i2][(j2 + 1) % SIZE];
    } else if (j1 == j2) {
        pair[0] = keyMatrix[(i1 + 1) % SIZE][j1];
        pair[1] = keyMatrix[(i2 + 1) % SIZE][j2];
    } else {
        pair[0] = keyMatrix[i1][j2];
        pair[1] = keyMatrix[i2][j1];
    }
}
void playfairEncrypt(char plaintext[], char key[], char ciphertext[]) {
    char keyMatrix[SIZE][SIZE];
    char formattedText[100];
    int i, j = 0;

    generateKeyMatrix(key, keyMatrix);
    formatPlaintext(plaintext, formattedText);

    for (i = 0; i < strlen(formattedText); i += 2) {
        char pair[3] = {formattedText[i], formattedText[i + 1], '\0'};
        encryptPair(keyMatrix, pair);
        ciphertext[j++] = pair[0];
        ciphertext[j++] = pair[1];
    }
    ciphertext[j] = '\0';
}

