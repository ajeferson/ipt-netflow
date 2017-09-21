/*
 * base_templates.h
 *
 *  Created on: Sep 21, 2017
 *      Author: ajeferson
 */

#ifndef BASE_TEMPLATES_H_
#define BASE_TEMPLATES_H_

struct base_template {
	int length; /* number of elements in template */
	u_int16_t types[]; /* {type, size} pairs */
};

static struct base_template template_base_9 = {
	.types = {
		INPUT_SNMP,
		OUTPUT_SNMP,
#ifdef ENABLE_PHYSDEV
		ingressPhysicalInterface,
		egressPhysicalInterface,
#endif
		IN_PKTS,
		IN_BYTES,
		FIRST_SWITCHED,
		LAST_SWITCHED,
		PROTOCOL,
		TOS,
		0
	}
};
static struct base_template template_base_ipfix = {
	.types = {
		ingressInterface,
		egressInterface,
#ifdef ENABLE_PHYSDEV
		ingressPhysicalInterface,
		egressPhysicalInterface,
#endif
		packetDeltaCount,
		octetDeltaCount,
		flowStartMilliseconds,
		flowEndMilliseconds,
		protocolIdentifier,
		ipClassOfService,
		flowEndReason,
		0
	}
};

#ifdef ENABLE_MAC
static struct base_template template_mac_ipfix = {
	.types = {
		destinationMacAddress,
		sourceMacAddress,
		0
	}
};
#endif

#if defined(ENABLE_MAC) || defined(ENABLE_VLAN)
static struct base_template template_ethertype = {
	.types = { ethernetType, 0 }
};
#endif

#ifdef ENABLE_VLAN
static struct base_template template_vlan_v9 = {
	.types = { SRC_VLAN, 0 }
};
/* IPFIX is different from v9, see rfc7133. */
static struct base_template template_vlan_ipfix = {
	.types = {
		dot1qVlanId,
		dot1qPriority,
		0
	}
};
static struct base_template template_vlan_inner = {
	.types = {
		dot1qCustomerVlanId,
		dot1qCustomerPriority,
		0
	}
};
#endif

#ifdef MPLS_DEPTH
static struct base_template template_mpls = {
	.types = {
		mplsTopLabelTTL,
		/* do not just add element here, becasue this array
		 * is truncated in ipt_netflow_init() */
#define MPLS_LABELS_BASE_INDEX 1
		MPLS_LABEL_1,
		MPLS_LABEL_2,
		MPLS_LABEL_3,
		MPLS_LABEL_4,
		MPLS_LABEL_5,
		MPLS_LABEL_6,
		MPLS_LABEL_7,
		MPLS_LABEL_8,
		MPLS_LABEL_9,
		MPLS_LABEL_10,
		0
	}
};
#endif

#ifdef ENABLE_DIRECTION
static struct base_template template_direction = {
	.types = { DIRECTION, 0 }
};
#endif

static struct base_template template_ipv4 = {
	.types = {
		IPV4_SRC_ADDR,
		IPV4_DST_ADDR,
		IPV4_NEXT_HOP,
		0
	}
};

static struct base_template template_options4 = {
	.types = { ipv4Options, 0 }
};

static struct base_template template_tcpoptions = {
	.types = { tcpOptions, 0 }
};

static struct base_template template_ipv6 = {
	.types = {
		IPV6_SRC_ADDR,
		IPV6_DST_ADDR,
		IPV6_NEXT_HOP,
		0
	}
};

static struct base_template template_options6 = {
	.types = { IPV6_OPTION_HEADERS, 0 }
};

static struct base_template template_label6 = {
	.types = { IPV6_FLOW_LABEL, 0 }
};

static struct base_template template_ipv4_mask = {
	.types = {
		SRC_MASK,
		DST_MASK,
		0
	}
};

static struct base_template template_ports = {
	.types = {
		L4_SRC_PORT,
		L4_DST_PORT,
		TCP_FLAGS,
		0
	}
};

static struct base_template template_icmp_v9 = {
	.types = {
		L4_SRC_PORT,	/* dummy (required by some collector(s) to
				   recognize ICMP flows) */
		L4_DST_PORT,	/* actually used in V9 world instead of
				   ICMP_TYPE(32), disregarding docs */
		0
	}
};

static struct base_template template_icmp_ipv4 = {
	.types = { icmpTypeCodeIPv4, 0 }
};

static struct base_template template_icmp_ipv6 = {
	.types = { icmpTypeCodeIPv6, 0 }
};

static struct base_template template_igmp = {
	.types = { MUL_IGMP_TYPE, 0 }
};

static struct base_template template_ipsec = {
	.types = { IPSecSPI, 0 }
};

static struct base_template template_nat4 = {
	.types = {
		observationTimeMilliseconds,
		IPV4_SRC_ADDR,
		IPV4_DST_ADDR,
		postNATSourceIPv4Address,
		postNATDestinationIPv4Address,
		L4_SRC_PORT,
		L4_DST_PORT,
		postNAPTSourceTransportPort,
		postNAPTDestinationTransportPort,
		PROTOCOL,
		natEvent,
		0
	}
};

static struct base_template template_sys_init_time = {
	.types = {
		observationDomainId,

		/* ipfix does not report sys_uptime_ms like v9 does,
		 * so this could be useful to detect system restart
		 * (rfc5102), and conversion of flow times to absolute
		 * time (rfc5153 4.7) */
		systemInitTimeMilliseconds,

		/* this will let collector detect module version and
		 * recompilation (by srcversion) */
		observationDomainName,

		/* useful to detect module reload */
		flowStartMilliseconds,
		flowEndMilliseconds,
		0
	}
};

/* http://tools.ietf.org/html/rfc5101#section-4 */
/* The Metering Process Statistics Option Template */
static struct base_template template_meter_stat = {
	.types = {
		observationDomainId,
		exportedMessageTotalCount,
		exportedFlowRecordTotalCount,
		exportedOctetTotalCount,
		observedFlowTotalCount,
		0
	}
};

/* The Metering Process Reliability Statistics Option Template */
static struct base_template template_meter_rel_stat = {
	.types = {
		observationDomainId,
		ignoredPacketTotalCount,
		ignoredOctetTotalCount,
		flowStartMilliseconds, /* sampling start time */
		flowEndMilliseconds,
		0
	}
};

/* The Exporting Process Reliability Statistics Option Template */
static struct base_template template_exp_rel_stat = {
	.types = {
		exportingProcessId,
		notSentFlowTotalCount,
		notSentPacketTotalCount,
		notSentOctetTotalCount,
		flowStartMilliseconds, /* sampling start time */
		flowEndMilliseconds,
		0
	}
};


#ifdef ENABLE_SAMPLER
static struct base_template template_samplerid = {
	.types = { FLOW_SAMPLER_ID, 0 }
};
static struct base_template template_selectorid = {
	.types = { selectorId, 0 }
};

/* sampler for v9 */
static struct base_template template_sampler = {
	.types = {
		observationDomainId,
		FLOW_SAMPLER_ID,
		FLOW_SAMPLER_MODE,
		FLOW_SAMPLER_RANDOM_INTERVAL,
		0
	}
};
/* sampler for ipfix */
static struct base_template template_selector_systematic = {
	.types = {
		observationDomainId,
		selectorId,
		flowSelectorAlgorithm,
		samplingFlowInterval,
		samplingFlowSpacing,
		0
	}
};
static struct base_template template_selector_random = {
	.types = {
		observationDomainId,
		selectorId,
		flowSelectorAlgorithm,
		samplingSize,
		samplingPopulation,
		0
	}
};
static struct base_template template_selector_stat = {
	.types = {
		selectorId,
		selectorIDTotalFlowsObserved,
		selectorIDTotalFlowsSelected,
		selectorIdTotalPktsObserved,
		selectorIdTotalPktsSelected,
		flowStartMilliseconds,
		flowEndMilliseconds,
		0
	}
};
/* can't calc selectorIDTotalFlowsObserved for hash sampling,
 * because dropped flows are not accounted */
static struct base_template template_selector_stat_hash = {
	.types = {
		selectorId,
		selectorIDTotalFlowsSelected,
		selectorIdTotalPktsObserved,
		selectorIdTotalPktsSelected,
		flowStartMilliseconds,
		flowEndMilliseconds,
		0
	}
};
#endif

static struct base_template template_interfaces = {
	.types = {
		observationDomainId,
		INPUT_SNMP,
		IF_NAME,
		IF_DESC,
		0
	}
};


#endif /* BASE_TEMPLATES_H_ */
