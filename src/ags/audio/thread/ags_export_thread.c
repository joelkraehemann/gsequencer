/* AGS - Advanced GTK Sequencer
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

#include <ags/audio/thread/ags_export_thread.h>

#include <ags/object/ags_connectable.h>
#include <ags/object/ags_soundcard.h>

void ags_export_thread_class_init(AgsExportThreadClass *export_thread);
void ags_export_thread_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_export_thread_init(AgsExportThread *export_thread);
void ags_export_thread_set_property(GObject *gobject,
				    guint prop_id,
				    const GValue *value,
				    GParamSpec *param_spec);
void ags_export_thread_get_property(GObject *gobject,
				    guint prop_id,
				    GValue *value,
				    GParamSpec *param_spec);
void ags_export_thread_connect(AgsConnectable *connectable);
void ags_export_thread_disconnect(AgsConnectable *connectable);
void ags_export_thread_finalize(GObject *gobject);

void ags_export_thread_start(AgsThread *thread);
void ags_export_thread_run(AgsThread *thread);
void ags_export_thread_stop(AgsThread *thread);

/**
 * SECTION:ags_export_thread
 * @short_description: export thread
 * @title: AgsExportThread
 * @section_id:
 * @include: ags/thread/ags_export_thread.h
 *
 * The #AgsExportThread acts as audio output thread to file.
 */

enum{
  PROP_0,
  PROP_SOUNDCARD,
  PROP_AUDIO_FILE,
};

static gpointer ags_export_thread_parent_class = NULL;
static AgsConnectableInterface *ags_export_thread_parent_connectable_interface;

GType
ags_export_thread_get_type()
{
  static GType ags_type_export_thread = 0;

  if(!ags_type_export_thread){
    static const GTypeInfo ags_export_thread_info = {
      sizeof (AgsExportThreadClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_export_thread_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (AgsExportThread),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_export_thread_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_export_thread_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    ags_type_export_thread = g_type_register_static(AGS_TYPE_THREAD,
						    "AgsExportThread\0",
						    &ags_export_thread_info,
						    0);
    
    g_type_add_interface_static(ags_type_export_thread,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);
  }
  
  return (ags_type_export_thread);
}

void
ags_export_thread_class_init(AgsExportThreadClass *export_thread)
{
  GObjectClass *gobject;
  AgsThreadClass *thread;
  GParamSpec *param_spec;

  ags_export_thread_parent_class = g_type_class_peek_parent(export_thread);

  /* GObject */
  gobject = (GObjectClass *) export_thread;

  gobject->get_property = ags_export_thread_get_property;
  gobject->set_property = ags_export_thread_set_property;

  gobject->finalize = ags_export_thread_finalize;

  /* properties */
  /**
   * AgsExportThread:soundcard:
   *
   * The assigned #AgsSoundcard.
   * 
   * Since: 0.4
   */
  param_spec = g_param_spec_object("soundcard\0",
				   "soundcard assigned to\0",
				   "The AgsSoundcard it is assigned to.\0",
				   G_TYPE_OBJECT,
				   G_PARAM_WRITABLE);
  g_object_class_install_property(gobject,
				  PROP_SOUNDCARD,
				  param_spec);

  /**
   * AgsExportThread:audio-file:
   *
   * The assigned #AgsAudioFile.
   * 
   * Since: 0.4
   */
  param_spec = g_param_spec_object("audio-file\0",
				   "audio file to write\0",
				   "The audio file to write output.\0",
				   AGS_TYPE_AUDIO_FILE,
				   G_PARAM_READABLE | G_PARAM_WRITABLE);
  g_object_class_install_property(gobject,
				  PROP_AUDIO_FILE,
				  param_spec);

  /* AgsThread */
  thread = (AgsThreadClass *) export_thread;

  thread->start = ags_export_thread_start;
  thread->run = ags_export_thread_run;
  thread->stop = ags_export_thread_stop;
}

void
ags_export_thread_connectable_interface_init(AgsConnectableInterface *connectable)
{
  ags_export_thread_parent_connectable_interface = g_type_interface_peek_parent(connectable);

  connectable->connect = ags_export_thread_connect;
  connectable->disconnect = ags_export_thread_disconnect;
}

void
ags_export_thread_init(AgsExportThread *export_thread)
{
  AgsThread *thread;

  thread = AGS_THREAD(export_thread);
  thread->freq = AGS_EXPORT_THREAD_DEFAULT_JIFFIE;

  export_thread->flags = 0;

  export_thread->tic = 0;
  export_thread->counter = 0;

  export_thread->soundcard = NULL;

  export_thread->audio_file = NULL;
}

void
ags_export_thread_set_property(GObject *gobject,
			       guint prop_id,
			       const GValue *value,
			       GParamSpec *param_spec)
{
  AgsExportThread *export_thread;

  export_thread = AGS_EXPORT_THREAD(gobject);

  switch(prop_id){
  case PROP_SOUNDCARD:
    {
      GObject *soundcard;

      soundcard = (GObject *) g_value_get_object(value);

      if(export_thread->soundcard != NULL){
	g_object_unref(G_OBJECT(export_thread->soundcard));
      }

      if(soundcard != NULL){
	g_object_ref(G_OBJECT(soundcard));
      }

      export_thread->soundcard = G_OBJECT(soundcard);
    }
    break;
  case PROP_AUDIO_FILE:
    {
      AgsAudioFile *audio_file;

      audio_file = g_value_get_object(value);

      if(export_thread->audio_file == audio_file){
	return;
      }

      if(export_thread->audio_file != NULL){
	g_object_unref(export_thread->audio_file);
      }

      if(audio_file != NULL){
	g_object_ref(audio_file);
      }

      export_thread->audio_file = audio_file;
    }
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }
}

void
ags_export_thread_get_property(GObject *gobject,
			       guint prop_id,
			       GValue *value,
			       GParamSpec *param_spec)
{
  AgsExportThread *export_thread;

  export_thread = AGS_EXPORT_THREAD(gobject);

  switch(prop_id){
  case PROP_SOUNDCARD:
    {
      g_value_set_object(value, G_OBJECT(export_thread->soundcard));
    }
    break;
  case PROP_AUDIO_FILE:
    {
      g_value_set_object(value, export_thread->audio_file);
    }
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }
}

void
ags_export_thread_connect(AgsConnectable *connectable)
{
  ags_export_thread_parent_connectable_interface->connect(connectable);

  /* empty */
}

void
ags_export_thread_disconnect(AgsConnectable *connectable)
{
  ags_export_thread_parent_connectable_interface->disconnect(connectable);

  /* empty */
}

void
ags_export_thread_finalize(GObject *gobject)
{
  G_OBJECT_CLASS(ags_export_thread_parent_class)->finalize(gobject);

  /* empty */
}

void
ags_export_thread_start(AgsThread *thread)
{
  //TODO:JK: implement me
  g_message("export start");

  AGS_THREAD_CLASS(ags_export_thread_parent_class)->start(thread);
}

void
ags_export_thread_run(AgsThread *thread)
{
  AgsExportThread *export_thread;
  AgsSoundcard *soundcard;
  signed short *soundcard_buffer;
  guint buffer_size;

  export_thread = AGS_EXPORT_THREAD(thread);

  if(export_thread->counter == export_thread->tic){
    ags_thread_stop(thread);
  }else{
    export_thread->counter += 1;
  }

  soundcard = AGS_SOUNDCARD(export_thread->soundcard);

  soundcard_buffer = ags_soundcard_get_buffer(soundcard);
  ags_soundcard_get_presets(soundcard,
			    NULL,
			    NULL,
			    &buffer_size,
			    NULL);

  ags_audio_file_write(export_thread->audio_file,
		       soundcard_buffer, (guint) buffer_size);
}

void
ags_export_thread_stop(AgsThread *thread)
{
  AgsExportThread *export_thread;

  export_thread = AGS_EXPORT_THREAD(thread);

  AGS_THREAD_CLASS(ags_export_thread_parent_class)->stop(thread);

  ags_audio_file_flush(export_thread->audio_file);
  ags_audio_file_close(export_thread->audio_file);
}

/**
 * ags_export_thread_new:
 * @soundcard: the #AgsSoundcard
 * @audio_file: the output file
 *
 * Create a new #AgsExportThread.
 *
 * Returns: the new #AgsExportThread
 *
 * Since: 0.4
 */
AgsExportThread*
ags_export_thread_new(GObject *soundcard, AgsAudioFile *audio_file)
{
  AgsExportThread *export_thread;

  export_thread = (AgsExportThread *) g_object_new(AGS_TYPE_EXPORT_THREAD,
						   "soundcard\0", soundcard,
						   "audio-file\0", audio_file,
						   NULL);
  
  return(export_thread);
}
