from random import choice
from os import system as UI
numbers = "0123456789"
ABC = "ABCDEFGHIJKLMNOPQRSTYVWXYZ"
abc = "abcdefghijklmnopqrstyvwxyz"
symbol = "@#$&(_-=%*':/!?+÷;`]}><{[^¡¿~™®©¢¥€£¶§×`)"
Abc123 = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789"
ABcd = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"
Abc123symbols = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789@#$&(_-=%*':/!?+÷;`]}><{[^¡¿~™®©¢¥€£¶§×`)"
print("\033[;31;m\033[;5;m")
UI("cat logo/logo.txt")
print("\033[;37;m")
password = []
try:
    while True:
        select = input("""\033[;32;m\033[;5;m

╭── Choose the password \033[;31;mformat\033[;32;m
│
├─ [1] \033[;31;m1234... \033[;32;m [default]
├─ [2] \033[;31;mABCD... \033[;32;m
├─ [3] \033[;31;mabcd... \033[;32;m
├─ [4] \033[;31;mABcd... \033[;32;m
├─ [5] \033[;31;m@#$&... \033[;32;m
├─ [6] \033[;31;mAc23... \033[;32;m
├─ [7] \033[;31;mAb3&... \033[;32;m
│
╰────▶\033[;33;m """)
        if select in "123456":
            break
    while True:
        try:
            num_while = int(input("\033[;32;m\033[;5;m│\n│\n├── How many passwords do you need ? [Ex:1000]\n│\n│\n╰────▶\033[;33;m\033[;5;m "))
            length_pass = int(input("\033[;32;m\033[;5;m│\n│\n├── How long is password ? [Ex:8]\n│\n│\n╰────▶\033[;33;m\033[;5;m "))
            break
        except ValueError:
            print("\033[;31;m│\n│\n├── \033[;37;m\033[;41;mEnter number!\033[;40;m")
    while True:
        name_file = input("\033[;32;m\033[;5;m│\n│\n├── Enter name save file [Ex:pass.txt]\n│\n│\n╰────▶\033[;33;m\033[;5;m")
        if name_file[-4:] != ".txt":
            name_file += ".txt"
            break
        break
    def run(data,num,length,name_file):
        f = open(name_file,"w")
        number_while = 0
        while True:
            password_ram = ""
            for i in range(length):
                password_ram += choice(data)    
            if password_ram not in password:
                password.append(password_ram)
                f.writelines(f"{password_ram}\n")
                print(f"\033[;32;m│\n├── {password_ram}")
                number_while += 1
            if number_while >= num: 
                print(f"│\n╰────⎙ Saved as {name_file}")
                break
    if select == "1":
        run(numbers,num_while,length_pass,name_file)
    elif select == "2":
        run(ABC,num_while,length_pass,name_file)
    elif select == "3":
        run(abc,num_while,length_pass,name_file)
    elif select == "4":
        run(ABcd,num_while,length_pass,name_file)
    elif select == "5":
        run(symbol,num_while,length_pass,name_file)
    elif select == "6":
        run(Abc123,num_while,length_pass,name_file)
    elif select == "7":
        run(Abc123symbols,num_while,length_pass,name_file)
    else :
        run(numbers,num_while,length_pass,name_file)
except KeyboardInterrupt:
    exit("\033[;31;m│\n│\n│\n├─── sudden stop!\n│\n╰─── Exit...\033[;37;m")
