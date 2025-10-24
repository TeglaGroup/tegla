#include <gtk/gtk.h>
#if GTK_MAJOR_VERSION == 2 
#include <gtk/gtkgl.h>
#endif

#ifndef TEGLA_DRAWING_AREA_H
#define TEGLA_DRAWING_AREA_H
G_BEGIN_DECLS

#define TEGLA_TYPE_DRAWING_AREA (tegla_drawing_area_get_type())
#define TEGLA_DRAWING_AREA(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TEGLA_TYPE_DRAWING_AREA, TeglaDrawingArea))
#define TEGLA_DRAWING_AREA_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), TEGLA_TYPE_DRAWING_AREA, TeglaDrawingAreaClass))
#define TEGLA_IS_DRAWING_AREA(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TEGLA_TYPE_DRAWING_AREA))
#define TEGLA_IS_DRAWING_AREA_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), TEGLA_TYPE_DRAWING_AREA))
#define TEGLA_DRAWING_AREA_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), TEGLA_TYPE_DRAWING_AREA, TeglaDrawingAreaClass))

typedef struct _TeglaDrawingArea TeglaDrawingArea;
typedef struct _TeglaDrawingAreaClass TeglaDrawingAreaClass;

struct _TeglaDrawingArea {
#if GTK_MAJOR_VERSION == 3 
	GtkGLArea parent;
#else
	GtkDrawingArea parent;
	GdkGLConfig *config;
#endif
};

struct _TeglaDrawingAreaClass {
#if GTK_MAJOR_VERSION == 3 
	GtkGLAreaClass parent;
#else
	GtkDrawingAreaClass parent;
#endif
};

GType tegla_drawing_area_get_type(void) G_GNUC_CONST;
GtkWidget *tegla_drawing_area_new(void);

G_END_DECLS
#endif /* TEGLA_DRAWING_AREA_H */
