#include <stdio.h>
#include <stdlib.h>

int mod(int generator,int power,int prime_modulus);
int totient_function(int p1,int p2);

int prime1 = 53;
int prime2 = 59;

int public_exponent = 3;

int main(){
    int prime_modulus = prime1 * prime2;
    int totient = totient_function(prime1,prime2);
    int k = 2;


    int bob_message = 89;
    int bob_encrypted_message = mod(bob_message,public_exponent,prime_modulus);
    printf("Bob original message : %d\n",bob_message);
    printf("Bob encrypted message : %d\n\n",bob_encrypted_message);

    int alice_private_key = ((k * totient) + 1) / public_exponent; // key for decrypt
    int alice_decrypted_message = mod(bob_encrypted_message,alice_private_key,prime_modulus);
    printf("Alice decrypted message : %d\n",alice_decrypted_message);

}
// totient function calculator
int totient_function(int p1,int p2){
    int totient = (p1 - 1) * (p2 - 1);
    return totient;
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
