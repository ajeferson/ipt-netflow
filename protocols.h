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
#include <linux/types.h>
#include "compat.h"
#include <linux/string.h>

typedef struct {
	struct hlist_node hlist;
	__u8 protocol;
	char *name;
	int byte_count;
	int packet_count;
	unsigned long int first_ts;
	unsigned long int last_ts;
} ProtocolStat;

#define PROTO_HSIZE 23				// Based on empiric heuristics to avoid collisions
#define PROTO_UNKNOWN 0
#define BYTES_PER_PACKET(ps) DIVISION(ps->byte_count, ps->packet_count)

const char proto_unknown_name[6] = "Other";

DEFINE_RWLOCK(proto_stats_lock);

static struct hlist_head *proto_htable __read_mostly;


/**
 * Definitions
 * */

static ProtocolStat* alloc_protocol_stat(__u8 protocol);
static void proto_htable_add(ProtocolStat *ps);
static int alloc_protocol_stats_hashtable(void);
static ProtocolStat* find_protocol_stat(__u8 protocol);
static char* get_protocol_name(__u8 protocol);
static void free_proto_stats(void);
static int is_proto_known(ProtocolStat *ps);
static void aggreage_proto_stats(ProtocolStat *a, ProtocolStat *b);
//static float bytes_per_packet(ProtocolStat *ps);


/**
 * Implementations
 * */

static ProtocolStat* alloc_protocol_stat(__u8 protocol) {
	// TODO Maybe use kmem_cache_alloc
	ProtocolStat *ps = (ProtocolStat *) kmalloc(sizeof(ProtocolStat), GFP_ATOMIC);
	if (!ps) {
		printk(KERN_ERR "ipt_NETFLOW: Can't protocol stat.\n");
		return NULL;
	}
	memset(ps, 0, sizeof(ProtocolStat));
	ps->protocol = protocol;
	ps->name = get_protocol_name(protocol);
	return ps;
}

static void proto_htable_add(ProtocolStat *ps) {
	int hash = ps->protocol % PROTO_HSIZE;
	hlist_add_head(&ps->hlist, &proto_htable[hash]);
}

static int alloc_protocol_stats_hashtable(void) {
	proto_htable = alloc_hashtable(PROTO_HSIZE);
	return proto_htable != NULL;
}

static ProtocolStat* find_protocol_stat(__u8 protocol) {
	ProtocolStat *cursor;
	int hash = protocol % PROTO_HSIZE;
	hlist_for_each_entry(cursor, &proto_htable[hash], hlist) {
		if(cursor->protocol == protocol) {
			return cursor;
		}
	}
	return NULL;
}

//static int bytes_per_packet(ProtocolStat *ps) {
//	return (float) ps->byte_count / (float) ps->packet_count;
//}

static char* get_protocol_name(__u8 protocol) {
	char *protocol_name = (char *) kmalloc(sizeof(char) * 1000, GFP_ATOMIC);
	switch(protocol) {
	case IPPROTO_ICMP:
		strcpy(protocol_name, "ICMP");
		break;
	case IPPROTO_IGMP:
		strcpy(protocol_name, "IGMP");
		break;
	case IPPROTO_IPIP:
		strcpy(protocol_name, "IPIP");
		break;
	case IPPROTO_TCP:
		strcpy(protocol_name, "TCP");
		break;
	case IPPROTO_EGP:
		strcpy(protocol_name, "EGP");
		break;
	case IPPROTO_PUP:
		strcpy(protocol_name, "PUP");
		break;
	case IPPROTO_UDP:
		strcpy(protocol_name, "UDP");
		break;
	case IPPROTO_IDP:
		strcpy(protocol_name, "XNS IDP");
		break;
	case IPPROTO_TP:
		strcpy(protocol_name, "TranProt4");
		break;
	case IPPROTO_DCCP:
		strcpy(protocol_name, "DCCP");
		break;
	case IPPROTO_IPV6:
		strcpy(protocol_name, "IPv6-in-IPv4");
		break;
	case IPPROTO_RSVP:
		strcpy(protocol_name, "RSVP");
		break;
	case IPPROTO_GRE:
		strcpy(protocol_name, "GRE");
		break;
	case IPPROTO_ESP:
		strcpy(protocol_name, "ESP");
		break;
	case IPPROTO_AH:
		strcpy(protocol_name, "AH");
		break;
	case IPPROTO_MTP:
		strcpy(protocol_name, "MTP");
		break;
	case IPPROTO_BEETPH:
		strcpy(protocol_name, "BEETPH");
		break;
	case IPPROTO_ENCAP:
		strcpy(protocol_name, "ENCAP");
		break;
	case IPPROTO_PIM:
		strcpy(protocol_name, "PIM");
		break;
	case IPPROTO_COMP:
		strcpy(protocol_name, "COMP");
		break;
	case IPPROTO_SCTP:
		strcpy(protocol_name, "SCTP");
		break;
	case IPPROTO_UDPLITE:
		strcpy(protocol_name, "UDP-Lite");
		break;
	case IPPROTO_RAW:
		strcpy(protocol_name, "Raw IP");
		break;
	default:
		strcpy(protocol_name, proto_unknown_name);
	}
	return protocol_name;
}

static int is_proto_known(ProtocolStat *ps) {
	return strcmp(ps->name, proto_unknown_name) != 0;
}

static void free_proto_stats(void) {
	ProtocolStat *cursor;
	struct hlist_node *next;
	int i;
	for(i = 0; i < PROTO_HSIZE; i++) {
		hlist_for_each_entry_safe(cursor, next, &proto_htable[i], hlist) {
			kfree(cursor);
		}
	}
	vfree(proto_htable);
}

static void aggreage_proto_stats(ProtocolStat *a, ProtocolStat *b) {
	a->packet_count += b->packet_count;
	a->byte_count += b->byte_count;
}

#endif /* PROTOCOLS_H_ */
