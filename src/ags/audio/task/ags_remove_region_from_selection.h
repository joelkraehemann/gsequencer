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

#ifndef __AGS_REMOVE_REGION_FROM_SELECTION_H__
#define __AGS_REMOVE_REGION_FROM_SELECTION_H__

#include <glib.h>
#include <glib-object.h>

#include <ags/thread/ags_task.h>
#include <ags/audio/ags_notation.h>

#define AGS_TYPE_REMOVE_REGION_FROM_SELECTION                (ags_remove_region_from_selection_get_type())
#define AGS_REMOVE_REGION_FROM_SELECTION(obj)                (G_TYPE_CHECK_INSTANCE_CAST((obj), AGS_TYPE_REMOVE_REGION_FROM_SELECTION, AgsRemoveRegionFromSelection))
#define AGS_REMOVE_REGION_FROM_SELECTION_CLASS(class)        (G_TYPE_CHECK_CLASS_CAST((class), AGS_TYPE_REMOVE_REGION_FROM_SELECTION, AgsRemoveRegionFromSelectionClass))
#define AGS_IS_REMOVE_REGION_FROM_SELECTION(obj)             (G_TYPE_CHECK_INSTANCE_TYPE((obj), AGS_TYPE_REMOVE_REGION_FROM_SELECTION))
#define AGS_IS_REMOVE_REGION_FROM_SELECTION_CLASS(class)     (G_TYPE_CHECK_CLASS_TYPE((class), AGS_TYPE_REMOVE_REGION_FROM_SELECTION))
#define AGS_REMOVE_REGION_FROM_SELECTION_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS((obj), AGS_TYPE_REMOVE_REGION_FROM_SELECTION, AgsRemoveRegionFromSelectionClass))

typedef struct _AgsRemoveRegionFromSelection AgsRemoveRegionFromSelection;
typedef struct _AgsRemoveRegionFromSelectionClass AgsRemoveRegionFromSelectionClass;

struct _AgsRemoveRegionFromSelection
{
  AgsTask task;

  AgsNotation *notation;

  guint x0;
  guint y0;
  guint x1;
  guint y1;
};

struct _AgsRemoveRegionFromSelectionClass
{
  AgsTaskClass task;
};

GType ags_remove_region_from_selection_get_type();

AgsRemoveRegionFromSelection* ags_remove_region_from_selection_new(AgsNotation *notation,
								   guint x0, guint y0,
								   guint x1, guint y1);

#endif /*__AGS_REMOVE_REGION_FROM_SELECTION_H__*/
