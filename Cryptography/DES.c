#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assistive functions
int *array_xor_48(int *data,int *key);
int *array_xor_32(int *data,int *key);
int *array_shift(int *data,int shift_amount);
int *array_sum_56(int *left_data,int *right_data);
int *array_sum_64(int *left_data,int *right_data);
int power(int number,int power);
int *Decimal_to_Binary_4(int data);
int Binary_to_Decimal(int *data,int length);

// Functions for each step in DES
int *Initial_Permutation(int *data);
int *Inverse_Permutation(int *data);
int *Expansion_Permutation(int *data);
int *Permutation(int *data);
int *Permuted_Choice_1(int *data);
int *Permuted_Choice_2(int *data);
int *Left_Shifting(int *data,int round);
int *Substitution_Sbox(int data[48]);

// Using sub_functions under DES
int *DES(int data[64],int key[64]);

int main(){
    int msg[64] = {1,1,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,1,0};
    int key[64] = {1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0};

    int *encrypted_msg = DES(msg,key);
    for(int i = 0;i < 64;i = i + 1){
        printf("%d",*(encrypted_msg + i));
    }
}

// 48 bit data xor 48 bit key
int *array_xor_48(int *data,int *key){
    static int xored_plaintext[48];
    for(int i = 0;i < 48;i = i + 1){
        xored_plaintext[i] = *(data + i) ^ *(key + i);
    }
    return xored_plaintext;
}

// 32 bit data xor 32 bit key
int *array_xor_32(int *data,int *key){
    static int xored_plaintext[32];
    for(int i = 0;i < 32;i = i + 1){
        xored_plaintext[i] = *(data + i) ^ *(key + i);
    }
    return xored_plaintext;
}

// 28 bit data --> shift left
int *array_shift(int *data,int shift_amount){
    static int shifted_data[28];
    shift_amount = -shift_amount;
    for(int i = 0;i < 28;i = i + 1){
        if(i + shift_amount < 0)
            shifted_data[28 + i + shift_amount] = *(data + i);
        else if(i + shift_amount > 27)
            shifted_data[i + shift_amount - 28] = *(data + i);
        else
            shifted_data[i + shift_amount] = *(data + i);
    }
    return shifted_data;
}

// 28 bit array + 28 bit array = 56 bit array
int *array_sum_56(int *left_data,int *right_data){
    static int summed_array[56];
    int index = 0;
    for(int i = 0;i < 28;i = i + 1){
        summed_array[index] = *(left_data + i);
        index = index + 1;
    }
    for(int j = 0;j < 28;j = j + 1){
        summed_array[index] = *(left_data + j);
        index = index + 1;
    }
    return summed_array;
}

// 32 bit array + 32 bit array = 64 bit array
int *array_sum_64(int *left_data,int *right_data){
    static int summed_array[64];
    int index = 0;
    for(int i = 0;i < 32;i = i + 1){
        summed_array[index] = *(left_data + i);
        index = index + 1;
    }
    for(int j = 0;j < 32;j = j + 1){
        summed_array[index] = *(left_data + j);
        index = index + 1;
    }
    return summed_array;
}

// product = number ** power
int power(int number,int power){
    int product = 1;
    for(int i = 0;i < power;i = i + 1)
        product = product * number;
    return product;
}

// Decimal number --> 4 bit array(binary number)
int *Decimal_to_Binary_4(int data){
    static int binary[4];
    for(int i = 3;i > 0;i = i - 1){
        binary[i] = data % 2;
        data = data / 2;
    }
    binary[0] = data;
    return binary;
}

// (int length) bit array(binary number) --> Decimal number
int Binary_to_Decimal(int *data,int length){
    int decimal = 0;
    for(int i = 0;i < length;i = i + 1)
        decimal = decimal + *(data + length - i - 1) * power(2,i);
    return decimal;
}

// 64 bit input --> shuffle --> 64 bit output
int *Initial_Permutation(int *data){
    static int rearranged_data[64];

    int const IP[64] = {58,50,42,34,26,18,10,2,
                        60,52,44,36,28,20,12,4,
                        62,54,46,38,30,22,14,6,
                        64,56,48,40,32,24,16,8,
                        57,49,41,33,25,17, 9,1,
                        59,51,43,35,27,19,11,3,
                        61,53,45,37,29,21,13,5,
                        63,55,47,39,31,23,15,7};

    for(int i = 0;i < 64;i = i + 1){
        rearranged_data[i] = *(data + IP[i] - 1);
    }
    return rearranged_data;
}

// 64 bit input --> shuffle back --> 64 bit output
// return back to input of Initial_Permutation
int *Inverse_Permutation(int *data){
    static int arranged_data[64];

    int const INP[64] = {40,8,48,16,56,24,64,32,
                         39,7,47,15,55,23,63,31,
                         38,6,46,14,54,22,62,30,
                         37,5,45,13,53,21,61,29,
                         36,4,44,12,52,20,60,28,
                         35,3,43,11,51,19,59,27,
                         34,2,42,10,50,18,58,26,
                         33,1,41, 9,49,17,57,25};

    for(int i = 0;i < 64;i = i + 1){
        arranged_data[i] = *(data + INP[i] - 1);
    }
    return arranged_data;
}

// 32 bit input --> expand --> 48 bit output
int *Expansion_Permutation(int *data){
    static int expanded_data[48];

    int const EP[48] = {32, 1, 2, 3, 4, 5, 4, 5,
                        6, 7, 8, 9, 8, 9, 10,11,
                        12,13,12,13,14,15,16,17,
                        16,17,18,19,20,21,20,21,
                        22,23,24,25,24,25,26,27,
                        28,29,28,29,30,31,32, 1};

    for(int i = 0;i < 48;i = i + 1){
        expanded_data[i] = *(data + EP[i] - 1);
    }
    return expanded_data;
}

// 32 bit input --> shuffle --> 32 bit output
int *Permutation(int *data){
    static int permuted_data[32];

    int const P[32] = {16,7,20,21,29,12,28,17,
                       1 ,15,23,26,5,18,31,10,
                       2 ,8,24,14,32,27, 3, 9,
                       19,13,30, 6,22,11,4,25};

    for(int i = 0;i < 32;i = i + 1){
        permuted_data[i] = *(data + P[i] - 1);
    }
    return permuted_data;
}

// 64 bit input --> narrow --> 56 bit output
int *Permuted_Choice_1(int *data){
    static int permuted_data_1[56];

    int PC1[56] = {57,49,41,33,25,17, 9,
                   1,58,50,42,34,26, 18,
                   10, 2,59,51,43,35,27,
                   19,11, 3,60,52,44,36,
                   63,55,47,39,31,23,15,
                   7,62,54,46,38,30, 22,
                   14, 6,61,53,45,37,29,
                   21,13, 5,28,20,12, 4};

    for(int i = 0;i < 56;i = i + 1){
        permuted_data_1[i] = *(data + PC1[i] - 1);
    }
    return permuted_data_1;
}

// 56 bit input --> narrow --> 48 bit output
int *Permuted_Choice_2(int *data){
    static int permuted_data_2[48];

    int PC2[48] = {14,17,11,24, 1, 5,
                   3 ,28,15, 6,21,10,
                   23,19,12, 4,26, 8,
                   16, 7,27,20,13, 2,
                   41,52,31,37,47,55,
                   30,40,51,45,33,48,
                   44,49,39,56,34,53,
                   46,42,50,36,29,32};

    for(int i = 0;i < 48;i = i + 1){
        permuted_data_2[i] = *(data + PC2[i] - 1);
    }
    return permuted_data_2;
}

// 56 bit input --> 28-28 bit split and shift left --> 56 bit output
int *Left_Shifting(int *data,int round){
    int S[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
    int shift_amount = S[round];

    int left_data[28];
    int right_data[28];

    for(int i = 0;i < 28;i = i + 1){
        left_data[i] = *(data + i);
        right_data[i] = *(data + i + 28);
    }
    int *shifted_left_data = array_shift(left_data,round);
    int *shifted_right_data = array_shift(right_data,round);

    int *shifted_data = array_sum_56(shifted_left_data,shifted_right_data);
    return shifted_data;
}

// 48 bit input --> 32 bit output
int *Substitution_Sbox(int *data){
    static const int S_box[8][4][16] =
   {
   {
   {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
   { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
   { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
   {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
   },

   {
   {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
   { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
   { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
   {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
   },

   {
   {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
   {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
   {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
   { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
   },

   {
   { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
   {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
   {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
   { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
   },

   {
   { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
   {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
   { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
   {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
   },

   {
   {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
   {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
   { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
   { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
   },

   {
   { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
   {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
   { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
   { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
   },

   {
   {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
   { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
   { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
   { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
   },
   };
   static int Substituted_data[32];
   int chunk[6]; // six bit chunk
   int y_binary[2]; // 1. and 6. bit of chunk
   int z_binary[4]; // 2,3,4,5 bit of chunk

   int data_index = 0;
   int chunk_index = 0;

   int x = 0;
   int y = 0;
   int z = 0;
   for(int i = 0;i <= 48;i = i + 1){
       if(i % 6 == 0 && i != 0){
           y_binary[0] = chunk[0];
           y_binary[1] = chunk[5];
           y = Binary_to_Decimal(y_binary,2);

           z_binary[0] = chunk[1];
           z_binary[1] = chunk[2];
           z_binary[2] = chunk[3];
           z_binary[3] = chunk[4];
           z = Binary_to_Decimal(z_binary,4);

           int *subs_binary = Decimal_to_Binary_4(S_box[x][y][z]);
           for(int j = 0;j < 4;j = j + 1){
                Substituted_data[data_index] = *(subs_binary + j);
                data_index = data_index + 1;
           }
           x = x + 1;
           chunk_index = 0;
       }
       chunk[chunk_index] = data[i];
       chunk_index = chunk_index + 1;
   }
   return Substituted_data;
}

// DES algorithm
int *DES(int *data,int *key){
    static int ciphertext[64];
    int *ip_data = Initial_Permutation(data);
    int *plaintext = ip_data;

    int *pc1_key = Permuted_Choice_1(key);
    int *plaintext_key = pc1_key;

    int left_plaintext[32];
    int right_plaintext[32];
    for(int i = 0;i < 32;i = i + 1){
        left_plaintext[i] = *(plaintext + i);
        right_plaintext[i] = *(plaintext + i + 32);
    }

    for(int round = 0;round < 16;round = round + 1){
        int *shifted_key = Left_Shifting(plaintext_key,round);
        int *pc2_key = Permuted_Choice_2(shifted_key);
        int *plaintext_key = shifted_key;
        int *ep_right_plaintext = Expansion_Permutation(right_plaintext);
        int *xored_right_plaintext = array_xor_48(ep_right_plaintext,pc2_key);
        int *subs_right_plaintext = Substitution_Sbox(xored_right_plaintext);

        int *perm_right_plaintext = Permutation(subs_right_plaintext);

        int *xored2_right_plaintext = array_xor_32(perm_right_plaintext,left_plaintext);

        for(int i = 0;i < 32;i = i + 1){
            left_plaintext[i] = right_plaintext[i];
        }
        for(int i = 0;i < 32;i = i + 1){
            right_plaintext[i] = *(xored2_right_plaintext + i);
        }
    }
    int *swapped_plaintext = array_sum_64(left_plaintext,right_plaintext);
    int *inv_plaintext = Inverse_Permutation(swapped_plaintext);

    for(int i = 0;i < 64;i = i + 1){
        ciphertext[i] = *(inv_plaintext + i);
    }
    return ciphertext;
}
