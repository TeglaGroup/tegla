#if GTK_MAJOR_VERSION == 2 
#include <epoxy/gl.h>
#include <epoxy/glx.h>
#endif
#include <gtk/gtk.h>
#if GTK_MAJOR_VERSION == 2 
#include <gtk/gtkgl.h>
#endif

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *gl_area;
#if GTK_MAJOR_VERSION == 2 
	GdkGLConfig *gl_config;
#endif

	/* init gtk */
	gtk_init(&argc, &argv);
#if GTK_MAJOR_VERSION == 2 
	gtk_gl_init(&argc, &argv);
	gl_config = gdk_gl_config_new_by_mode(GDK_GL_MODE_RGB);
#endif

	/* create window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
	
	/* gl area */
#if GTK_MAJOR_VERSION == 3 
	gl_area = gtk_gl_area_new();
#else
	gl_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(gl_area, 640, 480);
	gtk_widget_set_gl_capability(gl_area, gl_config, NULL, TRUE, GDK_GL_RGBA_TYPE);
#endif
	gtk_container_add(GTK_CONTAINER(window), gl_area);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
