#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char monoalp_encrypt(char character);
char monoalp_decrypt(char character);
char *encrypt(char *word);
char *decrypt(char *word);

char random_mapping[] = {'q','w','E','r','t','y','u','I','o','p','a','s','d','f','g','h','j','k','L','z','x','c','v','b','n','m'};

int main()
{
    printf("%s\n",encrypt("abdullah"));
    printf("%s\n",decrypt(encrypt("abdullah")));
}

// Encrypt Single Character
char monoalp_encrypt(char character){
    int mapping_place;
    if(character >= 'a' && character <= 'z')
        character = character - 32; // to uppercase
    mapping_place = character - 65;
    return random_mapping[mapping_place];
}

// Decrypt Single Character
char monoalp_decrypt(char character){
    int i = 0;
    char word;
    while(random_mapping[i] != character)
        i = i + 1;
    char decrypted_character = word + i + 65;
    return decrypted_character;
}

// Encrypt a String
char *encrypt(char *word){
    static char encrypted_word[MAX];
    int i;
    for(i = 0;*(word + i) != '\0';i = i + 1)
        encrypted_word[i] = monoalp_encrypt(*(word + i));
    return encrypted_word;
}

// Decrypt a String
char *decrypt(char *word){
    static char decrypted_word[MAX];
    int i;
    for(i = 0;*(word + i) != '\0';i = i + 1)
        decrypted_word[i] = monoalp_decrypt(*(word + i));
    return decrypted_word;
}
