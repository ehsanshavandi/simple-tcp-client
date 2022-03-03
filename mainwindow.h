#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QIODevice>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_btnConnect_clicked();
  void onReadyRead();
  void onConnected();
  void onDisconnected();
  void onBytesWritten(qint64 bytes);

  void on_btnSend_clicked();

  void on_lineEditSendingText_textChanged(const QString& arg1);

 private:
  Ui::MainWindow* ui;
  QHostAddress ip;
  quint16 port;
  bool isConnecting;
  QTcpSocket* socket;

  void init();
  // Helper method
  QHostAddress createIpAddr();
  quint16 createPort();
};
#endif // MAINWINDOW_H
