/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_LOADIMAGEFROMFILEOPERATION_H
#define KSNIP_LOADIMAGEFROMFILEOPERATION_H

#include <QObject>

#include "src/gui/INotificationService.h"
#include "src/gui/IImageProcessor.h"
#include "src/gui/operations/NotifyOperation.h"
#include "src/gui/fileService/IFileService.h"
#include "src/backend/recentImages/IRecentImageService.h"
#include "src/common/dtos/CaptureFromFileDto.h"

class LoadImageFromFileOperation : public QObject
{
Q_OBJECT
public:
	LoadImageFromFileOperation(
			const QString &path,
			IImageProcessor *imageProcessor,
			const QSharedPointer<INotificationService> &notificationService,
			const QSharedPointer<IRecentImageService> &recentImageService,
			const QSharedPointer<IFileService> &fileService,
			const QSharedPointer<IConfig> &config);
	~LoadImageFromFileOperation() override = default;
	bool execute();

private:
	QString mPath;
	IImageProcessor *mImageProcessor;
	QSharedPointer<INotificationService> mNotificationService;
	QSharedPointer<IRecentImageService> mRecentImageService;
	QSharedPointer<IFileService> mFileService;
	QSharedPointer<IConfig> mConfig;

	void notifyAboutInvalidPath() const;
};

#endif //KSNIP_LOADIMAGEFROMFILEOPERATION_H
