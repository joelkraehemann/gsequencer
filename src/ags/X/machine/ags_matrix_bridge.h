/* AGS - Advanced GTK Sequencer
 * Copyright (C) 2015 Joël Krähemann
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

#ifndef __AGS_MATRIX_BRIDGE_H__
#define __AGS_MATRIX_BRIDGE_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

#include <ags/X/ags_effect_bridge.h>

#define AGS_TYPE_MATRIX_BRIDGE                (ags_matrix_bridge_get_type())
#define AGS_MATRIX_BRIDGE(obj)                (G_TYPE_CHECK_INSTANCE_CAST((obj), AGS_TYPE_MATRIX_BRIDGE, AgsMatrixBridge))
#define AGS_MATRIX_BRIDGE_CLASS(class)        (G_TYPE_CHECK_CLASS_CAST((class), AGS_TYPE_MATRIX_BRIDGE, AgsMatrixBridgeClass))
#define AGS_IS_MATRIX_BRIDGE(obj)             (G_TYPE_CHECK_INSTANCE_TYPE((obj), AGS_TYPE_MATRIX_BRIDGE))
#define AGS_IS_MATRIX_BRIDGE_CLASS(class)     (G_TYPE_CHECK_CLASS_TYPE ((class), AGS_TYPE_MATRIX_BRIDGE))
#define AGS_MATRIX_BRIDGE_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS (obj, AGS_TYPE_MATRIX_BRIDGE, AgsMatrixBridgeClass))

typedef struct _AgsMatrixBridge AgsMatrixBridge;
typedef struct _AgsMatrixBridgeClass AgsMatrixBridgeClass;

struct _AgsMatrixBridge
{
  AgsEffectBridge effect_bridge;
};

struct _AgsMatrixBridgeClass
{
  AgsEffectBridgeClass effect_bridge;
};

GType ags_matrix_bridge_get_type(void);

AgsMatrixBridge* ags_matrix_bridge_new(AgsAudio *audio);

#endif /*__AGS_MATRIX_BRIDGE_H__*/