//
//  hellstorm.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#define __RUNTIME_INFORMATION__

#include "hs_types.h"
#include "file_util.h"
#include "timer.h"
#include "user_settings.h"
#include "hellstorm_config.h"
#include "notification_system.h"

#include "vec_2d.h"
#include "renderer.h"
#include "texture_2d.h"
#include "texture_manager.h"
#include "renderable.h"
#include "renderable_manager.h"
#include "quad.h"
#include "atlas_quad.h"
#include "bitmap_font.h"
#include "particle_emitter.h"
#include "input_device.h"
#include "audio_system.h"

#include "entity_manager.h"
#include "components.h"
#include "system.h"

#include "corpse_retrieval_system.h"
#include "render_system.h"
#include "actions.h"
#include "action_system.h"
#include "animation_system.h"
#include "particle_system.h"
#include "ui_system.h"
#include "sprite_factory.h"
#include "ui_factory.h"

#include "scene.h"
#include "game.h"