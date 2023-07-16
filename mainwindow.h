#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QProgressBar>

class Course
{
public:
    QString name;
    int totalProgress;
    int currentProgress;
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:

    void onLoadButtonClicked();
    void onUpdateButtonClicked();

private:
    QTextEdit *learningTextEdit;
    QLineEdit *totalProgressLineEdit;
    QLineEdit *pageLineEdit;
    QProgressBar *progressBar;


};

#endif // MAINWINDOW_H
