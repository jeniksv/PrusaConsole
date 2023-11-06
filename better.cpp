#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <map>
#include <functional>


void setNonCanonicalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void MoveNext() {
    char arrow = getchar(); // Read the [ character
    if (arrow == 'A') {
        std::cout << "Move next" << std::endl;
    }
}

void MoveBack() {
    char arrow = getchar(); // Read the [ character
    if (arrow == 'B') {
        std::cout << "Move back" << std::endl;
    }
}

void TabAction() {
    std::cout << "Completion" << std::endl;
}

void BackspaceAction() {
    std::cout << "\b \b"; // Move cursor left, erase character, move cursor left
}

int main() {
    setNonCanonicalMode();
    char ch;

    std::map<int, std::function<void()>> keyActions = {
        {27, MoveNext}, // Escape
        {9, TabAction}, // Tab
        {127, BackspaceAction} // Backspace
    };

    while (true) {
        ch = getchar();

        if (keyActions.find(ch) != keyActions.end()) {
            keyActions[ch]();
        } else {
            std::cout << ch;
        }
    }

    return 0;
}

