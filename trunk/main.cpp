#include <qapplication.h>
#include <qtranslator.h>
#include <qstring.h>
#include <qtextcodec.h>
#include "commimainform.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    QTranslator translator( 0 );
    translator.load( QString("commi_") + QTextCodec::locale(), "/usr/local/share/commi" );
    a.installTranslator( &translator );
    CommiMainForm w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
