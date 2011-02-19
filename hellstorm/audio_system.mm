//
//  audio_system.cpp
//  hellstorm
//
//  Created by jrk on 19/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "audio_system.h"
#include "hellstorm.h"

#if __IPHONE_OS_VERSION_MIN_REQUIRED >= 30000
#import <AVFoundation/AVFoundation.h>
#endif
#import <AudioToolbox/AudioToolbox.h>

#import "CocosDenshion.h"
#import "SimpleAudioEngine.h"


namespace hs 
{
	audio_system::audio_system()
	{
		
	}
	
	audio_system::~audio_system()
	{
		
	}
	
	void audio_system::preload_sound(std::string filename)
	{
		NSString *fn = [NSString stringWithCString: filename.c_str() encoding: NSASCIIStringEncoding];
		[[SimpleAudioEngine sharedEngine] preloadEffect: fn];
	}

	void audio_system::unload_sound(std::string filename)
	{
		NSString *fn = [NSString stringWithCString: filename.c_str() encoding: NSASCIIStringEncoding];
		[[SimpleAudioEngine sharedEngine] unloadEffect: fn];
	}

	void audio_system::play_sound(std::string filename)
	{
		NSString *fn = [NSString stringWithCString: filename.c_str() encoding: NSASCIIStringEncoding];
		[[SimpleAudioEngine sharedEngine] playEffect: fn];
	}
	
	void audio_system::play_music(std::string filename)
	{
		[[SimpleAudioEngine sharedEngine] stopBackgroundMusic];
		
		NSString *fn = [NSString stringWithCString: filename.c_str() encoding: NSASCIIStringEncoding];
		
		[[SimpleAudioEngine sharedEngine] playBackgroundMusic: fn loop: YES];
		
		last_music_played = filename;
	}
	
	void audio_system::stop_music(void)
	{
		[[SimpleAudioEngine sharedEngine] stopBackgroundMusic];
	}
	
	void audio_system::pause_music(void)
	{
		[[SimpleAudioEngine sharedEngine] pauseBackgroundMusic];
	}
	
	void audio_system::rewind_music(void)
	{
		[[SimpleAudioEngine sharedEngine] rewindBackgroundMusic];
	}
	
	void audio_system::resume_music(void)
	{
		if (last_music_played.length() > 2) //> ""
			play_music(last_music_played);
	//	[[SimpleAudioEngine sharedEngine] resumeBackgroundMusic];
	}
	
	
	void audio_system::set_music_volume(double vol)
	{
		//if we change to volume 0 let's set the fx only mode
		//so other apps may play music
		if (vol <= 0.0 && music_volume > 0.0)
		{
			CDAudioManager *am = [CDAudioManager sharedManager];
			[am setMode: kAMM_FxOnly];
		}
		
		//if new volume is > 0 and previous volume was 0
		//then let's set a new mode and resume music
		if (vol > 0.0 && music_volume <= 0.0)
		{
			CDAudioManager *am = [CDAudioManager sharedManager];
			[am setMode: kAMM_FxPlusMusic];
			resume_music();
		}
		
		[[SimpleAudioEngine sharedEngine] setBackgroundMusicVolume: vol];
		music_volume = vol;
	}
	
	double audio_system::get_music_volume(void)
	{
		return music_volume;
	}
	
	void audio_system::set_sound_volume(double vol)
	{
		[[SimpleAudioEngine sharedEngine] setEffectsVolume: vol];
		sound_volume = vol;
	}
	
	double audio_system::get_sound_volume(void)
	{
		return sound_volume;
	}


}
