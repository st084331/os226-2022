
#include <stddef.h>

#include "pool.h"

void pool_init(struct pool *p, void *mem, unsigned long nmemb, unsigned long membsz) {
        p -> membsz = membsz;
        p -> nmemb = nmemb;
        p -> memb = NULL;
        p -> mem = mem;
}

void *pool_alloc(struct pool *p) {
    if(p -> nmemb > 0) {
        p -> nmemb--;
        void *ptrBlock = p -> mem;
        p -> mem = (void *) (((unsigned char *) p -> mem) + p -> membsz);
        return ptrBlock;
    } else if(p -> memb) {
        void *ptrBlock = p -> memb;
        p -> memb = ((struct block *) p -> memb) -> next;
        return ptrBlock;
    }
	return NULL;
}

void pool_free(struct pool *p, void *ptr) {
    ((struct block *) ptr) -> next = p -> memb;
    p -> memb = ptr;
}
