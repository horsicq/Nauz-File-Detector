// Copyright (c) 2018-2021 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "dialogoptions.h"
#include "ui_dialogoptions.h"

DialogOptions::DialogOptions(QWidget *pParent, XOptions *pOptions) :
    QDialog(pParent),
    ui(new Ui::DialogOptions)
{
    ui->setupUi(this);

    this->pOptions=pOptions;

    pOptions->setCheckBox(ui->checkBoxScanAfterOpen,XOptions::ID_SCANAFTEROPEN);
    pOptions->setCheckBox(ui->checkBoxRecursiveScan,XOptions::ID_RECURSIVESCAN);
    pOptions->setCheckBox(ui->checkBoxDeepScan,XOptions::ID_DEEPSCAN);
    pOptions->setCheckBox(ui->checkBoxHeuristicScan,XOptions::ID_HEURISTICSCAN);
    pOptions->setCheckBox(ui->checkBoxStayOnTop,XOptions::ID_STAYONTOP);
    pOptions->setCheckBox(ui->checkBoxSaveLastDirectory,XOptions::ID_SAVELASTDIRECTORY);

#ifdef WIN32
    ui->checkBoxContext->setChecked(pOptions->checkContext(X_APPLICATIONNAME,"*"));
#else
    ui->checkBoxContext->hide();
#endif
}

DialogOptions::~DialogOptions()
{
    delete ui;
}

void DialogOptions::on_pushButtonOK_clicked()
{
    pOptions->getCheckBox(ui->checkBoxDeepScan,XOptions::ID_DEEPSCAN);
    pOptions->getCheckBox(ui->checkBoxScanAfterOpen,XOptions::ID_SCANAFTEROPEN);
    pOptions->getCheckBox(ui->checkBoxRecursiveScan,XOptions::ID_RECURSIVESCAN);
    pOptions->getCheckBox(ui->checkBoxHeuristicScan,XOptions::ID_HEURISTICSCAN);
    pOptions->getCheckBox(ui->checkBoxSaveLastDirectory,XOptions::ID_SAVELASTDIRECTORY);
    pOptions->getCheckBox(ui->checkBoxStayOnTop,XOptions::ID_STAYONTOP);

#ifdef WIN32
    if(pOptions->checkContext(X_APPLICATIONNAME,"*")!=ui->checkBoxContext->isChecked())
    {
        if(ui->checkBoxContext->isChecked())
        {
            pOptions->registerContext(X_APPLICATIONNAME,"*",qApp->applicationFilePath());
        }
        else
        {
            pOptions->clearContext(X_APPLICATIONNAME,"*");
        }
    }
#endif

    if(pOptions->isRestartNeeded())
    {
        QMessageBox::information(this,tr("Information"),tr("Please restart the application"));
    }

    this->close();
}

void DialogOptions::on_pushButtonCancel_clicked()
{
    this->close();
}
