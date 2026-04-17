/* Copyright (c) 2018-2026 hors<horsicq@gmail.com>
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

#ifdef USE_XSIMD
    xsimd_init();
#endif

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
    if (!g_xOptions.isNative()) {
        g_xOptions.addID(XOptions::ID_FILE_CONTEXT, "*");
    }
#endif

    g_xOptions.addID(XOptions::ID_FEATURE_READBUFFERSIZE, 8 * 1024);
    g_xOptions.addID(XOptions::ID_FEATURE_FILEBUFFERSIZE, 2 * 1024 * 1024);

#ifdef USE_XSIMD
#ifdef Q_PROCESSOR_X86
    g_xOptions.addID(XOptions::ID_FEATURE_SSE2, true);
    g_xOptions.addID(XOptions::ID_FEATURE_AVX2, true);
#endif
#endif

    g_xOptions.addID(XOptions::ID_SCAN_ENGINE_NFD_ENABLED, true);

    XScanEngineOptionsWidget::setDefaultValues(&g_xOptions);

    g_xOptions.load();

    g_xShortcuts.setName(X_SHORTCUTSFILE);
    g_xShortcuts.setNative(g_xOptions.isNative());

    g_xShortcuts.load();

    connect(&g_xOptions, SIGNAL(openFile(QString)), this, SLOT(_scan(QString)));
    connect(&g_xOptions, SIGNAL(errorMessage(QString)), this, SLOT(errorMessageSlot(QString)));

    g_pRecentFilesMenu = g_xOptions.createRecentFilesMenu(this);

    ui->toolButtonRecentFiles->setEnabled(g_xOptions.getRecentFiles().count());

    ui->widgetResult->setGlobal(&g_xShortcuts, &g_xOptions);

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

void GuiMainWindow::_scan(const QString &sFileName)
{
    QFileInfo fi(sFileName);

    if (fi.isFile()) {
        bool bBlock1 = ui->lineEditFileName->blockSignals(true);
        ui->lineEditFileName->setText(QDir().toNativeSeparators(sFileName));
        ui->lineEditFileName->blockSignals(bBlock1);

        ui->widgetResult->setData(sFileName, g_xOptions.isScanAfterOpen());

        g_xOptions.setLastFileName(sFileName);

        ui->toolButtonRecentFiles->setEnabled(g_xOptions.getRecentFiles().count());
    } else if (fi.isDir()) {
        DialogXScanEngineDirectory dds(this);
        dds.setGlobal(&g_xShortcuts, &g_xOptions);

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
    dialogOptions.setGlobal(&g_xShortcuts, &g_xOptions);

    dialogOptions.exec();

    adjustView();
}

void GuiMainWindow::on_toolButtonRecentFiles_clicked()
{
    g_pRecentFilesMenu->exec(QCursor::pos());

    ui->toolButtonRecentFiles->setEnabled(g_xOptions.getRecentFiles().count());
}

void GuiMainWindow::adjustView()
{
    if (g_xOptions.isIDPresent(XOptions::ID_VIEW_STAYONTOP)) {
        g_xOptions.adjustStayOnTop(this);
    }

    g_xOptions.adjustWidget(this, XOptions::ID_VIEW_FONT_CONTROLS);
    ui->widgetResult->adjustView();
}


