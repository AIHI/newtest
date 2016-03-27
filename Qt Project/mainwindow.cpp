/* Для чтения с БДХК */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QByteArray>
#include <windows.h>
#include <QMessageBox>
#include <QSettings>
#include <QFile>
#include <QList>
#include <QTimer>
#include <QThread>
#include <QTextCodec>
#include <QStringList>
#include <QtCore/qmath.h>
#include <QtSql>






QSerialPort *serial;
QSerialPort *port = new QSerialPort();
QSerialPort *portkrxo;
QStringList list, listhex;
QString str,sum;
QString sum2; //для GPS
QByteArray ba;

QString latitude, longitude; //широта, долгота для GPS-датчика
QString brlatitude, brlongitude; //широта, долгота для GPS-датчика

int statusdanger=0;//статус знака опасности


//глобальные переменные для ПДК датчиков БДХК
float PDKSolKisl, PDKMonoYgl, PDKYglGaz, PDKSerVod, PDKOksSer, PDKFtvk,
      PDKHlor, PDKAmiak, PDKH2CO, PDKOksAzot, PDKHP10, PDKMetan, PDKPropan,
      PDKGeksan, PDKHCN, PDKGB, PDKHD;


//глобальные переменные для значения с датчиков БДХК
QString gHp10, gMetan, gFtvk, gMonoYgl, gSerVod, gHlor, gGeksan, gOksSer,
        gOksAzot, gSolKisl, gPropan, gAmmiak, gYglGaz, gGB, gHD, gHCN, gH2CO;

//глобальные переменные для значения с датчиков БР РХО
QString gBRAmmiak, gBRChlor, gBRDioksSer, gBRDioksAzot, gBRDoza;


//глобальные переменные для значения с метео БДХК
QString Sm, Dm, Pa, Ta, Ua;

//глобальная переменная - кол-во записей в БК РХО
QString rec;

QTimer* timer  = new QTimer;
QTimer* timer2 = new QTimer;


QString trap="54524150",
        sek="bd656b09",
        sec="736563",
        min="6d696e",
        hour="686f7572",
        mounth="6d6f6e7468",
        day="646179",
        year="79656172",
        hp10="48703130",
        metan="cce5f2e0ed",
        ftorkisl="d4f2eef0eee2eee4eef0eee4ede0ff20eae8f1ebeef2e0",
        monoygl="cceeedeeeeeaf1e8e420f3e3ebe5f0eee4e0",
        servod="d1e5f0eee2eee4eef0eee4",
        hlor="d5ebeef0",
        geksan="c3e5eaf1e0ed",
        oksser="ceeaf1e8e420f1e5f0fb",
        oksazot="ceeaf1e8e420e0e7eef2e0",
        solkisl="d1eeebffede0ff20eae8f1ebeef2e0",
        propan="cff0eeefe0ed",
        amiak="c0ecece8e0ea",
        yglgaz="d3e3ebe5eae8f1ebfbe920e3e0e7",
        gb="4742",
        hd="4844",
        hcn="d1e8ede8ebfcede0ff20eae8f1ebeef2e0"/*"48434e"*/, //синильная кислота
        h2co="d4eef0ece0ebfce4e5e3e8e4"/*"4832434f"*/, //формальдегид

        comand1="01211001",
        zpt="2c";

QList<int> posledov; //собираем номера-последовательность датчиков


QStringList getComPortList() //получаем список com-портов из реестра
{
    QStringList list;
    HKEY hKey = 0;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        DWORD cbMaxValueNameLen, cbMaxValueLen;

        if (RegQueryInfoKey(hKey, // дескриптор ключа
                            NULL, // адрес буфера для имени класса
                            NULL, // адрес размера буфер для имени класса
                            NULL, // зарезервировано
                            NULL, // адрес буфера для количества подключей
                            NULL, // адрес буфера для наибольшего размера имени подключа
                            NULL, // адрес буфера для наибольшего размера имени класса
                            NULL, // адрес буфера для количества вхождений значений
                            &cbMaxValueNameLen,       // адрес буфера для наибольшего размера имени значения
                            &cbMaxValueLen, // адрес буфера для наибольшего размера данных значения
                            NULL,       // адрес буфера для длины дескриптора безопасности
                            NULL        // адрес буфера для получения времени последней записи
            ) == ERROR_SUCCESS)
        {
            cbMaxValueNameLen++;
            cbMaxValueLen++;
            TCHAR ValueName[cbMaxValueNameLen];
            DWORD Type = REG_SZ;
            BYTE Data[cbMaxValueLen];
            char temp[cbMaxValueLen];
            DWORD cbValueNameLen, cbValueLen;

            DWORD index = 0;
            cbValueNameLen = cbMaxValueNameLen;
            cbValueLen = cbMaxValueLen;
            while (RegEnumValue(hKey,  // дескриптор запрашиваемого ключа
                            index++,  // индекс запрашиваемого значения
                            ValueName, // адрес буфера для имени значения
                            &cbValueNameLen, // адрес переменной с  размером буфера для имени значения
                            NULL, // зарезервировано
                            &Type,  // адрес переменной с типом данных
                            Data,  // адрес буфера для данных значения
                            &cbValueLen  // адрес переменной с  размером буфера для данных
                   ) == ERROR_SUCCESS)
            {
                wcstombs(temp, (WCHAR*)Data, cbValueLen/2);
                list.append(temp);
                cbValueNameLen = cbMaxValueNameLen;
                cbValueLen = cbMaxValueLen;
            }
        }
        RegCloseKey(hKey);
    }



    QRegExp COM("COM");
    QString temp;
    QStringList strlsttemp;

    for (int i=0; i<list.length(); i++) //убираем слово "COM"
    {

        if ( COM.indexIn(list.at(i)) == 0 )
        {
            temp = list.at(i).mid(3,list.at(i).length()-3);
            strlsttemp.append(temp);
        }
    }

    for (int i=0; i<strlsttemp.length()-1; i++) // упорядочиваем номера по возрастанию
    {
        if (strlsttemp.at(i+1).toFloat() < strlsttemp.at(i).toFloat())
        {
            QString s;
            s = strlsttemp.at(i+1);
            strlsttemp[i+1] = strlsttemp.at(i);
            strlsttemp[i] = s;
        }

        else
        {
        i = i + 1;
        }
    }

    for (int i=0; i<strlsttemp.length()-1; i++) //добавляем слово "COM"
    {
        list[i] = "COM" + strlsttemp.at(i);
    }

    return list;
}


//============================================================================================
//============================================================================================
//============================= БДХК =========================================================
//============================================================================================
//============================================================================================

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    status=1;


    QPalette palette;
    //palette.setColor(QPalette::Text, Qt::red);
    palette.setColor(QPalette::Window, Qt::red);


    //ui->lineEdit_6->setStyleSheet("selection-background-color: rgb(255, 255, 127);");
    //ui->lineEdit_6->setStyleSheet("background-image: url(:/Images/Green.png);");



    connect(this, SIGNAL(read(QString)), this, SLOT(parse_rxo(QString)));


    ui->pb_closeportkrxo->setEnabled(false);
    ui->le_countkrxo->setEnabled(false);




    for (int i=0; i<getComPortList().length(); i++) //добавляем в комбо список в соответствии с количеством портов
    {

        ui->cb_portkrxo->addItem(getComPortList().at(i)); //для АСКРХО
    }


    deviceOff(); //убираем элементы, т.к. не прошли идентиф.






}

void MainWindow::deviceOff() //не получили идент. пакет от устройства
{
}

MainWindow::~MainWindow()
{

   //serial->close();
    delete ui;
}




bool MainWindow::compare(QString a, QStringList b, int c)
{
//a - слово для сравнения (заголовки датчиков)
//b - название списка
//c - номер группы


    for(int i=0;i<a.length();i++)
 {

        if (b[c].at(i)==a.at(i))
            return true;
        else
            return false;
 }
}

bool MainWindow::comparestr(QString a, int c)
{
//a - слово для сравнения (заголовки датчиков)
//c - номер ячейки в str с которой начать сравнивать

bool result=true;

    for(int i=0;i<a.length();i++)
 {

        if (str[c+i]==a.at(i))
            result=result && true;
        else
            result=result && false;
 }

    return result;

}


QString MainWindow::FormatText(QString IEEE754) //полученный результат приводим к 4-х значному виду: значение*(10^-6)
{

    //В IEEE754 приходит число. Пр.: 1.21487e-07

    QRegExp e("[e]");

    if (IEEE754.mid((IEEE754.length()-4),1)=="e") //начинаем искать 4-ый символ с конца строки (e) чтобы узнать, что число в степени
    {

        int stepen=IEEE754.right(3).toInt(); //последние три знака в строке в int: -07


        float fl;

        if (e.indexIn(IEEE754)<5)
        {
           IEEE754.insert(4,"0");
        }

        fl=IEEE754.left(5).toFloat(); //первые 5 символов слева: 1.214

        if (stepen>-9 & stepen<-4) // если число не больше 10^-4 и не меньше 10^-9
        {
            QString strl=QString::number(fl/(qPow(10,(-6-(stepen))))); // 1.214/10^(-6-(-07)) т.е. получаем 0.1214
            strl.resize(5);//возвращаем значение. Снова ограничиваем 5 первыми знаками: 0.121
            return strl;
        }
        else
        {
            if (stepen>-4) //если больше 10^-4 т.е. очень большое число
            {
                return ">999";
            }

            if (stepen<-9) //если больше 10^-9 т.е. очень маленькое
            {
                return "0.0";
            }
        }
    }
    else //если число без степени
    {
        IEEE754.resize(5);
        return IEEE754;
    }
}

QString MainWindow::IEEE754(int b) //входной HEX (32bit) переводим в BIN и высчитываем значение по формату IEEE754
{

    //b - конечный байт

    qDebug()<<"STR AT b-8"<<str.at(b-7);
    qDebug()<<"STR AT b-8"<<str.at(b-6);
    qDebug()<<"STR AT b-8"<<str.at(b-5);
    qDebug()<<"STR AT b-8"<<str.at(b-4);
    qDebug()<<"STR AT b-8"<<str.at(b-3);
    qDebug()<<"STR AT b-8"<<str.at(b-2);
    qDebug()<<"STR AT b-8"<<str.at(b-1);
    qDebug()<<"STR AT"<<str.at(b);



    QString qs, qsE, qsM;
    int E,M, znak;
    float F;

    qs.clear();
    qsE.clear();
    qsM.clear();
    E=0;
    M=0;
    F=0;

    qDebug()<<"STRIEEEEE"<<str;
    qDebug()<<"STRIEEEEELEN"<<str.length();

    while (str.length()<180)
    {
        str.insert(str.length(),"0");
    }


    for (int i=0; i<4; ++i) //c b по b-8 перевели в BIN
    {
    qs.append(hextobin(str.at(b-1-(i*2)))); // Пр: 50,48,46...шаг=2
    qs.append(hextobin(str.at(b-(i*2)))); // Пр: 51,49,47...шаг=2
    }

    qDebug()<<"QSSSSTRIEEEEE"<<qs;

    /*=== Вычисляем S ===*/
    if (realint(qs.at(31-31))==0) //Если 31 байт 0, тогда знак "+". Иначе "-" (Вычисляем S из FLOAT)

         znak=1;

    else znak=-1;

    /*=== Вычисляем E ===*/
    for (int i=0; i<8; ++i) //c 30 по 23 байт - вычисляем E из FLOAT
   {
    qsE.append(qs.at((31-30)+i)); //31-23 = 8 т.е. меняем направление счёта. Двигаемся справа налево <-|
       qDebug()<<"qsE"<<qsE;
    }

    /*=== Вычисляем M ===*/
    for (int i=0; i<=22; ++i) //c 22 по 0 байт - вычисляем M из FLOAT
   {
    qsM.append(qs.at((32-23)+i)); //Двигаемся справа налево <-|
           qDebug()<<"qsM"<<qsM;
   }

    E=bintodec(qsE);
    M=bintodec(qsM);
               qDebug()<<"E"<<E;
                          qDebug()<<"M"<<M;
    F=znak*(qPow(2,E-127))*(1+(M/(qPow(2,23))));

    qDebug()<<"FFFF"<<F;
    return QString::number(F).toLatin1();
}

QString MainWindow::hextobin(QString hex) //конвертация из HEX в BIN
{

QString hexStr = "0123456789abcdef";
QStringList List;

List << "0000" << "0001" << "0010" << "0011" << "0100" << "0101" << "0110" << "0111" << "1000" << "1001" << "1010" << "1011" << "1100" << "1101" << "1110"<< "1111";



    for (int i=0; i <= 15; ++i)
    {
        if (hex == hexStr.at(i))
        {
            hex.clear();
        return List.at(i);
        }
    }
}

int MainWindow::realint(QString string) //переводим из QString "0" и "1" в Int (почему то .toint не поперло)
{
    if (string=="0") return 0;
    else return 1;
}

int MainWindow::bintodec(QString bin) //переводим из BIN в DEC
{

int result=0;

    for (int i=0; i < bin.length(); i++)
    {

            result=result+ (realint(bin.at(i))*qPow(2,((bin.length()-1)-i))); //значение бита * 2 в степени длина - 1
    }

return result;
}


//====================================================================================================================
//====================================================================================================================
//=============================  БК РХО ==============================================================================
//====================================================================================================================
//====================================================================================================================


void MainWindow::on_pb_openportkrxo_clicked()
{

    portkrxo = new QSerialPort(this);
    portkrxo->close();
    portkrxo->setPortName(ui->cb_portkrxo->currentText());
    portkrxo->setBaudRate(QSerialPort::Baud4800);
    portkrxo->setDataBits(QSerialPort::Data8);
    portkrxo->setParity(QSerialPort::NoParity);
    portkrxo->setStopBits(QSerialPort::OneStop);
    portkrxo->setFlowControl(QSerialPort::NoFlowControl);
    if (portkrxo->open(QIODevice::ReadWrite))
    {

        qDebug()<< "COMPORT KRXO OPEN!";
        connect (portkrxo,SIGNAL(readyRead()),this,SLOT(Readkrxo()));
        ui->pb_openportkrxo->setEnabled(false);
        ui->pb_closeportkrxo->setEnabled(true);
        ui->le_countkrxo->setEnabled(true);
        ui->spinBox->setEnabled(false);
        ui->statusBar->showMessage("Порт БР АСКРХО открыт!");

    }
    else
    {
        qDebug()<<"COMPORT CLOSE!";

    }


}

void MainWindow::Readkrxo()
{
    QString readport;
    readport=portkrxo->readAll().toHex();
    qDebug()<<"P"<<readport;
    emit read(readport);
}


void MainWindow::parse_rxo(QString data)
{
    QRegExp tch("[.]");
    bool ok;
    readkrxo.append(data);

    qDebug()<<"DATA:"<<readkrxo;

    qDebug()<<"DATA:lenght"<<readkrxo.length();

    if (readkrxo.length()==62 && readkrxo.endsWith("02")) //запрос параметров. Команда 0х02
    {
        rec = readkrxo.mid(readkrxo.length()-10,2) + readkrxo.mid(readkrxo.length()-12,2);
        ui->le_countkrxo->setText(QString::number(rec.toInt(&ok, 16)));
    }

    if (readkrxo.length()==230 && readkrxo.startsWith("5452415064")) //запрос результатов. Команда 09 & 03
    {
        //qDebug() << "WE NO SPEAK" << readkrxo.mid(210,8);
        //qDebug() << "FLOAT CRACK" <<FormatText(IEEE754forKRXO(readkrxo.mid(210,8),7));
        //qDebug() << "READDOLG" << readkrxo.mid(170,8);

// высчитываем широту
            QString temp, temp2;

            temp = readkrxo.mid(170,8);
            temp2.append(temp.at(6));
            temp2.append(temp.at(7));
            temp2.append(temp.at(4));
            temp2.append(temp.at(5));
            temp2.append(temp.at(2));
            temp2.append(temp.at(3));
            temp2.append(temp.at(0));
            temp2.append(temp.at(1));

            temp = QString::number(temp2.toInt(&ok, 16));

            while (temp.length()>8) // сокращаем до 8 -ми знаков, если больше
            {
                temp.remove(temp.length()-1,1);
            }

            while (temp.length()<8) // добавляем до 8 -ми знаков, если меньше
            {
                temp.insert(0,"0");
            }

            if (temp.length() == 8)
            {
                temp.insert(2,".");
            }

            temp2.clear();
            temp2 = temp.mid(3, temp.length()-3);
            temp2 = QString::number((temp2.toFloat())/60);
            temp2 = temp2.remove(tch.indexIn(temp2), 1);


            brlatitude = temp.mid(0,3) + temp2; //пишем широту в глобальную переменную

            ui->le_krxolatit->setText(brlatitude);


/*
            dolg1temp = dolg1.mid(3,dolg1.length()-3); //выносим дробную часть
            dolg1temp = QString::number((dolg1temp.toFloat())/60); //делим её на 60
            dolg1temp.remove(tch.indexIn(dolg1temp),1); //удаляем из неё точку
            dolg1 = dolg1.mid(0,3) + dolg1temp; //соединяем целую и дробную часть
            latitude = dolg1 ; //передаем в глобальную var
*/


// ===========================================


// высчитываем долготу

            temp.clear();
            temp2.clear();


                        temp = readkrxo.mid(178,8);
                        temp2.append(temp.at(6));
                        temp2.append(temp.at(7));
                        temp2.append(temp.at(4));
                        temp2.append(temp.at(5));
                        temp2.append(temp.at(2));
                        temp2.append(temp.at(3));
                        temp2.append(temp.at(0));
                        temp2.append(temp.at(1));


                        qDebug() << "OLOLOO2" << temp2;
                        temp = QString::number(temp2.toInt(&ok, 16));

                                                qDebug() << "OLOLOO" << temp;

                        while (temp.length()>8) // сокращаем до 8-и знаков, если больше
                        {
                            temp.remove(temp.length()-1,1);
                        }

                        while (temp.length()<9) // добавляем до 9-и знаков, если меньше
                        {
                            temp.insert(0,"0");
                        }

                        if (temp.length() == 9)
                        {
                            temp.insert(3,".");
                        }

                        int start;
                        temp2.clear();
                        temp2 = temp.mid(4, temp.length()-4);
                        qDebug() << "TEMP222" << temp2;

                        if (temp.startsWith("0"))
                        {
                            start = 0;
                        }
                        temp2 = QString::number((temp2.toFloat())/60);
                        temp2 = temp2.remove(tch.indexIn(temp2), 1);

                        if (start == 0)
                        {
                            temp2.insert(0,"0");
                        }

                        while ( temp2.length() > 6 )
                        {
                            temp2.remove(temp2.length()-1,1);
                        }



                        brlongitude = temp.mid(0,4) + temp2; //пишем широту в глобальную переменную

                        ui->le_krxolong->setText(brlongitude);

// ===========================================






        gBRAmmiak = FormatText(IEEE754forKRXO(readkrxo.mid(186,8),7));
        ui->le_krxoammiak->setText(gBRAmmiak + " [мг/м3]");

        gBRChlor = FormatText(IEEE754forKRXO(readkrxo.mid(194,8),7));
        ui->le_krxochlor->setText(gBRChlor + " [мг/м3]");

        gBRDioksSer = FormatText(IEEE754forKRXO(readkrxo.mid(202,8),7));
        ui->le_krxodioksser->setText(gBRDioksSer + " [мг/м3]");

        gBRDioksAzot = FormatText(IEEE754forKRXO(readkrxo.mid(210,8),7));
        ui->le_krxodioksazota->setText(gBRDioksAzot + " [мг/м3]");

        gBRDoza = FormatText(IEEE754forKRXO(readkrxo.mid(218,8),7));
        qDebug() << "TEST DEBUG" << readkrxo.mid(218,8);
        ui->le_krxodoza->setText(gBRDoza + " [мкЗв]");
    }

}


QString MainWindow::IEEE754forKRXO(QString str, int b) //входной HEX (32bit) переводим в BIN и высчитываем значение по формату IEEE754
    {

        //b - конечный байт


        qDebug()<<"STR AT"<<str.at(b);
        qDebug()<<"STR AT b-8"<<str.at(b-8);

        QString qs, qsE, qsM;
        int E,M, znak;
        float F;

        qs.clear();
        qsE.clear();
        qsM.clear();
        E=0;
        M=0;
        F=0;

        qDebug()<<"STRIEEEEE"<<str;

        for (int i=0; i<4; ++i) //c b по b-8 перевели в BIN
        {
            qs.append(hextobin(str.at(b-1-(i*2)))); // Пр: 50,48,46...шаг=2
            qs.append(hextobin(str.at(b-(i*2)))); // Пр: 51,49,47...шаг=2
        }

        qDebug()<<"QSSSSTRIEEEEE"<<qs;

        /*=== Вычисляем S ===*/
        if (realint(qs.at(31-31))==0) //Если 31 байт 0, тогда знак "+". Иначе "-" (Вычисляем S из FLOAT)

        znak=1;

        else znak=-1;

        /*=== Вычисляем E ===*/
        for (int i=0; i<8; ++i) //c 30 по 23 байт - вычисляем E из FLOAT
        {
            qsE.append(qs.at((31-30)+i)); //31-23 = 8 т.е. меняем направление счёта. Двигаемся справа налево <-|
            qDebug()<<"qsE"<<qsE;
        }

        /*=== Вычисляем M ===*/
        for (int i=0; i<=22; ++i) //c 22 по 0 байт - вычисляем M из FLOAT
        {
            qsM.append(qs.at((32-23)+i)); //Двигаемся справа налево <-|
            qDebug()<<"qsM"<<qsM;
        }

        E=bintodec(qsE);
        M=bintodec(qsM);
        qDebug()<<"E"<<E;
        qDebug()<<"M"<<M;
        F=znak*(qPow(2,E-127))*(1+(M/(qPow(2,23))));

        qDebug()<<"FFFF"<<F;
        return QString::number(F).toLatin1();
    }


void MainWindow::on_pb_closeportkrxo_clicked()
{
    portkrxo->close();
    ui->pb_closeportkrxo->setEnabled(false);
    ui->pb_openportkrxo->setEnabled(true);
    ui->le_countkrxo->clear();
    ui->le_countkrxo->setEnabled(false);
    ui->spinBox->setEnabled(true);
    ui->statusBar->showMessage("Порт БР АСКРХО закрыт!");
    qDebug()<< "COMPORT KRXO CLOSE!";
}

void MainWindow::on_pushButton_4_clicked()
{
    readkrxo.clear();
    identkrxo();
}


void MainWindow::on_pushButton_7_clicked()
{

    rec.clear(); // очищаем глобальную переменную кол-ва записей в HEX
    readkrxo.clear();
    identkrxo();
    timer->singleShot(4000,this,SLOT(resultkrxo()));

}



void MainWindow::identkrxo()
{
    //char data[23]; //0x54 0x52 0x41 0x50 2 0x00 0x00 0x00 0x01 0x00 0x00 0x00
    QByteArray qbdata, qbdata2, qbdata3;
    qbdata = QByteArray::fromHex("54524150000000006400000003000000"); //23

    //qbdata[16]=0xA1;
    //qbdata[17]=0xA9;
    //qbdata[18]=0xE7;
    //qbdata[19]=0x3F;
    qbdata[20]=0x02;
    qbdata[21]=0x00;
    qbdata[22]=0x00;

/*
    data[0]=0x54;
    data[1]=0x52;
    data[2]=0x41;
    data[3]=0x50;
    // номер КРХО
    data[4]=0x0A;
    data[5]=0x00;
    data[6]=0x00;
    data[7]=0x00;
    // _номер КРХО
    data[8]=0x64;
    data[9]=0x00;
    data[10]=0x00;
    data[11]=0x00;
    // =========
    data[12]=0x03;
    data[13]=0x00;
    data[14]=0x00;
    data[15]=0x00;
    // CRC
    // инф.
    //data[16]=0xa1;
    //data[17]=0xa9;
    // системн.
    // для 10
    data[18]=0xe7;
    data[19]=0x3f;
    // для 5 устр-ва
    data[18]=0x44;
    data[19]=0x28;

    // end CRC

    data[20]=0x08; //команда P
    data[21]=0x00; // I
    data[22]=0x00; // I

*/


    QString spbox=ui->spinBox->text();
    switch (spbox.toInt())
    {
    case 1:
        qbdata[4]=0x01;
        break;
    case 2:
        qbdata[4]=0x02;
        break;
    case 3:
        qbdata[4]=0x03;
        break;
    case 4:
        qbdata[4]=0x04;
        break;
    case 5:
        qbdata[4]=0x05;
        break;
    case 6:
        qbdata[4]=0x06;
        break;
    case 7:
        qbdata[4]=0x07;
        break;
    case 8:
        qbdata[4]=0x08;
        break;
    case 9:
        qbdata[4]=0x09;
        break;
    case 10:
        qbdata[4]=0x0A;
        break;
    case 11:
        qbdata[4]=0x0B;
        break;
    case 12:
        qbdata[4]=0x0C;
        break;
    case 13:
        qbdata[4]=0x0D;
        break;
    case 14:
        qbdata[4]=0x0E;
        break;
    case 15:
        qbdata[4]=0x0F;
        break;
    case 16:
        qbdata[4]=0x10;
        break;
    case 17:
        qbdata[4]=0x11;
    case 18:
        qbdata[4]=0x12;
    case 19:
        qbdata[4]=0x13;
    case 20:
        qbdata[4]=0x14;
        break;
    default:
        break;
    }


    QString qtr, tempstr;
    QByteArray qba;

    //================ CRC CSd ===================================

    tempstr = bintohex(CRC(datatobin(qbdata, 20, 22))); //вычисляем CRC по инф. части
    qDebug()<<"tempstr"<<tempstr;


    qtr.clear();
    qba.clear();
    qtr.append(tempstr.at(2));
    qtr.append(tempstr.at(3));
    qDebug()<<"qtr"<<qtr;
    qba=qtr.toLatin1();
    qDebug()<<"qba"<<qba;
    qbdata2=QByteArray::fromHex(qba); //CRC по инф. части


    qtr.clear();
    qba.clear();
    qtr.append(tempstr.at(0));
    qtr.append(tempstr.at(1));
    qDebug()<<"qtr"<<qtr;
    qba=qtr.toLatin1();
    qDebug()<<"qba"<<qba;
    qbdata2.append(QByteArray::fromHex(qba)); //[16-17] //CRC по инф. части




    //================ CRC CSs ===================================

    QByteArray poi;
    poi = qbdata.mid(0,16);
    poi.append(qbdata2.mid(0,2));
    poi.append(qbdata.mid(18,5));

    qDebug()<<"CRC CSs"<<bintohex(CRC(datatobin(poi, 4, 17)));

    tempstr = bintohex(CRC(datatobin(poi, 4, 17))); //вычисляем CRC по системной части


    qtr.clear();
    qba.clear();
    qtr.append(tempstr.at(2));
    qtr.append(tempstr.at(3));
    qDebug()<<"qtr"<<qtr;
    qba=qtr.toLatin1();
    qDebug()<<"qba"<<qba;
    qbdata3=QByteArray::fromHex(qba);


    qtr.clear();
    qba.clear();
    qtr.append(tempstr.at(0));
    qtr.append(tempstr.at(1));
    qDebug()<<"qtr"<<qtr;
    qba=qtr.toLatin1();
    qDebug()<<"qba"<<qba;
    qbdata3.append(QByteArray::fromHex(qba)); //[16-17]



    if (portkrxo->isOpen()) //если порт открыт
    {
    portkrxo->write(qbdata,16);
    portkrxo->write(qbdata2,2);
    portkrxo->write(qbdata3,2);
    qbdata.remove(0,20);
    portkrxo->write(qbdata,3);
    portkrxo->waitForBytesWritten(2000); //ждем пока не запишутся все данные
    }

}



QString MainWindow::datatobin(QByteArray data, int s, int e) //convert HEX to BIN + Polinom^16 (data-hex array, s-start position, e-end position)
{
    QByteArray ba, ba2;
    ba.clear();
    ba2.clear();


    for (s; s<=e; s++)
    {
        if (data.at(s)==0) //если пришла ячейка "0"
        {
            qDebug()<<"data.at(s)"<<data.at(s);
            ba.append("00000000");
        }
        else
        {
            /*
            if (data.at(s)==1 || data.at(s)==2 ||
                data.at(s)==3 || data.at(s)==5 || data.at(s)==6 ||
                data.at(s)==7 || data.at(s)==8 || data.at(s)==9)
            {
                ba2="0000";
                ba2.append(QByteArray::number(data[s], 2));
                qDebug()<<"IXAAAA"<<ba2;
            }

        else
        {
*/
            ba2=QByteArray::number(data[s], 2);
            qDebug()<<"ba2"<<ba2;


            if (ba2.length()>8) //если у нас пришло ffff ffff ffff ffxx т.е. в начале ff
            {
                ba2=ba2.right(8);
                qDebug()<<"ba2RIGHT"<<ba2;
            }


            while (ba2.length()<8) //если не кратно 4-м - добавляем в начало "0"
            {
                qDebug()<<"ROCKKKK";
                ba2.insert(0,'0');
                                qDebug()<<"BA2ROCKKKK"<<ba2;
            }
       // }


            ba.append(ba2);

        }
                    qDebug()<<"ba.append(ba2)"<<ba;
    }

    ba.append("0000000000000000"); //polinom 16 stepen (x^16 + x^12 + x^5 + 1)
        qDebug()<<"BA"<<ba;
        data.clear();
    return ba;

}


QString MainWindow::CRC(QString qs) //подсчет контрольной суммы по CRC-16 CCITT (возвращает bin)
{
    QString poli="10001000000100001"; //x^16 + x^12 + x^5 + 1
    QString qstemp; //для куска из пакета
    QString restemp; // для временного результата при вычитании
    QRegExp one("[1]");
    int pos; //позиция единицы


    qDebug()<<"QS ORIGINAL"<<qs;

    if (qs.startsWith("0")) //если результата начинается с "0"
    {
        pos = one.indexIn(qs);
        qs.remove(0,pos); //удаляем первые нули до "1"
    }

    qstemp = qs.left(poli.length()); //вырезаем кусок из изначального пакета

    qs.remove(0,qstemp.length()); //удаляем из первоначального пакета в соответствии с длиной куска

    qDebug()<<"QS ORIGINAL CUT"<<qs;


    restemp.clear();
    for (int i=0; i<qstemp.length();i++) //делаем вычитание XOR
        {

        restemp.append(XOR(qstemp.at(i), poli.at(i)));
        qDebug()<<"RESTEMP"<<restemp;
        }

    qDebug()<<"RESTEMP"<<restemp;


    if (restemp.startsWith("0")) //если результата начинается с "0"
    {
        pos = one.indexIn(restemp);
        restemp.remove(0,pos); //удаляем первые нули до "1"
    }

    qDebug()<<"RESTEMP AFTER REMOVE"<<restemp;

    qstemp=restemp.insert(restemp.length(),qs.left(pos)); //вставляем кол-во символов равное удаленным нулям из первоначального qs
    qs.remove(0, pos); //удаляем из qs количество вставленных символов

        qDebug()<<"RESTEMP AFTER INSERT"<<restemp;
        qDebug()<<"QSTEMP AFTER INSERT"<<qstemp;

// ===========================================================================================
// ===========================================================================================
// ===========================================================================================


   while (poli.length()<=qs.length()+restemp.length())
   {
        restemp.clear();
        for (int i=0; i<qstemp.length();i++) //делаем вычитание XOR
           {
           restemp.append(XOR(qstemp.at(i), poli.at(i)));
           qDebug()<<"RESTEMP2"<<restemp;
           }

       qDebug()<<"RESTEMP2"<<restemp;


       if (restemp.startsWith("0")) //если результата начинается с "0"
       {
           pos = one.indexIn(restemp);
           restemp.remove(0,pos); //удаляем первые нули до "1"
       }

       qDebug()<<"RESTEMP AFTER REMOVE2"<<restemp;

       qstemp=restemp.insert(restemp.length(),qs.left(pos)); //вставляем кол-во символов равное удаленным нулям из первоначального qs
       qs.remove(0, pos); //удаляем из qs количество вставленных символов


       qDebug()<<"RESTEMP AFTER INSERT2"<<restemp;
       qDebug()<<"QSTEMP AFTER INSERT2"<<qstemp;

   }


while (qstemp.length()%4>0) //если количество не кратно 4, добавляем нули в начало
{
    qstemp.insert(0,"0");
}

qDebug()<<"QSTEMP %"<<qstemp;

qDebug()<<"BIn TO HEX"<<bintohex(qstemp);


       return qstemp;
}


QString MainWindow::bintohex(QString bin)
{
    QString hexStr = "0123456789abcdef";
    QStringList List;
    QString res;
    List << "0000" << "0001" << "0010" << "0011" << "0100" << "0101" << "0110" << "0111" << "1000" << "1001" << "1010" << "1011" << "1100" << "1101" << "1110"<<"1111";


    int binlen = bin.length();

    if ((binlen%4)==0) //если кол-во бит кратно 4
    {
        for (int n=0; n<binlen/4; n++)
        {
            for (int i=0; i<16; i++)
            {
                if (bin.left(4)==List.at(i))
                    {
                        res.append(hexStr.at(i));
                    }
            }
                bin.remove(0,4);
            }
        return res;
    }
    else
    {
        return "-1";
    }

}


QString MainWindow::XOR(QString a, QString b)
{
    if (a=="0" && b=="0")
    {
        return "0";
    }
    if (a=="1" && b=="0")
    {
        return "1";
    }
    if (a=="0" && b=="1")
    {
        return "1";
    }
    if (a=="1" && b=="1")
    {
        return "0";
    }
}


void MainWindow::resultkrxo()
{

//=====================================================================================================
//================================ Для команды 09 =====================================================
//=====================================================================================================


    int dec;
    bool ok;

    dec = rec.toInt(&ok, 16) - 1;

    rec = QString::number(dec, 16);

    while (rec.length()<4)
    {
        rec.insert(0,"0");
    }

    QString temp = rec.mid(2,2);
    QString temp2 = rec.mid(0,2);
    rec.clear();
    rec.append(temp);
    rec.append(temp2);


    qDebug() << "REC" << rec;

    QByteArray inf = QByteArray::fromHex("0000000000") + QByteArray::fromHex(rec.toLatin1()) + QByteArray::fromHex("0000");


    QString number = QString("%1").arg(ui->spinBox->text().toInt(),0,16);

    if (number.length()<2)
    {
        number.insert(0,"0");
    }

    QString qtr, tempstr;
    QByteArray qba, qbdata2, qbdata3;

    //================ CRC CSd ===================================

    tempstr = bintohex(CRC(datatobin(inf, 0, 8))); //вычисляем CRC по инф. части
    qDebug()<<"tempstrres"<<tempstr;


    qtr.clear();
    qba.clear();
    qtr.append(tempstr.at(2));
    qtr.append(tempstr.at(3));
    qDebug()<<"qtr"<<qtr;
    qba=qtr.toLatin1();
    qDebug()<<"qba"<<qba;
    qbdata2=QByteArray::fromHex(qba); //CRC по инф. части


    qtr.clear();
    qba.clear();
    qtr.append(tempstr.at(0));
    qtr.append(tempstr.at(1));
    qDebug()<<"qtr"<<qtr;
    qba=qtr.toLatin1();
    qDebug()<<"qba"<<qba;
    qbdata2.append(QByteArray::fromHex(qba)); //[16-17] //CRC по инф. части


    QByteArray head =  QByteArray::fromHex("54524150");
    QByteArray sys = QByteArray::fromHex(number.toLatin1()) + QByteArray::fromHex("0000006400000009000000");
    sys.append(qbdata2);


    //================ CRC CSs ===================================


    tempstr = bintohex(CRC(datatobin(sys, 0, 13))); //вычисляем CRC по системной части


    qtr.clear();
    qba.clear();
    qtr.append(tempstr.at(2));
    qtr.append(tempstr.at(3));
    qba=qtr.toLatin1();
    qbdata3=QByteArray::fromHex(qba);


    qtr.clear();
    qba.clear();
    qtr.append(tempstr.at(0));
    qtr.append(tempstr.at(1));
    qba=qtr.toLatin1();
    qbdata3.append(QByteArray::fromHex(qba)); //[16-17]



   if (portkrxo->isOpen()) //если порт открыт
    {
       // Для команды 09
       portkrxo->write(head,4);
       portkrxo->write(sys,14); //параметрическая часть + CRCd
       portkrxo->write(qbdata3,2); //CRCs
       portkrxo->write(inf,9); //инф. сообщение

   }

   QTimer* timerkrxo = new QTimer;
   timerkrxo->singleShot(4000,this,SLOT(resultkrxo03()));

   rec.clear();


}


void MainWindow::resultkrxo03()
{
    //=====================================================================================================
    //================================ Для команды 03 =====================================================
    //=====================================================================================================

        QString qtr, tempstr;
        QByteArray qba, qbdata2, qbdata3;

       QByteArray inf = QByteArray::fromHex("040000");
       QByteArray head =  QByteArray::fromHex("54524150");


       QString number = QString("%1").arg(ui->spinBox->text().toInt(),0,16);

       if (number.length()<2)
       {
           number.insert(0,"0");
       }


       //================ CRC CSd ===================================

       tempstr = bintohex(CRC(datatobin(inf, 0, 2))); //вычисляем CRC по инф. части
       qDebug()<<"tempstrres"<<tempstr;


       qtr.clear();
       qba.clear();
       qtr.append(tempstr.at(2));
       qtr.append(tempstr.at(3));
       qDebug()<<"qtr"<<qtr;
       qba=qtr.toLatin1();
       qDebug()<<"qba"<<qba;
       qbdata2=QByteArray::fromHex(qba); //CRC по инф. части


       qtr.clear();
       qba.clear();
       qtr.append(tempstr.at(0));
       qtr.append(tempstr.at(1));
       qDebug()<<"qtr"<<qtr;
       qba=qtr.toLatin1();
       qDebug()<<"qba"<<qba;
       qbdata2.append(QByteArray::fromHex(qba)); //[16-17] //CRC по инф. части


       QByteArray sys = QByteArray::fromHex(number.toLatin1()) + QByteArray::fromHex("0000006400000003000000");
       sys.append(qbdata2);


       //================ CRC CSs ===================================


       tempstr = bintohex(CRC(datatobin(sys, 0, 13))); //вычисляем CRC по системной части


       qtr.clear();
       qba.clear();
       qtr.append(tempstr.at(2));
       qtr.append(tempstr.at(3));
       qba=qtr.toLatin1();
       qbdata3=QByteArray::fromHex(qba);


       qtr.clear();
       qba.clear();
       qtr.append(tempstr.at(0));
       qtr.append(tempstr.at(1));
       qba=qtr.toLatin1();
       qbdata3.append(QByteArray::fromHex(qba)); //[16-17]



      if (portkrxo->isOpen()) //если порт открыт
       {
          // Для команды 03
          portkrxo->write(head,4);
          portkrxo->write(sys,14); //параметрическая часть + CRCd
          portkrxo->write(qbdata3,2); //CRCs
          portkrxo->write(inf,3); //инф. сообщение

      }

}

