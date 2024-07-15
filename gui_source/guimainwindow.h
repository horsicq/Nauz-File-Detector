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
#ifndef GUIMAINWINDOW_H
#define GUIMAINWINDOW_H

#include <QDragEnterEvent>
#include <QFileDialog>
#include <QMainWindow>
#include <QMimeData>

#include "../global.h"
#include "dialogabout.h"
#include "dialogoptions.h"
#include "dialognfdscandirectory.h"
#include "dialognfdscanprocess.h"
#include "xoptions.h"

namespace Ui {
class GuiMainWindow;
}

class GuiMainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit GuiMainWindow(QWidget *pParent = nullptr);
    ~GuiMainWindow() override;

private slots:
    void scanFile(const QString &sFileName);
    void _scan(const QString &sName);
    void process();
    void errorMessageSlot(const QString &sText);
    void on_pushButtonScan_clicked();
    void on_pushButtonExit_clicked();
    void on_pushButtonOpenFile_clicked();
    void on_pushButtonAbout_clicked();
    void on_pushButtonOptions_clicked();
    void adjustView();
    void on_pushButtonDirectoryScan_clicked();
    void on_toolButtonRecentFiles_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonExtra_clicked();
    void on_comboBoxType_currentIndexChanged(int nIndex);
    void on_lineEditFileName_textChanged(const QString &sString);

protected:
    void dragEnterEvent(QDragEnterEvent *pEvent) override;
    void dragMoveEvent(QDragMoveEvent *pEvent) override;
    void dropEvent(QDropEvent *pEvent) override;

private:
    Ui::GuiMainWindow *ui;
    XOptions g_xOptions;
    XShortcuts g_xShortcuts;
    QMenu *g_pRecentFilesMenu;
    QAbstractItemModel *g_pModel;
};

#endif  // GUIMAINWINDOW_H
