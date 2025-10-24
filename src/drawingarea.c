#if GTK_MAJOR_VERSION == 2 
#include <epoxy/gl.h>
#endif
#include <gtk/gtk.h>
#if GTK_MAJOR_VERSION == 2 
#include <gtk/gtkgl.h>
#endif
#include "drawingarea.h"

#if GTK_MAJOR_VERSION == 3 
G_DEFINE_TYPE(TeglaDrawingArea, tegla_drawing_area, GTK_TYPE_GL_AREA)
#else
G_DEFINE_TYPE(TeglaDrawingArea, tegla_drawing_area, GTK_TYPE_DRAWING_AREA)
#endif

static void tegla_drawing_area_dispose(GObject *gobject) {
#if GTK_MAJOR_VERSION == 2
	TeglaDrawingArea *area;
  
	area = TEGLA_DRAWING_AREA(gobject);

	g_clear_object(&area->config);
#endif
	G_OBJECT_CLASS(tegla_drawing_area_parent_class)->dispose(gobject);
}

static void tegla_drawing_area_class_init(TeglaDrawingAreaClass *a) {
	GObjectClass *object_class;

	object_class = G_OBJECT_CLASS(a);

	object_class->dispose = tegla_drawing_area_dispose;
}

static void tegla_drawing_area_init(TeglaDrawingArea *a) {
#if GTK_MAJOR_VERSION == 2 
	GdkGLConfigMode mode;
	
	a->config = gdk_gl_config_new_by_mode(GDK_GL_MODE_RGBA | GDK_GL_MODE_DEPTH | GDK_GL_MODE_DOUBLE);
	gtk_widget_set_gl_capability(GTK_WIDGET(a), a->config, NULL, TRUE, GDK_GL_RGBA_TYPE);
#else
	gtk_gl_area_set_use_es(GTK_GL_AREA(a), FALSE);
	gtk_gl_area_set_has_depth_buffer(GTK_GL_AREA(a), TRUE);
#endif
}

GtkWidget *tegla_drawing_area_new(void) {
	return g_object_new(TEGLA_TYPE_DRAWING_AREA, NULL);
}


