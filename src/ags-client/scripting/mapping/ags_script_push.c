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

#include <ags-client/scripting/mapping/ags_script_push.h>

#include <ags/object/ags_connectable.h>

void ags_script_push_class_init(AgsScriptPushClass *script_push);
void ags_script_push_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_script_push_init(AgsScriptPush *script_push);
void ags_script_push_connect(AgsConnectable *connectable);
void ags_script_push_disconnect(AgsConnectable *connectable);
void ags_script_push_finalize(GObject *gobject);

static gpointer ags_script_push_parent_class = NULL;

GType
ags_script_push_get_type()
{
  static GType ags_type_script_push = 0;

  if(!ags_type_script_push){
    static const GTypeInfo ags_script_push_info = {
      sizeof (AgsScriptPushClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_script_push_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (AgsScriptPush),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_script_push_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_script_push_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    ags_type_script_push = g_type_register_static(AGS_TYPE_SCRIPT_CONTROLLER,
						  "AgsScriptPush\0",
						  &ags_script_push_info,
						  0);
    
    g_type_add_interface_static(ags_type_script_push,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);
  }

  return (ags_type_script_push);
}

void
ags_script_push_class_init(AgsScriptPushClass *script_push)
{
  GObjectClass *gobject;

  ags_script_push_parent_class = g_type_class_peek_parent(script_push);

  /* GObjectClass */
  gobject = (GObjectClass *) script_push;

  gobject->finalize = ags_script_push_finalize;
}

void
ags_script_push_connectable_interface_init(AgsConnectableInterface *connectable)
{
  connectable->connect = ags_script_push_connect;
  connectable->disconnect = ags_script_push_disconnect;
}

void
ags_script_push_init(AgsScriptPush *script_push)
{
  //TODO:JK: implement me
}

void
ags_script_push_connect(AgsConnectable *connectable)
{
  /* empty */
}

void
ags_script_push_disconnect(AgsConnectable *connectable)
{
  /* empty */
}

void
ags_script_push_finalize(GObject *gobject)
{
  AgsScriptPush *script_push;

  script_push = AGS_SCRIPT_PUSH(gobject);

  G_OBJECT_CLASS(ags_script_push_parent_class)->finalize(gobject);
}

AgsScriptPush*
ags_script_push_new()
{
  AgsScriptPush *script_push;

  script_push = (AgsScriptPush *) g_object_new(AGS_TYPE_SCRIPT_PUSH,
					       NULL);

  return(script_push);
}
