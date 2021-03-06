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

#include <ags/X/task/ags_add_bulk_member.h>

#include <ags/object/ags_connectable.h>

#include <ags/audio/ags_audio.h>
#include <ags/audio/ags_channel.h>

#include <ags/X/ags_effect_bulk.h>

void ags_add_bulk_member_class_init(AgsAddBulkMemberClass *add_bulk_member);
void ags_add_bulk_member_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_add_bulk_member_init(AgsAddBulkMember *add_bulk_member);
void ags_add_bulk_member_connect(AgsConnectable *connectable);
void ags_add_bulk_member_disconnect(AgsConnectable *connectable);
void ags_add_bulk_member_finalize(GObject *gobject);

void ags_add_bulk_member_launch(AgsTask *task);

/**
 * SECTION:ags_add_bulk_member
 * @short_description: add line_member object to line
 * @title: AgsAddBulkMember
 * @section_id:
 * @include: ags/audio/task/ags_add_bulk_member.h
 *
 * The #AgsAddBulkMember task addspacks #AgsLineMember to #AgsLine.
 */

static gpointer ags_add_bulk_member_parent_class = NULL;
static AgsConnectableInterface *ags_add_bulk_member_parent_connectable_interface;

GType
ags_add_bulk_member_get_type()
{
  static GType ags_type_add_bulk_member = 0;

  if(!ags_type_add_bulk_member){
    static const GTypeInfo ags_add_bulk_member_info = {
      sizeof (AgsAddBulkMemberClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_add_bulk_member_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (AgsAddBulkMember),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_add_bulk_member_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_add_bulk_member_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    ags_type_add_bulk_member = g_type_register_static(AGS_TYPE_TASK,
						 "AgsAddBulkMember\0",
						 &ags_add_bulk_member_info,
						 0);

    g_type_add_interface_static(ags_type_add_bulk_member,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);
  }
  
  return (ags_type_add_bulk_member);
}

void
ags_add_bulk_member_class_init(AgsAddBulkMemberClass *add_bulk_member)
{
  GObjectClass *gobject;
  AgsTaskClass *task;

  ags_add_bulk_member_parent_class = g_type_class_peek_parent(add_bulk_member);

  /* gobject */
  gobject = (GObjectClass *) add_bulk_member;

  gobject->finalize = ags_add_bulk_member_finalize;

  /* task */
  task = (AgsTaskClass *) add_bulk_member;

  task->launch = ags_add_bulk_member_launch;
}

void
ags_add_bulk_member_connectable_interface_init(AgsConnectableInterface *connectable)
{
  ags_add_bulk_member_parent_connectable_interface = g_type_interface_peek_parent(connectable);

  connectable->connect = ags_add_bulk_member_connect;
  connectable->disconnect = ags_add_bulk_member_disconnect;
}

void
ags_add_bulk_member_init(AgsAddBulkMember *add_bulk_member)
{
  add_bulk_member->effect_bulk = NULL;
  add_bulk_member->bulk_member = NULL;
  add_bulk_member->x = 0;
  add_bulk_member->y = 0;
  add_bulk_member->width = 0;
  add_bulk_member->height = 0;
}

void
ags_add_bulk_member_connect(AgsConnectable *connectable)
{
  ags_add_bulk_member_parent_connectable_interface->connect(connectable);

  /* empty */
}

void
ags_add_bulk_member_disconnect(AgsConnectable *connectable)
{
  ags_add_bulk_member_parent_connectable_interface->disconnect(connectable);

  /* empty */
}

void
ags_add_bulk_member_finalize(GObject *gobject)
{
  G_OBJECT_CLASS(ags_add_bulk_member_parent_class)->finalize(gobject);

  /* empty */
}

void
ags_add_bulk_member_launch(AgsTask *task)
{
  AgsAddBulkMember *add_bulk_member;

  add_bulk_member = AGS_ADD_BULK_MEMBER(task);

  gtk_table_attach(AGS_EFFECT_BULK(add_bulk_member->effect_bulk)->table,
		   add_bulk_member->bulk_member,
		   add_bulk_member->x, add_bulk_member->x + add_bulk_member->width,
		   add_bulk_member->y, add_bulk_member->y + add_bulk_member->height,
		   GTK_FILL, GTK_FILL,
		   0, 0);
  gtk_widget_show_all(AGS_EFFECT_BULK(add_bulk_member->effect_bulk)->table);
}

/**
 * ags_add_bulk_member_new:
 * @line: the #AgsLine or #AgsEffectLine
 * @line_member: the #AgsLineMember to add
 * @x: pack start x
 * @y: pack start y
 * @width: pack width
 * @height: pack height
 *
 * Creates an #AgsAddBulkMember.
 *
 * Returns: an new #AgsAddBulkMember.
 *
 * Since: 0.4
 */
AgsAddBulkMember*
ags_add_bulk_member_new(GtkWidget *effect_bulk,
			AgsLineMember *bulk_member,
			guint x, guint y,
			guint width, guint height)
{
  AgsAddBulkMember *add_bulk_member;

  add_bulk_member = (AgsAddBulkMember *) g_object_new(AGS_TYPE_ADD_BULK_MEMBER,
						      NULL);

  add_bulk_member->effect_bulk = effect_bulk;
  add_bulk_member->bulk_member = bulk_member;
  add_bulk_member->x = x;
  add_bulk_member->y = y;
  add_bulk_member->width = width;
  add_bulk_member->height = height;

  return(add_bulk_member);
}
