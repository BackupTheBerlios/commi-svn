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

void transferForm::init() {
    receive = false;
    directory = false;
}

void transferForm::setReceive() {
    setCaption(tr("Receive file"));
    receive = true;
}

void transferForm::fileChoose()
{
if(receive && !directory) fileNameLEdit->setText(QFileDialog::getSaveFileName(
                    "",
                    tr("All Files (*.*)"),
                    this,
                    tr("save file dialog"),
                    tr("Choose a file") ));
else if(receive && directory) fileNameLEdit->setText(QFileDialog::getExistingDirectory(
                    "",
                    this,
                    "get existing directory",
                    tr("Choose a directory for storing received files"),
                    false ));
else fileNameLEdit->setText(QFileDialog::getOpenFileName(
                    "",
                    tr("All Files (*.*)"),
                    this,
                    tr("open file dialog"),
                    tr("Choose a file") ));
}


void transferForm::validate()
{
    if((protocolCB->currentItem() == 1 || protocolCB->currentItem() == 2) && receive) {
       QDir dir (fileNameLEdit->text());
       QFileInfo info(fileNameLEdit->text());
       if ( dir.exists() && info.isWritable())  accept(); 
       else {
    QMessageBox::warning(this,tr("Error"),tr("Directory does not exist or is not writable !!")); 
       }
       return;
    }
    int fd;
    fd = ::open(fileNameLEdit->text(),O_RDONLY);
    if(receive) {
      // File exists !? Overwrite it !?
      if(fd!=-1 && QMessageBox::question(
            this,
            tr("Overwrite File?"),
            tr("A file called %1 already exists."
                "Do you want to overwrite it?")
                .arg( fileNameLEdit->text() ),
            tr("&Yes"), tr("&No"),
            QString::null, 0, 1 ) ) return;
      else {
         if(fd!=-1) ::close(fd);
         fd = ::open(fileNameLEdit->text(),O_CREAT|O_WRONLY, S_IREAD|S_IWRITE);
      }
    }
    if(fd!=-1) {
      ::close(fd);
      accept();
    }
    else {
 QMessageBox::critical(this,tr("Transfer File..."),tr("Can't open %1").arg(fileNameLEdit->text())); 
    }

}



void transferForm::protocolCB_activated( const QString & )
{
    if(receive) {
    if(protocolCB->currentItem() == 1 || protocolCB->currentItem() == 2) {
       directory = true;
    }
    else {
       directory = false;
    }
}
}
