TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

HEADERS	+= mylineedit.h

SOURCES	+= main.cpp \
	mylineedit.cpp

FORMS	= commimainform.ui \
	optionsform.ui \
	transferform.ui \
	aboutform.ui \
	helpform.ui

IMAGES	= images/back.png \
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

TRANSLATIONS = commi_de.ts


unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

DESKTOP_PATH = $$system(kde-config --install apps --expandvars)

desktop.files=commi.desktop
desktop.path=$$DESKTOP_PATH/Utilities

documentation.path = /usr/local/share/commi/docs
documentation.files = docs/*

target.path = /usr/local/bin

translations.path = /usr/local/share/commi
translations.files = translations/*

INSTALLS += target desktop documentation translations