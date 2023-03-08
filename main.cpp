#include "mainwindow.h"

#include <QApplication>

/*int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}*/

class MyWidget : public QMainWindow, private Ui::MainWindow
{
public:
    MyWidget(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        setupUi(this);

        // QLineEdit 위젯에서 숫자 입력 시, QPushButton을 클릭하는 것과 동일한 동작을 수행하도록 합니다.
        connect(menu_lineEdit, &QLineEdit::returnPressed, menu_pushButton, &QPushButton::click);

        // QPushButton 위젯을 클릭하면, 숫자에 해당하는 함수를 호출합니다.
        connect(menu_pushButton, &QPushButton::clicked, this, &MyWidget::callFunction);
    }

private slots:
    void callFunction()
    {
        int number = menu_lineEdit->text().toInt();
        switch (number)
        {
        case 1:
            FileLoad();
            break;

        case 2:
            FilePrint();
            break;

        case 3:
            FileUpdate();
            break;

        case 4:
            FileDelele();
            break;

        case 5:
            FileFind();
            break;

        case 6:
            FileSave();
            break;

        case 7:
            Exit();
            break;

        default:
            // 입력한 숫자가 올바르지 않은 경우, 경고창을 표시합니다.
            QMessageBox::warning(this, "Error", "Invalid number!");
            break;
        }
    }

    void FileLoad()
    {
        qDebug() << "FileLoad";
    }

    void FilePrint()
    {
        qDebug() << "FilePrint";
    }

    void FileUpdate()
    {
        qDebug() << "FileUpdate";
    }

    void FileDelele()
    {
        qDebug() << "FileDelele";
    }

    void FileFind()
    {
        qDebug() << "FileFind";
    }

    void FileSave()
    {
        qDebug() << "FileSave";
    }

    void Exit()
    {
        qDebug() << "Exit";
    }

};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyWidget widget;
    widget.show();

    return app.exec();
}
