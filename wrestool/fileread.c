/* fileread.c - Offset checking routines for file reading
 *
 * Copyright (C) 1998 Oskar Liljeblad
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <stdio.h>		/* C89 */
#include <stdlib.h>		/* C89 */
#include <string.h>		/* C89 */
#include <stdbool.h>		/* POSIX/Gnulib */
#include "gettext.h"			/* Gnulib */
#define _(s) gettext(s)
#define N_(s) gettext_noop(s)
#include "common/error.h"
#include "common/common.h"

/* check_offset:
 *   Check if a chunk of data (determined by offset and size)
 *   is within the bounds of the WinLibrary file.
 *   Usually not called directly.
 */
bool
check_offset(const char *memory, size_t total_size,
             const char *name, const void *offset, size_t size)
{
	const char* memory_end = memory + total_size;
	const char* block = (const char*) offset;
	const char* block_end = block + size;

	/*debug("check_offset: size=%x vs %x offset=%x size=%x\n",
		need_size, total_size, (char *) offset - memory, size);*/

	if (((memory > memory_end) || (block > block_end))
		|| (block < memory) || (block >= memory_end) || (block_end > memory_end)) {
		warn(_("%s: premature end"), name);
		return false;
	}

	return true;
}
