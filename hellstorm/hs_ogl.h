//
//  hs_ogl.h
//  hellstorm
//
//  Created by jrk on 18/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#else
#include <OpenGL/OpenGL.h>
#include <OpenGL/glext.h>
#define GL_FRAMEBUFFER_BINDING_OES GL_FRAMEBUFFER_BINDING
#define GL_FRAMEBUFFER_OES GL_FRAMEBUFFER
#define glGenFramebuffersOES glGenFramebuffers
#define GL_COLOR_ATTACHMENT0_OES GL_COLOR_ATTACHMENT0
#define glFramebufferTexture2DOES glFramebufferTexture2D
#define glBindFramebufferOES glBindFramebuffer
#define GL_RENDERBUFFER_OES GL_RENDERBUFFER
#define GL_RENDERBUFFER_WIDTH_OES GL_RENDERBUFFER_WIDTH
#define GL_RENDERBUFFER_HEIGHT_OES GL_RENDERBUFFER_HEIGHT
#define glGetRenderbufferParameterivOES glGetRenderbufferParameteriv
#define glGenRenderbuffersOES glGenRenderbuffers
#define GL_DEPTH_COMPONENT16_OES GL_DEPTH_COMPONENT16
#define glBindRenderbufferOES glBindRenderbuffer
#define glRenderbufferStorageOES glRenderbufferStorage
#define GL_DEPTH_ATTACHMENT_OES GL_DEPTH_ATTACHMENT
#define glFramebufferRenderbufferOES glFramebufferRenderbuffer
#define GL_POINT_SIZE_ARRAY_OES GL_POINT_SIZE_ARRAY
#define glPointSizePointerOES glPointSizePointer
#define GL_POINT_SPRITE_OES GL_POINT_SPRITE
#define glOrthof glOrtho
#endif

