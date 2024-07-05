/* Copyright (c) 2018-2024 hors<horsicq@gmail.com>
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

GuiMainWindow::GuiMainWindow(QWidget *pParent) : QMainWindow(pParent), ui(new Ui::GuiMainWindow)
{
    ui->setupUi(this);

    g_pModel = nullptr;

    setWindowTitle(XOptions::getTitle(X_APPLICATIONDISPLAYNAME, X_APPLICATIONVERSION));

    setAcceptDrops(true);

    g_xOptions.setName(X_OPTIONSFILE);

    g_xOptions.addID(XOptions::ID_VIEW_STAYONTOP, false);
    g_xOptions.addID(XOptions::ID_VIEW_STYLE, "Fusion");
    g_xOptions.addID(XOptions::ID_VIEW_LANG, "System");
    g_xOptions.addID(XOptions::ID_VIEW_QSS, "");
    g_xOptions.addID(XOptions::ID_VIEW_FONT_CONTROLS, XOptions::getDefaultFont().toString());
    g_xOptions.addID(XOptions::ID_VIEW_FONT_TABLEVIEWS, XOptions::getMonoFont().toString());
    g_xOptions.addID(XOptions::ID_VIEW_FONT_TREEVIEWS, XOptions::getDefaultFont().toString());
    g_xOptions.addID(XOptions::ID_VIEW_FONT_TEXTEDITS, XOptions::getMonoFont().toString());
    g_xOptions.addID(XOptions::ID_FILE_SAVELASTDIRECTORY, true);
    g_xOptions.addID(XOptions::ID_FILE_SAVERECENTFILES, true);

#ifdef Q_OS_WIN
    g_xOptions.addID(XOptions::ID_FILE_CONTEXT, "*");
#endif

    NFDOptionsWidget::setDefaultValues(&g_xOptions);

    g_xOptions.load();

    connect(&g_xOptions, SIGNAL(openFile(QString)), this, SLOT(_scan(QString)));
    connect(&g_xOptions, SIGNAL(errorMessage(QString)), this, SLOT(errorMessageSlot(QString)));

    g_pRecentFilesMenu = g_xOptions.createRecentFilesMenu(this);

    ui->toolButtonRecentFiles->setEnabled(g_xOptions.getRecentFiles().count());

    adjustView();

    if (QCoreApplication::arguments().count() > 1) {
        _scan(QCoreApplication::arguments().at(1));
    }
}

GuiMainWindow::~GuiMainWindow()
{
    g_xOptions.save();

    delete ui;
}

void GuiMainWindow::scanFile(const QString &sFileName)
{
    if (sFileName != "") {
        SpecAbstract::SCAN_RESULT scanResult = {0};

        SpecAbstract::SCAN_OPTIONS options = {0};

        options.fileType = (XBinary::FT)(ui->comboBoxType->currentData().toInt());
        options.bIsRecursiveScan = ui->checkBoxRecursiveScan->isChecked();
        options.bIsDeepScan = ui->checkBoxDeepScan->isChecked();
        options.bIsHeuristicScan = ui->checkBoxHeuristicScan->isChecked();
        options.bIsVerbose = ui->checkBoxVerbose->isChecked();
        options.bAllTypesScan = ui->checkBoxAllTypesScan->isChecked();

        // #ifdef QT_DEBUG
        //         options.bIsTest=true;
        // #endif

        DialogNFDScanProcess ds(this);
        ds.setData(sFileName, &options, &scanResult);
        ds.exec();

        ui->labelTime->clear();

        QAbstractItemModel *pOldModel = ui->treeViewResult->model();

        QList<XBinary::SCANSTRUCT> _listRecords = SpecAbstract::convert(&(scanResult.listRecords));

        bool bHighlight = g_xOptions.getValue(XOptions::ID_SCAN_HIGHLIGHT).toBool();

        g_pModel = new ScanItemModel(&(_listRecords), 1, bHighlight);
        ui->treeViewResult->setModel(g_pModel);
        ui->treeViewResult->expandAll();

        delete pOldModel;  // TODO Thread

        ui->labelTime->setText(QString("%1 %2").arg(QString::number(scanResult.nScanTime), tr("msec")));

        g_xOptions.setLastFileName(sFileName);

        ui->toolButtonRecentFiles->setEnabled(g_xOptions.getRecentFiles().count());
    }
}

void GuiMainWindow::_scan(const QString &sName)
{
    QFileInfo fi(sName);

    if (fi.isFile()) {
        ui->lineEditFileName->setText(QDir().toNativeSeparators(sName));

        XFormats::setFileTypeComboBox(XBinary::FT_UNKNOWN, sName, ui->comboBoxType);

        scanFile(sName);
    } else if (fi.isDir()) {
        DialogNFDScanDirectory dds(this, sName);
        dds.setGlobal(nullptr, &g_xOptions);

        dds.exec();

        adjustView();
    }
}

void GuiMainWindow::errorMessageSlot(const QString &sText)
{
    QMessageBox::critical(this, tr("Error"), sText);
}

void GuiMainWindow::on_pushButtonExit_clicked()
{
    this->close();
}

void GuiMainWindow::on_pushButtonOpenFile_clicked()
{
    QString sDirectory = g_xOptions.getLastDirectory();

    QString sFileName = QFileDialog::getOpenFileName(this, tr("Open file") + QString("..."), sDirectory, tr("All files") + QString(" (*)"));

    if (!sFileName.isEmpty()) {
        ui->lineEditFileName->setText(sFileName);

        if (g_xOptions.isScanAfterOpen()) {
            _scan(sFileName);
        }
    }
}

void GuiMainWindow::on_pushButtonScan_clicked()
{
    QString sFileName = ui->lineEditFileName->text().trimmed();

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
    const QMimeData *mimeData = pEvent->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();

        if (urlList.count()) {
            QString sFileName = urlList.at(0).toLocalFile();

            sFileName = XBinary::convertFileName(sFileName);

            if (g_xOptions.isScanAfterOpen()) {
                _scan(sFileName);
            }
        }
    }
}

void GuiMainWindow::on_pushButtonOptions_clicked()
{
    DialogOptions dialogOptions(this, &g_xOptions, XOptions::GROUPID_FILE);

    dialogOptions.exec();

    adjustView();
}

void GuiMainWindow::adjustView()
{
    g_xOptions.adjustWindow(this);

    ui->checkBoxDeepScan->setChecked(g_xOptions.isDeepScan());
    ui->checkBoxRecursiveScan->setChecked(g_xOptions.isRecursiveScan());
    ui->checkBoxHeuristicScan->setChecked(g_xOptions.isHeuristicScan());
    ui->checkBoxAllTypesScan->setChecked(g_xOptions.isAllTypesScan());
}

void GuiMainWindow::on_pushButtonDirectoryScan_clicked()
{
    QString sFolderPath = QFileInfo(ui->lineEditFileName->text()).absolutePath();

    if (sFolderPath == "") {
        sFolderPath = g_xOptions.getLastDirectory();
    }

    DialogNFDScanDirectory dds(this, sFolderPath);

    dds.exec();

    adjustView();
}

void GuiMainWindow::on_toolButtonRecentFiles_clicked()
{
    g_pRecentFilesMenu->exec(QCursor::pos());

    ui->toolButtonRecentFiles->setEnabled(g_xOptions.getRecentFiles().count());
}

void GuiMainWindow::on_pushButtonClear_clicked()
{
    QAbstractItemModel *pOldModel = ui->treeViewResult->model();

    ui->treeViewResult->setModel(nullptr);

    delete pOldModel;  // TODO Thread

    ui->labelTime->clear();
}

void GuiMainWindow::on_pushButtonSave_clicked()
{
    QAbstractItemModel *pModel = ui->treeViewResult->model();

    if (pModel) {
        QString sSaveDirectory = XBinary::getResultFileName(ui->lineEditFileName->text(), QString("%1.txt").arg(tr("Result")));
        DialogNFDScanProcess::saveResult(this, (ScanItemModel *)pModel, sSaveDirectory);
    }
}

void GuiMainWindow::on_pushButtonExtra_clicked()
{
    if (g_pModel) {
        DialogTextInfo dialogTextInfo(this);

        QString sText = ((ScanItemModel *)g_pModel)->toFormattedString();

        dialogTextInfo.setText(sText);

        dialogTextInfo.exec();
    }
}
