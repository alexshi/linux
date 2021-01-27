/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright(c) 2019 Huawei Technologies Co., Ltd
 * Author: Zengruan Ye <yezengruan@huawei.com>
 */

#ifndef __ASM_PVLOCK_ABI_H
#define __ASM_PVLOCK_ABI_H

struct pvlock_vcpu_state {
	__le64 preempted;
	/* Structure must be 64 byte aligned, pad to that size */
	u8 padding[56];
} __packed;

#endif
