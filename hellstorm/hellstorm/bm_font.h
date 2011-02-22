/*
 *  bm_font.h
 *  ComponentV3
 *
 *  Created by jrk on 11/11/10.
 *  Copyright 2010 flux forge. All rights reserved.
 *
 */
#pragma once
typedef struct bm_char
{
	int x,y,w,h;
	
	int x_offset, y_offset;
	int x_advance, page, chnl;
} bm_char;

typedef struct bm_kerninfo
{
	short first, second;
	short kerning;
} bm_kerninfo;

typedef struct bm_font
{
	float scale;
	int base;
	int line_h;
	int w,h;
	int pages;
	int kerninfo_count;
	
	bm_char chars[255];
	char tex_filename[255];
	
} bm_font;

enum bm_alignment 
{
	left = 0,
	center,
	right
};

extern int bm_loadfont (const char *filename, bm_font *font);
extern int bm_width (bm_font *font, const char *text);
extern int bm_height (bm_font *font, const char *text);
extern void bm_destroyfont (bm_font *font);
