#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTime>
#include <QDebug>

void write_contact_info(QString usr_name, QString usr_ip, QString usr_key)
{
  QJsonArray json;
  json.insert(0, usr_name);
  json.insert(1, usr_ip);
  json.insert(2, usr_key);

  QJsonDocument document;
  document.setArray(json);
  //QByteArray byte_array = document.toJson(QJsonDocument::Compact);

  QFile f("/Users/Echo/Desktop/a.txt");
  if(!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
  {
      //boooom!
  }

  QTextStream txtOutput(&f);



  txtOutput<<document.toJson(QJsonDocument::Compact)<<endl;
  f.close();
  f.flush();

}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  for(int i = 0; i <1000; i++)
    {
      write_contact_info("Tim","192.168.1.2",QString::number(QTime::currentTime().msec()));
    }
  qDebug()<<"Done!!!!!!";


  return a.exec();
}
