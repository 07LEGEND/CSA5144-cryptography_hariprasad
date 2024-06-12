#include <stdio.h>
#include <string.h>

void encryptRailFence(char *text, int key, char *result) {
    int len = strlen(text);
    int row, col, dir_down;
    char rail[key][len];
    for (row = 0; row < key; row++)
        for (col = 0; col < len; col++)
            rail[row][col] = '\n';
    row = 0; col = 0;
    dir_down = 0; 
    for (int i = 0; i < len; i++) {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;
        
        rail[row][col++] = text[i];
        
        dir_down ? row++ : row--;
    }
    int idx = 0;
    for (row = 0; row < key; row++)
        for (col = 0; col < len; col++)
            if (rail[row][col] != '\n')
                result[idx++] = rail[row][col];
    
    result[idx] = '\0';
}

void decryptRailFence(char *cipher, int key, char *result) {
    int len = strlen(cipher);
    int row, col, dir_down;
    char rail[key][len];
    for (row = 0; row < key; row++)
        for (col = 0; col < len; col++)
            rail[row][col] = '\n';
    row = 0; col = 0;
    dir_down = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;
        
        rail[row][col++] = '*';
        
        dir_down ? row++ : row--;
    }    int idx = 0;
    for (row = 0; row < key; row++)
        for (col = 0; col < len; col++)
            if (rail[row][col] == '*' && idx < len)
                rail[row][col] = cipher[idx++];
    row = 0; col = 0;
    dir_down = 0; 
    for (int i = 0; i < len; i++) {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;
        
        if (rail[row][col] != '*')
            result[i] = rail[row][col++];
        
        dir_down ? row++ : row--;
    }
    
    result[len] = '\0';
}

int main() {
    char text[100];
    int key;
    char encrypted[100];
    char decrypted[100];

    printf("Enter the text to be encrypted: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 
    printf("Enter the key (number of rails): ");
    scanf("%d", &key);
    printf("Original Text: %s\n", text);
    encryptRailFence(text, key, encrypted);
    printf("Encrypted Text: %s\n", encrypted);
    decryptRailFence(encrypted, key, decrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}

