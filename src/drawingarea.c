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

static void tegla_drawing_area_class_init(TeglaDrawingAreaClass *a) {
	/* init property getters/setters and virtual functions */
	/* https://developer.gnome.org/gobject/stable/howto-gobject-methods.html#virtual-public-methods */
}

static void tegla_drawing_area_init(TeglaDrawingArea *a) {
	/* init widget */
#if GTK_MAJOR_VERSION == 2 
	a->config = gdk_gl_config_new_by_mode(GDK_GL_MODE_RGB);
	gtk_widget_set_gl_capability(GTK_WIDGET(a), a->config, NULL, TRUE, GDK_GL_RGBA_TYPE);
#endif
}

GtkWidget *tegla_drawing_area_new(void) {
	return g_object_new(TEGLA_TYPE_DRAWING_AREA, NULL);
}



