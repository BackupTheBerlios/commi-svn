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

void aboutForm::init() {
    textBrowser1->mimeSourceFactory()->setFilePath("/usr/local/share/commi/docs");
    textBrowser1->setSource("gpl.txt");
    textBrowser1->insertParagraph("(c) Sebastian Block 2004\n"+tr("This program is published under the terms of the GPL v2.") + "\n",0);
}
