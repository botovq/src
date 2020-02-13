/*
 * Copyright (C) Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/* $Id: time.h,v 1.3 2020/02/13 13:53:01 jsg Exp $ */

#ifndef ISC_TIME_H
#define ISC_TIME_H 1

/*! \file */

#include <isc/types.h>

/***
 *** Intervals
 ***/

/*!
 *  \brief
 * The contents of this structure are private, and MUST NOT be accessed
 * directly by callers.
 *
 * The contents are exposed only to allow callers to avoid dynamic allocation.
 */
struct interval {
	unsigned int seconds;
	unsigned int nanoseconds;
};

extern const interval_t * const interval_zero;

/*
 * ISC_FORMATHTTPTIMESTAMP_SIZE needs to be 30 in C locale and potentially
 * more for other locales to handle longer national abbreviations when
 * expanding strftime's %a and %b.
 */
#define ISC_FORMATHTTPTIMESTAMP_SIZE 50

void
interval_set(interval_t *i,
		 unsigned int seconds, unsigned int nanoseconds);
/*%<
 * Set 'i' to a value representing an interval of 'seconds' seconds and
 * 'nanoseconds' nanoseconds, suitable for use in isc_time_add() and
 * isc_time_subtract().
 *
 * Requires:
 *
 *\li	't' is a valid pointer.
 *\li	nanoseconds < 1000000000.
 */

isc_boolean_t
interval_iszero(const interval_t *i);
/*%<
 * Returns ISC_TRUE iff. 'i' is the zero interval.
 *
 * Requires:
 *
 *\li	'i' is a valid pointer.
 */

/***
 *** Absolute Times
 ***/

/*%
 * The contents of this structure are private, and MUST NOT be accessed
 * directly by callers.
 *
 * The contents are exposed only to allow callers to avoid dynamic allocation.
 */

struct isc_time {
	unsigned int	seconds;
	unsigned int	nanoseconds;
};

extern const isc_time_t * const isc_time_epoch;

void
isc_time_set(isc_time_t *t, unsigned int seconds, unsigned int nanoseconds);
/*%<
 * Set 't' to a value which represents the given number of seconds and
 * nanoseconds since 00:00:00 January 1, 1970, UTC.
 *
 * Notes:
 *\li	The Unix version of this call is equivalent to:
 *\code
 *	isc_time_settoepoch(t);
 *	interval_set(i, seconds, nanoseconds);
 *	isc_time_add(t, i, t);
 *\endcode
 *
 * Requires:
 *\li	't' is a valid pointer.
 *\li	nanoseconds < 1000000000.
 */

void
isc_time_settoepoch(isc_time_t *t);
/*%<
 * Set 't' to the time of the epoch.
 *
 * Notes:
 *\li	The date of the epoch is platform-dependent.
 *
 * Requires:
 *
 *\li	't' is a valid pointer.
 */

isc_boolean_t
isc_time_isepoch(const isc_time_t *t);
/*%<
 * Returns ISC_TRUE iff. 't' is the epoch ("time zero").
 *
 * Requires:
 *
 *\li	't' is a valid pointer.
 */

isc_result_t
isc_time_now(isc_time_t *t);
/*%<
 * Set 't' to the current absolute time.
 *
 * Requires:
 *
 *\li	't' is a valid pointer.
 *
 * Returns:
 *
 *\li	Success
 *\li	Unexpected error
 *		Getting the time from the system failed.
 *\li	Out of range
 *		The time from the system is too large to be represented
 *		in the current definition of isc_time_t.
 */

int
isc_time_compare(const isc_time_t *t1, const isc_time_t *t2);
/*%<
 * Compare the times referenced by 't1' and 't2'
 *
 * Requires:
 *
 *\li	't1' and 't2' are valid pointers.
 *
 * Returns:
 *
 *\li	-1		t1 < t2		(comparing times, not pointers)
 *\li	0		t1 = t2
 *\li	1		t1 > t2
 */

isc_result_t
isc_time_add(const isc_time_t *t, const interval_t *i, isc_time_t *result);
/*%<
 * Add 'i' to 't', storing the result in 'result'.
 *
 * Requires:
 *
 *\li	't', 'i', and 'result' are valid pointers.
 *
 * Returns:
 *\li	Success
 *\li	Out of range
 * 		The interval added to the time is too large to
 *		be represented in the current definition of isc_time_t.
 */

isc_result_t
isc_time_subtract(const isc_time_t *t, const interval_t *i,
		  isc_time_t *result);
/*%<
 * Subtract 'i' from 't', storing the result in 'result'.
 *
 * Requires:
 *
 *\li	't', 'i', and 'result' are valid pointers.
 *
 * Returns:
 *\li	Success
 *\li	Out of range
 *		The interval is larger than the time since the epoch.
 */

uint64_t
isc_time_microdiff(const isc_time_t *t1, const isc_time_t *t2);
/*%<
 * Find the difference in microseconds between time t1 and time t2.
 * t2 is the subtrahend of t1; ie, difference = t1 - t2.
 *
 * Requires:
 *
 *\li	't1' and 't2' are valid pointers.
 *
 * Returns:
 *\li	The difference of t1 - t2, or 0 if t1 <= t2.
 */

uint32_t
isc_time_seconds(const isc_time_t *t);
/*%<
 * Return the number of seconds since the epoch stored in a time structure.
 *
 * Requires:
 *
 *\li	't' is a valid pointer.
 */

uint32_t
isc_time_nanoseconds(const isc_time_t *t);
/*%<
 * Return the number of nanoseconds stored in a time structure.
 *
 * Notes:
 *\li	This is the number of nanoseconds in excess of the number
 *	of seconds since the epoch; it will always be less than one
 *	full second.
 *
 * Requires:
 *\li	't' is a valid pointer.
 *
 * Ensures:
 *\li	The returned value is less than 1*10^9.
 */

void
isc_time_formattimestamp(const isc_time_t *t, char *buf, unsigned int len);
/*%<
 * Format the time 't' into the buffer 'buf' of length 'len',
 * using a format like "30-Aug-2000 04:06:47.997" and the local time zone.
 * If the text does not fit in the buffer, the result is indeterminate,
 * but is always guaranteed to be null terminated.
 *
 *  Requires:
 *\li      'len' > 0
 *\li      'buf' points to an array of at least len chars
 *
 */

void
isc_time_formathttptimestamp(const isc_time_t *t, char *buf, unsigned int len);
/*%<
 * Format the time 't' into the buffer 'buf' of length 'len',
 * using a format like "Mon, 30 Aug 2000 04:06:47 GMT"
 * If the text does not fit in the buffer, the result is indeterminate,
 * but is always guaranteed to be null terminated.
 *
 *  Requires:
 *\li      'len' > 0
 *\li      'buf' points to an array of at least len chars
 *
 */

#endif /* ISC_TIME_H */
