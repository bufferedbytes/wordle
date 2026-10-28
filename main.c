#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAXLINELENGTH 1000
#define DATA_PATH "wordlist.txt"

int getword(char* store);
bool checkvalid(char* word);
int getfilelen();
int playword();
void strip_newline(char* stringtoclean);
void clear_line();
void print_response(char* word, char* guess, int guess_number);
bool get_yesno(char* message);

int file_length;
FILE* data_file;

int main() {
    puts("WORDLE\n");
    // Open our data and check if successful
    data_file = fopen(DATA_PATH, "r");
    if (data_file == NULL) {
        puts("Data file could not be read!");
        return -1;
    };
    file_length = getfilelen();
    // Setup our random seed
    srand((unsigned int) time(NULL) * (unsigned int)time(NULL));
    // Core loop
    bool done = false;
    char choice = '\0';
    while (done == false) {
        playword();
        if (get_yesno("Would you like to play again?") == false) {
            done = true;
        };
    };
    fclose(data_file);
    return 0;
};

int getfilelen() {
    unsigned int linescounted = 0;
    char buffer[MAXLINELENGTH];
    while (fgets(buffer, MAXLINELENGTH, data_file) != NULL) {
        linescounted++;
    };
    rewind(data_file);
    return linescounted;
}

void strip_newline(char* stringtoclean) {
    // Undefined behavior if the string doesn't have a newline
    stringtoclean[strcspn(stringtoclean, "\n")] = 0; // Set the first occurance of "\n" to the null terminator.
};

int getword(char* store) {
    int random_word_position = rand() % file_length;
    int current_line = 1;
    while (current_line < random_word_position - 1) {
        fgets(store, 10, data_file);
        strip_newline(store);
        current_line++;
    }; 
    rewind(data_file);
    return 0;
};

bool checkvalid(char* word) {
    
    int current_line = 1;
    char current_contents[MAXLINELENGTH];
    bool done_searching_line = false;
    int current_char = 0;
    rewind(data_file);
    while (current_line < file_length) {
        fgets(current_contents, MAXLINELENGTH, data_file);
        while (done_searching_line == false) {
            // If characters don't match, we go right to the next line
            if (current_contents[current_char] != word[current_char]) {
                done_searching_line = true;
            }
            // If we reach a null terminator, that means the string matched and we can return true;
            else if (current_contents[current_char] == '\0') {
                rewind(data_file);
                return true;
            }
            // Else, we check the next character
            else {
                current_char++;
            };
        };
        done_searching_line = false;
        current_char = 0;
        current_line++;
    };
    rewind(data_file);
    return false;
};
void clear_line() {
    printf("\033M\033[2K\r");
}
void print_response(char* word, char* guess, int guess_number) {
    clear_line();
    char output_buff[50];
    int charword = 0;
    int charoutput = 0;
    char single_char_array[2] = { ' ', '\0' };
    while (charword < 5) {
        single_char_array[0] = guess[charword];
        if (word[charword] == guess[charword]) {
            output_buff[charoutput++] = '\033';
            output_buff[charoutput++] = '[';
            output_buff[charoutput++] = '3';
            output_buff[charoutput++] = '2';
            output_buff[charoutput++] = 'm';
            output_buff[charoutput++] = guess[charword];
        }
        else if (strstr(word, single_char_array) != NULL) {
            output_buff[charoutput++] = '\033';
            output_buff[charoutput++] = '[';
            output_buff[charoutput++] = '3';
            output_buff[charoutput++] = '3';
            output_buff[charoutput++] = 'm';
            output_buff[charoutput++] = guess[charword];
        }
        else {
            output_buff[charoutput++] = '\033';
            output_buff[charoutput++] = '[';
            output_buff[charoutput++] = '3';
            output_buff[charoutput++] = '1';
            output_buff[charoutput++] = 'm';
            output_buff[charoutput++] = guess[charword];
        };
        charword++;
    };
    output_buff[charoutput++] = '\033';
    output_buff[charoutput++] = '[';
    output_buff[charoutput++] = '3';
    output_buff[charoutput++] = '9';
    output_buff[charoutput++] = 'm';
    output_buff[charoutput] = '\0';
    printf("%s [%d/6]\n", output_buff, guess_number + 1);
};

int playword() {
    char chosenword[10];
    char guess[10];
    int guesses = 0;
    getword(chosenword);

    while (guesses < 6) {
        fgets(&guess, 10, stdin);
        // We strip the newline for 
        if (checkvalid(&guess) == false) {
            clear_line();
        }
        else {
            strip_newline(&guess);
            print_response(&chosenword, &guess, guesses);
            guesses++;
            if (strcmp(&guess, chosenword) == 0) {
                puts("You won!!!");
                return 0;
            }
        }
    }
    
    printf("You lost!!! The answer was %s!\n", chosenword);
    return 0;
}

bool get_yesno(char* message) {
    printf("%s [y/n] ", message);
    char c = '\0';
    while (!(c == 'y' || c == 'Y' || c == 'n' || c == 'N')) {
        c = getchar();
    };
    if (c == 'y' || c == 'Y') {
        return true;
    }
    else return false;
};