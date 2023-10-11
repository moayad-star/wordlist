#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RED_COLOR   "\033[0;31m"
#define GREEN_COLOR "\033[0;32m"
#define YELLOW_COLOR "\033[0;33m"
#define WHITE_COLOR "\033[0;37m"
#define BOLD_TEXT   "\033[5;1m"
#define BACKGROUND_RED "\033[41m"
#define RESET_FORMAT "\033[0m"

#define PASSWORD_FORMATS  "0123456789", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", "@#$&(_-=%*':/!?+÷;`]}><{[^¡¿~™®©¢¥€£¶§×`", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@#$&(_-=%*':/!?+÷;`]}><{[^¡¿~™®©¢¥€£¶§×`"

void get_password_format(char* format);
void get_password_info(int* num_passwords, int* password_length);
void get_file_name(char* output_file);
void generate_passwords(char* password_format, int num_passwords, int password_length, char* output_file);

int main() {
    char format[2];
    get_password_format(format);
    int num_passwords, password_length;
    get_password_info(&num_passwords, &password_length);
    char output_file[100];
    get_file_name(output_file);

    generate_passwords(format, num_passwords, password_length, output_file);
    return 0;
}

void get_password_format(char* format) {
    while (1) {
        printf("%s%s\n", GREEN_COLOR, BOLD_TEXT);
        printf("Enter the password format:\n");
        printf("[1] 1234...\n");
        printf("[2] ABCD...\n");
        printf("[3] abcd...\n");
        printf("[4] ABcd...\n");
        printf("[5] @#$&...\n");
        printf("[6] Ac23...\n");
        printf("[7] Ab3&...\n");
        printf("%s", YELLOW_COLOR);

        char select[2];
        fgets(select, sizeof(select), stdin);
        select[strlen(select) - 1] = '\0';

        if (strcmp(select, "1") == 0 || strcmp(select, "2") == 0 || strcmp(select, "3") == 0 || strcmp(select, "4") == 0 || strcmp(select, "5") == 0 || strcmp(select, "6") == 0 || strcmp(select, "7") == 0) {
            strncpy(format, select, 2);
            break;
        }
    }
}

void get_password_info(int* num_passwords, int* password_length) {
    while (1) {
        printf("%s%s\n", GREEN_COLOR, BOLD_TEXT);
        printf("How many passwords do you need? [Ex:1000]:\n");
        printf("%s", YELLOW_COLOR);

        char input[10];
        fgets(input, sizeof(input), stdin);
        *num_passwords = atoi(input);

        if (*num_passwords > 0) {
            break;
        }
    }

    while (1) {
        printf("%s%s\n", GREEN_COLOR, BOLD_TEXT);
        printf("How long is the password? [Ex:8]:\n");
        printf("%s", YELLOW_COLOR);

        char input[10];
        fgets(input, sizeof(input), stdin);
        *password_length = atoi(input);

        if (*password_length > 0) {
            break;
        }
    }
}

void get_file_name(char* output_file) {
    while (1) {
        printf("%s%s\n", GREEN_COLOR, BOLD_TEXT);
        printf("Enter the filename to save passwords [Ex: pass.txt]:\n");
        printf("%s", YELLOW_COLOR);

        fgets(output_file, 100, stdin);
        output_file[strlen(output_file) - 1] = '\0';

        if (strlen(output_file) == 0) {
            strcpy(output_file, "pass.txt");
        }

        if (output_file[strlen(output_file) - 4] != '.') {
            strcat(output_file, ".txt");
        }

        break;
    }
}

void generate_passwords(char* password_format, int num_passwords, int password_length, char* output_file) {
    const char* characters = PASSWORD_FORMATS[*password_format - '1'];
    char passwords[num_passwords][password_length + 1];
    int count = 0;

    while (count < num_passwords) {
        char password[password_length + 1];
        password[password_length] = '\0';

        for (int i = 0; i < password_length; i++) {
            int index = rand() % strlen(characters);
            password[i] = characters[index];
        }

        int is_duplicate = 0;

        for (int i = 0; i < count; i++) {
            if (strcmp(passwords[i], password) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            strcpy(passwords[count], password);
            printf("%s%s\n", GREEN_COLOR, BOLD_TEXT);
            printf("%s", YELLOW_COLOR);
            printf("Password: %s\n", password);
            count++;
        }
    }

    FILE* file = fopen(output_file, "w");

    for (int i = 0; i < num_passwords; i++) {
        fprintf(file, "%s\n", passwords[i]);
    }

    fclose(file);
    printf("%s%s\n", GREEN_COLOR, BOLD_TEXT);
    printf("Saved as %s\n", output_file);
}
