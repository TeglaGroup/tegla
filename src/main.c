#include <gtk/gtk.h>
#if GTK_MAJOR_VERSION == 2 
#include <gtk/gtkgl.h>
#endif
#include "drawingarea.h"

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *gl_area;
	
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

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
