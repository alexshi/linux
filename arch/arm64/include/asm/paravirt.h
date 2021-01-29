/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_ARM64_PARAVIRT_H
#define _ASM_ARM64_PARAVIRT_H

#ifdef CONFIG_PARAVIRT
struct static_key;
extern struct static_key paravirt_steal_enabled;
extern struct static_key paravirt_steal_rq_enabled;

struct pv_time_ops {
	unsigned long long (*steal_clock)(int cpu);
};

struct pv_lock_ops {
	bool (*vcpu_is_preempted)(int cpu);

	void (*queued_spin_lock_slowpath)(struct qspinlock *lock, u32 val);
	void (*queued_spin_unlock)(struct qspinlock *lock);

	void (*wait)(u8 *ptr, u8 val);
	void (*kick)(int cpu);
};

struct paravirt_patch_template {
	struct pv_time_ops time;
	struct pv_lock_ops lock;
};

extern struct paravirt_patch_template pv_ops;

static inline u64 paravirt_steal_clock(int cpu)
{
	return pv_ops.time.steal_clock(cpu);
}

int __init pv_time_init(void);

int __init pv_lock_init(void);

__visible bool __native_vcpu_is_preempted(int cpu);

static __always_inline void pv_queued_spin_lock_slowpath(struct qspinlock *lock,
							u32 val)
{
	return pv_ops.lock.queued_spin_lock_slowpath(lock, val);
}

static __always_inline void pv_queued_spin_unlock(struct qspinlock *lock)
{
	return pv_ops.lock.queued_spin_unlock(lock);
}

static __always_inline void pv_wait(u8 *ptr, u8 val)
{
	return pv_ops.lock.wait(ptr, val);
}

static __always_inline void pv_kick(int cpu)
{
	return pv_ops.lock.kick(cpu);
}

//void __raw_callee_save___native_queued_spin_unlock(struct qspinlock *lock);
//bool __raw_callee_save___native_vcpu_is_preempted(long cpu);


static inline bool pv_vcpu_is_preempted(int cpu)
{
	return pv_ops.lock.vcpu_is_preempted(cpu);
}

#else

#define pv_time_init() do {} while (0)
#define pv_lock_init() do {} while (0)

#endif // CONFIG_PARAVIRT

#endif
