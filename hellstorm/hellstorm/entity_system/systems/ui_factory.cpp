//
//  ui_factory.cpp
//  hellstorm
//
//  Created by jrk on 23/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ui_factory.h"
#include "ConfigFile.h"
namespace hs 
{
	namespace ui
	{
		entity *create_button(entity_manager *em, 
							  std::string filename, 
							  std::string label_text,
							  rect rc_unpressed,
							  rect rc_pressed,
							  vec3d position,
							  vec2d anchor)
		{
			entity *ret = em->new_entity();
			button *btn = em->add_component<button>(ret);
			btn->type = e_control_button;
		
			btn->rc_idle = rc_unpressed;
			btn->rc_pressed = rc_pressed;
			
			btn->graphic = hs::factory::create_atlas_sprite(em, filename, position, rc_unpressed, anchor);
			
			if (label_text.length() > 0)
				btn->text = hs::factory::create_text_label(em, "impact20.fnt", label_text, position, anchor);
			else
				btn->text = NULL;
				
			return ret;
		}
		
		entity *create_button_from_file(entity_manager *em, std::string filename, vec3d position, std::string caption, vec2d anchor)
		{
			try
			{
				ConfigFile cfg(path_for_file(filename.c_str()));
				
				//mandatory
				std::string button_texture;
				button_texture = cfg.read<std::string>("texture");

				//mandatory!
				rect rc_idle;
				rc_idle.x = cfg.read<double>("idle.x");
				rc_idle.y = cfg.read<double>("idle.y");
				rc_idle.w = cfg.read<double>("idle.w");
				rc_idle.h = cfg.read<double>("idle.h");

				//mandatory!
				rect rc_pressed;
				rc_pressed.x = cfg.read<double>("pressed.x");
				rc_pressed.y = cfg.read<double>("pressed.y");
				rc_pressed.w = cfg.read<double>("pressed.w");
				rc_pressed.h = cfg.read<double>("pressed.h");
				
				//mandatory!
				std::string font;
				font = cfg.read<std::string>("font");
				
				//optional
				hs::vec2d pressin = hs::vec2d_zero;
				cfg.readInto(pressin.x, "pressin.x");
				cfg.readInto(pressin.y, "pressin.y");
				
				//optional
				double pressin_rot = 0.0;
				cfg.readInto(pressin_rot, "pressin.rot");

				entity *ret = em->new_entity();
				button *btn = em->add_component<button>(ret);
				btn->type = e_control_button;
				btn->rc_idle = rc_idle;
				btn->rc_pressed = rc_pressed;
				btn->pressin = pressin;
				btn->pressin_rot = pressin_rot;

				
				btn->graphic = hs::factory::create_atlas_sprite(em, button_texture, position, rc_idle, anchor);
				btn->text = hs::factory::create_text_label(em, font, caption, position, anchor);
				
				return ret;
			} 
			catch (ConfigFile::file_not_found f)
			{
				printf("couldn't open %s!\n", f.filename.c_str());
				abort();
			}
			catch (ConfigFile::key_not_found f)
			{
				printf("couldn't find key %s in file %s!\n", f.key.c_str(), filename.c_str());
				abort();
			}
			return NULL;
		}
	}
}