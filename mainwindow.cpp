#include "mainwindow.h"
#include "./ui_mainwindow.h"

FileWorker::FileWorker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FileWorker)
{
    ui->setupUi(this);
}

FileWorker::~FileWorker()
{
    delete ui;
}
