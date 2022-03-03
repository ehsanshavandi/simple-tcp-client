#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  init();
}

MainWindow::~MainWindow()
{
  socket->close();
  socket->deleteLater();
  delete ui;
}


void MainWindow::on_btnConnect_clicked()
{
  this->ip = this->createIpAddr();
  this->port = this->createPort();

  socket->connectToHost(this->ip, this->port);

  ui->btnConnect->setEnabled(false);
  ui->statusRight->setText("Connecting....");
}

void MainWindow::onReadyRead()
{
  QByteArray datas = socket->readAll();
  //  qInfo() << datas;
  ui->plainTextEditData->appendPlainText(QString(datas));
}

void MainWindow::onConnected()
{
  ui->statusRight->setText("Connected");
}

void MainWindow::onDisconnected()
{
  ui->statusRight->setText("Disconnected");
  ui->btnConnect->setEnabled(true);
}

void MainWindow::onBytesWritten(qint64 bytes)
{
  //  qDebug() << "We wrote: " << bytes;
}

void MainWindow::init()
{
  this->setWindowTitle("TCP Client");
  socket = new QTcpSocket(this);
  connect(socket,  &QIODevice::readyRead, this, &MainWindow::onReadyRead);
  connect(socket,  &QTcpSocket::connected, this, &MainWindow::onConnected);
  connect(socket,  &QTcpSocket::disconnected, this, &MainWindow::onDisconnected);
  connect(socket,  &QTcpSocket::bytesWritten, this, &MainWindow::onBytesWritten);
  ui->btnSend->setEnabled(false);
  ui->plainTextEditData->setReadOnly(true);
}

QHostAddress MainWindow::createIpAddr()
{
  QString selectedIp = ui->lineEditIp->text();
  QHostAddress ipAddr = QHostAddress(selectedIp);
  return ipAddr;
}

quint16 MainWindow::createPort()
{
  bool isPortOk;
  auto portStr = ui->lineEditPort->text();
  port = portStr.toDouble(&isPortOk);

  if (!isPortOk)
  {
    qInfo() << "error";
    return -1;
  }
  else
    return port;
}


void MainWindow::on_btnSend_clicked()
{
  QString data = ui->lineEditSendingText->text();
  QString me = "Me: ";
  ui->plainTextEditData->appendPlainText(me + data);
  QByteArray dataToSend = QByteArray(data.toUtf8());
  socket->write(dataToSend);
  ui->lineEditSendingText->clear();
}


void MainWindow::on_lineEditSendingText_textChanged(const QString& arg1)
{
  if (arg1 != "")
    ui->btnSend->setEnabled(true);
  else
    ui->btnSend->setEnabled(false);
}

