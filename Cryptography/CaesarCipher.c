#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char caesar_encrypt(char character, int shift);
char caesar_decrypt(char character, int shift);
char *encrypt(char *word);
char *decrypt(char *word);


int main()
{
    printf("%s\n",encrypt("abdullah"));
    printf("%s",decrypt(encrypt("abdullah")));
    int k = 1;
    int t = 1;
    printf("%d\n",k++);
    printf("%d\n",++t);

    int *p;
    int l = 20;
    p = &l;
    printf("%p",p);
}


// Encrypt Single Character
char caesar_encrypt(char character, int shift){
    if(character >= 'a' && character <= 'z')
        character = character - 32; // to uppercase
    character = (((character - 65) + shift) % 26) + 65; // mod 26
    return character;
}

// Decrypt Single Character
char caesar_decrypt(char character, int shift){
    character = ((((character - 65) - shift) + 26) % 26) + 65; // mod 26
    character = character + 32;
    return character;
}

// Encrypt a String
char *encrypt(char *word){
    static char encrypted_word[MAX];
    int i;
    for(i = 0;*(word + i) != '\0';i = i + 1)
        encrypted_word[i] = caesar_encrypt(*(word + i),2);
    return encrypted_word;
}

// Decrypt a String
char *decrypt(char *word){
    static char decrypted_word[MAX];
    int i;
    for(i = 0;*(word + i) != '\0';i = i + 1)
        decrypted_word[i] = caesar_decrypt(*(word + i),2);
    return decrypted_word;
}



