/* This software is released under the MIT License, see LICENSE */

#pragma once

#define ICON_SIZE 16

#define MIN(p, q)				((p) <= (q) ? (p) : (q))
#define MAX(p, q)				((p) >= (q) ? (p) : (q))

#define MINUTE_TO_TRIGANGLE(m)	DEG_TO_TRIGANGLE((m) * 6)
#define HOUR_TO_TRIGANGLE(h)	DEG_TO_TRIGANGLE((h) * 30)

