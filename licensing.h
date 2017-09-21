/*
 * licensing.h
 *
 *  Created on: Sep 21, 2017
 *      Author: ajeferson
 */

#ifndef LICENSING_H_
#define LICENSING_H_

#define IPT_NETFLOW_VERSION "2.2"   /* Note that if you are using git, you will see version in other format. */
#include "version.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("<abc@telekom.ru>");
MODULE_DESCRIPTION("iptables NETFLOW target module");
MODULE_VERSION(IPT_NETFLOW_VERSION);
MODULE_ALIAS("ip6t_NETFLOW");

#endif /* LICENSING_H_ */
