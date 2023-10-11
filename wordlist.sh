#!/bin/bash

RED_COLOR="\033[0;31m"
GREEN_COLOR="\033[0;32m"
YELLOW_COLOR="\033[0;33m"
WHITE_COLOR="\033[0;37m"
BOLD_TEXT="\033[5;1m"
BACKGROUND_RED="\033[41m"
RESET_FORMAT="\033[0m"

PASSWORD_FORMATS=("0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" "@#$&(_-=%*':/!?+÷;`]}><{[^¡¿~™®©¢¥€£¶§×`" "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@#$&(_-=%*':/!?+÷;`]}><{[^¡¿~™®©¢¥€£¶§×`")

get_password_format() {
    while true; do
        echo -e "${GREEN_COLOR}${BOLD_TEXT}"
        echo "Enter the password format:"
        echo "[1] 1234..."
        echo "[2] ABCD..."
        echo "[3] abcd..."
        echo "[4] ABcd..."
        echo "[5] @#$&..."
        echo "[6] Ac23..."
        echo "[7] Ab3&..."
        echo -e "${YELLOW_COLOR}"
        read select

        if [[ $select == [1-7] ]]; then
            password_format=${PASSWORD_FORMATS[$select-1]}
            break
        fi
    done
}

get_password_info() {
    while true; do
        echo -e "${GREEN_COLOR}${BOLD_TEXT}"
        echo "How many passwords do you need? [Ex:1000]:"
        echo -e "${YELLOW_COLOR}"
        read num_passwords

        if [[ $num_passwords -gt 0 ]]; then
            break
        fi
    done

    while true; do
        echo -e "${GREEN_COLOR}${BOLD_TEXT}"
        echo "How long is the password? [Ex:8]:"
        echo -e "${YELLOW_COLOR}"
        read password_length

        if [[ $password_length -gt 0 ]]; then
            break
        fi
    done
}

get_file_name() {
    while true; do
        echo -e "${GREEN_COLOR}${BOLD_TEXT}"
        echo "Enter the filename to save passwords [Ex: pass.txt]:"
        echo -e "${YELLOW_COLOR}"
        read output_file

        if [ -z "$output_file" ]; then
            output_file="pass.txt"
        fi

        if [[ $output_file != *.txt ]]; then
            output_file="$output_file.txt"
        fi

        break
    done
}

generate_passwords() {
    characters=$1
    num_passwords=$2
    password_length=$3
    output_file=$4
    passwords=()
    count=0

    while [[ $count -lt $num_passwords ]]; do
        password=""
        for ((i = 0; i < password_length; i++)); do
            index=$((RANDOM % ${#characters}))
            password="${password}${characters:$index:1}"
        done

        is_duplicate=0
        for pass in "${passwords[@]}"; do
            if [ "$password" == "$pass" ]; then
                is_duplicate=1
                break
            fi
        done

        if [[ $is_duplicate -eq 0 ]]; then
            passwords+=("$password")
            echo -e "${GREEN_COLOR}${BOLD_TEXT}"
            echo -e "${YELLOW_COLOR}Password: $password"
            count=$((count + 1))
        fi
    done

    for pass in "${passwords[@]}"; do
        echo "$pass" >> "$output_file"
    done

    echo -e "${GREEN_COLOR}${BOLD_TEXT}"
    echo "Saved as $output_file"
}

main() {
    echo -e "${RED_COLOR}${BOLD_TEXT}"
    cat logo/logo.txt
    echo -e "${WHITE_COLOR}"

    get_password_format
    get_password_info
    get_file_name

    generate_passwords "$password_format" $num_passwords $password_length "$output_file"
}

trap 'echo -e "${RED_COLOR}${BOLD_TEXT}" && echo -e "Sudden stop!" && echo -e "${WHITE_COLOR}" && exit' INT

main
