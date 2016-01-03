#ifndef GUICENTRALWIDGET_H
#define GUICENTRALWIDGET_H

#include "GuiTabBlock.h"
#include "GuiMainBlock.h"

#include "DataManager.h"
#include "NetManager.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QTabWidget>

class GuiCentralWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiCentralWidget(QWidget *parent = 0);
  ~GuiCentralWidget();

  QHBoxLayout *main_layout;
  GuiTabBlock *gui_tab_block;
  GuiMainBlock *gui_main_block;

private:
  DataManager *data_manager;
  NetManager *net_manager;


  QStringList my_profile_str_list;
};

#endif // GUICENTRALWIDGET_H