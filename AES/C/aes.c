//
//  main.c
//  AES
//
//  Created by Joan Torres on 11/16/14.
//  Copyright (c) 2014 Joan Torres. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void cipher(char state[]);
void printArrayOfStrings(char arr[][3]);
void split(char input[], char tokenized[][3]);
void hexafy(char input[][3], uint16_t hexadecimal[]);
void keyExpansion(uint16_t expanded_key[]);
void rotWord(uint16_t word[4]);
void subWord(uint16_t word[4]);
void addRoundKey(uint16_t state[], uint16_t expanded_key[], int round);
void subBytes(uint16_t state[]);
void shiftRows(uint16_t state[]);
void mixColumns(uint16_t state[]);

char *key = "2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c";
int nb = 4, nk = 4, nr = 10;

const uint16_t rcon[11] = { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

const int sbox[] = {
         0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
         0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
         0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
         0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
         0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
         0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
         0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
         0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
         0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
         0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
         0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
         0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
         0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
         0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
         0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
         0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

int main(){
    
    char *input = "32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34";
    char tokenizedInput[16][3] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint16_t hexadecimal[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    printf("Input: %s\n", input);
    printf("Key:   %s\n", key);
    split(input, tokenizedInput);
    printf("Each byte:\n");
    hexafy(tokenizedInput, hexadecimal);
    printArrayOfStrings(tokenizedInput);

    cipher(hexadecimal);
    printf("Input: %s\n", input);

    return 0;
}

void printArrayOfStrings(char arr[][3]){
    for (int i = 0; i < 16; i++) {
        printf( "%7d%13s\n", i, arr[i] );
    }
}

void cipher(uint16_t state[]){
    uint16_t expanded_key[nk*(nb*(nr+1))];

    keyExpansion(expanded_key);

    addRoundKey(state, expanded_key, 0);
}

void split(char input[], char tokenized[][3]){
    char *token, string[strlen(input)];
    int i=0;

    strcpy(string, input);

    token = strtok( string, " " );

    while ( token != NULL ) {
        strcpy(tokenized[i], token);
        token = strtok( NULL, " " );
        i++;
    }
}

void hexafy(char input[][3], uint16_t hexadecimal[]){
    int i=0;
    char *str;
    char dest[] = {'0', 'x', 0, 0, 0};

    for (i = 0; i< 16; i++) {
//        printf("%7s-", input[i]);
        dest[2] = input[i][0];
        dest[3] = input[i][1];
        hexadecimal[i] = (uint16_t) strtoul(dest, &str, 16);
//        printf("%02x\n", hexadecimal[i]);
    }
}

void keyExpansion(uint16_t expanded_key[]){
    char cipherKey[16][3] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int i, j, limit = (nb*(nr+1));
    uint16_t temp[4];

    split(key, cipherKey);
    hexafy(cipherKey, expanded_key);

    for (i = nk; i < limit; i++) {
        for (j = 0; j < 4; j++)
            temp[j] = expanded_key[j+i*nk-4];
    
        if (i % nk*nk == 0) {
            //temp = SubWord(RotWord(temp)) xor Rcon[i/Nk]
            rotWord(temp);
            subWord(temp);
            temp[0] ^= rcon[i/nk];
        }

        for (j = 0; j < 4; j++)
            expanded_key[i*nk+j]= expanded_key[(i-nk)*nk+j] ^ temp[j];

    }
}

void rotWord(uint16_t word[4]){
    uint16_t first = word[0];

    for(int i = 0; i < 3; i++)
        word[i] = word[i+1];

    word[3] = first;

}

void subWord(uint16_t word[4]){
    for(int i = 0; i < 4; i++)
        word[i] = sbox[word[i]];
}

void addRoundKey(uint16_t state[], uint16_t expanded_key[], int round){
    int i = -1;

    while( i++ < 16)
        state[i] = state[i] ^ expanded_key[round*16 + i];
}

void subBytes(uint16_t state[]){
    int i = -1;

    while( i++ < 16)
        state[i] = sbox[state[i]];
}

void shiftRows(uint16_t state[]){
    int r, c;
    uint16_t temp[4*nb];

    for (r = 1; r < 4; r++)
        for (c = 0; c < nb; c++)
            temp[r+4*c] = state[r + 4*((c+r)%nb)];

    for (r = 1; r < 4; r++)
        for(c = 0; c < nb; c++ )
            state[r+4*c] = temp[r+4*c];
}

void mixColumns(uint16_t state[]){
    int c, i;
    uint16_t h, a[4], b[4];

    for (c = 0; c < 4; c++){
        for (i = 0; i < 4; i++){
            a[i] = state[i+4*c];
            h = state[i+4*c] >> 7;
            b[i] = state[i+4*c] << 1;
            if( h > 0 ) b[i] ^= 0x1b;
            b[i] %= 256;
        }

        state[0+4*c] = b[0] ^ a[1] ^ b[1] ^ a[2] ^ a[3];
        state[1+4*c] = a[0] ^ b[1] ^ a[2] ^ b[2] ^ a[3];
        state[2+4*c] = a[0] ^ a[1] ^ b[2] ^ a[3] ^ b[3];
        state[3+4*c] = a[0] ^ b[0] ^ a[1] ^ a[2] ^ b[3];
    }
}
