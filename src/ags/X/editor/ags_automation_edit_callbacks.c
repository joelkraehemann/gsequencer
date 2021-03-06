/* AGS - Advanced GTK Sequencer
 * Copyright (C) 2014 Joël Krähemann
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

#include <ags/X/editor/ags_automation_edit_callbacks.h>

#include <ags/X/ags_editor.h>

#include <ags/X/machine/ags_panel.h>
#include <ags/X/machine/ags_mixer.h>
#include <ags/X/machine/ags_drum.h>
#include <ags/X/machine/ags_matrix.h>
#include <ags/X/machine/ags_synth.h>
#include <ags/X/machine/ags_ffplayer.h>

gboolean
ags_automation_edit_scrolled_window_expose_event(GtkWidget *widget, GdkEventExpose *event,
						 AgsAutomationEdit *automation_edit)
{
  //TODO:JK: implement me

  return(TRUE);
}

gboolean
ags_automation_edit_scrolled_window_configure_event(GtkWidget *widget, GdkEventConfigure *event,
						    AgsAutomationEdit *automation_edit)
{
  automation_edit->flags |= AGS_AUTOMATION_EDIT_RESETING_VERTICALLY;
  ags_automation_edit_reset_vertically(automation_edit, AGS_AUTOMATION_EDIT_RESET_VSCROLLBAR);
  automation_edit->flags &= (~AGS_AUTOMATION_EDIT_RESETING_VERTICALLY);

  automation_edit->flags |= AGS_AUTOMATION_EDIT_RESETING_HORIZONTALLY;
  ags_automation_edit_reset_horizontally(automation_edit, AGS_AUTOMATION_EDIT_RESET_HSCROLLBAR);
  automation_edit->flags &= (~AGS_AUTOMATION_EDIT_RESETING_HORIZONTALLY);  

  return(FALSE);
}

gboolean
ags_automation_edit_scrolled_window_button_press_event(GtkWidget *widget, GdkEventButton *event,
						       AgsAutomationEdit *automation_edit)
{
  //TODO:JK: implement me

  return(TRUE);
}

gboolean
ags_automation_edit_scrolled_window_button_release_event(GtkWidget *widget, GdkEventButton *event,
							 AgsAutomationEdit *automation_edit)
{
  //TODO:JK: implement me

  return(FALSE);
}

gboolean
ags_automation_edit_scrolled_window_motion_notify_event(GtkWidget *widget, GdkEventMotion *event,
							AgsAutomationEdit *automation_edit)
{
  //TODO:JK: implement me

  return(FALSE);
}

void
ags_automation_edit_vscrollbar_value_changed(GtkRange *range, AgsAutomationEdit *automation_edit)
{
  if((AGS_AUTOMATION_EDIT_RESETING_VERTICALLY & automation_edit->flags) != 0){
    return;
  }

  automation_edit->flags |= AGS_AUTOMATION_EDIT_RESETING_VERTICALLY;
  ags_automation_edit_reset_vertically(automation_edit, 0);
  automation_edit->flags &= (~AGS_AUTOMATION_EDIT_RESETING_VERTICALLY);
}

void
ags_automation_edit_hscrollbar_value_changed(GtkRange *range, AgsAutomationEdit *automation_edit)
{
  if((AGS_AUTOMATION_EDIT_RESETING_HORIZONTALLY & automation_edit->flags) != 0){
    return;
  }

  /* reset ruler */
  gtk_adjustment_set_value(automation_edit->ruler->adjustment,
			   GTK_RANGE(gtk_scrolled_window_get_hadjustment(automation_edit->scrolled_window))->adjustment->value);
  gtk_widget_queue_draw(automation_edit->ruler);

  /* update automation edit */
  automation_edit->flags |= AGS_AUTOMATION_EDIT_RESETING_HORIZONTALLY;
  ags_automation_edit_reset_horizontally(automation_edit, 0);
  automation_edit->flags &= (~AGS_AUTOMATION_EDIT_RESETING_HORIZONTALLY);
}
