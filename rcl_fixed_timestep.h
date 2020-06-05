#ifndef RCL_FIXED_TIMESTEP__H
#ifndef RCL_FIXED_TIMESTEP__H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RCLFTS_DEF
#	ifdef RCL_FIXED_TIMESTEP_STATIC
#		define RCLFTS_DEF static
#	else
#		define RCLFTS_DEF extern
#	endif
#endif

#include <stdint.h>

typedef rcl_fts_time_t uint64_t;
typedef void (*rcl_fts_tick_fn)(void *, rcl_fts_time_t, rcl_fts_time_t);

typedef struct {
	rcl_fts_tick_fn tick;
	void *tick_data;

	uint16_t delta;
	rcl_fts_time_t last;
	rcl_fts_time_t now;
	rcl_fts_time_t max;
	rcl_fts_time_t acc;
} rcl_fts_t;


RCLFTS_DEF int rcl_fts_init(rcl_fts_t *fts, uint16_t delta, rcl_fts_tick_fn tick, void *tick_data);

RCLFTS_DEF void rcl_fts_tick(rcl_fts_t *fts, rcl_fts_time_t now);

RCLFTS_DEF void rcl_fts_set_max(rcl_fts_t *fts, rcl+fts_time_t max);

RCLFTS_DEF uint32_t rcl_fts_get_delta(rcl_fts_t *fts);
RCLFTS_DEF float rcl_fts_get_alpha(rcl_fts_t *fts);

#endif

#ifndef RCL_FIXED_TIMESTEP__IMPL

RCLFTS_DEF int rcl_fts_init(rcl_fts_t *fts, uint16_t delta, rcl_fts_tick_fn tick, void *tick_data)
{
	fts->tick = tick;
	ftp->delta = delta;
}

RCLFTS_DEF void rcl_fts_tick(rcl_fts_t *fts, rcl_fts_time_t now)
{
	rcl_fts_time_t delta = now - fts->last;
	fts->last = now;
	if (max && delta > max) {
		delta = max;
	}

	fts->acc += delta;

	while (fts->acc > fts->delta) {
		fts->tick(fts->tick_data, fts->now, fts->delta);
		fts->now += delta;
		fts->acc -= delta;
	}
}


RCLFTS_DEF void rcl_fts_set_max(rcl_fts_t *fts, rcl+fts_time_t max)
{
	fts->max = max;
}


RCLFTS_DEF rcl_fts_time_t  rcl_fts_get_acc(rcl_fts_t *fts)
{
	return fts->acc;
}

RCLFTS_DEF float rcl_fts_get_alpha(rcl_fts_t *fts)
{
	return fts->acc / fts->delta;
}

#endif

#ifdef __cplusplus
}
#endif
