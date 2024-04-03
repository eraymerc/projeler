#include "bignumbers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief
/// @param num1
/// @param num2
/// @param lastCarry the last carry for comparison (optional)
void addNumber(struct Bignumber *num1, struct Bignumber *num2, int *lastCarry) {
    size_t l1 = num1->size;
    size_t l2 = num2->size;
    size_t length = (l1 > l2) * (l1) + (l1 < l2) * (l2) + (l1 == l2) * l1;

    struct BignumberTail *current1 = num1->next;
    struct BignumberTail *current2 = num2->next;
    int carry = 0;
    int sum = 0;
    int n1 = current1->data, n2 = current2->data;
    for (size_t i = 0; i < length; i++) {
        sum = n1 + n2 + carry;
        current1->data = sum % 256;
        carry = sum / 256;

        if (current1->next == NULL && (i + 1) != length) {
            struct BignumberTail *new =
                (struct BignumberTail *)malloc(sizeof(struct BignumberTail));
            if (new == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }

            num1->size += 1;
            new->data = 0;
            new->next = NULL;
            current1->next = new;
        }
        if (current1->next != NULL) {
            current1 = current1->next;
            n1 = current1->data;
        } else {
            n1 = 0;
        }
        if (current2->next != NULL) {
            current2 = current2->next;
            n2 = current2->data;
        } else {
            n2 = 0;
        }
    }
    //*lastCarry = carry;
}

void complement(struct Bignumber *num) {
    size_t len = num->size;
    struct BignumberTail *current = num->next;
    for (size_t i = 0; i < len; i++) {
        current->data = (0xFF - current->data);
        if (current->next != NULL) {
            current = current->next;
        }
    }
    struct Bignumber one;
    initBignumberFromInt(&one, 1);
    addNumber(num, &one, NULL);
}

void subNumber(struct Bignumber *num1, struct Bignumber *num2, int* lastCarry) {
    complement(num2);
    addNumber(num1, num2, lastCarry);
    complement(num2);
}

struct Bignumber *copyNumber(struct Bignumber *num) {
    if (num == NULL) {
        return NULL;
    } else if (num->size == 0 || num->size == 0 || num->next == NULL) {
        return NULL;
    }

    struct Bignumber *result =
        (struct Bignumber *)malloc(sizeof(struct Bignumber));

    initBignumberFromInt(result, 0);
    addNumber(result, num, NULL);
    return result;
}

enum Comparison compareNumbers(struct Bignumber *num1, struct Bignumber *num2) {
    struct Bignumber *copy = copyNumber(num1);
    subNumber(copy, num2,NULL);

    // copy == 0 return EQUAL
    return EQUAL;
    // copy < 0 return LOW

    // copy > 0 return HIGH
}

// eklenecek
void multiplyNumber(struct Bignumber *num1, struct Bignumber *num2) {}

void karatsubaMul(struct Bignumber *num1, struct Bignumber *num2) {}

// 0 degerinde sayi veriyor, henuz parse ozelligi eklenmedi
void initBignumberFromStr(struct Bignumber *num, const char *str) {
    size_t length = strlen(str);
    size_t BignumberSize = (size_t)ceil(BIGNUMBER_RATIO * length);

    num->size = BignumberSize + 1;  // 1 byte gap
    num->next = NULL;

    struct BignumberTail *current = num->next;

    for (size_t i = 0; i < BignumberSize + 1; i++) {
        struct BignumberTail *new =
            (struct BignumberTail *)malloc(sizeof(struct BignumberTail));
        if (new == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        new->next = NULL;
        new->data = 0;

        if (current == NULL) {
            num->next = new;
            current = new;
        } else {
            current->next = new;
            current = new;
        }
    }
}

void initBignumberFromInt(struct Bignumber *num, int num_val) {
    // find len
    size_t length = 0;
    for (int mem = num_val; mem > 0; mem /= 10) {
        length++;
    }

    size_t BignumberSize = (size_t)ceil(BIGNUMBER_RATIO * length);

    num->size = BignumberSize + 1;  // 1 byte gap
    num->next = NULL;

    struct BignumberTail *current = num->next;

    for (size_t i = 0; i < BignumberSize + 1; i++) {
        struct BignumberTail *new =
            (struct BignumberTail *)malloc(sizeof(struct BignumberTail));
        if (new == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        new->next = NULL;
        new->data = 0;

        if (current == NULL) {
            num->next = new;
            current = new;
        } else {
            current->data = num_val % 256;
            num_val /= 256;
            current->next = new;
            current = new;
        }
    }
}

void printBignumberData(struct Bignumber *num) {
    struct BignumberTail *current = num->next;
    for (size_t i = 0; i < num->size; i++) {
        printf("[%u]", current->data);
        current = current->next;
    }
    printf("\n");
}