/* quirc -- QR-code recognition library
 * Copyright (C) 2010-2012 Daniel Beer <dlbeer@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include "quirc_internal.h"
#include "dbgutil.h"

int main(int argc, char **argv)
{
	struct quirc *q;

	printf("quirc inspection program\n");
	printf("Copyright (C) 2010-2012 Daniel Beer <dlbeer@gmail.com>\n");
	printf("Library version: %s\n", quirc_version());
	printf("\n");

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <testfile.jpg|testfile.png>\n", argv[0]);
		return -1;
	}

	q = quirc_new();
	if (!q) {
		perror("can't create quirc object");
		return -1;
	}

	int status = -1;
	if (check_if_png(argv[1])) {
		status = load_png(q, argv[1]);
	} else {
		status = load_jpeg(q, argv[1]);
	}
	if (status < 0) {
		quirc_destroy(q);
		return -1;
	}

	quirc_end(q);

	int count = quirc_count(q);
	printf("qrcode count %d\n", count);
	if (count == 0) {
		fprintf(stderr, "no qrcode");
	}

	quirc_destroy(q);
	return 0;
}
