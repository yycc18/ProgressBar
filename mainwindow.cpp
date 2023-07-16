#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QLabel>



MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    learningTextEdit = new QTextEdit;
    learningTextEdit->setFixedHeight(100);
    layout->addWidget(learningTextEdit);

    QHBoxLayout *totalProgressLayout = new QHBoxLayout;
    QLabel *totalProgressLabel = new QLabel("总进度:");
    totalProgressLineEdit = new QLineEdit;
    totalProgressLayout->addWidget(totalProgressLabel);
    totalProgressLayout->addWidget(totalProgressLineEdit);

    QHBoxLayout *currentProgressLayout = new QHBoxLayout;
    QLabel *currentProgressLabel = new QLabel("当前进度:");
    pageLineEdit = new QLineEdit;
    currentProgressLayout->addWidget(currentProgressLabel);
    currentProgressLayout->addWidget(pageLineEdit);


    QPushButton *loadButton = new QPushButton("加载");
    QPushButton *updateButton = new QPushButton("更新");
    progressBar = new QProgressBar;

    layout->addLayout(totalProgressLayout);
    layout->addLayout(currentProgressLayout);

    layout->addWidget(loadButton);
    layout->addWidget(updateButton);
    layout->addWidget(progressBar);

    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateButtonClicked);
}


void MainWindow::onLoadButtonClicked()
{
    QFile inputFile("saved_content.txt");
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&inputFile);

        QString learningContent = in.readLine();
        learningTextEdit->setPlainText(learningContent);

        QString totalProgress = in.readLine();
        totalProgressLineEdit->setText(totalProgress);

        QString currentPage = in.readLine();
        pageLineEdit->setText(currentPage);

        int total = totalProgress.toInt();
        int current = currentPage.toInt();
        int progress = static_cast<int>((static_cast<double>(current) / total) * 100);

        progressBar->setValue(progress);  // 设置进度条的值

        inputFile.close();
        qDebug() << "内容已加载！";
    }
    else
    {
        qDebug() << "加载失败！";
    }
}

void MainWindow::onUpdateButtonClicked()
{
    QString learningContent = learningTextEdit->toPlainText();

    QFile outputFile("saved_content.txt");
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&outputFile);
        out << learningContent << '\n';

        QString totalProgress = totalProgressLineEdit->text();
        out << totalProgress << '\n';

        QString currentPage = pageLineEdit->text();
        out << currentPage << '\n';

        outputFile.close();
        qDebug() << "内容已保存！";
    }
    else
    {
        qDebug() << "保存失败！";
    }
    QFile inputFile("saved_content.txt");
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&inputFile);

        QString learningContent = in.readLine();
        learningTextEdit->setPlainText(learningContent);

        QString totalProgress = in.readLine();
        totalProgressLineEdit->setText(totalProgress);

        QString currentPage = in.readLine();
        pageLineEdit->setText(currentPage);

        int total = totalProgress.toInt();
        int current = currentPage.toInt();
        int progress = static_cast<int>((static_cast<double>(current) / total) * 100);

        progressBar->setValue(progress);  // 设置进度条的值

        inputFile.close();
        qDebug() << "内容已更新！";
    }
    else
    {
        qDebug() << "更新失败！";
    }
}
