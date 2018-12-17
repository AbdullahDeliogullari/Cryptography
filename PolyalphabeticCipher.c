#include <stdio.h>
#include <stdlib.h>

#define MAX 100

char Vigenere_Table_encrypt(char row_char,char column_char);
char *Vigenere_encrypt(char *character, char *key);
char Vigenere_Table_decrypt(char character,char column_char);
int str_size(char *str);
char *str_reverse(char *str);
char *Vigenere_decrypt(char *character,char *key);

int main()
{
    printf("%s\n",Vigenere_encrypt("abdullah","key"));
    printf("%s\n",Vigenere_decrypt("KFBEPJKL","key"));
}
int str_size(char *str){
    int i;
    for(i = 0;*(str + i)!= '\0';i = i + 1)
        ;;
    return i;
}

char Vigenere_Table_encrypt(char row_char,char column_char){
    if(row_char >= 'a' && row_char <= 'z')
        row_char = row_char - 32;
    if(column_char >= 'a' && column_char <= 'z')
        column_char = column_char - 32;
    return 'A' + (((row_char + column_char) % 65) % 26);
}

char Vigenere_Table_decrypt(char character,char column_char){
    if(character >= 'a' && character <= 'z')
        character = character - 32;
    if(column_char >= 'a' && column_char <= 'z')
        column_char = column_char - 32;
    if(character >= column_char)
        return character - (column_char - 'A');
    if(character < column_char)
        return 'Z' - ((column_char - 'A') - (character - 'A')) + 1;

}

char *Vigenere_encrypt(char *character, char *key){
    static char encrypted_word[MAX];
    int i;
    int j = 0;
    for(i = 0;*(character + i) != '\0';i = i + 1){
        if(*(key + j) == '\0')
            j = 0;

        encrypted_word[i] = Vigenere_Table_encrypt(*(character + i),*(key + j));
        j = j + 1;
    }
    return encrypted_word;
}

char *Vigenere_decrypt(char *character,char *key){
    static char decrypted_word[MAX];
    int i;
    int j = 0;
    for(i = 0;i < str_size(character); i = i + 1){
        if(*(key + j) == '\0'){
            j = 0;
        }
        decrypted_word[i] = Vigenere_Table_decrypt(*(character + i),*(key + j));
        j = j + 1;
    }
    return decrypted_word;
}
