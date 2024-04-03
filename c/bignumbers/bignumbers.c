#include "bignumbers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addNumber(struct Bignumber *num1, struct Bignumber *num2) {
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
    addNumber(num, &one);
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
    addNumber(result, num);
    return result;
}

char compareNumbers(struct Bignumber *num1, struct Bignumber *num2) {
    // most significant bit (is negative or positive)
    size_t s1 = num1->size;
    size_t s2 = num2->size;
    size_t length = (s1 > s2) * (s1) + (s1 < s2) * (s2) + (s1 == s2) * s1;
    char result = s1 > s2;
    size_t m1 = 0;  // index of num1's first sigfig
    size_t m2 = 0;  // index of num2's first sigfig

    char sign1 = 0;  // -1 if negative 1 if positive
    char sign2 = 0;

    struct BignumberTail *h1 = num1->next;
    struct BignumberTail *h2 = num2->next;
    for (size_t i = 0; i < length; i++) {
        if (h1->next != NULL) {
            if ((h1->next->data == 0 && h1->data != 0) ||
                (h1->next->data == 255 && h1->data != 255)) {
                m1 = i;
            }
            h1 = h1->next;
        }
        if (h2->next != NULL) {
            if ((h2->next->data == 0 && h2->data != 0) ||
                (h2->next->data == 255 && h2->data != 255)) {
                m2 = i;
            }
            h2 = h2->next;
        }
    }
    h1 = num1->next;
    h2 = num2->next;
    for (size_t i = 0; i < m1; i++) {
        h1 = h1->next;
    }
    for (size_t i = 0; i < m2; i++) {
        h2 = h2->next;
    }
    sign1 = (char)(-1 * (h1->next->data > 127) + 1 * (h1->next->data < 128));
    sign2 = (char)(-1 * (h2->next->data > 127) + 1 * (h2->next->data < 128));
    if (sign1 > sign2) {
        return 1;  // num1 > num2
    } else if (sign2 > sign1) {
        return -1;
    }

    // if signs are equal do size magic
    if (sign1 > 0 && sign2 > 0 && (m1 > m2)) {
        return 1;  // num1 > num2
    } else if (sign1 < 0 && sign2 < 0 && (m1 > m2)) {
        return -1;
    }

    // if not worked scan backward
    if (m1 == m2) {
        for (size_t i = m1 + 1; i > 0; i--) {
            h1 = num1->next;
            h2 = num2->next;
            for (size_t j = 0; j < m1; j++) {
                h1 = h1->next;
                h2 = h2->next;
            }
            if ((h1->data) > (h2->data)) {
                return 1;
            }
            if ((h1->data) < (h2->data)) {
                return -1;
            }
            m1--;
        }
    }

    return 0;
    // fprintf(stderr, "COULDN'T COMPARE!?");
    // abort();
}

void subNumber(struct Bignumber *num1, struct Bignumber *num2) {
    complement(num2);
    addNumber(num1, num2);
    complement(num2);
}

// eklenecek
void multiplyNumber(struct Bignumber *num1, struct Bignumber *num2) {}
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