/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

void helpForm::init() {
    helpTB->mimeSourceFactory()->setFilePath("/usr/local/share/commi/docs");
    helpTB->setSource(tr("index.html"));
}


void helpForm::helpLB_selectionChanged( QListBoxItem *item ){
    QString helpfile;
    if(item->text()==tr("Commi")) helpfile=tr("index.html");
    else if (item->text()==tr("Batchfiles")) helpfile=tr("batch.html");
    else helpfile=tr("index.html");
    helpTB->setSource(helpfile);
}
