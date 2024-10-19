#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_open_files,&QPushButton::clicked,this,&MainWindow::openFiles);
    connect(ui->btn_save_file,&QPushButton::clicked,this,&MainWindow::saveFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFiles()
{
    if(ui->select_multiple_files->isChecked())
    {
        auto file_names=QFileDialog::getOpenFileNames(this,"Select Files");
        ui->combo_box->addItems(file_names);
    }else
    {
        auto file_name=QFileDialog::getOpenFileName(this,"Open File");
        ui->combo_box->addItem(file_name);
    };
};

void MainWindow::saveFile()
{
    auto file_name=QFileDialog::getSaveFileName(this,"Save All Files in Combo Box");
    QFile file(file_name);
    file.open(QFile::OpenModeFlag::WriteOnly);
    if(file.isOpen())
    {
        for(int i=0;i<ui->combo_box->count();++i)
        {
            file.write((ui->combo_box->itemText(i).toStdString()+"\n").c_str());
        };
        file.close();
    }else
    {
        qDebug()<<"Invalid "<<file_name;
    };
};
