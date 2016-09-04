/* GStreamer Instruments
 * Copyright (C) 2015 Kyrylo Polezhaiev <kirushyk@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify i t under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "gsttraceentry.h"

struct GstTraceEntry
{
  GstTraceEntryType type;
  GstClockTime timestamp;
  gpointer pipeline;
};

struct GstTraceElementDiscoveredEntry
{
  GstTraceEntry entry;
  gpointer element_id;
  gchar element_name[GST_ELEMENT_NAME_LENGTH_MAX];
  gchar element_type_name[GST_ELEMENT_TYPE_NAME_LENGTH_MAX];
  gpointer parent_element_id;
};

struct GstTraceElementEnteredEntry
{
  GstTraceEntry entry;
  gpointer thread_id;
  gpointer upperstack_element_id;
  gpointer downstack_element_id;
  gchar upperstack_element_name[GST_ELEMENT_NAME_LENGTH_MAX];
  gchar downstack_element_name[GST_ELEMENT_NAME_LENGTH_MAX];
  guint64 start;
};

struct GstTraceElementExitedEntry
{
  GstTraceEntry entry;
  gpointer thread_id;
  gchar upperstack_element_name[GST_ELEMENT_NAME_LENGTH_MAX];
  gchar downstack_element_name[GST_ELEMENT_NAME_LENGTH_MAX];
  guint64 end;
  guint64 duration;
};

void
gst_trace_entry_init (GstTraceEntry *entry)
{
  g_assert (entry != NULL);
  entry->type = GST_TRACE_ENTRY_TYPE_UNKNOWN;
  entry->timestamp = GST_CLOCK_TIME_NONE;
  entry->pipeline = NULL;
}

void
gst_trace_entry_set_pipeline  (GstTraceEntry *entry, GstPipeline *pipeline)
{
  g_assert (entry != NULL);
  entry->pipeline = pipeline;
}

gpointer
gst_trace_entry_get_pipeline (GstTraceEntry *entry)
{
  g_assert (entry != NULL);
  return entry->pipeline;
}

void
gst_trace_entry_set_timestamp (GstTraceEntry *entry, GstClockTime timestamp)
{
  g_assert (entry != NULL);
  entry->timestamp = timestamp;
}

GstClockTime
gst_trace_entry_get_timestamp (GstTraceEntry *entry)
{
  g_assert (entry != NULL);
  return entry->timestamp;
}

void
gst_trace_entry_dump_to_file (GstTraceEntry *entry, FILE *fd)
{
  
}

void
gst_trace_element_discoved_entry_init (GstTraceElementDiscoveredEntry *entry)
{
  gst_trace_entry_init ((GstTraceEntry *)entry);
  ((GstTraceEntry *)entry)->type = GST_TRACE_ENTRY_TYPE_ELEMENT_DISCOVERED;
  entry->element_id = NULL;
  entry->element_name[0] = '\0';
  entry->element_type_name[0] = '\0';
  entry->parent_element_id = NULL;
}

GstTraceElementDiscoveredEntry *
gst_trace_element_discoved_entry_new (void)
{
  GstTraceElementDiscoveredEntry *entry = g_new(GstTraceElementDiscoveredEntry, 1);
  gst_trace_element_discoved_entry_init (entry);
  return entry;
}

void
gst_trace_element_discoved_entry_init_set_element (GstTraceElementDiscoveredEntry *entry,  GstElement    *element)
{
  entry->element_id = element;
  g_strlcpy(entry->element_name, LGI_ELEMENT_NAME (element), GST_ELEMENT_NAME_LENGTH_MAX);
  g_strlcpy(entry->element_type_name, LGI_OBJECT_TYPE_NAME (element), GST_ELEMENT_TYPE_NAME_LENGTH_MAX);
  entry->parent_element_id = (element);
}

