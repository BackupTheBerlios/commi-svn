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