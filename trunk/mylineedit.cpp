#include "mylineedit.h"
#include <qmessagebox.h>
#include <iostream>

using std::cout; using std::endl;
MyLineEdit::MyLineEdit(QWidget *parent,const char *name) : QLineEdit(parent,name)
{
    m_it = historylist.begin();
}
void MyLineEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->state()==Qt::ControlButton) {
 if(e->key() == Qt::Key_C) {
   m_command="!ctrl_c";
   emit(QLineEdit::returnPressed());
 }
 else if(e->key()==Qt::Key_Q) {
   m_command="!ctrl_q";
   emit(QLineEdit::returnPressed());
 }
 else if(e->key()==Qt::Key_S) {
   m_command="!ctrl_s";
   emit(QLineEdit::returnPressed());
 }
    }
    else {
 switch(e->key()) {
    case Qt::Key_Up: m_it--;
 QLineEdit::setText(*m_it);
 break;
 case Qt::Key_Down:  m_it++;
 QLineEdit::setText(*m_it);
 break;
case Qt::Key_Return: 
    if(QLineEdit::text()!="") {
 historylist<<QLineEdit::text();
 m_it=historylist.end();
 m_command = QLineEdit::text();
 QLineEdit::clear();
}
    else m_command="";
    emit(QLineEdit::returnPressed());
    break;
case Qt::Key_Escape: printHistList();
    break;
    default:QLineEdit::keyPressEvent(e);
    }
}
 
}

void MyLineEdit::printHistList(void) 
{
    for ( QStringList::Iterator it = historylist.begin(); it != historylist.end(); ++it ) {
        cout << *it << endl;
    }
}
