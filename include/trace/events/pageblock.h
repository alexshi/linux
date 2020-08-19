/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM pageblock

#if !defined(_TRACE_PAGEBLOCK_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_PAGEBLOCK_H

#include <linux/tracepoint.h>

TRACE_EVENT(hit_cmpxchg,

	TP_PROTO(char byte),

	TP_ARGS(byte),

	TP_STRUCT__entry(
		__field(char, byte)
	),

	TP_fast_assign(
		__entry->byte = byte;
	),

	TP_printk("%d", __entry->byte)
);

#endif /* _TRACE_PAGE_ISOLATION_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
