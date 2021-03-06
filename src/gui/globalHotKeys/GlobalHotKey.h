/*
 * Copyright (C) 2019 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KSNIP_GLOBALHOTKEY_H
#define KSNIP_GLOBALHOTKEY_H

#include <QCoreApplication>
#include <QObject>

#include "NativeKeyEventFilter.h"
#include "src/gui/globalHotKeys/keyHandler/KeyHandlerFactory.h"

class GlobalHotKey : public QObject
{
    Q_OBJECT
public:
    explicit GlobalHotKey(QCoreApplication *app, const QKeySequence &keySequence, const QSharedPointer<IPlatformChecker> &platformChecker);
    ~GlobalHotKey() override;

signals:
    void pressed() const;

private:
	QCoreApplication *mApp;
	NativeKeyEventFilter *mKeyEventFilter;
};

#endif //KSNIP_GLOBALHOTKEY_H
