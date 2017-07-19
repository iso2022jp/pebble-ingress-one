/* This software is released under the MIT License, see LICENSE */

#include "./ingress.h"

// 2014 Cycle 01, CheckPoint 00 (2014-01-08 03:00 UTC)
// 2016 Cycle 01, CheckPoint 00 (2016-01-07 07:00 UTC)

// Compute ingress time
void ingress_get_cycle(const time_t timestamp, Cycle *cycle) {

	if (!cycle) {
		return; // Boom
	}

	cycle->year = gmtime(&timestamp)->tm_year + 1900;

	struct tm firstDay = {
		.tm_year = cycle->year - 1900,
		.tm_mon = 0, // Jan
		.tm_mday = 1, // 1st
	};
	
	time_t firstDayTime = mktime(&firstDay);
	time_t firstCycle = (firstDayTime + SECONDS_PER_CYCLE - 1) / SECONDS_PER_CYCLE * SECONDS_PER_CYCLE;

	if (timestamp < firstCycle) {

		--firstDay.tm_year;
		--cycle->year;
		firstDayTime = mktime(&firstDay);
		firstCycle = (firstDayTime + SECONDS_PER_CYCLE - 1) / SECONDS_PER_CYCLE * SECONDS_PER_CYCLE;

	}
	cycle->cycle = (timestamp - firstCycle) / SECONDS_PER_CYCLE;

	int duration = timestamp % SECONDS_PER_CYCLE;
	cycle->checkpoint = duration / SECONDS_PER_CHECKPOINT;
	cycle->seconds = duration % SECONDS_PER_CHECKPOINT;

}
