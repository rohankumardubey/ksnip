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

#ifndef KSNIP_IMAGESAVER_H
#define KSNIP_IMAGESAVER_H

#include <QImage>
#include <QFileDialog>
#include <QCoreApplication>

#include "IImageSaver.h"
#include "src/backend/config/IConfig.h"
#include "src/common/helper/PathHelper.h"

class ImageSaver : public IImageSaver
{
public:
	explicit ImageSaver(const QSharedPointer<IConfig> &config);
	~ImageSaver() = default;
    bool save(const QImage &image, const QString &path);

private:
    QSharedPointer<IConfig> mConfig;

	static void ensurePathExists(const QString &path);
    QString ensureFilenameHasFormat(const QString &path);
	int getSaveQuality();
};

#endif //KSNIP_IMAGESAVER_H
