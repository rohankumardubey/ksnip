/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_COPYASDATAURIOPERATION_H
#define KSNIP_COPYASDATAURIOPERATION_H

#include <QBuffer>
#include <QImage>

#include "src/gui/clipboard/IClipboard.h"
#include "src/gui/INotificationService.h"
#include "src/gui/operations/NotifyOperation.h"
#include "src/backend/config/Config.h"

class CopyAsDataUriOperation : public QObject
{
	Q_OBJECT
public:
	CopyAsDataUriOperation(
			QImage image,
			const QSharedPointer<IClipboard> &clipboardService,
			const QSharedPointer<INotificationService> &notificationService,
			const QSharedPointer<IConfig> &config);
	~CopyAsDataUriOperation() override = default;
	bool execute();

private:
	QImage mImage;
	QSharedPointer<IClipboard> mClipboardService;
	QSharedPointer<INotificationService> mNotificationService;
	QSharedPointer<IConfig> mConfig;

	void notifySuccess() const;
	void notifyFailure() const;
	void notify(const QString &title, const QString &message, NotificationTypes type) const;
};

#endif //KSNIP_COPYASDATAURIOPERATION_H
