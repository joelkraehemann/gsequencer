/* AGS - Advanced GTK Sequencer
 * Copyright (C) 2005-2011 Joël Krähemann
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __AGS_SYNTH_H__
#define __AGS_SYNTH_H__

#include <glib.h>
#include <glib-object.h>

#include <ags/object/ags_soundcard.h>

void ags_synth_sin(AgsSoundcard *soundcard, signed short *buffer, guint offset,
		   guint freq, guint phase, guint length,
		   double volume);

void ags_synth_saw(AgsSoundcard *soundcard, signed short *buffer, guint offset,
		   guint freq, guint phase, guint length,
		   double volume);
void ags_synth_triangle(AgsSoundcard *soundcard, signed short *buffer, guint offset,
			guint freq, guint phase, guint length,
			double volume);
void ags_synth_square(AgsSoundcard *soundcard, signed short *buffer, guint offset,
		      guint freq, guint phase, guint length,
		      double volume);

#endif /*__AGS_SYNTH_H__*/
