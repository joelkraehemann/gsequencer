/* AGS Client - Advanced GTK Sequencer Client
 * Copyright (C) 2013 Joël Krähemann
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

#ifndef __AGS_SCRIPT_FSCANF_H__
#define __AGS_SCRIPT_FSCANF_H__

#include <glib.h>
#include <glib-object.h>

#include <ags-client/scripting/mapping/ags_script_controller.h>

#define AGS_TYPE_SCRIPT_FSCANF                (ags_script_fscanf_get_type())
#define AGS_SCRIPT_FSCANF(obj)                (G_TYPE_CHECK_INSTANCE_CAST((obj), AGS_TYPE_SCRIPT_FSCANF, AgsScriptFScanf))
#define AGS_SCRIPT_FSCANF_CLASS(class)        (G_TYPE_CHECK_CLASS_CAST(class, AGS_TYPE_SCRIPT_FSCANF, AgsScriptFScanfClass))
#define AGS_IS_SCRIPT_FSCANF(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), AGS_TYPE_SCRIPT_FSCANF))
#define AGS_IS_SCRIPT_FSCANF_CLASS(class)     (G_TYPE_CHECK_CLASS_TYPE ((class), AGS_TYPE_SCRIPT_FSCANF))
#define AGS_SCRIPT_FSCANF_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS(obj, AGS_TYPE_SCRIPT_FSCANF, AgsScriptFScanfClass))

typedef struct _AgsScriptFScanf AgsScriptFScanf;
typedef struct _AgsScriptFScanfClass AgsScriptFScanfClass;

struct _AgsScriptFScanf
{
  AgsScriptController controller;
};

struct _AgsScriptFScanfClass
{
  AgsScriptControllerClass controller;
};

GType ags_script_fscanf_get_type();

AgsScriptFScanf* ags_script_fscanf_new();

#endif /*__AGS_SCRIPT_FSCANF_H__*/
