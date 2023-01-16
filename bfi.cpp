#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
// simple debug tool
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define HERE __FUNCTION__ " : LINE " TOSTRING(__LINE__)
// a namespace for useful static functions
namespace utilities {
    // date
    static void displayDate() {
        std::cout << __TIMESTAMP__ << std::endl;
    }
    // debug
    static void breakPoint(const char* loc) {
        std::cout << loc << std::endl;
    }
    // list folder with codes
    static void listFolder()
    {
        std::string path(".\\examples");
        std::string ext(".txt"); // change the extension name here
        // check if folder exists
        bool checkFolder = std::filesystem::is_directory(path);
        short i = 1;
        // get it!
        if (checkFolder) {
            std::cout << "Available Codes List :" << std::endl;

            for (auto& p : std::filesystem::recursive_directory_iterator(path))
                if (p.path().extension() == ext)
                {   // list files according to the extension txt
                    std::cout << i << ". " << p.path().stem().string() << ".txt" << std::endl;
                    ++i;
                }

            std::cout << std::endl;
        }
        else { // no folder?
            std::cout << "Folder With Codes Does Not Exist" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    // read a file and store its content
    static std::string readCodeFile(std::string nameFile) {

        std::ifstream src;
        src.open(nameFile);
        // bad file name?
        if (!src.is_open())
            std::cerr << "Unable To Open Code File" << std::endl;

        std::string code;

        for (std::string line; std::getline(src, line);)
            code += line;

        src.close();
        // other chars are comments
        const std::string _syntax = "><+-.,[]@";
        // clean up
        code.erase(std::remove_if(code.begin(), code.end(), [&_syntax](const char& c) {
            return _syntax.find(c) == std::string::npos;
            }), code.end());
        // return our instructions code
        return code;
    }
}

class brainFuck {

private:
    int mp;
    int ip;
    std::string instructions;
    std::vector<char> memory;

public: // constructor
    brainFuck(const std::string code, int size) {
        this->memory = std::vector<char>(size, 0);
        this->instructions = code;
        this->ip = 0;
        this->mp = 0;
    };
    // instruction >
    void inc_pointer() {
        ++mp;
    };
    // instruction <
    void dec_pointer() {
        --mp;
    };
    // instruction +
    void inc_value() {
        ++memory[mp];
    };
    // instruction -
    void dec_value() {
        --memory[mp];
    };
    // instruction ,
    void input() {
        std::cin >> memory[mp];
    };
    // instruction .
    void output() {
        std::cout << memory[mp];
    };
    // instruction [
    void jmp_forward() {
        if (memory[mp] == 0) {
            int value = 1;

            while (value != 0) {
                ++ip;
                if (instructions[ip] == '[')
                    ++value;
                else if (instructions[ip] == ']')
                    --value;
            }
        }
    };
    // instruction ] 
    void jmp_backward() {
        if (memory[mp] != 0) {
            int value = 1;

            while (value != 0) {
                --ip;
                if (instructions[ip] == '[')
                    --value;
                else if (instructions[ip] == ']')
                    ++value;
            }
        }
    };
    // until code reaches a NULL char
    void interpret() {
        while (instructions[ip] != '\0') {
            switch (instructions[ip]) {
            case '>':
                inc_pointer();
                break;
            case '<':
                dec_pointer();
                break;
            case '+':
                inc_value();
                break;
            case '-':
                dec_value();
                break;
            case '.':
                output();
                break;
            case ',':
                input();
                break;
            case '[':
                jmp_forward();
                break;
            case ']':
                jmp_backward();
                break;
            }
            ++ip;
        }
        std::cout << std::endl;
    };
};

int main() {

    utilities::displayDate(); // display date using static function
    utilities::listFolder();  // lists folder with available codes
    std::string s;  // for our instructions code

    while (1)
    {
        std::cout << "Select the code that the interpreter will run - (ex : hello.txt)" << std::endl;
        std::cin >> s;

        if (s == "exit")
            break;

        std::string code = utilities::readCodeFile(".\\examples/" + s);
        // set here a string (as a ribbon) according to its size
        brainFuck bf(code, 256);
        bf.interpret(); // read it - executes instructions
    }
    // utilities::breakPoint(HERE);
    return 0;
}