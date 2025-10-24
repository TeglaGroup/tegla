#include <epoxy/gl.h>
#include <gtk/gtk.h>
#if GTK_MAJOR_VERSION == 2 
#include <gtk/gtkgl.h>
#endif
#include "drawingarea.h"

void init_gl_state(void) {
	puts(glGetString(GL_VERSION));
	printf("%d\n", epoxy_gl_version());
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void draw_gl(void) {
	glClear(GL_COLOR_BUFFER_BIT);
}

#if GTK_MAJOR_VERSION == 2 
static void realize(GtkWidget *widget, gpointer data) {
	GdkGLContext *gl_ctx;
	GdkGLDrawable *gl_drawable;

	gl_ctx = gtk_widget_get_gl_context(widget);
	gl_drawable = gtk_widget_get_gl_drawable(widget);
	if (!gdk_gl_drawable_gl_begin(gl_drawable, gl_ctx)) {
		return;
	}
	
	init_gl_state();

	gdk_gl_drawable_gl_end (gl_drawable);
	return;
}

static gboolean expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer data) {
	GdkGLContext *gl_ctx;
	GdkGLDrawable *gl_drawable;

	gl_ctx = gtk_widget_get_gl_context(widget);
	gl_drawable = gtk_widget_get_gl_drawable(widget);
	if (!gdk_gl_drawable_gl_begin(gl_drawable, gl_ctx)) {
		return TRUE; 
	}
	
	draw_gl();
	
    if (gdk_gl_drawable_is_double_buffered(gl_drawable)) {
		gdk_gl_drawable_swap_buffers(gl_drawable);
	} else {
		glFlush();
	}
	gdk_gl_drawable_gl_end(gl_drawable);
	return TRUE;
}
#else 
static void realize(GtkWidget *widget, gpointer data) {
    gtk_gl_area_make_current(GTK_GL_AREA(widget));
    
    init_gl_state();
    
	return;
}

static gboolean render(GtkGLArea *area, GdkGLContext *context, gpointer user_data) {    
    draw_gl();
    
	return TRUE;
}
#endif

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *gl_area;
	guint maj;
	guint min;
	
	/* init gtk */
	gtk_init(&argc, &argv);
#if GTK_MAJOR_VERSION == 2 
	gtk_gl_init(&argc, &argv);
#endif

	/* create window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
	
	/* gl area */
	gl_area = tegla_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), gl_area);
	g_signal_connect_after(G_OBJECT(gl_area), "realize", G_CALLBACK(realize), NULL);
#if GTK_MAJOR_VERSION == 2 
	g_signal_connect(G_OBJECT(gl_area), "expose_event", G_CALLBACK(expose_event), NULL);
#else
	g_signal_connect(G_OBJECT(gl_area), "render", G_CALLBACK(render), NULL);
#endif
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
