/*
 * Copyright (C) 2020 Damir Porobic <https://github.com/damirporobic>
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

#ifndef KSNIP_UPLOADSTATUS_H
#define KSNIP_UPLOADSTATUS_H

enum class UploadStatus
{
	NoError,
	UnableToSaveTemporaryImage,
	FailedToStart,               // file not found, resource error
	Crashed,
	TimedOut,
	ReadError,
	WriteError,
	WebError,
	UnknownError,
	ScriptWroteToStdErr,
	ConnectionError,
	PermissionError
};

inline uint qHash(const UploadStatus uploadStatus, uint seed) {
	return qHash(static_cast<int>(uploadStatus), seed);
}

#endif //KSNIP_UPLOADSTATUS_H
