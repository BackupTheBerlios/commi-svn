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


void transferForm::fileChoose()
{
fileNameLEdit->setText(QFileDialog::getOpenFileName(
                    "",
                    "All Files (*.*)",
                    this,
                    "open file dialog",
                    "Choose a file" ));
}


void transferForm::validate()
{
    int fd = ::open(fileNameLEdit->text(),O_RDONLY);
    if(fd!=-1) {
    ::close(fd);
    accept();
    }
    else {
 QMessageBox::critical(this,tr("Transfer File..."),tr("Can't open %1",fileNameLEdit->text())); 
    }
}
