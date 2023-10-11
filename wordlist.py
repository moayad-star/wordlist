import os
import random
import readline

# Define constants for color formatting
RED_COLOR = "\033[0;31m"
GREEN_COLOR = "\033[0;32m"
YELLOW_COLOR = "\033[0;33m"
WHITE_COLOR = "\033[0;37m"
BOLD_TEXT = "\033[5;1m"
BACKGROUND_RED = "\033[41m"
RESET_FORMAT = "\033[0m"

# Define password formats
PASSWORD_FORMATS = {
    '1': "0123456789",
    '2': "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    '3': "abcdefghijklmnopqrstuvwxyz",
    '4': "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
    '5': "@#$&(_-=%*':/!?+÷;`]}><{[^¡¿~™®©¢¥€£¶§×`",
    '6': "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
    '7': "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@#$&(_-=%*':/!?+÷;`]}><{[^¡¿~™®©¢¥€£¶§×`"
}

def main():
    print(f"{RED_COLOR}{BOLD_TEXT}")
    os.system("cat logo/logo.txt")
    print(f"{WHITE_COLOR}")

    password_format = get_password_format()
    num_passwords, password_length = get_password_info()
    output_file = get_file_name()

    generated_passwords = generate_passwords(password_format, num_passwords, password_length, output_file)
    save_passwords(output_file, generated_passwords)

def get_password_format():
    while True:
        select = input(f"{GREEN_COLOR}{BOLD_TEXT}\n╭── Choose the password format\n│\n"
                       f"├─ [1] {RED_COLOR}1234... {GREEN_COLOR}\n"
                       f"├─ [2] {RED_COLOR}ABCD... {GREEN_COLOR}\n"
                       f"├─ [3] {RED_COLOR}abcd... {GREEN_COLOR}\n"
                       f"├─ [4] {RED_COLOR}ABcd... {GREEN_COLOR}\n"
                       f"├─ [5] {RED_COLOR}@#$&... {GREEN_COLOR}\n"
                       f"├─ [6] {RED_COLOR}Ac23... {GREEN_COLOR}\n"
                       f"├─ [7] {RED_COLOR}Ab3&... {GREEN_COLOR}\n"
                       f"│\n╰────▶{YELLOW_COLOR} ")
        if select in PASSWORD_FORMATS:
            return select

def get_password_info():
    while True:
        try:
            num_passwords = int(input(f"{GREEN_COLOR}{BOLD_TEXT}│\n│\n├── How many passwords do you need ? [Ex:1000]\n│\n│\n"
                                    f"╰────▶{YELLOW_COLOR}{BOLD_TEXT} "))
            password_length = int(input(f"{GREEN_COLOR}{BOLD_TEXT}│\n│\n├── How long is password ? [Ex:8]\n│\n│\n"
                                       f"╰────▶{YELLOW_COLOR}{BOLD_TEXT} "))
            return num_passwords, password_length
        except ValueError:
            print(f"{RED_COLOR}{BOLD_TEXT}│\n│\n├── {WHITE_COLOR}{BACKGROUND_RED}Enter a number!{RESET_FORMAT}")

def get_file_name():
    while True:
        output_file = input(f"{GREEN_COLOR}{BOLD_TEXT}│\n│\n├── Enter the filename to save passwords [Ex: pass.txt]\n│\n│\n"
                            f"╰────▶{YELLOW_COLOR}{BOLD_TEXT}")
        if output_file == "":
            output_file = "pass.txt"
        if output_file[-4:] != ".txt":
            output_file += ".txt"
        return output_file

def generate_passwords(password_format, num_passwords, password_length, output_file):
    characters = PASSWORD_FORMATS[password_format]
    passwords = set()

    count = 0
    while count < num_passwords:
        password = "".join(random.choice(characters) for _ in range(password_length))
        if password not in passwords:
            passwords.add(password)
            print(f"{GREEN_COLOR}{BOLD_TEXT}│\n├── {YELLOW_COLOR}{password}")
            count += 1

    print(f"{GREEN_COLOR}│\n╰────⎙ Saved as {output_file}")
    return passwords

def save_passwords(output_file, passwords):
    with open(output_file, "w") as file:
        file.writelines("\n".join(passwords))

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        exit(f"{RED_COLOR}{BOLD_TEXT}│\n│\n│\n├── Sudden stop!\n│\n╰── Exit...{WHITE_COLOR}")
