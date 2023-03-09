#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FileWorker : public QMainWindow
{
    Q_OBJECT

public:
    FileWorker(QWidget *parent = nullptr);
    ~FileWorker();

private:
    Ui::FileWorker *ui;
};
#endif // MAINWINDOW_H
