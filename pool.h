#pragma once

#include "util.h"

struct block {
    void *next;
};

struct pool {
    unsigned long membsz;
    unsigned long nmemb;
    void *memb;
    void *mem;
};

#define POOL_INITIALIZER(_mem, _nmemb, _membsz) { \
}

#define POOL_INITIALIZER_ARRAY(_array) \
	POOL_INITIALIZER(_array, ARRAY_SIZE(_array), sizeof((_array)[0]));

struct pool p;

void pool_init(struct pool *p, void *mem, unsigned long nmemb, unsigned long membsz);

void *pool_alloc(struct pool *p);

void pool_free(struct pool *p, void *ptr);