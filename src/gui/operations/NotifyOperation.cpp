/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "NotifyOperation.h"

NotifyOperation::NotifyOperation(
		const QString &title,
		const QString &message,
		const QString &contentUrl,
		NotificationTypes notificationType,
		const QSharedPointer<INotificationService> &notificationService,
		const QSharedPointer<IConfig> &config) :
	NotifyOperation(title, message, notificationType, notificationService, config)
{
	mContentUrl = contentUrl;
}

NotifyOperation::NotifyOperation(
		const QString &title,
		const QString &message,
		NotificationTypes notificationType,
		const QSharedPointer<INotificationService> &notificationService,
		const QSharedPointer<IConfig> &config) :
	mNotificationService(notificationService),
	mTitle(title),
	mMessage(message),
	mNotificationType(notificationType),
	mConfig(config)
{
	Q_ASSERT(mNotificationService != nullptr);
}

bool NotifyOperation::execute()
{
	if(mConfig->trayIconNotificationsEnabled()) {
		notifyViaToastMessage();
	}

	notifyViaConsoleMessage();

	return true;
}

void NotifyOperation::notifyViaToastMessage() const
{
	switch (mNotificationType) {
		case NotificationTypes::Information:
			mNotificationService->showInfo(mTitle, mMessage, mContentUrl);
			break;
		case NotificationTypes::Warning:
			mNotificationService->showWarning(mTitle, mMessage, mContentUrl);
			break;
		case NotificationTypes::Critical:
			mNotificationService->showCritical(mTitle, mMessage, mContentUrl);
			break;
	}
}

void NotifyOperation::notifyViaConsoleMessage() const
{
	switch (mNotificationType) {
		case NotificationTypes::Information:
			qInfo("%s: %s", qPrintable(mTitle), qPrintable(mMessage));
			break;
		case NotificationTypes::Warning:
			qWarning("%s: %s", qPrintable(mTitle), qPrintable(mMessage));
			break;
		case NotificationTypes::Critical:
			qCritical("%s: %s", qPrintable(mTitle), qPrintable(mMessage));
			break;
	}
}

