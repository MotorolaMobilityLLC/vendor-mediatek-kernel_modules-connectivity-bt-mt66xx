/*
 *  Copyright (c) 2016,2017 MediaTek Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */

#ifndef __BTMTK_DEFINE_H__
#define __BTMTK_DEFINE_H__


#include <linux/version.h>
#include <linux/firmware.h>
#include <linux/slab.h>
#include <linux/module.h>

#include <net/bluetooth/bluetooth.h>
#include <net/bluetooth/hci_core.h>

#include <linux/cdev.h>
#include <linux/spinlock.h>
#include <linux/kallsyms.h>
#include <linux/device.h>
#include <asm/unaligned.h>

/* Define for proce node */
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "btmtk_config.h"


/** Driver version */
#define VERSION "7.0.18081001"
#define SUBVER ":turnkey"


#define ENABLESTP FALSE
#define BLUEDROID TRUE
#define BTMTKUART_TX_STATE_ACTIVE	1
#define BTMTKUART_TX_STATE_WAKEUP	2
#define BTMTKUART_TX_WAIT_VND_EVT	3
#define BTMTKUART_REQUIRED_WAKEUP	4
#define BTMTKUART_REQUIRED_DOWNLOAD	5
#define BTMTKUART_TX_SKIP_VENDOR_EVT	6

#define BTMTKUART_RX_STATE_ACTIVE	1
#define BTMTKUART_RX_STATE_WAKEUP	2
#define BTMTKUART_RX_STATE_RESET	3



/**
 * Type definition
 */
#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif

#ifndef UNUSED
	#define UNUSED(x) (void)(x)
#endif

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))



/**
 * Log and level definition
 */
#define BTMTK_LOG_LVL_ERR	1
#define BTMTK_LOG_LVL_WARN	2
#define BTMTK_LOG_LVL_INFO	3
#define BTMTK_LOG_LVL_DBG	4
#define BTMTK_LOG_LVL_MAX	BTMTK_LOG_LVL_DBG
//#define BTMTK_LOG_LVL_DEF	BTMTK_LOG_LVL_INFO	/* default setting */
#define BTMTK_LOG_LVL_DEF	BTMTK_LOG_LVL_MAX	/* default setting */


extern uint8_t btmtk_log_lvl;

#define BTMTK_ERR(fmt, ...)	 \
	do { if (btmtk_log_lvl >= BTMTK_LOG_LVL_ERR) pr_info("[btmtk_err] ***"fmt"***\n", ##__VA_ARGS__); } while (0)
#define BTMTK_WARN(fmt, ...)	\
	do { if (btmtk_log_lvl >= BTMTK_LOG_LVL_WARN) pr_info("[btmtk_warn] "fmt"\n", ##__VA_ARGS__); } while (0)
#define BTMTK_INFO(fmt, ...)	\
	do { if (btmtk_log_lvl >= BTMTK_LOG_LVL_INFO) pr_info("[btmtk_info] "fmt"\n", ##__VA_ARGS__); } while (0)
#define BTMTK_DBG(fmt, ...)	 \
	do { if (btmtk_log_lvl >= BTMTK_LOG_LVL_DBG) pr_info("[btmtk_dbg] "fmt"\n", ##__VA_ARGS__); } while (0)

#define BTMTK_INFO_RAW(p, l, fmt, ...)						\
	do {									\
		if (btmtk_log_lvl >= BTMTK_LOG_LVL_INFO) {			\
			int raw_count = 0;					\
			const unsigned char *ptr = p;				\
			pr_cont("[btmtk_info] "fmt, ##__VA_ARGS__);		\
			for (raw_count = 0; raw_count < l; ++raw_count) {	\
				pr_cont(" 0x%02X", ptr[raw_count]);		\
			}							\
			pr_cont("\n");						\
		}								\
	} while (0)

#define BTMTK_DBG_RAW(p, l, fmt, ...)						\
	do {									\
		if (btmtk_log_lvl >= BTMTK_LOG_LVL_DBG) {			\
			int raw_count = 0;					\
			const unsigned char *ptr = p;				\
			pr_cont("[btmtk_debug] "fmt, ##__VA_ARGS__);		\
			for (raw_count = 0; raw_count < l; ++raw_count) {	\
				pr_cont(" %02X", ptr[raw_count]);		\
			}							\
			pr_cont("\n");						\
		}								\
	} while (0)

#define FN_ENTER(fmt, ...) \
	pr_cont("[btmtk_info] %s Enter: "fmt"\n", __func__, ##__VA_ARGS__);
#define FN_END(fmt, ...) \
	pr_cont("[btmtk_info] %s End: "fmt"\n", __func__, ##__VA_ARGS__);


/**
 *
 * HCI packet type
 */
#define MTK_HCI_COMMAND_PKT	 0x01
#define MTK_HCI_ACLDATA_PKT		0x02
#define MTK_HCI_SCODATA_PKT		0x03
#define MTK_HCI_EVENT_PKT		0x04

/**
 * ROM patch related
 */
#define PATCH_HCI_HEADER_SIZE	4
#define PATCH_WMT_HEADER_SIZE	5
/*
 * Enable STP
 * HCI+WMT+STP = 4 + 5 + 1(phase) +(4=STP_HEADER + 2=CRC)
#define PATCH_HEADER_SIZE	16
 */
/*#ifdef ENABLESTP
#define PATCH_HEADER_SIZE	(PATCH_HCI_HEADER_SIZE + PATCH_WMT_HEADER_SIZE + 1 + 6)
#define UPLOAD_PATCH_UNIT	916
#define PATCH_INFO_SIZE		30
#else*/
#define PATCH_HEADER_SIZE	(PATCH_HCI_HEADER_SIZE + PATCH_WMT_HEADER_SIZE + 1)
#define UPLOAD_PATCH_UNIT	910
#define PATCH_INFO_SIZE		30
//#endif
#define PATCH_PHASE1		1
#define PATCH_PHASE2		2
#define PATCH_PHASE3		3


#define USB_IO_BUF_SIZE		(HCI_MAX_EVENT_SIZE > 256 ? HCI_MAX_EVENT_SIZE : 256)
#define HCI_SNOOP_ENTRY_NUM	30
#define HCI_SNOOP_BUF_SIZE	32

#endif /* __BTMTK_DEFINE_H__ */
