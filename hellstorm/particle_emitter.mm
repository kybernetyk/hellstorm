//
//  particle_emitter.cpp
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "particle_emitter.h"
#include "hellstorm.h"
#import "ParticleEmitter.h"

namespace hs 
{
	particle_emitter::particle_emitter()
	{
		init();
	}
	
	particle_emitter::particle_emitter(std::string fn)
	{
		init();
		load_from_file(fn);
	}
	
	particle_emitter::~particle_emitter()
	{
		if (objc_pe_ptr)
		{
			ParticleEmitter *pem = (ParticleEmitter *)objc_pe_ptr;
			[pem release];
			objc_pe_ptr = nil;
		}
	}
	
	void particle_emitter::init(void)
	{
		renderable::init();
		objc_pe_ptr = 0;
		do_not_delete = false;
	}
	
	bool particle_emitter::load_from_file(std::string fn)
	{
		NSString *nsfilename = [NSString stringWithCString: fn.c_str() 
												  encoding: NSASCIIStringEncoding];
		objc_pe_ptr = [[ParticleEmitter alloc] initParticleEmitterWithFile: nsfilename];
		if (objc_pe_ptr)
			return true;
		
		return false;
	}
	
	void particle_emitter::update(double dt)
	{
		Vector2f p = {position.x, position.y};
		
		ParticleEmitter *pe = (ParticleEmitter*)objc_pe_ptr;
		
		[pe setSourcePosition: p];
		[pe updateWithDelta: dt];
	}
	
	void particle_emitter::render_content(void)
	{
		if (![(ParticleEmitter*)objc_pe_ptr particleCount])
			return;
		
		glPushMatrix();
		glTranslatef(0.0, 0.0, position.z);
		[(ParticleEmitter*)objc_pe_ptr renderParticles];
		glPopMatrix();
	}
	
	bool particle_emitter::is_active(void)
	{
		return [(ParticleEmitter*)objc_pe_ptr active];
	}
	
	bool particle_emitter::should_handle(void)
	{
		if (![(ParticleEmitter*)objc_pe_ptr active] && [(ParticleEmitter*)objc_pe_ptr particleCount] == 0)
			return false;
		return true;
	}
	
	void particle_emitter::start(void)
	{
		[(ParticleEmitter*)objc_pe_ptr startParticleEmitter];
	}
	
	void particle_emitter::stop(void)
	{
		[(ParticleEmitter*)objc_pe_ptr stopParticleEmitter];
	}
	
	void particle_emitter::reset(void)
	{
		[(ParticleEmitter*)objc_pe_ptr reset];
	}
	
	double particle_emitter::duration(void)
	{
		return [(ParticleEmitter*)objc_pe_ptr duration];
	}
	
	void particle_emitter::set_duration(double dur)
	{
		[(ParticleEmitter*)objc_pe_ptr setDuration: dur];
	}
				
	
}