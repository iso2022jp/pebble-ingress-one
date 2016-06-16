/* This software is released under the MIT License, see LICENSE */

#pragma once
#include <pebble.h>

#define HOURS_PER_CHECKPOINT	5
#define MITUTES_PER_CHECKPOINT	(MINUTES_PER_HOUR * HOURS_PER_CHECKPOINT)
#define SECONDS_PER_CHECKPOINT	(SECONDS_PER_HOUR * HOURS_PER_CHECKPOINT)

#define CHECKPOINTS_PER_CYCLE	35
#define HOURS_PER_CYCLE			(HOURS_PER_CHECKPOINT * CHECKPOINTS_PER_CYCLE)
#define MITUTES_PER_CYCLE		(MINUTES_PER_CHECKPOINT * CHECKPOINTS_PER_CYCLE)
#define SECONDS_PER_CYCLE		(SECONDS_PER_CHECKPOINT * CHECKPOINTS_PER_CYCLE)

#define ingress_is_checkpoint(timestamp)	(((timestamp) / SECONDS_PER_HOUR % HOURS_PER_CHECKPOINT) == 0)
#define ingress_is_cycle(timestamp)			(((timestamp) / SECONDS_PER_HOUR % HOURS_PER_CYCLE) == 0)

typedef struct Cycle {
	int year;
	int cycle;
	int checkpoint;
	int seconds;
} Cycle;

void ingress_get_cycle(const time_t time, Cycle *cycle);

