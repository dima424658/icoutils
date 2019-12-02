/* icotool.h - Common definitions for icotool
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

#ifndef ICOTOOL_H
#define ICOTOOL_H

#include <stdbool.h>		/* POSIX/Gnulib */
#include <stdint.h>		/* POSIX/Gnulib */
#include <stdio.h>		/* C89 */
#include "common/common.h"

typedef struct _Palette Palette;

/* palette.c */
Palette *palette_new(void);
void palette_free(Palette *palette);
void palette_add(Palette *palette, uint8_t r, uint8_t g, uint8_t b);
bool palette_next(Palette *palette, uint8_t *r, uint8_t *g, uint8_t *b);
void palette_assign_indices(Palette *palette);
uint32_t palette_lookup(Palette *palette, uint8_t r, uint8_t g, uint8_t b);
uint32_t palette_count(Palette *palette);

/* extract.c */
typedef FILE *(*ExtractNameGen)(const char *inname, char **outname, int width, int height, int bitcount, int index);
typedef bool (*ExtractFilter)(int index, int width, int height, int bitdepth, int palettesize, bool icon, int hotspot_x, int hotspot_y);
int extract_icons(FILE *in, const char *inname, bool listmode, ExtractNameGen outfile_gen, ExtractFilter filter);

/* create.c */
typedef FILE *(*CreateNameGen)(char **outname);
typedef struct InputFile_s {
    char *name;
    bool is_raw;
    int32_t bit_count;
    int32_t hotspot_x;
    int32_t hotspot_y;
} InputFile;
typedef struct InputFiles_s {
    size_t count;
    InputFile *files;
} InputFiles;
bool create_icon(InputFiles *files, CreateNameGen outfile_gen, bool icon_mode, int32_t alpha_threshold);
#endif
