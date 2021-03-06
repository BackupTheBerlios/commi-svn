#############################################################################
# Makefile for building: commi
# Generated by qmake (1.07a) (Qt 3.3.3) on: Mon Oct 25 13:08:45 2004
# Project:  commi.pro
# Template: app
# Command: $(QMAKE) -o Makefile commi.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -O2  -DQT_NO_DEBUG -DQT_SHARED -DQT_THREAD_SUPPORT
CXXFLAGS = -pipe -Wall -W -O2  -DQT_NO_DEBUG -DQT_SHARED -DQT_THREAD_SUPPORT
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I/usr/lib/qt/mkspecs/default -I. -I$(QTDIR)/include -I.ui/ -I. -I.moc/
LINK     = g++
LFLAGS   =  -Wl,-rpath,$(QTDIR)/lib
LIBS     = $(SUBLIBS) -L$(QTDIR)/lib -L/usr/X11R6/lib -lqt-mt -lXext -lX11 -lm
AR       = ar cqs
RANLIB   = 
MOC      = $(QTDIR)/bin/moc
UIC      = $(QTDIR)/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = .obj/

####### Files

HEADERS = mylineedit.h
SOURCES = main.cpp \
		mylineedit.cpp
OBJECTS = .obj/main.o \
		.obj/mylineedit.o \
		.obj/commimainform.o \
		.obj/optionsform.o \
		.obj/transferform.o \
		.obj/aboutform.o \
		.obj/helpform.o \
		.obj/qmake_image_collection.o
FORMS = commimainform.ui \
		optionsform.ui \
		transferform.ui \
		aboutform.ui \
		helpform.ui
UICDECLS = .ui/commimainform.h \
		.ui/optionsform.h \
		.ui/transferform.h \
		.ui/aboutform.h \
		.ui/helpform.h
UICIMPLS = .ui/commimainform.cpp \
		.ui/optionsform.cpp \
		.ui/transferform.cpp \
		.ui/aboutform.cpp \
		.ui/helpform.cpp
SRCMOC   = .moc/moc_mylineedit.cpp \
		.moc/moc_commimainform.cpp \
		.moc/moc_optionsform.cpp \
		.moc/moc_transferform.cpp \
		.moc/moc_aboutform.cpp \
		.moc/moc_helpform.cpp
OBJMOC = .obj/moc_mylineedit.o \
		.obj/moc_commimainform.o \
		.obj/moc_optionsform.o \
		.obj/moc_transferform.o \
		.obj/moc_aboutform.o \
		.obj/moc_helpform.o
DIST	   = commi.pro
QMAKE_TARGET = commi
DESTDIR  = 
TARGET   = commi

first: all
####### Implicit rules

.SUFFIXES: .c .o .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(OBJCOMP) $(LIBS)

mocables: $(SRCMOC)
uicables: $(UICDECLS) $(UICIMPLS)

$(MOC): 
	( cd $(QTDIR)/src/moc && $(MAKE) )

Makefile: commi.pro  /usr/lib/qt/mkspecs/default/qmake.conf /usr/lib/qt/lib/libqt-mt.prl
	$(QMAKE) -o Makefile commi.pro
qmake: 
	@$(QMAKE) -o Makefile commi.pro

dist: 
	@mkdir -p .obj/commi && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .obj/commi/ && $(COPY_FILE) --parents commi_de.ts .obj/commi/ && $(COPY_FILE) --parents images/back.png images/configure.png images/connect_creating.png images/connect_established.png images/connect_no.png images/decrypted.png images/editcopy images/editcopy.png images/editcut images/editpaste images/editpaste.png images/encrypted.png images/fileimport.png images/filenew images/fileopen images/filesave images/forward.png images/gohome.png images/help.png images/khtml_kget.png images/print images/redo images/searchfind images/terminal.png images/undo .obj/commi/ && $(COPY_FILE) --parents commimainform.ui.h optionsform.ui.h transferform.ui.h aboutform.ui.h helpform.ui.h .obj/commi/ && ( cd `dirname .obj/commi` && $(TAR) commi.tar commi && $(GZIP) commi.tar ) && $(MOVE) `dirname .obj/commi`/commi.tar.gz . && $(DEL_FILE) -r .obj/commi

mocclean:
	-$(DEL_FILE) $(OBJMOC)
	-$(DEL_FILE) $(SRCMOC)

uiclean:
	-$(DEL_FILE) $(UICIMPLS) $(UICDECLS)

yaccclean:
lexclean:
clean: mocclean uiclean
	-$(DEL_FILE) $(OBJECTS)
		-$(DEL_FILE) .ui/qmake_image_collection.cpp
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET)


FORCE:

####### Compile

.obj/main.o: main.cpp .ui/commimainform.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/main.o main.cpp

.obj/mylineedit.o: mylineedit.cpp mylineedit.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/mylineedit.o mylineedit.cpp

.ui/commimainform.h: commimainform.ui mylineedit.h
	$(UIC) commimainform.ui -o .ui/commimainform.h

.ui/commimainform.cpp: .ui/commimainform.h commimainform.ui mylineedit.h
	$(UIC) commimainform.ui -i commimainform.h -o .ui/commimainform.cpp

.ui/optionsform.h: optionsform.ui 
	$(UIC) optionsform.ui -o .ui/optionsform.h

.ui/optionsform.cpp: .ui/optionsform.h optionsform.ui 
	$(UIC) optionsform.ui -i optionsform.h -o .ui/optionsform.cpp

.ui/transferform.h: transferform.ui 
	$(UIC) transferform.ui -o .ui/transferform.h

.ui/transferform.cpp: .ui/transferform.h transferform.ui 
	$(UIC) transferform.ui -i transferform.h -o .ui/transferform.cpp

.ui/aboutform.h: aboutform.ui 
	$(UIC) aboutform.ui -o .ui/aboutform.h

.ui/aboutform.cpp: .ui/aboutform.h aboutform.ui 
	$(UIC) aboutform.ui -i aboutform.h -o .ui/aboutform.cpp

.ui/helpform.h: helpform.ui 
	$(UIC) helpform.ui -o .ui/helpform.h

.ui/helpform.cpp: .ui/helpform.h helpform.ui 
	$(UIC) helpform.ui -i helpform.h -o .ui/helpform.cpp

.obj/commimainform.o: .ui/commimainform.cpp .ui/optionsform.h \
		.ui/transferform.h \
		.ui/aboutform.h \
		.ui/helpform.h \
		commimainform.ui.h \
		.ui/commimainform.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/commimainform.o .ui/commimainform.cpp

.obj/optionsform.o: .ui/optionsform.cpp optionsform.ui.h \
		.ui/optionsform.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/optionsform.o .ui/optionsform.cpp

.obj/transferform.o: .ui/transferform.cpp transferform.ui.h \
		.ui/transferform.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/transferform.o .ui/transferform.cpp

.obj/aboutform.o: .ui/aboutform.cpp aboutform.ui.h \
		.ui/aboutform.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/aboutform.o .ui/aboutform.cpp

.obj/helpform.o: .ui/helpform.cpp helpform.ui.h \
		.ui/helpform.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/helpform.o .ui/helpform.cpp

.obj/moc_mylineedit.o: .moc/moc_mylineedit.cpp  mylineedit.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_mylineedit.o .moc/moc_mylineedit.cpp

.obj/moc_commimainform.o: .moc/moc_commimainform.cpp  .ui/commimainform.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_commimainform.o .moc/moc_commimainform.cpp

.obj/moc_optionsform.o: .moc/moc_optionsform.cpp  .ui/optionsform.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_optionsform.o .moc/moc_optionsform.cpp

.obj/moc_transferform.o: .moc/moc_transferform.cpp  .ui/transferform.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_transferform.o .moc/moc_transferform.cpp

.obj/moc_aboutform.o: .moc/moc_aboutform.cpp  .ui/aboutform.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_aboutform.o .moc/moc_aboutform.cpp

.obj/moc_helpform.o: .moc/moc_helpform.cpp  .ui/helpform.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_helpform.o .moc/moc_helpform.cpp

.moc/moc_mylineedit.cpp: $(MOC) mylineedit.h
	$(MOC) mylineedit.h -o .moc/moc_mylineedit.cpp

.moc/moc_commimainform.cpp: $(MOC) .ui/commimainform.h
	$(MOC) .ui/commimainform.h -o .moc/moc_commimainform.cpp

.moc/moc_optionsform.cpp: $(MOC) .ui/optionsform.h
	$(MOC) .ui/optionsform.h -o .moc/moc_optionsform.cpp

.moc/moc_transferform.cpp: $(MOC) .ui/transferform.h
	$(MOC) .ui/transferform.h -o .moc/moc_transferform.cpp

.moc/moc_aboutform.cpp: $(MOC) .ui/aboutform.h
	$(MOC) .ui/aboutform.h -o .moc/moc_aboutform.cpp

.moc/moc_helpform.cpp: $(MOC) .ui/helpform.h
	$(MOC) .ui/helpform.h -o .moc/moc_helpform.cpp

.obj/qmake_image_collection.o: .ui/qmake_image_collection.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/qmake_image_collection.o .ui/qmake_image_collection.cpp

.ui/qmake_image_collection.cpp: images/back.png \
		images/configure.png \
		images/connect_creating.png \
		images/connect_established.png \
		images/connect_no.png \
		images/decrypted.png \
		images/editcopy \
		images/editcopy.png \
		images/editcut \
		images/editpaste \
		images/editpaste.png \
		images/encrypted.png \
		images/fileimport.png \
		images/filenew \
		images/fileopen \
		images/filesave \
		images/forward.png \
		images/gohome.png \
		images/help.png \
		images/khtml_kget.png \
		images/print \
		images/redo \
		images/searchfind \
		images/terminal.png \
		images/undo
	$(UIC)  -embed commi images/back.png images/configure.png images/connect_creating.png images/connect_established.png images/connect_no.png images/decrypted.png images/editcopy images/editcopy.png images/editcut images/editpaste images/editpaste.png images/encrypted.png images/fileimport.png images/filenew images/fileopen images/filesave images/forward.png images/gohome.png images/help.png images/khtml_kget.png images/print images/redo images/searchfind images/terminal.png images/undo -o .ui/qmake_image_collection.cpp

####### Install

install_target: all 
	@$(CHK_DIR_EXISTS) "$(INSTALL_ROOT)/usr/local/bin/" || $(MKDIR) "$(INSTALL_ROOT)/usr/local/bin/"
	-$(INSTALL_FILE) "$(QMAKE_TARGET)" "$(INSTALL_ROOT)/usr/local/bin/$(QMAKE_TARGET)"
	-strip "$(INSTALL_ROOT)/usr/local/bin/$(QMAKE_TARGET)"

uninstall_target: 
	-$(DEL_FILE) "$(INSTALL_ROOT)/usr/local/bin/$(QMAKE_TARGET)"
	-$(DEL_DIR) "$(INSTALL_ROOT)/usr/local/bin/"


install_desktop: all 
	@$(CHK_DIR_EXISTS) "$(INSTALL_ROOT)/opt/kde/share/applnk/Utilities/" || $(MKDIR) "$(INSTALL_ROOT)/opt/kde/share/applnk/Utilities/"
	-$(INSTALL_FILE) "commi.desktop" "$(INSTALL_ROOT)/opt/kde/share/applnk/Utilities/"


uninstall_desktop: 
	-$(DEL_FILE) -r "$(INSTALL_ROOT)/opt/kde/share/applnk/Utilities/commi.desktop"
	-$(DEL_DIR) "$(INSTALL_ROOT)/opt/kde/share/applnk/Utilities/"


install_documentation: all 
	@$(CHK_DIR_EXISTS) "$(INSTALL_ROOT)/usr/local/share/commi/docs/" || $(MKDIR) "$(INSTALL_ROOT)/usr/local/share/commi/docs/"
	-$(INSTALL_FILE) "docs/batch.html" "$(INSTALL_ROOT)/usr/local/share/commi/docs/"
	-$(INSTALL_FILE) "docs/commimain.gif" "$(INSTALL_ROOT)/usr/local/share/commi/docs/"
	-$(INSTALL_FILE) "docs/commioptions.png" "$(INSTALL_ROOT)/usr/local/share/commi/docs/"
	-$(INSTALL_FILE) "docs/commitransfer.png" "$(INSTALL_ROOT)/usr/local/share/commi/docs/"
	-$(INSTALL_FILE) "docs/gpl.txt" "$(INSTALL_ROOT)/usr/local/share/commi/docs/"
	-$(INSTALL_FILE) "docs/index.html" "$(INSTALL_ROOT)/usr/local/share/commi/docs/"


uninstall_documentation: 
	-$(DEL_FILE) -r "$(INSTALL_ROOT)/usr/local/share/commi/docs/batch.html"
	-$(DEL_FILE) -r "$(INSTALL_ROOT)/usr/local/share/commi/docs/commimain.gif"
	-$(DEL_FILE) -r "$(INSTALL_ROOT)/usr/local/share/commi/docs/commioptions.png"
	-$(DEL_FILE) -r "$(INSTALL_ROOT)/usr/local/share/commi/docs/commitransfer.png"
	-$(DEL_FILE) -r "$(INSTALL_ROOT)/usr/local/share/commi/docs/gpl.txt"
	-$(DEL_FILE) -r "$(INSTALL_ROOT)/usr/local/share/commi/docs/index.html"
	-$(DEL_DIR) "$(INSTALL_ROOT)/usr/local/share/commi/docs/"


install_translations: all 
	@$(CHK_DIR_EXISTS) "$(INSTALL_ROOT)/usr/local/share/commi/" || $(MKDIR) "$(INSTALL_ROOT)/usr/local/share/commi/"
	-$(INSTALL_FILE) "translations/commi_de.qm" "$(INSTALL_ROOT)/usr/local/share/commi/"


uninstall_translations: 
	-$(DEL_FILE) -r "$(INSTALL_ROOT)/usr/local/share/commi/commi_de.qm"
	-$(DEL_DIR) "$(INSTALL_ROOT)/usr/local/share/commi/"


install: install_target install_desktop install_documentation install_translations  

uninstall: uninstall_target uninstall_desktop uninstall_documentation uninstall_translations  

