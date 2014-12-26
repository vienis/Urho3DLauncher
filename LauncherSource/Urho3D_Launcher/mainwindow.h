/*
===========================================================================

Copyright (C) 2014-2015 David Palacios (Hevedy) <github.com/Hevedy>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

===========================================================================
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSettings>
#include <QProcess>
#include <QDesktopWidget>
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

private slots:
    void on_PB_Launch_clicked();

    void on_PB_Panic_clicked();

    void on_PB_EEngine_clicked();

    void on_PB_EImage_clicked();

    void on_PB_E3D_clicked();

    void on_PB_EScript_clicked();

    void on_PB_SaveAll_clicked();

    void on_TB_EEngine_clicked();

    void on_TB_EImage_clicked();

    void on_TB_E3D_clicked();

    void on_TB_EScript_clicked();

    void on_CKB_SSettings_clicked();

    void on_PB_ApplyAll_clicked();

    void on_CKB_ExeOnly_clicked();

    void on_PB_ResetAll_clicked();

    void on_CB_Demo_currentIndexChanged(int index);

    void on_CB_DemoExt_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    void StartLoad();
    void LoadSettings();

    void CheckLaunch();
    int APPCheck();
    void BasicSettingsCheck();
    QString SettingsCheck();
    QString LauncherSettingsCheck();
    void SaveSettings( int _type );
    void ResetSettings( int _type );
    void StartNewProcess( QString exeName, int _type, QString _file, QString arg_0,
                          QString arg_1 );
    void KillProcess( QString processName , int ammount );
    void UIChecker( int _type, bool _status );
};

#endif // MAINWINDOW_H
