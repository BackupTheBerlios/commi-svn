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
#include <sys/ioctl.h>
#include <sys/termios.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <iostream>
#define debug_receive
using std::cerr; using std::endl;

void millisleep(int ms)
{
    struct timeval tv;
    tv.tv_sec=0;
    tv.tv_usec=ms*1000;
    select(0, 0, 0, 0, &tv);
}

void CommiMainForm::timerDone() {
  timer->stop();  
  //cerr << "Timer Done !!!" <<endl;
}

void CommiMainForm::sleep(int ms) {
      timer = new QTimer(this);
      connect( timer, SIGNAL(timeout()), this, SLOT(timerDone()) );
      timer->start(ms,true);
      while(timer->isActive()) {
          qApp->processEvents();  
      }
      delete timer;
}

void CommiMainForm::fileOpen()
{
    QString filename = QFileDialog::getOpenFileName(
                    "",
                    tr("Commi Batch Files (*.commi)"),
                    this,
                    tr("open file dialog"),
                    tr("Choose a file") );
    QFile file(filename);
    if(file.open(IO_ReadOnly)) {
 QTextStream stream( &file );
 QString line;
 int sleeptime;
 int fd = -1;
             while ( !stream.atEnd() ) {
     line = stream.readLine();  
     line = line.simplifyWhiteSpace();
     cerr << line << endl;
     if(line.startsWith("!!")) 
     { // Command
         if(line.startsWith("!!sleep")) { // wait x ms for actions
            line = line.mid(8);
            sleeptime = line.toInt();
            sleep(sleeptime);
         }
         else if(line.startsWith("!!openPort")) { // open IO-Port
             connectionOpen();
         }
         else if(line.startsWith("!!closePort")) { // close IO-Port
             connectionClose();
         }
         else if(line.startsWith("!!send")) { // send a file
             if(line.startsWith("!!send xmodem")) {
                 fd = ::open(line.mid(14),O_RDONLY);
                 if(fd!=-1) {
                   ::close(fd);
                   sendFileSZ(line.mid(14),0);  
                 }
                 else cerr << tr("Can't open file %1").arg(line.mid(14)) << endl;
             }
             else if(line.startsWith("!!send ymodem")) {
                 fd = ::open(line.mid(14),O_RDONLY);
                 if(fd!=-1) {
                   ::close(fd);
                   sendFileSZ(line.mid(14),1);  
                 }
                 else cerr << tr("Can't open file %1").arg(line.mid(14)) << endl;
             }
             else if(line.startsWith("!!send zmodem")) {
                 fd = ::open(line.mid(14),O_RDONLY);
                 if(fd!=-1) {
                   ::close(fd);
                   sendFileSZ(line.mid(14),2);  
                 }
                 else cerr << tr("Can't open file %1").arg(line.mid(14)) << endl;
             }
             else if(line.startsWith("!!send plain")) {
                 fd = ::open(line.mid(13),O_RDONLY);
                 if(fd!=-1) {
                   ::close(fd);
                   sendFileSZ(line.mid(13),0);  
                 }
                 else cerr << tr("Can't open file %1").arg(line.mid(13)) << endl;
             }         
         }
     }
     else 
     {
          sendString(line);
      }
 }
    }
    else {
 if(filename!="") QMessageBox::critical(this,tr("Open File Error"), tr("Can't open file \"%1\" !!").arg(filename));
}
}

void CommiMainForm::saveSettings() {
    QSettings settings;
    settings.writeEntry("/commi/device/DeviceName",opt_devicename);
    settings.writeEntry("/commi/device/Baudrate",opt_baudrate);
    settings.writeEntry("/commi/device/DataBits",opt_databits);
    settings.writeEntry("/commi/device/Parity",opt_parity);
    settings.writeEntry("/commi/device/StopBits",opt_stop);
    settings.writeEntry("/commi/device/SoftwareFlowControl",softwarehandshake);
    settings.writeEntry("/commi/device/HardwareFlowControl",hardwarehandshake);
    settings.writeEntry("/commi/device/OpenRead",opt_read);
    settings.writeEntry("/commi/device/OpenWrite",opt_write);
    settings.writeEntry("/commi/device/ApplySettings",opt_apply);
    settings.writeEntry("/commi/TerminalFont",textBrowser->font().toString());
    settings.writeEntry("/commi/Width",width());
    settings.writeEntry("/commi/Height",height());
    settings.writeEntry("/commi/Top",x());
    settings.writeEntry("/commi/Left",y());
    settings.writeEntry("/commi/AutoReceiveZModem",opt_autoreceive);
    settings.writeEntry("/commi/AutoReceiveDirectory",opt_autoreceivedir);
}

void CommiMainForm::readSettings() {
    QFont *font = new QFont();
    QSettings settings;
    int x,y, w, h;
    // general
    font->fromString(settings.readEntry("/commi/TerminalFont","Helvetica"));
    textBrowser->setFont(*font);
    x = (settings.readNumEntry("/commi/Top",50));
    y = (settings.readNumEntry("/commi/Left",50));
    w = (settings.readNumEntry("/commi/Width",550));
    h = (settings.readNumEntry("/commi/Height",450));
    opt_autoreceive = settings.readBoolEntry("/commi/AutoReceiveZModem",true);
    opt_autoreceivedir = settings.readEntry("/commi/AutoReceiveDirectory","");
    resize(w,h);
    move (x,y);
    // Device
    opt_devicename=settings.readEntry("/commi/device/DeviceName","/dev/ttyS0");
    opt_baudrate = settings.readNumEntry("/commi/device/Baudrate",38400);
    opt_databits = settings.readNumEntry("/commi/device/DataBits",8);
    opt_parity = settings.readEntry("/commi/device/Parity","None");
    opt_stop = settings.readEntry("/commi/device/StopBits","1");
    softwarehandshake = settings.readBoolEntry("/commi/device/SoftwareFlowControl",false);
    hardwarehandshake = settings.readBoolEntry("/commi/device/HardwareFlowControl",false);
    opt_read = settings.readBoolEntry("/commi/device/OpenRead",true);
    opt_write = settings.readBoolEntry("/commi/device/OpenWrite",false);
    opt_apply = settings.readBoolEntry("/commi/device/ApplySettings",true);
}

void CommiMainForm::closeEvent( QCloseEvent * )
{
    fileExit();
}

void CommiMainForm::fileExit()
{
    saveSettings();
    QApplication::exit( 0 );
}


void CommiMainForm::editCopy()
{
//    clipboard->setText ( textBrowser->text());
    textBrowser->copy();
}


void CommiMainForm::editPaste()
{
    lineEdit->setText( clipboard->text() );
}


void CommiMainForm::helpAbout()
{
    aboutForm *aForm = new aboutForm(this, "about", TRUE );
    aForm->exec();
    
}

void CommiMainForm::init()
{
    clipboard = QApplication::clipboard();
    m_fd=-1;
    if ( clipboard->supportsSelection() )
 clipboard->setSelectionMode( TRUE );
    readSettings();
    m_sending=false;
    helpContentsAction->setAccel( QKeySequence( tr("F1")));
    lineEdit->setFocus();
}


void CommiMainForm::textChange( const QString &test)
{
    QMessageBox::about(this, tr("About"), test );
}


void CommiMainForm::sendCommand()
{
    //QMessageBox::about(this, tr("About"), tr(lineEdit->command()) );
    if (m_fd==-1)
 return;
    if(lineEdit->command() == "!ctrl_c") sendByte(3);
    else if(lineEdit->command() == "!ctrl_q") sendByte(17);
    else if(lineEdit->command() == "!ctrl_s") sendByte(19);
    else sendString(lineEdit->command());
}


/** This function features some code from minicom 2.0.0, src/sysdep1.c */
void CommiMainForm::setNewOptions(int baudrate, int databits, const QString& parity, const QString& stop, bool softwareHandshake, bool hardwareHandshake)
{
    struct termios newtio;
    //   memset(&newtio, 0, sizeof(newtio));
    if (tcgetattr(m_fd, &newtio)!=0)
 cerr<<"tcgetattr() 3 failed"<<endl;
    
    /*{
      unsigned int i;
      char *c =(char*)&newtio;
      fprintf(stderr,"*****************\n");
      for (i=0; i<sizeof(newtio); i++)
      {
  unsigned int t=*c;
  if (i%8 == 0)
     fprintf(stderr,"\n");
  fprintf(stderr, " 0x%02x", t&0xff);
  c++;
      }
   }*/
    
    
    speed_t _baud=0;
    switch (baudrate)
    {
    case 600:
 _baud=B600;
 break;
    case 1200:
 _baud=B1200;
 break;
    case 2400:
 _baud=B2400;
 break;
    case 4800:
 _baud=B4800;
 break;
    case 9600:
 _baud=B9600;
 break;
 //   case 14400:
 //      _baud=B14400;
 //      break;
    case 19200:
 _baud=B19200;
 break;
 //   case 28800:
 //      _baud=B28800;
 //      break;
    case 38400:
 _baud=B38400;
 break;
 //   case 56000:
 //      _baud=B56000;
 //      break;
    case 57600:
 _baud=B57600;
 break;
    case 115200:
 _baud=B115200;
 break;
    case 230400:
 _baud=B230400;
 break;
    case 460800:
 _baud=B460800;
 break;
    case 576000:
 _baud=B576000;
 break;
    case 921600:
 _baud=B921600;
 break;
 //   case 128000:
 //      _baud=B128000;
 //      break;
    default:
 //   case 256000:
 //      _baud=B256000;
 break;
    }
    cfsetospeed(&newtio, (speed_t)_baud);
    cfsetispeed(&newtio, (speed_t)_baud);
    
    /* We generate mark and space parity ourself. */
    if (databits == 7 && (parity=="Mark" || parity == "Space"))
 databits = 8;
    switch (databits)
    {
    case 5:
 newtio.c_cflag = (newtio.c_cflag & ~CSIZE) | CS5;
 break;
    case 6:
 newtio.c_cflag = (newtio.c_cflag & ~CSIZE) | CS6;
 break;
    case 7:
 newtio.c_cflag = (newtio.c_cflag & ~CSIZE) | CS7;
 break;
    case 8:
    default:
 newtio.c_cflag = (newtio.c_cflag & ~CSIZE) | CS8;
 break;
    }
    newtio.c_cflag |= CLOCAL | CREAD;
    
    //parity
    newtio.c_cflag &= ~(PARENB | PARODD);
    if (parity == "Even")
 newtio.c_cflag |= PARENB;
    else if (parity== "Odd")
 newtio.c_cflag |= (PARENB | PARODD);
    
    //hardware handshake
    /*   if (hardwareHandshake)
      newtio.c_cflag |= CRTSCTS;
   else
      newtio.c_cflag &= ~CRTSCTS;*/
    newtio.c_cflag &= ~CRTSCTS;
    
    //stopbits
    if (stop=="2")
 newtio.c_cflag |= CSTOPB;
    else
 newtio.c_cflag &= ~CSTOPB;
    
    //   newtio.c_iflag=IGNPAR | IGNBRK;
    newtio.c_iflag=IGNBRK;
    //   newtio.c_iflag=IGNPAR;
    
    //software handshake
    if (softwareHandshake)
 newtio.c_iflag |= IXON | IXOFF;
    else
 newtio.c_iflag &= ~(IXON|IXOFF|IXANY);
    
    newtio.c_lflag=0;
    
    newtio.c_oflag=0;
    
    
    newtio.c_cc[VTIME]=2;
    newtio.c_cc[VMIN]=60;
    
    //   tcflush(m_fd, TCIFLUSH);
    if (tcsetattr(m_fd, TCSANOW, &newtio)!=0)
 cerr<<"tcsetattr() 1 failed"<<endl;
    
    int mcs=0;
    //   ioctl(m_fd, TIOCMODG, &mcs);
    ioctl(m_fd, TIOCMGET, &mcs);
    mcs |= TIOCM_RTS;
    ioctl(m_fd, TIOCMSET, &mcs);
    
    if (tcgetattr(m_fd, &newtio)!=0)
 cerr<<"tcgetattr() 4 failed"<<endl;
    //hardware handshake
    if (hardwareHandshake)
 newtio.c_cflag |= CRTSCTS;
    else
 newtio.c_cflag &= ~CRTSCTS;
    /*  if (on)
     newtio.c_cflag |= CRTSCTS;
  else
     newtio.c_cflag &= ~CRTSCTS;*/
    if (tcsetattr(m_fd, TCSANOW, &newtio)!=0)
 cerr<<"tcsetattr() 2 failed"<<endl;
    
    /*{
      unsigned int i;
      char *c =(char*)&newtio;
      fprintf(stderr,"-----------------\n");
      tcgetattr(m_fd, &newtio);
      for (i=0; i<sizeof(newtio); i++)
      {
  unsigned int t=*c;
  if (i%8 == 0)
     fprintf(stderr,"\n");
  fprintf(stderr, " 0x%02x", t&0xff);
  c++;
      }
   }*/
}


void CommiMainForm::connectionOpen()
{
    openTTY(true);  
    if(m_fd!=-1) {
      connectionOpenAction->setEnabled(false);
      connectionCloseAction->setEnabled(true);
      transferSend_FileAction->setEnabled(true);
      transferReceive_FileAction->setEnabled(true);
    }
}

void CommiMainForm::openTTY( bool oldsettings) {
    int flags=0;
    if (opt_read && opt_write)
 flags=O_RDWR;
    else if (!opt_read && opt_write)
 flags=O_WRONLY;
    else if (opt_read && !opt_write)
 flags=O_RDONLY;
    else
    {
 QMessageBox::information(this, tr("Error"), tr("Opening the device neither for reading nor writing doesn't seem to make much sense ;-)"));
 return;
    }
    m_fd=open(opt_devicename.latin1(), flags | O_NDELAY);
    if (m_fd<0)
    {
 cerr<<"opening failed"<<endl;
 m_fd=-1;
 QMessageBox::information(this, tr("Error"), tr("Could not open %1").arg(opt_devicename));
 return;
    }
    if (opt_apply)
    {
        int n = fcntl(m_fd, F_GETFL, 0);
        fcntl(m_fd, F_SETFL, n & ~O_NDELAY);
 
        if (oldsettings && tcgetattr(m_fd, &m_oldtio)!=0)
            cerr<<"tcgetattr() 2 failed"<<endl;
 
       setNewOptions(opt_baudrate, opt_databits, opt_parity, opt_stop, softwarehandshake, hardwarehandshake);
    }
    
    if (opt_read)
   {
    m_notifier=new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
    connect(m_notifier, SIGNAL(activated(int)), this, SLOT(readData(int)));
   }
}


void CommiMainForm::readData( int fd )
{
    if (fd!=m_fd)
 return;
    int bytesRead=::read(m_fd, m_buf, 4096);
    
    if (bytesRead<0)
    {
 cerr<<"read result: "<<bytesRead<<endl;
 perror("read: \n");
 return;
    }
    
    const char* c=m_buf;
    QString text;
    for (int i=0; i<bytesRead; i++)
    {
 if ((isprint(*c)) || (*c=='\n') || (*c=='\r'))
 {
     if (*c!='\r')
  text+=(*c);
 }
 else
 {
     char buf[16];
     unsigned int i=*c;
     snprintf(buf, 16, "\\0x%02x", i & 0xff);
     text+=buf;
 }
 c++;
    } 
//    cerr << text.latin1() << endl;
    if(text.startsWith("rz**") && !text.endsWith("\n") && opt_autoreceive) {
 receiveFileSZ(opt_autoreceivedir,2);
    }
    else {
 textBrowser->setCursorPosition(textBrowser->paragraphs()-1, textBrowser->paragraphLength(textBrowser->paragraphs()-1));  
    textBrowser->insert(text);
   }
}

bool CommiMainForm::sendString(const QString& s)
{
    const char *bytes=s.latin1();
    for (unsigned int i=0; i<s.length(); i++)
    {
 if (!sendByte(*bytes))
     return false;
 bytes++;
 millisleep(1);
    }
    if (!sendByte('\n'))
 return false;
    return true;
}

bool CommiMainForm::sendByte(char c)
{
    if (m_fd==-1)
 return false;
    //   c=c&0xff;
    int res=::write(m_fd, &c, 1);
    //   cerr<<"wrote "<<(unsigned int)(c)<<endl;
    if (res<1)
    {
 cerr<<"write returned "<<res<<" errno: "<<errno<<endl;
 perror("write\n");
 return false;
    }
    //   else
    //      cerr<<" \""<<c<<"\"; ";
    return true;
}

void CommiMainForm::closeTTY(bool oldsettings) {
    if(m_fd!=-1) {
        if (oldsettings) tcsetattr(m_fd, TCSANOW, &m_oldtio);
        ::close(m_fd); // close Port
    }
    m_fd=-1;
    delete m_notifier;
    m_notifier=0;
}

void CommiMainForm::connectionClose()
{
    connectionOpenAction->setEnabled(true);
    connectionCloseAction->setEnabled(false);
    transferSend_FileAction->setEnabled(false);
    transferReceive_FileAction->setEnabled(false);
    closeTTY(true);
}

void CommiMainForm::editOptions()
{
    QString str;
    optionsForm *optForm = new optionsForm(this, "options", TRUE );
    // general settings
    optForm->fontBtn->setFont(textBrowser->font());
    optForm->autosaveCB->setChecked(opt_autoreceive);
    optForm->autosaveLEdit->setText(opt_autoreceivedir);
    // old port settings
    optForm->deviceNameComboBox->setCurrentText(opt_devicename);
    optForm->writeCheckBox->setChecked(opt_write);
    optForm->readCheckBox->setChecked(opt_read);
    optForm->applyCheckBox->setChecked(opt_apply);
    optForm->stopbitsComboBox->setCurrentText(opt_stop);
    optForm->parityComboBox->setCurrentText(opt_parity);
    str = str.setNum(opt_databits,10);
    optForm->databitsComboBox->setCurrentText(str);
    str = str.setNum(opt_baudrate,10);
    optForm->baudrateComboBox->setCurrentText(str);
    if(softwarehandshake && !hardwarehandshake) optForm->flowcontrolComboBox->setCurrentItem(1);
    else if(!softwarehandshake && hardwarehandshake) optForm->flowcontrolComboBox->setCurrentItem(0);
    else optForm->flowcontrolComboBox->setCurrentItem(2);
  // Execute Options
    if ( optForm->exec() ) {
 // general
 textBrowser->setFont(optForm->fontBtn->font());
 opt_autoreceive = optForm->autosaveCB->isChecked();
 opt_autoreceivedir = optForm->autosaveLEdit->text();
 // port
 opt_devicename = optForm->deviceNameComboBox->currentText();
 opt_write = optForm->writeCheckBox->isChecked();
 opt_read = optForm->readCheckBox->isChecked();
 opt_apply = optForm->applyCheckBox->isChecked();
 opt_stop = optForm->stopbitsComboBox->currentText();
 opt_parity = optForm->parityComboBox->currentText();
 opt_databits = optForm->databitsComboBox->currentText().toInt();
 opt_baudrate = optForm->baudrateComboBox->currentText().toInt();
 switch(optForm->flowcontrolComboBox->currentItem()) {
 case 2: 
     softwarehandshake=false;
     hardwarehandshake=false;
     break;
 case 1:
     softwarehandshake=true;
     hardwarehandshake=false;
     break;
 case 0:
     softwarehandshake=false;
     hardwarehandshake=true;
break;
 }
 if(m_fd!=-1 && opt_apply) setNewOptions(opt_baudrate, opt_databits, opt_parity, opt_stop, softwarehandshake, hardwarehandshake);
    }
}

void CommiMainForm::sendPlainFile(QString filename) {
  m_sending=true;
  QFile file(filename);
  file.open(IO_ReadOnly);
  QByteArray data=file.readAll();
//  if(m_progress!=0) delete m_progress;
  m_progress=new QProgressDialog(tr("Sending file..."), tr("Cancel"), 100, this, "progress", TRUE);
  m_progress->setMinimumDuration(100);
  unsigned int step=data.size()/100;
  if (step<1) step=1;
  cerr << "test" << endl;
  for (unsigned int i=0; i<data.size(); i++)
  {
      if ((i%step)==0)
      {
   m_progress->setProgress(i/step);
   qApp->processEvents();
      }
      sendByte(data.data()[i]);
//         if (!sendByte(data.data()[i]))
      if (0)
      {
            QMessageBox::information(this, tr("Comm error"), tr("Sending failed (%1/%2)").arg(i).arg(data.count()));
            break;
      }
      if ( m_progress->wasCancelled() )
            break;
      }
      delete m_progress;
      m_progress=0;
      m_sending=false;
}

void CommiMainForm::sendFileSZ(QString filename, int mode) {
    m_sending = true;
    closeTTY(false);
    m_sz=new QProcess(this);
    m_sz->addArgument("sh");
    m_sz->addArgument("-c");
    QString tmp=QString("sz ");
    switch(mode) {
    case 0 : 
 tmp+="--xmodem ";
 break;
case 1:
    tmp+="--ymodem ";
    break;
case 2:
    tmp+="--zmodem ";
}
    tmp=tmp+"-vv \""+filename+"\" < "+opt_devicename+" > "+opt_devicename;
    m_sz->addArgument(tmp);
    m_sz->setCommunication(QProcess::Stderr);

    connect(m_sz, SIGNAL(readyReadStderr()), this, SLOT(readFromStderr()));
    connect(m_sz, SIGNAL(processExited()), this, SLOT(sendDone()));
      if (!m_sz->start())
      {
         QMessageBox::information(this, tr("Comm error"), tr("Could not start sx"));
         delete m_sz;
         m_sz=0;
         openTTY(false);
         m_sending=false;
         return;
      }
      switch (mode) {
   case 0: tmp="xmodem";
       break;
   case 1:
       tmp="ymodem";
       break;
       case 2:
    tmp="zmodem";
}
    
      m_progress=new QProgressDialog(tr("Sending file via %1...").arg(tmp), tr("Cancel"), 100, this, "progress", TRUE);
      connect(m_progress, SIGNAL(cancelled()), this, SLOT(killSz()));
      m_progress->setMinimumDuration(100);
      QFileInfo fi(filename);
      m_progressStepSize=fi.size()/1024/100;
      if (m_progressStepSize<1)
         m_progressStepSize=1;
//    cerr<<"while(isRunning)"<<endl;
      m_progress->setProgress(0);
      while (m_sz->isRunning())
      {
         qApp->processEvents();
         millisleep(10);
      }
//      cerr<<"----------------- sx done"<<endl;

      delete m_sz;
      m_sz=0;
      delete m_progress;
      m_progress=0;
    
    
    openTTY(false);
    m_sending=false;
}

void CommiMainForm::killSz()
{
   if (m_sz==0)
      return;
   m_sz->tryTerminate();
}

void CommiMainForm::readFromStdout()
{
   QByteArray ba=m_sz->readStdout();
//   cerr<<"readFromStdout() "<<ba.count()<<endl;
   unsigned int bytesToWrite=ba.count();
   char* src=ba.data();
   while (bytesToWrite>0)
   {
      int bytesWritten=::write(m_fd, src, (bytesToWrite>4096?4096:bytesToWrite));
      if (bytesWritten<0)
      {
  //       cerr<<"readFromStdout() error "<<bytesWritten<<" , "<<bytesToWrite<<" left"<<endl;
         return;
      }
      src+=bytesWritten;
      bytesToWrite-=bytesWritten;

   }
}

void CommiMainForm::readFromStderr()
{
   QByteArray ba=m_sz->readStderr();
//   cerr<<"readFromStderr() "<<ba.count()<<endl;
   if (m_progress==0)
      return;
   QString s(ba);
  // cerr << "text : " << s << endl;   
   QRegExp regex(".+\\d+/ *(\\d+)k.*");
   int pos=regex.search(s);
   if (pos>-1)
   {
      QString captured=regex.cap(1);
//      cerr<<"captured kb: -"<<captured.latin1()<<"-"<<endl;
      int kb=captured.toUInt();
      if ((kb%m_progressStepSize)==0)
      {
         int p=kb/m_progressStepSize;
         if (p<100)
            m_progress->setProgress(p);
      }
   }
//   else
//      cerr<<"--------"<<s.latin1()<<"-"<<endl;
/*   for (unsigned int i=0; i<ba.count(); i++)
   {
      char c=ba.data()[i];
      unsigned int tmp=c;
      if (isprint(tmp))
         cerr<<c;
      else
         fprintf(stderr, " \\0x%02x ", tmp&0xff);
   }*/
}

void CommiMainForm::sendDone()
{

}

void CommiMainForm::transferSend_FileAction_activated()
{
   // closeTTY(false);
   transferForm *transForm = new transferForm(this, "transfer", true);
   if(!transForm->exec()) return; // break if fails
   if(transForm->protocolCB->currentItem()==3) {
     sendPlainFile(transForm->fileNameLEdit->text());
   }
   else if(transForm->protocolCB->currentItem()>-1 && transForm->protocolCB->currentItem()<3) {
       sendFileSZ(transForm->fileNameLEdit->text(),transForm->protocolCB->currentItem());
   }
}


void CommiMainForm::textBrowser_clicked( int, int )
{
    lineEdit->setFocus();
}


void CommiMainForm::editClearAction_activated()
{
    textBrowser->clear();
}


void CommiMainForm::helpAbout_QtAction_activated()
{
    QMessageBox::aboutQt( this, "Commi" );
}


void CommiMainForm::helpContents_activated()
{
     helpForm *hForm = new helpForm(this, "help", true);
     hForm->exec();
}


void CommiMainForm::fileSave_asAction_activated()
{
    QString fn = QFileDialog::getSaveFileName( QString::null, "*", this );
    QFile f ( fn);
    if(f.exists() && QMessageBox::question(
            this,
            tr("Overwrite File?"),
            tr("A file called %1 already exists."
                "Do you want to overwrite it?")
                .arg( fn ),
            tr("&Yes"), tr("&No"),
            QString::null, 0, 1 ) )
        return;
    if(!f.open(IO_WriteOnly )) {
 QMessageBox::critical(this,tr("I/O Error"),tr("Can't open %1 for writing").arg(fn));
return;
    }
    QTextStream t(&f);
    t << textBrowser->text();
    f.close();
    statusBar()->message(tr("Terminal content saved to %1 ...").arg(fn), 4000);
}

void CommiMainForm::receiveFileSZ( QString filename, int mode) {
    m_sending = true;
    closeTTY(false);
    m_sz=new QProcess(this);
    m_sz->addArgument("sh");
    m_sz->addArgument("-c");
    QString tmp=QString("export LANG=C && rb ");
    switch(mode) {
    case 0 : 
 tmp+="--xmodem " + filename;
 break;
case 1:
    tmp+="--ymodem ";
    break;
case 2:
    tmp+="--zmodem ";
}
    if(mode==1 || mode==2) {   
 QDir dir(filename);
  m_sz->setWorkingDirectory(dir);
    }
//    tmp=tmp+"-vv \""+filename+"\" < "+opt_devicename+" > "+opt_devicename;
   tmp=tmp+" < "+opt_devicename+" > "+opt_devicename;
    m_sz->addArgument(tmp);
    m_sz->setCommunication(QProcess::Stderr);//|QProcess::Stdout);

    connect(m_sz, SIGNAL(readyReadStderr()), this, SLOT(readFromStderrReceive()));
      connect(m_sz, SIGNAL(readyReadStdout()), this, SLOT(readFromStderrReceive()));
    connect(m_sz, SIGNAL(processExited()), this, SLOT(sendDone()));
      if (!m_sz->start())
      {
         QMessageBox::information(this, tr("Comm error"), tr("Could not start rb"));
         delete m_sz;
         m_sz=0;
         openTTY(false);
         m_sending=false;
         return;
      }
      switch (mode) {
   case 0: tmp="xmodem";
       break;
   case 1:
       tmp="ymodem";
       break;
       case 2:
    tmp="zmodem";
}
    receiveblock=0;
    receivemode = mode;
      m_progress=new QProgressDialog(tr("Receiving file via %1...").arg(tmp), tr("Cancel"), 11, this, "progress", TRUE);
      connect(m_progress, SIGNAL(cancelled()), this, SLOT(killSz()));
      m_progress->setMinimumDuration(100);
      QFileInfo fi(filename);
      m_progressStepSize=10;
//      if (m_progressStepSize<1)
//         m_progressStepSize=1;
//    cerr<<"while(isRunning)"<<endl;
      m_progress->setProgress(0);
      while (m_sz->isRunning())
      {
         qApp->processEvents();
       //  millisleep(10);
      }
//      cerr<<"----------------- sx done"<<endl;

     openTTY(false);
    m_sending=false;
/*
  Exit Status
  
  -128   Abort transfer
  -128   Timeout 
  */
    if(!m_sz->normalExit()) { 
 QMessageBox::critical(this,tr("Error"),tr("Aborted by user"));
    }
    else {
    if(m_sz->exitStatus()==0) {
 switch(mode) {
 case 0:    QMessageBox::information(this,tr("Transer complete"),tr("File %1 receiced complete").arg(filename));
     break;
 case 1:
 case 2:
     QMessageBox::information(this,tr("Transfer complete"),tr("File %1 receiced complete").arg(receivefilename));
 }
    }
    else QMessageBox::information(this,tr("Transfer error"), tr("Error while transfer file\nExit Status : %1").arg(m_sz->exitStatus()));
}
      delete m_sz;
      m_sz=0;
      delete m_progress;
      m_progress=0;
    

    
}

void CommiMainForm::readFromStderrReceive()
{
   QByteArray ba=m_sz->readStderr();
   if (m_progress==0)
      return;
   QString s(ba);
   s = s.stripWhiteSpace();
   s = s.latin1();
//   textBrowser->append("text:"+s+"\n");
   //ba = m_sz->readStdout();
    QRegExp regex("[a-z]: (\\d+)"); // Blocks received
   QRegExp regex4("[a-z]: -(\\d+)"); // mistake
   QRegExp regex2("[a-z]: +(\\d+)/ +(\\d+) +BPS:(\\d+) +ETA (\\d+):(\\d+)"); // zmodem
   QRegExp regex3("[a-z]: +(\\d+)/ +(\\d+) +BPS:(\\d+)"); // ymodem
   QRegExp regex5("[a-z]: +(\\d+) +BPS:(\\d+)"); // xmodem
   int pos2 = regex2.search(s);
   int pos3 = regex3.search(s);
   int pos=regex.search(s);
   int pos4 = regex4.search(s);
   int pos5 = regex5.search(s);
   QString t;

   if(pos2>-1) {
     m_progress->setLabelText(tr("BPS: %1  -  ETA : %2:%3\nFile: %4").arg(regex2.cap(3),regex2.cap(4),regex2.cap(5), receivefilename));
       t = regex2.cap(2);
       m_progress->setTotalSteps(t.toInt());
       t = regex2.cap(1);
       m_progress->setProgress(t.toInt());
//       textBrowser->append("pos2\n");   
   }
   else if (pos3>-1) {
       t = regex3.cap(2);
//       QMessageBox::information(this,"Received File",tr("Bytes %1\nFilename: %2").arg(t,receivefilename));
   }
   else if(pos4>-1) {
     // do nothing ... is a mistake from rb-system  
   }
   else if(pos5>-1) {
       t = regex5.cap(1);
//       textBrowser->append("received "+t+"Bytes\n");
   }
   else if (pos>-1)
   {
       do {
    receiveblock++;
    pos += regex.matchedLength();
       }
       while((pos=regex.search(s,pos)) != -1);
       m_progress->setLabelText(tr("Received %1 blocks").arg(receiveblock));
       if(m_progress->progress()<10) m_progress->setProgress(m_progress->progress()+1);
       else m_progress->setProgress(0);
//    textBrowser->append("pos1\n");
   }
   else if(s.contains("TIMEOUT")) 
   {
       killSz(); // kill it when timeout
       QMessageBox::critical(this,tr("Receiving File"),tr("Stop while TIMEOUT"));
//       textBrowser->append("timeout\n");   
   }
   else if(s.contains(":")) {
      receivefilename=s.mid(s.find(":")+2);
//      textBrowser->append("filename\n");   
   }
   else {
//      textBrowser->append("else\n");        
   }
  textBrowser->setCursorPosition(textBrowser->paragraphs()-1, textBrowser->paragraphLength(textBrowser->paragraphs()-1)); 
   

}

void CommiMainForm::transferReceive()
{       
    transferForm *transForm = new transferForm(this, "transfer", true);
    transForm->setReceive();
   if(!transForm->exec()) return; // break if fails
   if(transForm->protocolCB->currentItem()==3) {
     cerr << "receive plain" << endl;
   }
   else {
      receiveFileSZ( transForm->fileNameLEdit->text(),transForm->protocolCB->currentItem());
   }
}
