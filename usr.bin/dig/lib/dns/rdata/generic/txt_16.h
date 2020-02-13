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

/* */
#ifndef GENERIC_TXT_16_H
#define GENERIC_TXT_16_H 1

/* $Id: txt_16.h,v 1.3 2020/02/13 13:53:01 jsg Exp $ */

typedef struct dns_rdata_txt_string {
		uint8_t    length;
		unsigned char   *data;
} dns_rdata_txt_string_t;

typedef struct dns_rdata_txt {
	dns_rdatacommon_t       common;
	unsigned char           *txt;
	uint16_t            txt_len;
	/* private */
	uint16_t            offset;
} dns_rdata_txt_t;

#endif /* GENERIC_TXT_16_H */
