/* -------------------------------------------------------- */
#ifndef __MYLINEEDIT__
#define __MYLINEEDIT__
/* -------------------------------------------------------- */
#include <qlineedit.h>
#include <qstringlist.h>
/* -------------------------------------------------------- */
 
class MyLineEdit : public QLineEdit {
    Q_OBJECT
    Q_PROPERTY( QString command READ command );
public:
    MyLineEdit(QWidget *parent,const char *name);
    void printHistList(void);
    QString command() const { return m_command; }
signals:
   // void returnPressed (void);
protected:
    virtual void      keyPressEvent(QKeyEvent *);
    QString m_command;
private:
    QStringList::Iterator m_it;
    QStringList historylist;
    

};

#endif
