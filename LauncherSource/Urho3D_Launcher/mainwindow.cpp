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


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

//#define WIN32

int GameTimesLaunched = 0, UIStatus = 0;
bool UIExeOnly = false;
QString APPName, APPVersion, ExeName, SettingsIni;
QString EImage, E3D, EScript, EEngine;

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ), ui( new Ui::MainWindow ){
    ui->setupUi( this );
    APPName = "Urho3D Launcher";
    APPVersion = "Version: 0.0.5";
    ExeName = "Urho3DPlayer";
#ifdef WIN32
    ExeName += ".exe";
#endif
    SettingsIni = "GlobalSettings.ini";
    QSettings::setDefaultFormat(QSettings::IniFormat);
    StartLoad();
}

MainWindow::~MainWindow() {
    delete ui;
}
//Startup check
void MainWindow::StartLoad() {
    QSettings::setDefaultFormat(QSettings::IniFormat);
    LoadSettings();
    ui->L_Version->setText(APPVersion);
}

void MainWindow::LoadSettings() {
    QSettings _settings(qApp->applicationDirPath() + "/" + SettingsIni, QSettings::IniFormat);
    //Basic
    EImage  = _settings.value("Basic/EImage", "").toString();
    E3D     = _settings.value("Basic/E3D", "").toString();
    EScript = _settings.value("Basic/EScript", "").toString();
    EEngine = _settings.value("Basic/EEngine", "").toString();
    ui->LE_EImage->setText(EImage);
    ui->LE_E3D->setText(E3D);
    ui->LE_EScript->setText(EScript);
    ui->LE_EEngine->setText(EEngine);

    //Launcher
    ui->LE_Exe->setText(_settings.value("Launcher/Exe", "").toString());
    ExeName = _settings.value("Launcher/Exe", "").toString();
    ui->CKB_ExeOnly->setChecked(_settings.value("Launcher/ExeOnly", false).toBool());
    if(ui->CKB_ExeOnly->isChecked() == true) { UIChecker(1,false); }else{ UIChecker(1,true); }
    ui->CB_Demo->setCurrentIndex(_settings.value("Launcher/DemoID", 0).toInt());
    ui->CB_DemoExt->setCurrentIndex(_settings.value("Launcher/DemoExtID", 0).toInt());
    ui->LE_Demo->setText(_settings.value("Launcher/Demo", "").toString());
    ui->LE_DemoExt->setText(_settings.value("Launcher/DemoExt", "").toString());
    //Launcher Vars
    ui->LE_VarName->setText(_settings.value("Launcher/VarName", "").toString());
    ui->LE_VarPass->setText(_settings.value("Launcher/VarPass", "").toString());
    ui->LE_VarIPV4->setText(_settings.value("Launcher/VarIPv4", "").toString());
    ui->LE_VarPort->setText(_settings.value("Launcher/VarPort", "").toString());
    ui->LE_VarCustom->setText(_settings.value("Launcher/VarCustom", "").toString());
    ui->CKB_IsVarHost->setChecked(_settings.value("Launcher/IsVarHost", false).toBool());

    //Settings Part 1
    ui->CB_Settings->setCurrentIndex(_settings.value("Settings/Settings", 0).toInt());
    ui->CB_Resolution->setCurrentIndex(_settings.value("Settings/Resolution", 0).toInt());
    ui->CB_Display->setCurrentIndex(_settings.value("Settings/Display", 0).toInt());
    ui->CKB_Vsync->setChecked(_settings.value("Settings/Vsync", false).toBool());
    //Settings Part 2
    ui->CKB_SSettings->setChecked(_settings.value("Settings/SSettings", false).toBool());
    ui->CKB_SLauncher->setChecked(_settings.value("Settings/SLauncher", false).toBool());
    ui->CKB_SBasic->setChecked(_settings.value("Settings/SBasic", false).toBool());

    //Basic B
    ui->TE_Notes->setText(_settings.value("BasicB/Notes", "").toString());
    ui->TE_Ideas->setText(_settings.value("BasicB/Ideas", "").toString());
    ui->TE_Bugs->setText(_settings.value("BasicB/Bugs", "").toString());

}

//UI Check and change
void MainWindow::UIChecker( int _type, bool _status ) {
    switch (_type) {
    case 1:
        ui->FR_OnlyExe->setEnabled(_status);
        UIExeOnly = _status;
        break;
    case 2:

        break;
    default:
        break;
    }

}

//Root check
void MainWindow::CheckLaunch() {
    QString LauncherLine = 0;

    if(ui->CKB_ExeOnly->isChecked() != true) {
        if(ui->CB_DemoExt->currentIndex() == 0 || ui->CB_DemoExt->currentIndex() == 1 || ui->CB_DemoExt->currentIndex() == 2) {
            if(ui->CB_DemoExt->currentIndex() == 0 || ui->CB_DemoExt->currentIndex() == 2) {
                StartNewProcess(ui->LE_Exe->text(), 1, " Scripts/" + ui->LE_Demo->text() + ui->LE_DemoExt->text() + " ",
                                SettingsCheck(), LauncherSettingsCheck()); }
            if(ui->CB_DemoExt->currentIndex() == 1) {
                StartNewProcess(ui->LE_Exe->text(), 1, " LuaScripts/" + ui->LE_Demo->text() + ui->LE_DemoExt->text() + " ",
                                SettingsCheck(), LauncherSettingsCheck()); }
        }else{
            StartNewProcess(ui->LE_Exe->text(), 1, " Scripts/" + ui->LE_Demo->text() + ui->LE_DemoExt->text() + " ",
                            SettingsCheck(), LauncherSettingsCheck());
        }
    } else {
        StartNewProcess(ui->LE_Exe->text(), 1, " ",SettingsCheck(), ""); }

}

//Type of App to launch
int MainWindow::APPCheck() {
    /*
    switch (control) {
    case value:

        break;
    default:
        break;
    }
*/
    return 0;
}

//ThirtyParty Apps and texbox
void MainWindow::BasicSettingsCheck() {



}

//Check settings of graphics and saves
QString MainWindow::SettingsCheck() {
    QString _final = "";
    QDesktopWidget desktopsizes;
    QRect mainScreenS = desktopsizes.availableGeometry(desktopsizes.primaryScreen());
    int screenX = 1024,screenY = 768;
    screenX = mainScreenS.width();
    screenY = mainScreenS.height();

    //Display Resolution
    switch(ui->CB_Resolution->currentIndex()){
        case 0: _final += "-x " + screenX; _final += " -y " + screenY + QString(" "); break;
        case 1: _final += "-x 1024 -y 768 "; break;
        case 2: _final += "-x 1152 -y 864 "; break;
        case 3: _final += "-x 1280 -y 720 "; break;
        case 4: _final += "-x 1280 -y 768 "; break;
        case 5: _final += "-x 1280 -y 800 "; break;
        case 6: _final += "-x 1280 -y 960 "; break;
        case 7: _final += "-x 1280 -y 1024 "; break;
        case 8: _final += "-x 1360 -y 768 "; break;
        case 9: _final += "-x 1366 -y 768 "; break;
        case 10: _final += "-x 1440 -y 900 "; break;
        case 11: _final += "-x 1600 -y 900 "; break;
        case 12: _final += "-x 1600 -y 1024 "; break;
        case 13: _final += "-x 1680 -y 1050 "; break;
        case 14: _final += "-x 1768 -y 992 "; break;
        case 15: _final += "-x 1920 -y 1080 "; break;
        case 16: _final += "-x 1920 -y 1200 "; break;
        case 17: _final += "-x 2048 -y 1152 "; break;
        case 18: _final += "-x 2560 -y 1440 "; break;
        case 19: _final += " "; break;
        default: _final += "-x 1024 -y 768 "; break; }

    //Window type [0=Window//1=Fullscreen//2=Borderless
    if(ui->CB_Display->currentIndex() == 0) { _final += ""; }
    else if(ui->CB_Display->currentIndex() == 1) { _final += "-w "; }
    else if(ui->CB_Display->currentIndex() == 2) { _final += "-borderless "; }

    //Check Vsync
    if(ui->CKB_Vsync->isChecked() == true) { _final += "-v "; }

    //Graphics [0=Minimun//1=Low//2=Medium//3=High//4=Very High//5=Ultra]
    if(ui->CB_Settings->currentIndex() == 0) { _final += "-noshadows -QMinimun"; }
    else if(ui->CB_Settings->currentIndex() == 1) { _final += "-lqshadows -QLow"; }
    else if(ui->CB_Settings->currentIndex() == 2) { _final += "-m 1 -QMedium";}
    else if(ui->CB_Settings->currentIndex() == 3) { _final += "-m 2 -QHigh"; }
    else if(ui->CB_Settings->currentIndex() == 4) { _final += "-m 4 -QVHigh -QFD"; }
    else if(ui->CB_Settings->currentIndex() == 5) { _final += "-m 8 -QUltra -QFD"; }

    return _final;
}

//Check settings of launcher vars
QString MainWindow::LauncherSettingsCheck() {
    QString _final = "";

    _final += " -User " + ui->LE_VarName->text();
    _final += " -Pass " + ui->LE_VarPass->text();
    _final += " -NetIP " + ui->LE_VarIPV4->text();
    _final += " -NetPort " + ui->LE_VarPort->text();
    _final += " " + ui->LE_VarCustom->text();
    return _final;
}

//Save Graphic settings and launcher settings
void MainWindow::SaveSettings( int _type ) {
    QSettings _settings(qApp->applicationDirPath() + "/" + SettingsIni, QSettings::IniFormat);
    switch (_type) {
    case 0: //No idea
        break;
    case 1: //Launcher Settings
        _settings.setValue("Launcher/Exe", ui->LE_Exe->text());
        _settings.setValue("Launcher/ExeOnly", ui->CKB_ExeOnly->isChecked());
        _settings.setValue("Launcher/DemoID", ui->CB_Demo->currentIndex());
        _settings.setValue("Launcher/DemoExtID", ui->CB_DemoExt->currentIndex());
        _settings.setValue("Launcher/Demo", ui->LE_Demo->text());
        _settings.setValue("Launcher/DemoExt", ui->LE_DemoExt->text());
        //Launcher Vars
        _settings.setValue("Launcher/VarName", ui->LE_VarName->text());
        _settings.setValue("Launcher/VarPass", ui->LE_VarPass->text());
        _settings.setValue("Launcher/VarIPv4", ui->LE_VarIPV4->text());
        _settings.setValue("Launcher/VarPort", ui->LE_VarPort->text());
        _settings.setValue("Launcher/VarCustom", ui->LE_VarCustom->text());
        _settings.setValue("Launcher/IsVarHost", ui->CKB_IsVarHost->isChecked());
        break;
    case 2: //Global Gameplay Settings
        _settings.setValue("Settings/Settings", ui->CB_Settings->currentIndex());
        _settings.setValue("Settings/Resolution", ui->CB_Resolution->currentIndex());
        _settings.setValue("Settings/Display", ui->CB_Display->currentIndex());
        _settings.setValue("Settings/Vsync", ui->CKB_Vsync->isChecked());
        //Settings Part 2
        //_settings.setValue("Settings/SSettings", ui->CKB_SSettings->isChecked());
        //_settings.setValue("Settings/SLauncher", ui->CKB_SLauncher->isChecked());
        //_settings.setValue("Settings/SBasic", ui->CKB_SBasic->isChecked());
        break;
    case 3: //Basic Settings
        EImage  = ui->LE_EImage->text();
        E3D     = ui->LE_E3D->text();
        EScript = ui->LE_EScript->text();
        EEngine = ui->LE_EEngine->text();
        _settings.setValue("Basic/EImage", EImage);
        _settings.setValue("Basic/E3D", E3D);
        _settings.setValue("Basic/EScript", EScript);
        _settings.setValue("Basic/EEngine", EEngine);
        _settings.setValue("BasicB/Notes", ui->TE_Notes->toPlainText());
        _settings.setValue("BasicB/Ideas", ui->TE_Ideas->toPlainText());
        _settings.setValue("BasicB/Bugs", ui->TE_Bugs->toPlainText());
        break;
    default: //0
        break;
    }
    _settings.setValue("Settings/SSettings", ui->CKB_SSettings->isChecked());
    _settings.setValue("Settings/SLauncher", ui->CKB_SLauncher->isChecked());
    _settings.setValue("Settings/SBasic", ui->CKB_SBasic->isChecked());

}

//Default settings and launcher vars
void MainWindow::ResetSettings( int _type ) {
    QSettings _settings(qApp->applicationDirPath() + "/" + "GlobalSettingsReset.ini", QSettings::IniFormat);
    //Basic
    if(_type == 3) {
        EImage  = _settings.value("Basic/EImage", "").toString();
        E3D     = _settings.value("Basic/E3D", "").toString();
        EScript = _settings.value("Basic/EScript", "").toString();
        EEngine = _settings.value("Basic/EEngine", "").toString();
        ui->LE_EImage->setText(EImage);
        ui->LE_E3D->setText(E3D);
        ui->LE_EScript->setText(EScript);
        ui->LE_EEngine->setText(EEngine);
        //Basic B
        ui->TE_Notes->setText(_settings.value("BasicB/Notes", "").toString());
        ui->TE_Ideas->setText(_settings.value("BasicB/Ideas", "").toString());
        ui->TE_Bugs->setText(_settings.value("BasicB/Bugs", "").toString());
    } else if(_type == 1){
        //Launcher
        ui->LE_Exe->setText(_settings.value("Launcher/Exe", "Urho3DPlayer.exe").toString());
        ExeName = _settings.value("Launcher/Exe", "Urho3DPlayer.exe").toString();
        ui->CKB_ExeOnly->setChecked(_settings.value("Launcher/ExeOnly", false).toBool());
        if(ui->CKB_ExeOnly->isChecked() == true) { UIChecker(1,false); }else{ UIChecker(1,true); }
        ui->CB_Demo->setCurrentIndex(_settings.value("Launcher/DemoID", 1).toInt());
        ui->CB_DemoExt->setCurrentIndex(_settings.value("Launcher/DemoExtID", 0).toInt());
        ui->LE_Demo->setText(_settings.value("Launcher/Demo", "01_HelloWorld").toString());
        ui->LE_DemoExt->setText(_settings.value("Launcher/DemoExt", ".as").toString());
        //Launcher Vars
        ui->LE_VarName->setText(_settings.value("Launcher/VarName", "").toString());
        ui->LE_VarPass->setText(_settings.value("Launcher/VarPass", "").toString());
        ui->LE_VarIPV4->setText(_settings.value("Launcher/VarIPv4", "").toString());
        ui->LE_VarPort->setText(_settings.value("Launcher/VarPort", "").toString());
        ui->LE_VarCustom->setText(_settings.value("Launcher/VarCustom", "").toString());
        ui->CKB_IsVarHost->setChecked(_settings.value("Launcher/IsVarHost", false).toBool());
    } else if(_type == 2){
        //Settings Part 1
        ui->CB_Settings->setCurrentIndex(_settings.value("Settings/Settings", 0).toInt());
        ui->CB_Resolution->setCurrentIndex(_settings.value("Settings/Resolution", 0).toInt());
        ui->CB_Display->setCurrentIndex(_settings.value("Settings/Display", 0).toInt());
        ui->CKB_Vsync->setChecked(_settings.value("Settings/Vsync", false).toBool());
        //Settings Part 2
        ui->CKB_SSettings->setChecked(_settings.value("Settings/SSettings", false).toBool());
        ui->CKB_SLauncher->setChecked(_settings.value("Settings/SLauncher", false).toBool());
        ui->CKB_SBasic->setChecked(_settings.value("Settings/SBasic", false).toBool());
    }


}

//Launch new process
void MainWindow::StartNewProcess( QString exeName, int _type, QString _file, QString arg_0,
                                  QString arg_1 ) {
    QProcess *newProcess = new QProcess(this);
    QFileInfo getExe = exeName;
    if(_type == 4){
        //TODO error, the QFileInfo no detect dir if have spaces (QT 5.1 Bug)
        newProcess->setWorkingDirectory(QDir::toNativeSeparators(getExe.absolutePath()));
        qDebug() << exeName;
        qDebug() << QDir::toNativeSeparators(getExe.absolutePath());
        newProcess->start(exeName);
    }else{
    newProcess->start(exeName + _file + arg_0 + arg_1); }

}

void MainWindow::KillProcess( QString processName , int ammount ) {
    //QProcess killProcess;
    QString _killProcess = "taskkill /f /im " + processName;
    //char* _kProcess = _killProcess.toStdString().c_str();
    for(int a = 0 ; ammount < a ; ++a ) {

        //killProcess.start("processName");
        //killProcess.waitForFinished();
        system(_killProcess.toUtf8().constData());
    }

}

/*
================================================
UI Controls
================================================
*/

//Global UI
void MainWindow::on_PB_Launch_clicked() {
    CheckLaunch();
}

void MainWindow::on_PB_Panic_clicked() {
    ui->PB_Panic->setEnabled(false);
    KillProcess(ExeName,1);
    ui->PB_Panic->setEnabled(true);
}

void MainWindow::on_PB_EEngine_clicked() {
    if(ui->LE_EEngine->text() == "") {
        BasicSettingsCheck();
    }else{
    if(EEngine != ui->LE_EEngine->text()) {
        StartNewProcess(QDir::toNativeSeparators(ui->LE_EEngine->text()),4,"","",""); }
    StartNewProcess(EEngine,4,"","","");
    }
}

void MainWindow::on_PB_EImage_clicked() {
    if(ui->LE_EImage->text() == "") {
        BasicSettingsCheck();
    }else{
    if(EImage != ui->LE_EImage->text()) {
        StartNewProcess(QDir::toNativeSeparators(ui->LE_EImage->text()),4,"","",""); }
    StartNewProcess(EImage,4,"","","");
    }
}

void MainWindow::on_PB_E3D_clicked() {
    if(ui->LE_E3D->text() == "") {
        BasicSettingsCheck();
    }else{
    if(E3D != ui->LE_E3D->text()) {
        StartNewProcess(QDir::toNativeSeparators(ui->LE_E3D->text()),4,"","",""); }
    StartNewProcess(E3D,4,"","","");
    }
}

void MainWindow::on_PB_EScript_clicked() {
    if(ui->LE_EScript->text() == "") {
        BasicSettingsCheck();
    }else{
        if(EScript != ui->LE_EScript->text()) {
            StartNewProcess(QDir::toNativeSeparators(ui->LE_EScript->text()),4,"","",""); }
        StartNewProcess(EScript,4,"","","");
    }
}


void MainWindow::on_PB_SaveAll_clicked()
{
    SaveSettings(3);
}

void MainWindow::on_TB_EEngine_clicked()
{
    ui->LE_EEngine->setText(QFileDialog::getOpenFileName(this, tr("Open Editor Engine File"),"",tr("Files (*.*)")));
}

void MainWindow::on_TB_EImage_clicked()
{
   ui->LE_EImage->setText(QFileDialog::getOpenFileName(this, tr("Open Image Editor File"),"",tr("Files (*.*)")));
}

void MainWindow::on_TB_E3D_clicked()
{
    ui->LE_E3D->setText(QFileDialog::getOpenFileName(this, tr("Open Editor 3D File"),"",tr("Files (*.*)")));
}

void MainWindow::on_TB_EScript_clicked()
{
    ui->LE_EScript->setText(QFileDialog::getOpenFileName(this, tr("Open Editor Script File"),"",tr("Files (*.*)")));
}

//Settings UI
void MainWindow::on_CKB_SSettings_clicked()
{

}

void MainWindow::on_PB_ApplyAll_clicked()
{
    SaveSettings(0);
    if(ui->CKB_SLauncher->isChecked() == true) { SaveSettings(1); }
    if(ui->CKB_SSettings->isChecked() == true) { SaveSettings(2); }
    if(ui->CKB_SBasic->isChecked() == true) { SaveSettings(3); }
}

void MainWindow::on_CKB_ExeOnly_clicked()
{
    if(ui->CKB_ExeOnly->isChecked() == true) {
        UIChecker(1,false);
    }else{
        UIChecker(1,true);
    }
}

void MainWindow::on_PB_ResetAll_clicked()
{
    if(ui->CKB_SLauncher->isChecked() == true) { ResetSettings(1); }
    if(ui->CKB_SSettings->isChecked() == true) { ResetSettings(2); }
    if(ui->CKB_SBasic->isChecked() == true) { ResetSettings(3); }
}

void MainWindow::on_CB_Demo_currentIndexChanged(int index)
{
    ui->LE_Demo->setText(ui->CB_Demo->currentText());
}

void MainWindow::on_CB_DemoExt_currentIndexChanged(int index)
{
    ui->LE_DemoExt->setText(ui->CB_DemoExt->currentText());
}
