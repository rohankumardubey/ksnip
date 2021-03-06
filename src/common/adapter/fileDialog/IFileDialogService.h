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

#ifndef KSNIP_IFILEDIALOGSERVICE_H
#define KSNIP_IFILEDIALOGSERVICE_H

class IFileDialogService
{
public:
	IFileDialogService() = default;
	virtual ~IFileDialogService() = default;
	virtual QString	getExistingDirectory(QWidget *parent, const QString &title, const QString &directory) = 0;
	virtual QString	getOpenFileName(QWidget *parent, const QString &title, const QString &directory) = 0;
	virtual QStringList	getOpenFileNames(QWidget *parent, const QString &title, const QString &directory, const QString &filter) = 0;
	virtual QString	getSavePath(QWidget *parent, const QString &title, const QString &path, const QString &filter) = 0;
};

#endif //KSNIP_IFILEDIALOGSERVICE_H
