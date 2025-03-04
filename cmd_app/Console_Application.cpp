#include "term.h"

int main(int argc, char** argv) {
    while (true) {
        std::string infix_string;
        std::cout << "print your expression: ";
        std::getline(std::cin, infix_string);
        Translator tr(infix_string);
        try {
            tr.everything();
        }
        catch (const char* e) {
            std::cout << "Caught an exception: " << e << std::endl;
        }
        catch (...) {
            std::cout << "Unknown exception" << std::endl;
        }
    }
    return 0;
}
