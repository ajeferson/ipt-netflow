/*
 * helper.h
 *
 *  Created on: Sep 21, 2017
 *      Author: ajeferson
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <linux/module.h>

static inline int ABS(int x) { return x >= 0 ? x : -x; }
#define SAFEDIV(x,y) ((y)? ({ u64 __tmp = x; do_div(__tmp, y); (int)__tmp; }) : 0)
#define FFLOAT(x, prec) (int)(x) / prec, ABS((int)(x) % prec)
#define DIVISION(x, y) FFLOAT(SAFEDIV(100LL * x, y), 100)

static inline __be32 bits2mask(int bits) {
	return (bits? 0xffffffff << (32 - bits) : 0);
}

static inline int mask2bits(__be32 mask) {
	int n;

	for (n = 0; mask; n++)
		mask = (mask << 1) & 0xffffffff;
	return n;
}

static struct hlist_head *alloc_hashtable(const int size) {

	struct hlist_head *hash = vmalloc(sizeof(struct hlist_head) * size);

	if (hash) {
		int i;
		for (i = 0; i < size; i++)
			INIT_HLIST_HEAD(&hash[i]);
	} else {
		printk(KERN_ERR "ipt_NETFLOW: unable to vmalloc hash table.\n");
	}

	return hash;
}

#endif /* HELPER_H_ */
