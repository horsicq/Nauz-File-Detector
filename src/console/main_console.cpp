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
#ifndef USE_ARCHIVE
#define USE_ARCHIVE
#endif
#ifndef USE_DEX
#define USE_DEX
#endif
#ifndef USE_PDF
#define USE_PDF
#endif

#include <QCoreApplication>

#include "../global.h"
#include "specabstract.h"
#include "xoptions.h"
#include "xscanengineconsole.h"

namespace {

void configureApplicationMetadata()
{
    QCoreApplication::setOrganizationName(X_ORGANIZATIONNAME);
    QCoreApplication::setOrganizationDomain(X_ORGANIZATIONDOMAIN);
    QCoreApplication::setApplicationName(X_APPLICATIONNAME);
    QCoreApplication::setApplicationVersion(X_APPLICATIONVERSION);
}

QString buildDescription()
{
    QString description;
    description.append(QStringLiteral("%1 v%2\n").arg(QStringLiteral(X_APPLICATIONDISPLAYNAME),
                                                      QStringLiteral(X_APPLICATIONVERSION)));
    description.append(QStringLiteral("Copyright(C) 2017-2026 hors<horsicq@gmail.com> Web: http://ntinfo.biz\n"));

    return description;
}

}  // namespace

int main(int argc, char *argv[])
{
    configureApplicationMetadata();

    QCoreApplication application(argc, argv);

#ifdef USE_XSIMD
    xsimd_init();
#endif

    SpecAbstract specAbstract;
    XScanEngineConsole scanEngineConsole(&application, &specAbstract, buildDescription());

    return scanEngineConsole.process();
}
