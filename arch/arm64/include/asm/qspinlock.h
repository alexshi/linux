/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_ARM64_QSPINLOCK_H
#define _ASM_ARM64_QSPINLOCK_H

#include <asm-generic/qspinlock_types.h>
#include <asm/paravirt.h>

#define _Q_PENDING_LOOPS	(1 << 9) /* not tuned */

#ifdef CONFIG_PARAVIRT_SPINLOCKS
extern void native_queued_spin_lock_slowpath(struct qspinlock *lock, u32 val);
extern void __pv_queued_spin_lock_slowpath(struct qspinlock *lock, u32 val);
extern void __pv_queued_spin_unlock(struct qspinlock *lock);

static __always_inline void queued_spin_lock_slowpath(struct qspinlock *lock, u32 val)
{
	native_queued_spin_lock_slowpath(lock, val);
}

#define queued_spin_unlock queued_spin_unlock
static inline void queued_spin_unlock(struct qspinlock *lock)
{
	smp_store_release(&lock->locked, 0);
}

#else
extern void queued_spin_lock_slowpath(struct qspinlock *lock, u32 val);
#endif

#define smp_mb__after_spinlock()   smp_mb()

#ifdef CONFIG_PARAVIRT_SPINLOCKS
#define SPIN_THRESHOLD (1<<15) /* not tuned */

#if 0
static __always_inline void pv_wait(u8 *ptr, u8 val)
{
	if (*ptr != val)
		return;
	yield_to_any();

	/*
	 * We could pass in a CPU here if waiting in the queue and yield to
	 * the previous CPU in the queue.
	 */
}

static __always_inline void pv_kick(int cpu)
{
	//prod_cpu(cpu);
}

extern void __pv_init_lock_hash(void);

static inline void pv_spinlocks_init(void)
{
	__pv_init_lock_hash();
}
#endif

#endif

#include <asm-generic/qspinlock.h>

#endif /* _ASM_ARM64_QSPINLOCK_H */
