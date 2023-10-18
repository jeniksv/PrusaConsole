#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

class console_reader{
public:
	console_reader();

	std::string read_line();
private:
	void set_non_canonical_mode();

	// history h;
	// TODO tab_completion t;
};

void console_reader::set_non_canonical_mode(){
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	
	t.c_lflag &= ~(ICANON | ECHO);
	t.c_cc[VMIN] = 1;
	t.c_cc[VTIME] = 0;

	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

console_reader::console_reader() : {
	set_non_canonical_mode();
}


int main() {
    setNonCanonicalMode();
    char ch;

    while (true) {
        ch = getchar();

        switch (ch) {
            case 27: // Arrow key (escape sequence)
                ch = getchar(); // Read the [
                ch = getchar(); // Read the A, B, C, or D for arrow direction
                if (ch == 'A') {
                    std::cout << "Move next" << std::endl;
                } else if (ch == 'B') {
                    std::cout << "Move back" << std::endl;
                }
                break;
            case '\t':
                std::cout << "Completion" << std::endl;
                break;
            case 127: // Backspace
                std::cout << "\b \b"; // Move cursor left, erase character, move cursor left
                break;
            default:
                std::cout << ch;
                break;
        }
    }

    return 0;
}

