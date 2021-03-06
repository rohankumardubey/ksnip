/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_CAPTUREMODEPICKER_H
#define KSNIP_CAPTUREMODEPICKER_H

#include <QAction>

#include "src/widgets/CustomToolButton.h"
#include "src/common/loader/IIconLoader.h"
#include "src/common/enum/CaptureModes.h"
#include "src/common/helper/EnumTranslator.h"

class CaptureModePicker : public CustomToolButton
{
Q_OBJECT
public:
    explicit CaptureModePicker(const QList<CaptureModes> &captureModes, const QSharedPointer<IIconLoader> &iconLoader);
    ~CaptureModePicker() override = default;
    void setCaptureMode(CaptureModes mode);
    CaptureModes captureMode() const;
    QList<QAction*> captureActions() const;

signals:
    void captureModeSelected(CaptureModes mode) const;

private:
    CaptureModes mSelectedCaptureMode;
    QList<QAction*> mCaptureActions;

    void init(const QList<CaptureModes> &captureModes, const QSharedPointer<IIconLoader> &iconLoader);
    void selectCaptureMode(CaptureModes mode);

	QAction *createAction(const QString &text, const QString &tooltip, const QIcon &icon, CaptureModes captureMode, const QKeySequence &shortcut);
	static bool isCaptureModeSupported(const QList<CaptureModes> &captureModes, CaptureModes captureMode) ;
};

#endif //KSNIP_CAPTUREMODEPICKER_H
