/*
 * templates.h
 *
 *  Created on: Sep 21, 2017
 *      Author: ajeferson
 */

#ifndef TEMPLATES_H_
#define TEMPLATES_H_


/* Data Templates */
#define BTPL_BASE9	0x00000001	/* netflow base stat */
#define BTPL_BASEIPFIX	0x00000002	/* ipfix base stat */
#define BTPL_IP4	0x00000004	/* IPv4 */
#define BTPL_MASK4	0x00000008	/* Aggregated */
#define BTPL_PORTS	0x00000010	/* UDP&TCP */
#define BTPL_IP6	0x00000020	/* IPv6 */
#define BTPL_ICMP9	0x00000040	/* ICMP (for V9) */
#define BTPL_ICMPX4	0x00000080	/* ICMP IPv4 (for IPFIX) */
#define BTPL_ICMPX6	0x00000100	/* ICMP IPv6 (for IPFIX) */
#define BTPL_IGMP	0x00000200	/* IGMP */
#define BTPL_IPSEC	0x00000400	/* AH&ESP */
#define BTPL_NAT4	0x00000800	/* NAT IPv4 */
#define BTPL_LABEL6	0x00001000	/* IPv6 flow label */
#define BTPL_IP4OPTIONS	0x00002000	/* IPv4 Options */
#define BTPL_IP6OPTIONS	0x00004000	/* IPv6 Options */
#define BTPL_TCPOPTIONS	0x00008000	/* TCP Options */
#define BTPL_MAC	0x00010000	/* MAC addresses */
#define BTPL_VLAN9	0x00020000	/* outer VLAN for v9 */
#define BTPL_VLANX	0x00040000	/* outer VLAN for IPFIX */
#define BTPL_VLANI	0x00080000	/* inner VLAN (IPFIX) */
#define BTPL_ETHERTYPE	0x00100000	/* ethernetType */
#define BTPL_DIRECTION	0x00200000	/* flowDirection */
#define BTPL_SAMPLERID	0x00400000	/* samplerId (v9) */
#define BTPL_SELECTORID	0x00800000	/* selectorId (IPFIX) */
#define BTPL_MPLS	0x01000000	/* MPLS stack */
#define BTPL_OPTION	0x80000000	/* Options Template */
#define BTPL_MAX	32


/* Options Templates */
#define OTPL(x) (BTPL_OPTION | x)
#define OTPL_SYSITIME	OTPL(1)		/* systemInitTimeMilliseconds */
#define OTPL_MPSTAT	OTPL(2)		/* The Metering Process Statistics (rfc5101) */
#define OTPL_MPRSTAT	OTPL(3)		/* The Metering Process Reliability Statistics */
#define OTPL_EPRSTAT	OTPL(4)		/* The Exporting Process Reliability Statistics */
#define OTPL_SAMPLER	OTPL(5)		/* Flow Sampler for v9 */
#define OTPL_SEL_RAND	OTPL(6)		/* Random Flow Selector for IPFIX */
#define OTPL_SEL_COUNT	OTPL(7)		/* Systematic count-based Flow Selector for IPFIX */
#define OTPL_SEL_STAT	OTPL(8)		/* rfc7014 */
#define OTPL_SEL_STATH	OTPL(9)		/* OTPL_SEL_STAT, except selectorIDTotalFlowsObserved */
#define OTPL_IFNAMES	OTPL(10)


#endif /* TEMPLATES_H_ */
