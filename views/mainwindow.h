#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>

#include "xodr.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initUI();
    void initWindow();
    void initCenterView();
    void initPtr();
    void initSignalSlots();

signals:
    void sigChangeMap(std::string);

private slots:
    void on_actionOpen_triggered();

    bool slotChangeMap(std::string);

private:
    xodr *m_pXodr;


private: // 界面
    Ui::MainWindow *ui;

    QGraphicsScene *m_pScene;
};

#endif // MAINWINDOW_H
