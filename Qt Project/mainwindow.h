#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int status;
    QString readkrxo;

signals:
    void read(QString);

private slots:











    bool compare(QString a, QStringList b, int c);
    bool comparestr(QString a, int c);
    void deviceOff();













    void on_pb_openportkrxo_clicked();

    void on_pb_closeportkrxo_clicked();

    void on_pushButton_4_clicked();

    void Readkrxo();

    void on_pushButton_7_clicked();

    void identkrxo();

    void resultkrxo();

    void resultkrxo03();

    QString CRC(QString qs);
    QString datatobin(QByteArray data, int s, int e);
    QString XOR(QString a, QString b);
    QString bintohex(QString bin);

    void parse_rxo(QString data);


































    QString IEEE754forKRXO(QString str, int b);




private:
    Ui::MainWindow *ui;

    QString FormatText(QString IEEE754);
    QString IEEE754(int b);
    QString hextobin(QString hex);
    int realint(QString string);
    int bintodec(QString bin);
    void all_lineedit_enable(bool en);



};

struct MyThread : public QThread { using QThread::msleep;};




#endif // MAINWINDOW_H
