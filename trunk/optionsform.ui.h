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


void optionsForm::iconView1_selectionChanged( QIconViewItem * item )
{
    widgetStack1->raiseWidget(item->index());
}


void optionsForm::okButton_clicked()
{
accept();
}


void optionsForm::fontBtn_clicked()
{
fontBtn->setFont( QFontDialog::getFont( 0, fontBtn->font() ) );
}


void optionsForm::pushButton7_clicked()
{
autosaveLEdit->setText(QFileDialog::getExistingDirectory(
                    "",
                    this,
                    "get existing directory",
                    tr("Choose a directory for storing received files"),
                    false ));
}
