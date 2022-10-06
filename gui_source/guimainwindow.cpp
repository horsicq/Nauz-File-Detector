/* Copyright (c) 2018-2022 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "guimainwindow.h"
#include "ui_guimainwindow.h"

GuiMainWindow::GuiMainWindow(QWidget *pParent) :
    QMainWindow(pParent),
    ui(new Ui::GuiMainWindow)
{
    ui->setupUi(this);

    setWindowTitle(XOptions::getTitle(X_APPLICATIONDISPLAYNAME,X_APPLICATIONVERSION));

    setAcceptDrops(true);

    g_xOptions.setName(X_OPTIONSFILE);

    g_xOptions.addID(XOptions::ID_VIEW_STAYONTOP,false);
    g_xOptions.addID(XOptions::ID_VIEW_STYLE,"Fusion");
    g_xOptions.addID(XOptions::ID_VIEW_LANG,"System");
    g_xOptions.addID(XOptions::ID_VIEW_QSS,"");
    g_xOptions.addID(XOptions::ID_VIEW_FONT,"");
    g_xOptions.addID(XOptions::ID_FILE_SAVELASTDIRECTORY,true);

#ifdef Q_OS_WIN
    g_xOptions.addID(XOptions::ID_FILE_CONTEXT,"*");
#endif

    StaticScanOptionsWidget::setDefaultValues(&g_xOptions);

    g_xOptions.load();

    adjustWindow();

    if(QCoreApplication::arguments().count()>1)
    {
        _scan(QCoreApplication::arguments().at(1));
    }
}

GuiMainWindow::~GuiMainWindow()
{
    g_xOptions.save();

    delete ui;
}

void GuiMainWindow::scanFile(QString sFileName)
{
    if(sFileName!="")
    {
        SpecAbstract::SCAN_RESULT scanResult={0};

        SpecAbstract::SCAN_OPTIONS options={0};

        options.bRecursiveScan=ui->checkBoxRecursiveScan->isChecked();
        options.bDeepScan=ui->checkBoxDeepScan->isChecked();
        options.bHeuristicScan=ui->checkBoxHeuristicScan->isChecked();
        options.bVerbose=ui->checkBoxVerbose->isChecked();
        options.bAllTypesScan=ui->checkBoxAllTypesScan->isChecked();

//#ifdef QT_DEBUG
//        options.bIsTest=true;
//#endif

        DialogStaticScanProcess ds(this);
        ds.setData(sFileName,&options,&scanResult);
        ds.exec();

        QString sSaveDirectory=XBinary::getResultFileName(sFileName,QString("%1.txt").arg(tr("Result")));

        ui->widgetResult->setData(scanResult,sSaveDirectory);

        g_xOptions.setLastDirectory(sFileName);
    }
}

void GuiMainWindow::_scan(QString sName)
{
    QFileInfo fi(sName);

    if(fi.isFile())
    {
        ui->lineEditFileName->setText(sName);
        
        scanFile(sName);
    }
    else if(fi.isDir())
    {
        DialogStaticScanDirectory dds(this,sName);
        dds.setGlobal(nullptr,&g_xOptions);

        dds.exec();

        adjustWindow();
    }
}

void GuiMainWindow::on_pushButtonExit_clicked()
{
    this->close();
}

void GuiMainWindow::on_pushButtonOpenFile_clicked()
{
    QString sDirectory=g_xOptions.getLastDirectory();

    QString sFileName=QFileDialog::getOpenFileName(this,tr("Open file")+QString("..."),sDirectory,tr("All files")+QString(" (*)"));

    if(!sFileName.isEmpty())
    {
        ui->lineEditFileName->setText(sFileName);
    
        if(g_xOptions.isScanAfterOpen())
        {
            _scan(sFileName);
        }
    }
}

void GuiMainWindow::on_pushButtonScan_clicked()
{
    QString sFileName=ui->lineEditFileName->text().trimmed();

    _scan(sFileName);
}

void GuiMainWindow::on_pushButtonAbout_clicked()
{
    DialogAbout di(this);

    di.exec();
}

void GuiMainWindow::dragEnterEvent(QDragEnterEvent *pEvent)
{
    pEvent->acceptProposedAction();
}

void GuiMainWindow::dragMoveEvent(QDragMoveEvent *pEvent)
{
    pEvent->acceptProposedAction();
}

void GuiMainWindow::dropEvent(QDropEvent *pEvent)
{
    const QMimeData* mimeData=pEvent->mimeData();

    if(mimeData->hasUrls())
    {
        QList<QUrl> urlList=mimeData->urls();

        if(urlList.count())
        {
            QString sFileName=urlList.at(0).toLocalFile();

            sFileName=XBinary::convertFileName(sFileName);

            if(g_xOptions.isScanAfterOpen())
            {
                _scan(sFileName);
            }
        }
    }
}

void GuiMainWindow::on_pushButtonOptions_clicked()
{
    DialogOptions dialogOptions(this,&g_xOptions,XOptions::GROUPID_FILE);

    dialogOptions.exec();

    adjustWindow();
}

void GuiMainWindow::adjustWindow()
{
    g_xOptions.adjustWindow(this);

    ui->checkBoxDeepScan->setChecked(g_xOptions.isDeepScan());
    ui->checkBoxRecursiveScan->setChecked(g_xOptions.isRecursiveScan());
    ui->checkBoxHeuristicScan->setChecked(g_xOptions.isHeuristicScan());
    ui->checkBoxAllTypesScan->setChecked(g_xOptions.isAllTypesScan());
}

void GuiMainWindow::on_pushButtonDirectoryScan_clicked()
{
    QString sFolderPath=QFileInfo(ui->lineEditFileName->text()).absolutePath();

    if(sFolderPath=="")
    {
        sFolderPath=g_xOptions.getLastDirectory();
    }

    DialogStaticScanDirectory dds(this,sFolderPath);

    dds.exec();

    adjustWindow();
}
