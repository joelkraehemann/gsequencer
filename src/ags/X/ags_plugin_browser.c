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

#include <ags/X/ags_plugin_browser.h>
#include <ags/X/ags_plugin_browser_callbacks.h>

#include <ags/object/ags_connectable.h>

#include <ags/object/ags_applicable.h>

void ags_plugin_browser_class_init(AgsPluginBrowserClass *plugin_browser);
void ags_plugin_browser_init(AgsPluginBrowser *plugin_browser);
void ags_plugin_browser_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_plugin_browser_applicable_interface_init(AgsApplicableInterface *applicable);
void ags_plugin_browser_connect(AgsConnectable *connectable);
void ags_plugin_browser_disconnect(AgsConnectable *connectable);
void ags_plugin_browser_set_update(AgsApplicable *applicable, gboolean update);
void ags_plugin_browser_apply(AgsApplicable *applicable);
void ags_plugin_browser_reset(AgsApplicable *applicable);

/**
 * SECTION:ags_plugin_browser
 * @short_description: A composite to select plugin effect.
 * @title: AgsPluginBrowser
 * @section_id:
 * @include: ags/X/ags_plugin_browser.h
 *
 * #AgsPluginBrowser is a composite widget to select plugin plugin and the desired
 * effect.
 */

GType
ags_plugin_browser_get_type(void)
{
  static GType ags_type_plugin_browser = 0;

  if(!ags_type_plugin_browser){
    static const GTypeInfo ags_plugin_browser_info = {
      sizeof (AgsPluginBrowserClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_plugin_browser_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (AgsPluginBrowser),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_plugin_browser_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_plugin_browser_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    static const GInterfaceInfo ags_applicable_interface_info = {
      (GInterfaceInitFunc) ags_plugin_browser_applicable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    ags_type_plugin_browser = g_type_register_static(GTK_TYPE_DIALOG,
						     "AgsPluginBrowser\0", &ags_plugin_browser_info,
						     0);

    g_type_add_interface_static(ags_type_plugin_browser,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);

    g_type_add_interface_static(ags_type_plugin_browser,
				AGS_TYPE_APPLICABLE,
				&ags_applicable_interface_info);
  }
  
  return(ags_type_plugin_browser);
}

void
ags_plugin_browser_class_init(AgsPluginBrowserClass *plugin_browser)
{
  /* empty */
}

void
ags_plugin_browser_connectable_interface_init(AgsConnectableInterface *connectable)
{
  connectable->is_ready = NULL;
  connectable->is_connected = NULL;
  connectable->connect = ags_plugin_browser_connect;
  connectable->disconnect = ags_plugin_browser_disconnect;
}

void
ags_plugin_browser_applicable_interface_init(AgsApplicableInterface *applicable)
{
  applicable->set_update = ags_plugin_browser_set_update;
  applicable->apply = ags_plugin_browser_apply;
  applicable->reset = ags_plugin_browser_reset;
}

void
ags_plugin_browser_init(AgsPluginBrowser *plugin_browser)
{
  GtkVBox *vbox;

  GList *list;

  vbox = (GtkVBox *) gtk_vbox_new(FALSE, 0);
  gtk_container_add((GtkContainer *) gtk_dialog_get_content_area(plugin_browser),
		    GTK_WIDGET(vbox));
  
  //TODO:JK: implement me
  
  /* action area */
  gtk_dialog_add_buttons(plugin_browser,
			 GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
			 GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT,
			 NULL);

  list = gtk_container_get_children(gtk_dialog_get_action_area(plugin_browser));
  plugin_browser->ok = GTK_BUTTON(list->data);
  plugin_browser->cancel = GTK_BUTTON(list->next->data);
  g_list_free(list);
}

void
ags_plugin_browser_connect(AgsConnectable *connectable)
{
  AgsPluginBrowser *plugin_browser;
  GList *list, *list_start;

  plugin_browser = AGS_PLUGIN_BROWSER(connectable);

  //TODO:JK: implement me

  /* AgsPluginBrowser buttons */
  g_signal_connect((GObject *) plugin_browser->ok, "clicked\0",
		   G_CALLBACK(ags_plugin_browser_ok_callback), (gpointer) plugin_browser);

  g_signal_connect((GObject *) plugin_browser->cancel, "clicked\0",
		   G_CALLBACK(ags_plugin_browser_cancel_callback), (gpointer) plugin_browser);
}

void
ags_plugin_browser_disconnect(AgsConnectable *connectable)
{
  /* empty */
}

void
ags_plugin_browser_set_update(AgsApplicable *applicable, gboolean update)
{
  AgsPluginBrowser *plugin_browser;

  plugin_browser = AGS_PLUGIN_BROWSER(applicable);

  /* empty */
}

void
ags_plugin_browser_apply(AgsApplicable *applicable)
{
  AgsPluginBrowser *plugin_browser;
  GtkComboBoxText *filename, *effect;

  plugin_browser = AGS_PLUGIN_BROWSER(applicable);

  //TODO:JK: implement me
}

void
ags_plugin_browser_reset(AgsApplicable *applicable)
{
  AgsPluginBrowser *plugin_browser;
  GtkComboBoxText *filename;
  GList *list;

  plugin_browser = AGS_PLUGIN_BROWSER(applicable);

  //TODO:JK: implement me
}

/**
 * ags_plugin_browser_get_plugin_filename:
 *
 * Retrieve selected plugin plugin filename.
 *
 * Returns: the active plugin filename
 *
 * Since: 0.4.3
 */
gchar*
ags_plugin_browser_get_plugin_filename(AgsPluginBrowser *plugin_browser)
{
  //TODO:JK: implement me

  return(NULL);
}

/**
 * ags_plugin_browser_get_plugin_effect:
 *
 * Retrieve selected plugin effect.
 *
 * Returns: the active plugin effect
 *
 * Since: 0.4.3
 */
gchar*
ags_plugin_browser_get_plugin_effect(AgsPluginBrowser *plugin_browser)
{
  //TODO:JK: implement me

  return(NULL);
}

/**
 * ags_plugin_browser_new:
 *
 * Creates an #AgsPluginBrowser
 *
 * Returns: a new #AgsPluginBrowser
 *
 * Since: 0.4.3
 */
AgsPluginBrowser*
ags_plugin_browser_new(GtkWidget *parent)
{
  AgsPluginBrowser *plugin_browser;

  plugin_browser = (AgsPluginBrowser *) g_object_new(AGS_TYPE_PLUGIN_BROWSER,
						     NULL);

  plugin_browser->parent = parent;

  return(plugin_browser);
}