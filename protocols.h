/*
 * protocols.h
 *
 *  Created on: Sep 21, 2017
 *      Author: ajeferson
 */

#ifndef PROTOCOLS_H_
#define PROTOCOLS_H_

#include <linux/ktime.h>
#include <linux/in.h>
#include <linux/spinlock.h>
#include <linux/gfp.h>

typedef struct {
	__u8 protocol;
	__u8 index; // Index for the name
	int byte_count;
	int packet_count;
	unsigned long int first_ts;
	unsigned long int last_ts;
	char *name;
} ProtocolStat;

DEFINE_RWLOCK(proto_stats_lock);

#define PROTO_SIZE 3
static ProtocolStat *proto_stats;

static __u8 protocol_ids[] = {
		IPPROTO_ICMP,
		IPPROTO_IGMP,
		IPPROTO_TCP,
		IPPROTO_RAW 				// Plceholder for "other"
};

static const char *const protocol_names[] = {
		"ICMP",
		"TCP",
		"Other"
};

#define PROTO_NAME(p) protocol_names[p.index]

static void init_protocol_stat(__u8 index);
static void alloc_protocol_stats(void);
static ProtocolStat* get_protocol_stat(__u8 protocol_id);

static void init_protocol_stat(__u8 index) {
	ProtocolStat* ps = &proto_stats[index];
	ps->byte_count = 0;
	ps->packet_count = 0;
	ps->protocol = protocol_ids[index];
	ps->index = index;
}

// TODO Alloc with kmalloc
static void alloc_protocol_stats(void) {
	__u8 i;
	proto_stats = (ProtocolStat *) kmalloc(sizeof(ProtocolStat) * PROTO_SIZE, GFP_KERNEL);
	for(i = 0; i < PROTO_SIZE - 1; i++) {
		init_protocol_stat(i);
	}
	init_protocol_stat(i);
}

static ProtocolStat* get_protocol_stat(__u8 protocol_id) {
	int i;
	for(i = 0; i < PROTO_SIZE - 1; i++) {
		if(protocol_id == protocol_ids[i])
			return &proto_stats[i];
	}
	return &proto_stats[PROTO_SIZE - 1];
}

#endif /* PROTOCOLS_H_ */
