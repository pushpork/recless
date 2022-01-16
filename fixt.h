/*
Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
*/
#ifndef FIXT__H
#define FIXT__H

/**
 * Documentation
 *
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FIXT_DEF
#	ifdef FIXT_STATIC
#		define FIXT_DEF static
#	else
#		define FIXT_DEF extern
#	endif
#endif

#include <stdint.h>

typedef uint64_t FixtTime;
typedef uint32_t FixtDelta;

typedef struct {
	FixtDelta delta;
	FixtDelta max;
	FixtTime last;
	FixtTime now;
	FixtTime acc;
} Fixt;

FIXT_DEF int fixt_init(Fixt *fixt, FixtDelta delta, FixtTime now);

FIXT_DEF void fixt_tick(Fixt *fixt, FixtTime now);
FIXT_DEF void fixt_step(Fixt *fixt);

FIXT_DEF void fixt_set_max(Fixt *fixt, FixtDelta max);

FIXT_DEF FixtTime fixt_get_acc(Fixt *fixt);
FIXT_DEF float fixt_get_alpha(Fixt *fixt);

#define fixtloop(f, t) for (fixt_tick(f, t); (f)->acc >= (f)->delta; fixt_step(f))

#ifdef __cplusplus
}
#endif

#endif

#ifdef FIXT__IMPL

FIXT_DEF int fixt_init(Fixt *fixt, FixtDelta delta, FixtTime now)
{
	fixt->delta = delta;
	fixt->max = 0;
	fixt->now = now;
	fixt->last = now;
	fixt->acc = 0;

	return 1;
}

FIXT_DEF void fixt_tick(Fixt *fixt, FixtTime now)
{
	FixtTime delta = now - fixt->last;
	fixt->last = now;
	if (fixt->max && delta > fixt->max) {
		delta = fixt->max;
	}

	fixt->acc += delta;
}

FIXT_DEF void fixt_step(Fixt *fixt)
{
		fixt->now += fixt->delta;
		fixt->acc -= fixt->delta;
}


FIXT_DEF void fixt_set_max(Fixt *fixt, FixtDelta max)
{
	fixt->max = max;
}


FIXT_DEF FixtTime fixt_get_acc(Fixt *fixt)
{
	return fixt->acc;
}

FIXT_DEF float fixt_get_alpha(Fixt *fixt)
{
	return (float) fixt->acc / fixt->delta;
}

#endif
