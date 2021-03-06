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

#ifndef __AGS_CLIENT_LOG_H__
#define __AGS_CLIENT_LOG_H__

#include <glib-object.h>
#include <gtk/gtk.h>

#define AGS_TYPE_CLIENT_LOG                (ags_client_log_get_type())
#define AGS_CLIENT_LOG(obj)                (G_TYPE_CHECK_INSTANCE_CAST((obj), AGS_TYPE_CLIENT_LOG, AgsClientLog))
#define AGS_CLIENT_LOG_CLASS(class)        (G_TYPE_CHECK_CLASS_CAST(class, AGS_TYPE_CLIENT_LOG, AgsClientLogClass))
#define AGS_IS_CLIENT_LOG(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), AGS_TYPE_CLIENT_LOG))
#define AGS_IS_CLIENT_LOG_CLASS(class)     (G_TYPE_CHECK_CLASS_TYPE ((class), AGS_TYPE_CLIENT_LOG))
#define AGS_CLIENT_LOG_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS(obj, AGS_TYPE_CLIENT_LOG, AgsClientLogClass))

typedef struct _AgsClientLog AgsClientLog;
typedef struct _AgsClientLogClass AgsClientLogClass;

struct _AgsClientLog
{
  GtkTextView text_view;
};

struct _AgsClientLogClass
{
  GtkTextViewClass text_view;
};

GType ags_client_log_get_type();

AgsClientLog* ags_client_log_new();

#endif /*__AGS_CLIENT_LOG_H__*/
