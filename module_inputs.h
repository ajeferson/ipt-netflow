/*
 * module_inputs.h
 *
 *  Created on: Sep 21, 2017
 *      Author: ajeferson
 */

#ifndef MODULE_INPUTS_H_
#define MODULE_INPUTS_H_


#define DST_SIZE 256
static char destination_buf[DST_SIZE] = "127.0.0.1:2055";
static char *destination = destination_buf;
module_param(destination, charp, 0444);
MODULE_PARM_DESC(destination, "export destination ipaddress:port");

#ifdef ENABLE_SAMPLER
static char sampler_buf[128] = "";
static char *sampler = sampler_buf;
module_param(sampler, charp, 0444);
MODULE_PARM_DESC(sampler, "flow sampler parameters");
static atomic_t flow_count = ATOMIC_INIT(0); /* flow counter for deterministic sampler */
static atomic64_t flows_observed = ATOMIC_INIT(0);
static atomic64_t flows_selected = ATOMIC_INIT(0);
#define SAMPLER_INFO_INTERVAL (5*60)
static unsigned long ts_sampler_last = 0; /* template send time (jiffies) */
static struct duration sampling_ts; /* ts of sampling start (ktime) */
#define SAMPLER_SHIFT       14
#define SAMPLER_INTERVAL_M  ((1 << SAMPLER_SHIFT) - 1)
enum {
	SAMPLER_DETERMINISTIC = 1,
	SAMPLER_RANDOM	      = 2,
	SAMPLER_HASH	      = 3
};
struct sampling {
	union {
		u32		v32;
		struct {
			u8	mode;
			u16 	interval;
		};
	};
} samp;
#endif


/**
 * Input params (through configure file)
 * */
static int inactive_timeout = 15;
module_param(inactive_timeout, int, 0644);
MODULE_PARM_DESC(inactive_timeout, "inactive flows timeout in seconds");

static int active_timeout = 30 * 60;
module_param(active_timeout, int, 0644);
MODULE_PARM_DESC(active_timeout, "active flows timeout in seconds");

static int exportcpu = -1;
module_param(exportcpu, int, 0644);
MODULE_PARM_DESC(exportcpu, "lock exporter to this cpu");

#ifdef ENABLE_PROMISC
static int promisc = 0;
module_param(promisc, int, 0444);
MODULE_PARM_DESC(promisc, "enable promisc hack (0=default, 1)");
static DEFINE_MUTEX(promisc_lock);
#endif

static int debug = 0;
module_param(debug, int, 0644);
MODULE_PARM_DESC(debug, "debug verbosity level");

static int sndbuf;
module_param(sndbuf, int, 0444);
MODULE_PARM_DESC(sndbuf, "udp socket SNDBUF size");

static int protocol = 5;
module_param(protocol, int, 0444);
MODULE_PARM_DESC(protocol, "netflow protocol version (5, 9, 10=IPFIX)");

static unsigned int refresh_rate = 20;
module_param(refresh_rate, uint, 0644);
MODULE_PARM_DESC(refresh_rate, "NetFlow v9/IPFIX refresh rate (packets)");

static unsigned int timeout_rate = 30;
module_param(timeout_rate, uint, 0644);
MODULE_PARM_DESC(timeout_rate, "NetFlow v9/IPFIX timeout rate (minutes)");

static int one = 1;
static unsigned int scan_min = 1;
static unsigned int scan_max = HZ / 10;
module_param(scan_min, uint, 0644);
MODULE_PARM_DESC(scan_min, "Minimal interval between export scans (jiffies)");

#ifdef SNMP_RULES
static char snmp_rules_buf[DST_SIZE] = "";
static char *snmp_rules = snmp_rules_buf;
module_param(snmp_rules, charp, 0444);
MODULE_PARM_DESC(snmp_rules, "SNMP-index conversion rules");
static unsigned char *snmp_ruleset;
static DEFINE_SPINLOCK(snmp_lock);
#endif

#ifdef CONFIG_NF_NAT_NEEDED
static int natevents = 0;
module_param(natevents, int, 0444);
MODULE_PARM_DESC(natevents, "enable NAT Events");
#endif

static int hashsize;
module_param(hashsize, int, 0444);
MODULE_PARM_DESC(hashsize, "hash table size");

static int maxflows = 2000000;
module_param(maxflows, int, 0644);
MODULE_PARM_DESC(maxflows, "maximum number of flows");
static int peakflows = 0;
static unsigned long peakflows_at; /* jfffies */

static int engine_id = 0;
module_param(engine_id, int, 0644);
MODULE_PARM_DESC(engine_id, "Observation Domain ID");


#endif /* MODULE_INPUTS_H_ */
