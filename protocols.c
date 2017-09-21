/*
 * protocols.c
 *
 *  Created on: Sep 21, 2017
 *      Author: ajeferson
 */

//#include "protocols.h"

//static __u8 protocol_ids[] = {
//		IPPROTO_ICMP,
//		IPPROTO_TCP,
//		IPPROTO_RAW 				// Plceholder for "other"
//};
//
//static const char *const protocol_names[] = {
//		"ICMP",
//		"TCP",
//		"Other"
//};
//
//static void init_protocol_stat(L3ProtocolStat* stat) {
//	stat->byte_count = 0;
//	stat->packet_count = 0;
//	stat->first = jiffies;
//}
//
//// TODO Alloc with kmalloc
//static void alloc_protocol_stats(void) {
//	int i;
//	for(i = 0; i < L3_PROTO_SIZE; i++) {
//		L3ProtocolStat lps;
//		init_protocol_stat(&lps);
//		l3_proto_stats[i] = lps;
//	}
//}
//
//static L3ProtocolStat* get_l3_protocol_stat(__u8 protocol_id) {
//	int i;
//	for(i = 0; i < L3_PROTO_SIZE - 1; i++) {
//		if(protocol_id == protocol_ids[i])
//			return &l3_proto_stats[i];
//	}
//	return &stats[L3_PROTO_SIZE - 1];
//}
