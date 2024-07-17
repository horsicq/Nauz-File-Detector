/* Copyright (c) 2018-2023 hors<horsicq@gmail.com>
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
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>

#include "../global.h"
#include "scanitemmodel.h"
#include "specabstract.h"
#include "xoptions.h"

XOptions::CR ScanFiles(QList<QString> *pListArgs, XScanEngine::SCAN_OPTIONS *pScanOptions)
{
    XOptions::CR result = XOptions::CR_SUCCESS;

    QList<QString> listFileNames;

    for (qint32 i = 0; i < pListArgs->count(); i++) {
        QString sFileName = pListArgs->at(i);

        if (QFileInfo::exists(sFileName)) {
            XBinary::findFiles(sFileName, &listFileNames);
        } else {
            printf("Cannot find: %s\n", sFileName.toUtf8().data());

            result = XOptions::CR_CANNOTFINDFILE;
        }
    }

    bool bShowFileName = listFileNames.count() > 1;

    for (qint32 i = 0; i < listFileNames.count(); i++) {
        QString sFileName = listFileNames.at(i);

        if (bShowFileName) {
            printf("%s:\n", sFileName.toUtf8().data());
        }

        XScanEngine::SCAN_RESULT scanResult = SpecAbstract().scanFile(sFileName, pScanOptions);

        ScanItemModel model(pScanOptions, &(scanResult.listRecords), 1);

        XBinary::FORMATTYPE formatType = XBinary::FORMATTYPE_TEXT;

        if (pScanOptions->bResultAsCSV) formatType = XBinary::FORMATTYPE_CSV;
        else if (pScanOptions->bResultAsJSON) formatType = XBinary::FORMATTYPE_JSON;
        else if (pScanOptions->bResultAsTSV) formatType = XBinary::FORMATTYPE_TSV;
        else if (pScanOptions->bResultAsXML) formatType = XBinary::FORMATTYPE_XML;
        else if (pScanOptions->bResultAsPlainText) formatType = XBinary::FORMATTYPE_PLAINTEXT;

        if (formatType != XBinary::FORMATTYPE_TEXT) {
            printf("%s\n", model.toString(formatType).toUtf8().data());
        } else {
            // Colored text
            model.coloredOutput();
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    qint32 nResult = XOptions::CR_SUCCESS;

    QCoreApplication::setOrganizationName(X_ORGANIZATIONNAME);
    QCoreApplication::setOrganizationDomain(X_ORGANIZATIONDOMAIN);
    QCoreApplication::setApplicationName(X_APPLICATIONNAME);
    QCoreApplication::setApplicationVersion(X_APPLICATIONVERSION);

    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    QString sDescription;
    sDescription.append(QString("%1 v%2\n").arg(X_APPLICATIONDISPLAYNAME, X_APPLICATIONVERSION));
    sDescription.append(QString("%1\n").arg("Copyright(C) 2017-2024 hors<horsicq@gmail.com> Web: http://ntinfo.biz"));
    parser.setApplicationDescription(sDescription);
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("target", "The file or directory to open.");

    QCommandLineOption clRecursiveScan(QStringList() << "r"
                                                     << "recursivescan",
                                       "Recursive scan.");
    QCommandLineOption clDeepScan(QStringList() << "d"
                                                << "deepscan",
                                  "Deep scan.");
    QCommandLineOption clHeuristicScan(QStringList() << "u"
                                                     << "heuristicscan",
                                       "Heuristic scan.");
    QCommandLineOption clVerbose(QStringList() << "b"
                                               << "verbose",
                                 "Verbose.");
    QCommandLineOption clAllTypesScan(QStringList() << "a"
                                                    << "alltypes",
                                      "Scan all types.");
    QCommandLineOption clResultAsXml(QStringList() << "x"
                                                   << "xml",
                                     "Result as XML.");
    QCommandLineOption clResultAsJson(QStringList() << "j"
                                                    << "json",
                                      "Result as JSON.");
    QCommandLineOption clResultAsCSV(QStringList() << "c"
                                                   << "csv",
                                     "Result as CSV.");
    QCommandLineOption clResultAsTSV(QStringList() << "t"
                                                   << "tsv",
                                     "Result as TSV.");
    QCommandLineOption clResultAsPlainText(QStringList() << "p"
                                                         << "plaintext",
                                           "Result as Plain Text.");

    parser.addOption(clRecursiveScan);
    parser.addOption(clDeepScan);
    parser.addOption(clHeuristicScan);
    parser.addOption(clVerbose);
    parser.addOption(clAllTypesScan);
    parser.addOption(clResultAsXml);
    parser.addOption(clResultAsJson);
    parser.addOption(clResultAsCSV);
    parser.addOption(clResultAsTSV);
    parser.addOption(clResultAsPlainText);

    parser.process(app);

    QList<QString> listArgs = parser.positionalArguments();

    XScanEngine::SCAN_OPTIONS scanOptions = {0};

    scanOptions.bIsRecursiveScan = parser.isSet(clRecursiveScan);
    scanOptions.bIsDeepScan = parser.isSet(clDeepScan);
    scanOptions.bIsHeuristicScan = parser.isSet(clHeuristicScan);
    scanOptions.bIsVerbose = parser.isSet(clVerbose);
    scanOptions.bAllTypesScan = parser.isSet(clAllTypesScan);
    scanOptions.bResultAsXML = parser.isSet(clResultAsXml);
    scanOptions.bResultAsJSON = parser.isSet(clResultAsJson);
    scanOptions.bResultAsCSV = parser.isSet(clResultAsCSV);
    scanOptions.bResultAsTSV = parser.isSet(clResultAsTSV);
    scanOptions.bResultAsPlainText = parser.isSet(clResultAsPlainText);
    scanOptions.nBufferSize = 2 * 1024 * 1024;  // TODO Check
    scanOptions.bIsHighlight =true;

    if (listArgs.count()) {
        nResult = ScanFiles(&listArgs, &scanOptions);
    } else {
        parser.showHelp();
        Q_UNREACHABLE();
    }

    return nResult;
}
