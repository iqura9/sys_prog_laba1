#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isDelimiter(char c) {
    return !isalpha(c);
}

int isVowel(char c) {
    c = toupper(c);
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}
char delimiters[] = " \t\n,.;:!()[]{}\"';/\\+*-=<>?#$%^&*!@";

int main() {
    FILE *file = fopen("../data.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[1024]; // Рядок для зберігання прочитаного з файлу
    char uniqueWords[1024][1024]; // Масив для зберігання унікальних слів
    int uniqueCount = 0; // Лічильник унікальних слів

    while (fgets(line, sizeof(line), file) != NULL) {
        char *word = strtok(line, delimiters);

        while (word != NULL) {
            int isWord = 1;
            for (int i = 0; word[i] != '\0'; i++) {
                if (isDelimiter(word[i])) {
                    isWord = 0;
                    break;
                }
            }

            if (isWord) {
                int isAllVowels = 1;
                for (int i = 0; word[i] != '\0'; i++) {
                    if (!isVowel(word[i])) {
                        isAllVowels = 0;
                        break;
                    }
                }

                int isUnique = 1;
                for (int i = 0; i < uniqueCount; i++) {
                    if (strcmp(word, uniqueWords[i]) == 0) {
                        isUnique = 0;
                        break;
                    }
                }

                if (isAllVowels && isUnique) {
                    strcpy(uniqueWords[uniqueCount], word);
                    uniqueCount++;
                    printf("%s\n", word);
                }

            }

            word = strtok(NULL, delimiters);
        }
    }

    fclose(file);

    return 0;
}
