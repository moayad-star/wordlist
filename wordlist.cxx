#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

const std::string RED_COLOR = "\033[0;31m";
const std::string GREEN_COLOR = "\033[0;32m";
const std::string YELLOW_COLOR = "\033[0;33m";
const std::string WHITE_COLOR = "\033[0;37m";
const std::string BOLD_TEXT = "\033[5;1m";
const std::string BACKGROUND_RED = "\033[41m";
const std::string RESET_FORMAT = "\033[0m";

const std::string PASSWORD_FORMATS[] = {
    "0123456789",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "abcdefghijklmnopqrstuvwxyz",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
    "@#$&(_-=%*':/!?+÷;`]}><{[^¡¿~™®©¢¥€£¶§×`",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@#$&(_-=%*':/!?+÷;`]}><{[^¡¿~™®©¢¥€£¶§×`"
};

void get_password_format(std::string& format);
void get_password_info(int& num_passwords, int& password_length);
void get_file_name(std::string& output_file);
void generate_passwords(const std::string& password_format, int num_passwords, int password_length, const std::string& output_file);

int main() {
    std::string format;
    get_password_format(format);
    int num_passwords, password_length;
    get_password_info(num_passwords, password_length);
    std::string output_file;
    get_file_name(output_file);

    generate_passwords(format, num_passwords, password_length, output_file);
    return 0;
}

void get_password_format(std::string& format) {
    while (true) {
        std::cout << GREEN_COLOR << BOLD_TEXT << "Enter the password format:" << std::endl;
        std::cout << "[1] 1234..." << std::endl;
        std::cout << "[2] ABCD..." << std::endl;
        std::cout << "[3] abcd..." << std::endl;
        std::cout << "[4] ABcd..." << std::endl;
        std::cout << "[5] @#$&..." << std::endl;
        std::cout << "[6] Ac23..." << std::endl;
        std::cout << "[7] Ab3&..." << std::endl;
        std::cout << YELLOW_COLOR;
        std::string select;
        std::cin >> select;

        if (select == "1" || select == "2" || select == "3" || select == "4" || select == "5" || select == "6" || select == "7") {
            format = select;
            break;
        }
    }
}

void get_password_info(int& num_passwords, int& password_length) {
    while (true) {
        std::cout << GREEN_COLOR << BOLD_TEXT << "How many passwords do you need? [Ex:1000]:" << std::endl;
        std::cout << YELLOW_COLOR;
        std::string input;
        std::cin >> input;
        num_passwords = std::stoi(input);

        if (num_passwords > 0) {
            break;
        }
    }

    while (true) {
        std::cout << GREEN_COLOR << BOLD_TEXT << "How long is the password? [Ex:8]:" << std::endl;
        std::cout << YELLOW_COLOR;
        std::string input;
        std::cin >> input;
        password_length = std::stoi(input);

        if (password_length > 0) {
            break;
        }
    }
}

void get_file_name(std::string& output_file) {
    while (true) {
        std::cout << GREEN_COLOR << BOLD_TEXT << "Enter the filename to save passwords [Ex: pass.txt]:" << std::endl;
        std::cout << YELLOW_COLOR;
        std::cin >> output_file;

        if (output_file.empty()) {
            output_file = "pass.txt";
        }

        if (output_file.size() < 4 || output_file.substr(output_file.size() - 4) != ".txt") {
            output_file += ".txt";
        }

        break;
    }
}

void generate_passwords(const std::string& password_format, int num_passwords, int password_length, const std::string& output_file) {
    const std::string characters = PASSWORD_FORMATS[std::stoi(password_format) - 1];
    std::string passwords[num_passwords];
    int count = 0;

    while (count < num_passwords) {
        std::string password;
        password.resize(password_length);

        for (int i = 0; i < password_length; i++) {
            int index = std::rand() % characters.size();
            password[i] = characters[index];
        }

        bool is_duplicate = false;

        for (int i = 0; i < count; i++) {
            if (passwords[i] == password) {
                is_duplicate = true;
                break;
            }
        }

        if (!is_duplicate) {
            passwords[count] = password;
            std::cout << GREEN_COLOR << BOLD_TEXT << "Password: " << YELLOW_COLOR << password << std::endl;
            count++;
        }
    }

    std::ofstream file(output_file);

    for (int i = 0; i < num_passwords; i++) {
        file << passwords[i] << std::endl;
    }

    file.close();
    std::cout << GREEN_COLOR << BOLD_TEXT << "Saved as " << output_file << std::endl;
}
