/***
  This file is part of libcanberra.

  Copyright 2009 Rachel Foecking, Ryan Gee, Foster Nichols
  Copyright 2009 HFOSS: Hartford

  libcanberra is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 2.1 of the
  License, or (at your option) any later version.

  libcanberra is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with libcanberra. If not, see
  <http://www.gnu.org/licenses/>.
***/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string.h>

#include "canberra.h"
#include "common.h"
#include "driver.h"
#include "vizaudio.h"
#include "proplist.h"


/* Plays a visual effect from the VizAudio library */
int driver_play(ca_context *c, uint32_t id, ca_proplist *proplist, ca_finish_callback_t cb, void *userdata) {
    ca_return_val_if_fail(c, CA_ERROR_INVALID);
    ca_return_val_if_fail(proplist, CA_ERROR_INVALID);
    ca_return_val_if_fail(!userdata || cb, CA_ERROR_INVALID);

	if(!isVAEnabled()){
		 return CA_ERROR_DISABLED;
	}
	
	char* effect;
	// Get the visual effect
    effect = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_VISUAL_EFFECT);
    // Return if its not found
    ca_return_val_if_fail(effect, CA_ERROR_INVALID);

	if(!strcmp(effect, "SONG_INFO_POPUP")){
		// Grab additional info and goto finish if any are found
		char* artist;
		char* title;

		artist = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_MEDIA_ARTIST);
		title = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_MEDIA_TITLE);
    
        ca_return_val_if_fail(title, CA_ERROR_INVALID);
        ca_return_val_if_fail(artist, CA_ERROR_INVALID);

		// TODO: Make sure this isn't causing GTK errors
		//song_popup(artist, title);
	}
	else if (!strcmp(effect, "COLOR_ALERT")){
        char* color;
        color = (char*)ca_proplist_gets_unlocked(proplist, CA_PROP_COLOR);
        
        ca_return_val_if_fail(color, CA_ERROR_INVALID);
        
		flash_color(color);
		return CA_SUCCESS;
	}
	else if (!strcmp(effect, "IMAGE_ALERT")){
		char* filePath = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_MEDIA_IMAGE_PATH);
		
		// Determine if the file actually exists
		FILE* file = fopen(filePath, "r");
        ca_return_val_if_fail(file, CA_ERROR_NOTFOUND);

		flash_image(filePath);

        fclose(file);
	}
	else if(!strcmp(effect, "FLYING_DESCRIPTION_TEXT_ALERT")){
		char* text = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_EVENT_DESCRIPTION);
		
		// Check for errors
        ca_return_val_if_fail(text, CA_ERROR_INVALID);

		flash_text(text);
	}

    
    if (cb){
        cb(c, id, CA_SUCCESS, userdata);
	}




    return CA_SUCCESS;
}

/* These methods are not currently relelvant to VizAudio*/
int driver_open(ca_context *c) {
    ca_return_val_if_fail(c, CA_ERROR_INVALID);
    ca_return_val_if_fail(!c->driver || ca_streq(c->driver, "vizaudio"), CA_ERROR_NODRIVER);

    return CA_SUCCESS;
}

int driver_destroy(ca_context *c) {
    ca_return_val_if_fail(c, CA_ERROR_INVALID);

    return CA_SUCCESS;
}

int driver_change_device(ca_context *c, const char *device) {
    ca_return_val_if_fail(c, CA_ERROR_INVALID);

    return CA_SUCCESS;
}

int driver_change_props(ca_context *c, ca_proplist *changed, ca_proplist *merged) {
    ca_return_val_if_fail(c, CA_ERROR_INVALID);
    ca_return_val_if_fail(changed, CA_ERROR_INVALID);
    ca_return_val_if_fail(merged, CA_ERROR_INVALID);

    return CA_SUCCESS;
}

int driver_cancel(ca_context *c, uint32_t id) {
    ca_return_val_if_fail(c, CA_ERROR_INVALID);

    return CA_SUCCESS;
}

int driver_cache(ca_context *c, ca_proplist *proplist) {
    ca_return_val_if_fail(c, CA_ERROR_INVALID);
    ca_return_val_if_fail(proplist, CA_ERROR_INVALID);

    return CA_ERROR_NOTSUPPORTED;
}
