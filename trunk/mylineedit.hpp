/* -------------------------------------------------------- */
#ifndef __MYLINEEDIT__
#define __MYLINEEDIT__
/* -------------------------------------------------------- */
#include <qlineedit.h>
/* -------------------------------------------------------- */
 
class WFloatLineEdit : public QLineEdit {
    Q_OBJECT
protected:
    virtual void      keyPressEvent(QKeyEvent *);
}

#endif
