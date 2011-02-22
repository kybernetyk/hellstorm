/*
 *  bm_font.c
 *  ComponentV3
 *
 *  Created by jrk on 11/11/10.
 *  Copyright 2010 flux forge. All rights reserved.
 *
 */

#include "bm_font.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int bm_loadfont (const char *filename, bm_font *font)
{
	char spaces[100];
	
	
	FILE *f_in = fopen(filename, "rt");
	if (!f_in)
		return 0;
	
	//info skip
#define BUFFSIZE 1024
	char buff[BUFFSIZE];
	memset(buff,0x00,BUFFSIZE);
	fgets(buff, BUFFSIZE, f_in);
	
	int packed;
	
	//DIFF 1: alphaChnl, .... - 4 more fields
	
	//header
	int br = fscanf(f_in, "common lineHeight=%d base=%d scaleW=%d scaleH=%d pages=%d packed=%d alphaChnl=%d redChnl=%d greenChnl=%d blueChnl=%d\n",
					&font->line_h, &font->base, &font->w, &font->h, &font->pages,&packed,&packed,&packed,&packed,&packed 
					);
	//page skip
	
	memset(buff,0x00,BUFFSIZE);
	fgets(buff, BUFFSIZE, f_in);
	
	int page_id = 0;
	br = sscanf(buff, "page%[ ]id=%d%[ ]file=\"%s\"%[ ]\n",spaces,&page_id,spaces,font->tex_filename,spaces);
	
	if (font->tex_filename[strlen(font->tex_filename)-1] == '"')
		font->tex_filename[strlen(font->tex_filename)-1] = 0; //remove "
	
	//char count
	memset(buff,0x00,BUFFSIZE);
	fgets(buff, BUFFSIZE, f_in);
	int chars_count = 0;
	br = sscanf(buff, "chars%[ ]count=%d\n",spaces,&chars_count);
	
	
	//chars
	int char_id;
	bm_char temp_char;
		
	//DIFF 3: i < chars_count (for hiero <=) oO
	for (int i = 0; i <= chars_count; i++)
	{
		memset(buff,0x00,BUFFSIZE);
		fgets(buff, BUFFSIZE, f_in);
		//printf("%s",buff);
		//DIFF 2: no whitespace before \n. so br == 19 and not 20 like in hiero
		br = sscanf(buff, "char id=%d%[ ]x=%d%[ ]y=%d%[ ]width=%d%[ ]height=%d%[ ]xoffset=%d%[ ]yoffset=%d%[ ]xadvance=%d%[ ]page=%d%[ ]chnl=%d\n",
					&char_id, spaces,
					
					&temp_char.x, spaces,
					&temp_char.y, spaces,
					&temp_char.w, spaces,
					&temp_char.h, spaces,
					&temp_char.x_offset, spaces,
					&temp_char.y_offset, spaces,
					&temp_char.x_advance, spaces,
					&temp_char.page, spaces,
					&temp_char.chnl
					);
		if (br == 19)
		{
			font->chars[char_id] = temp_char;
		}
		else
		{
			break; //break the loop if we have no chars left (discard kerning, etc)
				   //abort();
		}
	}
	
	//DIFF 4: we should parse the kerning info
	//but we'll ignore it
	
	//	printf("\n##\n");
	fclose (f_in);
	return 1;
}


int bm_loadfont_hiero (const char *filename, bm_font *font)
{
	char spaces[100];
	
	
	FILE *f_in = fopen(filename, "rt");
	if (!f_in)
		return 0;
	
	//info skip
	char buff[512];
	memset(buff,0x00,512);
	fgets(buff, 512, f_in);
	
	int packed;
	
	//header
	int br = fscanf(f_in, "common lineHeight=%d base=%d scaleW=%d scaleH=%d pages=%d packed=%d\n",
					&font->line_h, &font->base, &font->w, &font->h, &font->pages,&packed
					);
	//page skip
	
	memset(buff,0x00,512);
	fgets(buff, 512, f_in);
	
	int page_id = 0;
	br = sscanf(buff, "page%[ ]id=%d%[ ]file=\"%s\"%[ ]\n",spaces,&page_id,spaces,font->tex_filename,spaces);
	
	if (font->tex_filename[strlen(font->tex_filename)-1] == '"')
		font->tex_filename[strlen(font->tex_filename)-1] = 0; //remove "
	
	//char count
	memset(buff,0x00,512);
	fgets(buff, 512, f_in);
	int chars_count = 0;
	br = sscanf(buff, "chars%[ ]count=%d%[ ]\n",spaces,&chars_count,spaces);
	
	
	//chars
	
	
	for (int i = 0; i <= chars_count; i++)
	{
		int char_id;
		bm_char temp_char;
		
		memset(buff,0x00,512);
		fgets(buff, 512, f_in);
		
		
		br = sscanf(buff, "char id=%d%[ ]x=%d%[ ]y=%d%[ ]width=%d%[ ]height=%d%[ ]xoffset=%d%[ ]yoffset=%d%[ ]xadvance=%d%[ ]page=%d%[ ]chnl=%d%[ ]\n",
					&char_id, spaces,
					
					&temp_char.x, spaces,
					&temp_char.y, spaces,
					&temp_char.w, spaces,
					&temp_char.h, spaces,
					&temp_char.x_offset, spaces,
					&temp_char.y_offset, spaces,
					&temp_char.x_advance, spaces,
					&temp_char.page, spaces,
					&temp_char.chnl,spaces	
					);
		if (br == 20)
		{
			font->chars[char_id] = temp_char;
		}
		else
		{
			abort();
		}
		
	}
	
	
	fclose (f_in);
	return 1;
}

int bm_width (bm_font *font, const char *text)
{
	int w, l;
	
	w = 0;
	l = strlen(text);
	
	for (int i = 0; i < l; i++)
	{
		//w += font->chars[text[i]].w;
		w += font->chars[text[i]].x_advance-font->chars[text[i]].x_offset;
	}
	
	return w;
}

int bm_height (bm_font *font, const char *text)
{
	int h = 0;
	int l = strlen(text);
	int th = 0;
	for (int i = 0; i < l; i++)
	{
		th = font->chars[text[i]].h;
		if (th > h)
			h = th;
	}
	
	return h;
}

void bm_destroyfont (bm_font *font)
{
	
}
