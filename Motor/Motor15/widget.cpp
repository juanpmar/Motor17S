#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QString>
#include <QtSerialPort>
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
        //product 67 de un arduino y vendor 9025
        //if(info.vendorIdentifier()==vendor && info.productIdentifier()==product){
        if(info.vendorIdentifier()==vendor && info.productIdentifier()==product){
            portn=info.portName();
            ui->pushButton->setEnabled(true);            
            ui->conect->setText("Conectado");
            qDebug()<<"si";
            connect(timer1,                            //conexion entre el timer y la funcion incrementar
                    SIGNAL(timeout()),
                    this,
                    SLOT(request())
                    );
            timer1->setInterval(5000);//cada 100 msegundo llamará a segundo, para enviar request
            timer1->start();
            qDebug()<<"si";
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

void Widget::request(){ //con esta funcion incrementamos el valor de una variable cada vez que el timer me dice
    char a[]={0x6D,0x03,0x01, 0x06, 0x02, 0x10, 0x7B, 0x29 };//protocolo de request
    sl->write(a,8);//envio al micro.
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
    qDebug()<<"nop";
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
        OpenSerialPort(portn);
    }   
}

void Widget::readSerial()
{
    static int a=0,RPa;
    QString text1;
    QByteArray serialData=sl->readAll();
    int tam=serialData.size();
    /*qDebug()<<"tam"<<tam;
    qDebug()<<"data1:"<<(int)*(serialData.data());
    qDebug()<<"data2:"<<(int)*(serialData.data()+1);
    qDebug()<<"data3:"<<(int)*(serialData.data()+2);
    qDebug()<<"data4:"<<(int)*(serialData.data()+3);*/
    char com=0x6D^0x04^0x01^*(serialData.data()+4)^*(serialData.data()+5)^*(serialData.data()+6)^*(serialData.data()+3);
    char text[4]={*(serialData.data()+3),*(serialData.data()+4),*(serialData.data()+5),*(serialData.data()+6)};
    int d=0;
    if (0x29==*(serialData.data()+(tam-1)) && com==*(serialData.data()+(tam-2))) {
        d=(uint8_t)text[0]<<24;
        d|=(uint8_t)text[1]<<16;
        d|=(uint8_t)text[2]<<8;
        d|=(uint8_t)text[3];
        if (RPa<=d) {
        ui->LMin->setNum(d);
        }else if(RPa>=d) {
        ui->LMax->setNum(d);
        }
        ui->label->setNum(d);
        qDebug()<<d;
        text1.setNum(text[3]);
        text1.setNum(text[2]<<8);
        //text1.append(":");
        //text1.setNum(a);
        ui->plainTextEdit->appendPlainText(text1);//impresion para posterior uso en excel
        a++;
        if (a>=100) {
            a=0;
        }
        RPa=d;
     }
    //sprintf(text,"%ld",d);
}
/*
 *la funcion de transmicion char no recibe datos mayores a 0x7F  TENER EN CUENTA PROTOCOLO
  */
void Widget::on_dial_valueChanged(int value)
{
    uint16_t tiempo;
    char valuec=(uint8_t)value;
    ui->Progres->setValue(value);//value as the percentaje of the dial.
    tiempo=ui->TMotor->text().toUInt();
    char t1=(uint8_t)(tiempo>>8);
    char t2=(uint8_t)tiempo;
    char com=0x6D^0x03^0x02^valuec^t1^t2;
    char a[]={0x6D,0x03,0x02,valuec,t1,t2,com,0x29 };//protocolo de request
    qDebug()<<"tiempo "<<com;
    if (sl->isOpen()){
     sl->write(a,8);//envio al micro.
    }
}
