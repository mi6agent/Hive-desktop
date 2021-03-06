#ifndef GUICOMBWIDGET_H
#define GUICOMBWIDGET_H

#include <QVBoxLayout>
#include <QHostAddress>
#include <QDragMoveEvent>
#include <QMouseEvent>
#include <QDrag>
#include <QPropertyAnimation>
#include <QMimeData>

#include "GlobalType.h"
#include "GlobalData.h"
#include "Gui/Frameworks/Widgets/LabelButton.h"
#include "Gui/Frameworks/Widgets/AvatarWidgets.h"
#include "Gui/Frameworks/Widgets/BadgeIcon.h"

class CombWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CombWidget(UsrProfileStruct *usrProfileStruct, QWidget *parent = 0);
  ~CombWidget();

  void setProfile(UsrProfileStruct *usrProfile);
  void setBadgeNumber(const int &num);

protected:
  bool mousePressed = false;
  QMouseEvent *mouseEvent;

  void paintEvent(QPaintEvent  *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void enterEvent(QEvent *event );
  void leaveEvent(QEvent *);
  void dragMoveEvent(QEvent *event);

private:
  AvatarButton *avatar;
  QLabel *usr_name_label;
  QLabel *ip_addr_label;
  QLabel *status_label;
  BadgeIcon *badge_icon;
  QVBoxLayout *usr_info_layout;
  QHBoxLayout *net_status_layout;
  QHBoxLayout *main_layout;

  QString online_dot = "<span style=\" color:#39c828;\">●</span>";
  QString offline_dot = "<span style=\" color:#ed403f;\">●</span>";
  QString unstable_dot = "<span style=\" color:#ffb500;\">●</span>";


  QPalette hover_palette;
  QColor default_window_color = Global::color_tab;
  QColor hovered_window_color = QColor(255,175,0,161);

  bool hovered  = false;

  ///data
  UsrProfileStruct usr_profile;
  QString getSubNetStr(const QString &ipAddr);



signals:
  void clicked(const QString &usrKey);



};

#endif // GUICOMBWIDGET_H
