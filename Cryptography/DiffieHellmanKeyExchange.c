#include <stdio.h>
#include <stdlib.h>

int mod(int generator,int power,int prime_modulus);

// public generator and prime_modulus
int generator = 3;
int prime_modulus = 17;

int main(){
    printf("Public generator : %d - Public prime_modulus : %d\n\n",generator,prime_modulus);

    int alice_private_number = 15;
    int bob_private_number = 13;

    printf("Alice private number : %d\n",alice_private_number);
    printf("Bob private number : %d\n\n",bob_private_number);

    int alice_public_number = mod(generator,alice_private_number,prime_modulus);
    int bob_public_number = mod(generator,bob_private_number,prime_modulus);

    printf("Alice public number : %d\n",alice_public_number);
    printf("Bob public number : %d\n\n",bob_public_number);

    int alice_private_key = mod(bob_public_number,alice_private_number,prime_modulus);
    int bob_private_key = mod(alice_public_number,bob_private_number,prime_modulus);

    printf("Alice private key : %d\n",alice_private_key);
    printf("Bob private key : %d\n",bob_private_key);
}

// mod operation for big numbers
int mod(int generator,int power,int prime_modulus){
    int product = 1;
    for(int i = 0;i < power;i = i + 1){
        if(product < prime_modulus)
            product = product * generator;
        else{
            product = product % prime_modulus;
            product = product * generator;
        }
    }
    return product % prime_modulus;
}
