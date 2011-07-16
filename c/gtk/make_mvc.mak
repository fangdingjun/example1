# make_mvc.mak
GTK_DIR=e:\fangdingjun\gtk

INC_DIR=$(GTK_DIR)\include
LIB_DIR=$(GTK_DIR)\lib

GTK_LIB_INC=$(LIB_DIR)\gtk-2.0\include
GDK_INC=$(GTK_DIR)\include\gdk
GTK_INC=$(GTK_DIR)\include\gtk-2.0
GLIB_INC=$(GTK_DIR)\include\glib-2.0
GLIB_LIB_INC=$(LIB_DIR)\glib-2.0\include

CAIRO_INC=$(GTK_DIR)\include\cairo
PANGO_INC=$(GTK_DIR)\include\pango-1.0
ATK_INC=$(GTK_DIR)\include\atk-1.0

CFLAGS=/O2 /I $(INC_DIR) /I $(GLIB_LIB_INC) /I $(CAIRO_INC) /I $(PANGO_INC) /I $(GTK_LIB_INC) /I $(ATK_INC) /I $(GDK_INC) /I $(GTK_INC) /I $(GLIB_INC) /DWIN32

LDFLAGS=/LIBPATH:$(LIB_DIR) gailutil.lib gdk_pixbuf-2.0.lib gdk-win32-2.0.lib gtk-win32-2.0.lib glib-2.0.lib gio-2.0.lib gmodule-2.0.lib pango-1.0.lib pangowin32-1.0.lib cairo.lib gobject-2.0.lib gthread-2.0.lib atk-1.0.lib pangocairo-1.0.lib pangoft2-1.0.lib
#/SUBSYSTEM:windows /entry:mainCRTStartup

CC=cl /c /nologo
LD=link /nologo

all: hello.exe entry.exe easy_cmd.exe

#hello.obj:hello.c
#	$(CC) $(CFLAGS) hello.c
hello.exe:hello.obj
	$(LD)  $(LDFLAGS) hello.obj 
#entry.obj:entry.c
#	$(CC) $(CFLAGS) entry.c
entry.exe:entry.obj
	$(LD) $(LDFLAGS) entry.obj
easy_cmd.obj:easy_cmd.c easy_cmd.h
	$(CC) $(CFLAGS) easy_cmd.c
easy_cmd.exe:easy_cmd.obj
	$(LD) $(LDFLAGS) easy_cmd.obj
clean:
	del *.exe *.obj
