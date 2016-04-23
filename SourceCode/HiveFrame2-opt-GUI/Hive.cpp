#include "Hive.h"
#include "GuiOSXNotification.h"

Hive::Hive(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_MAC
  QApplication::setQuitOnLastWindowClosed(false);
  QtMac::setBadgeLabelText("Hi");
#endif

  ////thread info
  thread_info = new ThreadInfo(this);

  ////data manager
  thread_data = new ThreadData(this);

  ////net manager
  thread_net = new ThreadNet(this);

  ////gui
  gui_central_widget = new GuiCentralWidget();

  ////connect
  connect(thread_net, SIGNAL(usrEnter(UsrProfileStruct*)), thread_data, SLOT(onUsrEntered(UsrProfileStruct*)));
  connect(thread_data, SIGNAL(usrProfileLoaded(UsrProfileStruct*)), gui_central_widget, SLOT(onUsrEnter(UsrProfileStruct*)));
  connect(thread_data, SIGNAL(usrProfileChanged(UsrProfileStruct*)), gui_central_widget, SLOT(onUsrProfileChanged(UsrProfileStruct*)));

  thread_info->start(QThread::LowestPriority);
  thread_data->start(QThread::NormalPriority);
  thread_net->start(QThread::NormalPriority);


#ifdef Q_OS_MAC
  QtMac::setBadgeLabelText("");
#endif
}

Hive::~Hive()
{
  delete gui_central_widget;
}

