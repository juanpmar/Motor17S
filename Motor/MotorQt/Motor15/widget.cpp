#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QString>
#include <stdio.h>
#include <QTimer>

QTimer *timer1 = new QTimer();
Widget::Widget(QWidget *parent) :

    QWidget(parent),
    ui(new Ui::Widget)

{
    ui->setupUi(this);
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        /*qDebug()<<"Name:"<<info.portName();
        qDebug()<<"Manufacturer:"<<info.manufacturer();
        qDebug()<<"ID:"<<info.vendorIdentifier();
        qDebug()<<"Vendor:"<<info.hasVendorIdentifier();
        qDebug()<<"Product:"<<info.hasProductIdentifier();
        qDebug()<<"VendorID:"<<info.vendorIdentifier();
        qDebug()<<"ProductID:"<<info.productIdentifier();*/
        if(info.vendorIdentifier()==vendor && info.productIdentifier()==product){
            portn=info.portName();
            ui->pushButton->setEnabled(true);            
            ui->conect->setText("Conectado");
            ui->setupUi(this);
            connect(timer1,                            //conexion entre el timer y la funcion incrementar
                    SIGNAL(timeout()),
                    this,
                    SLOT(segundo())
                    );
            timer1->setInterval(1000);//cada 1 segundo llamará a segundo, para enviar request
            break;
        }else{
            ui->pushButton->setEnabled(false);
            ui->conect->setText("Desconectado");
        }
    }


    sl=new QSerialPort(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::segundo(){ //con esta funcion incrementamos el valor de una variable cada vez que el timer me dice
    char a[]={0x6D,0x03,0x01, 0x06, 0x02, 0x10, 0x7B };//protocolo de request
    sl->write(a,7);//envio al micro.
}

void Widget::OpenSerialPort(QString p)
{
    if(sl->isOpen()){
        sl->close();
    }
    disconnect(sl,SIGNAL(readyRead()),this,SLOT(readSerial()));
    sl->setPortName(p);
    sl->setBaudRate(QSerialPort::Baud115200);
    sl->setDataBits(QSerialPort::Data8);
    sl->setParity(QSerialPort::NoParity);
    sl->setStopBits(QSerialPort::OneStop);
    sl->setFlowControl(QSerialPort::NoFlowControl);
    connect(sl,SIGNAL(readyRead()),this,SLOT(readSerial()));
    if(sl->open(QIODevice::ReadWrite)){
        ui->pushButton->setText("Cerrar");
    }else{
        QMessageBox::critical(this,tr("Error"),sl->errorString());
    }
}


void Widget::on_pushButton_clicked()
{
    if(sl->isOpen()){
        sl->close();
        if(timer1->isActive()){
            timer1->stop();
            ui->pushButton->setText("Abrir");
        }
    }else{
        timer1->start();        //el timer cada segundo ejecuta la funcion incrementar
        OpenSerialPort(portn);
    }   
}

void Widget::readSerial()
{
    QByteArray serialData=sl->readAll();
    qDebug()<<"data1:"<<(int)*(serialData.data());
    qDebug()<<"data2:"<<(int)*(serialData.data()+1);
    qDebug()<<"data3:"<<(int)*(serialData.data()+2);
    qDebug()<<"data4:"<<(int)*(serialData.data()+3);
    char text[4]={*(serialData.data()+3),*(serialData.data()+4),*(serialData.data()+5),*(serialData.data()+6)};
    //sprintf(text,"%ld",d);
    qDebug()<<"data:"<<text;
    int d=(uint8_t)text[0]<<24;
    d|=(uint8_t)text[1]<<16;
    d|=(uint8_t)text[2]<<8;
    d|=(uint8_t)text[3];
    ui->label->setNum(d);
}
