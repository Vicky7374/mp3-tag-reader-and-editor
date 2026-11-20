#ifndef DETAILS_H
#define DETAILS_H
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define BOLD_RED    "\033[1;31m"
#define BOLD_GREEN  "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_CYAN   "\033[1;36m"
#define FAILURE 0
// Clears the screen and moves the cursor to the top-left corner
#define CLEAR_SCREEN() printf("\033[H\033[J")


typedef struct {
    char tag[5];
    int size;
}view_var;
 

void viewfunction();
void editfunction();
void helpfunction();


#endif
