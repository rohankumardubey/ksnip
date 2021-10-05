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

#include <gtest/gtest.h>

#include "src/gui/captureHandler/MultiCaptureHandler.h"

#include "tests/mocks/gui/imageAnnotator/ImageAnnotatorMock.h"
#include "tests/mocks/gui/NotificationServiceMock.h"
#include "tests/mocks/gui/fileService/FileServiceMock.h"
#include "tests/mocks/gui/desktopService/DesktopServiceMock.h"
#include "tests/mocks/gui/clipboard/ClipboardMock.h"
#include "tests/mocks/gui/messageBoxService/MessageBoxServiceMock.h"
#include "tests/mocks/gui/captureHandler/CaptureTabStateHandlerMock.h"
#include "tests/mocks/backend/config/ConfigMock.h"

TEST(MultiCaptureHandlerTests, Copy_Should_CopyCurrentTabImageToClipboard)
{
	// arrange
	auto index = 22;
	auto image = QImage();

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);
	auto clipboardMock = QSharedPointer<ClipboardMock>(new ClipboardMock);

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			clipboardMock,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(imageAnnotatorMock, imageAt(index))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](int index) {
				return image;
			});

	EXPECT_CALL(*clipboardMock, setImage(image))
			.Times(testing::Exactly(1));

	// act & assert
	multiCaptureHandler.copy();
}

TEST(MultiCaptureHandlerTests, CopyToClipboardTab_Should_FetchCorrectImageFromAnnotator_And_CopyItToClipboard)
{
	// arrange
	int index = 22;
	auto image = QImage();
	QList<QAction*> parameterActions;

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);
	auto clipboardMock = QSharedPointer<ClipboardMock>(new ClipboardMock);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(imageAnnotatorMock, imageAt(index))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](int index) {
				return image;
			});

	EXPECT_CALL(*clipboardMock, setImage(image))
			.Times(testing::Exactly(1));

	EXPECT_CALL(imageAnnotatorMock, addTabContextMenuActions(testing::_))
			.WillRepeatedly([&](const QList<QAction*> & actions) {
				parameterActions = actions;
			});

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			clipboardMock,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

	// act & assert
	for(auto action : parameterActions) {
		if(action->text() == QLatin1Literal("Copy")) {
			action->setData(index);
			action->trigger();
		}
	}
}

TEST(MultiCaptureHandlerTests, CopyPathToClipboardTab_Should_FetchCorrectPathFromTabStateHandler_And_CopyItToClipboard)
{
	// arrange
	int index = 22;
	auto path = QString("lala");
	QList<QAction*> parameterActions;

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);
	auto clipboardMock = QSharedPointer<ClipboardMock>(new ClipboardMock);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(*captureTabStateHandlerMock, path(index))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](int index) {
				return path;
			});

	EXPECT_CALL(*clipboardMock, setText(path))
			.Times(testing::Exactly(1));

	EXPECT_CALL(imageAnnotatorMock, addTabContextMenuActions(testing::_))
			.WillRepeatedly([&](const QList<QAction*> & actions) {
				parameterActions = actions;
			});

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			clipboardMock,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

	// act & assert
	for(auto action : parameterActions) {
		if(action->text() == QLatin1Literal("Copy Path")) {
			action->setData(index);
			action->trigger();
		}
	}
}

TEST(MultiCaptureHandlerTests, OpenDirectory_Should_FetchCorrectPathFromTabStateHandler_And_PassTheParentDirectoryOnlyToDesktopService)
{
	// arrange
	int index = 22;
	auto parentDir = QString("/foo");
	auto path = parentDir + QString("/bar.png");
	QList<QAction*> parameterActions;

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);
	auto desktopServiceMock = QSharedPointer<DesktopServiceMock>(new DesktopServiceMock);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(*captureTabStateHandlerMock, path(index))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](int index) {
				return path;
			});

	EXPECT_CALL(*desktopServiceMock, openFile(parentDir))
			.Times(testing::Exactly(1));

	EXPECT_CALL(imageAnnotatorMock, addTabContextMenuActions(testing::_))
			.WillRepeatedly([&](const QList<QAction*> & actions) {
				parameterActions = actions;
			});

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			nullptr,
			desktopServiceMock,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

	// act & assert
	for(auto action : parameterActions) {
		if(action->text() == QLatin1Literal("Open Directory")) {
			action->setData(index);
			action->trigger();
		}
	}
}

TEST(MultiCaptureHandlerTests, UpdateContextMenuActions_Should_SetAllActionThatRequirePathToEnabled_When_PathIsValid)
{
	// arrange
	int index = 22;
	QList<QAction*> parameterActions;

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(*captureTabStateHandlerMock, isPathValid(index))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](int index) {
				return true;
			});

	EXPECT_CALL(imageAnnotatorMock, addTabContextMenuActions(testing::_))
			.WillRepeatedly([&](const QList<QAction*> & actions) {
				parameterActions = actions;
			});

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

	// act
	imageAnnotatorMock.tabContextMenuOpened(index);

	// assert
	QAction *saveContextMenuAction = nullptr;
	QAction *saveAsContextMenuAction = nullptr;
	QAction *openDirectoryContextMenuAction = nullptr;
	QAction *copyPathToClipboardContextMenuAction = nullptr;
	QAction *copyToClipboardContextMenuAction = nullptr;
	for(auto action : parameterActions) {
		if(action->text() == QLatin1Literal("Save")) {
			saveContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Save As")) {
			saveAsContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Open Directory")) {
			openDirectoryContextMenuAction = action;
		}
		if(action->text() ==QLatin1Literal("Copy Path")) {
			copyPathToClipboardContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Copy")) {
			copyToClipboardContextMenuAction = action;
		}
	}

	EXPECT_TRUE(saveContextMenuAction->isEnabled());
	EXPECT_TRUE(saveAsContextMenuAction->isEnabled());
	EXPECT_TRUE(openDirectoryContextMenuAction->isEnabled());
	EXPECT_TRUE(copyPathToClipboardContextMenuAction->isEnabled());
	EXPECT_TRUE(copyToClipboardContextMenuAction->isEnabled());
}

TEST(MultiCaptureHandlerTests, UpdateContextMenuActions_Should_SetAllActionThatRequirePathToDisabled_When_PathIsNotValid)
{
	// arrange
	int index = 22;
	QList<QAction*> parameterActions;

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(*captureTabStateHandlerMock, isPathValid(index))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](int index) {
				return false;
			});

	EXPECT_CALL(imageAnnotatorMock, addTabContextMenuActions(testing::_))
			.WillRepeatedly([&](const QList<QAction*> & actions) {
				parameterActions = actions;
			});

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

	// act
	imageAnnotatorMock.tabContextMenuOpened(index);

	// assert
	QAction *saveContextMenuAction = nullptr;
	QAction *saveAsContextMenuAction = nullptr;
	QAction *openDirectoryContextMenuAction = nullptr;
	QAction *copyPathToClipboardContextMenuAction = nullptr;
	QAction *copyToClipboardContextMenuAction = nullptr;
	for(auto action : parameterActions) {
		if(action->text() == QLatin1Literal("Save")) {
			saveContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Save As")) {
			saveAsContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Open Directory")) {
			openDirectoryContextMenuAction = action;
		}
		if(action->text() ==QLatin1Literal("Copy Path")) {
			copyPathToClipboardContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Copy")) {
			copyToClipboardContextMenuAction = action;
		}
	}

	EXPECT_TRUE(saveContextMenuAction->isEnabled());
	EXPECT_TRUE(saveAsContextMenuAction->isEnabled());
	EXPECT_FALSE(openDirectoryContextMenuAction->isEnabled());
	EXPECT_FALSE(copyPathToClipboardContextMenuAction->isEnabled());
	EXPECT_TRUE(copyToClipboardContextMenuAction->isEnabled());
}

TEST(MultiCaptureHandlerTests, UpdateContextMenuActions_Should_SetSaveActionToDisabled_When_CaptureSaved)
{
	// arrange
	int index = 22;
	QList<QAction*> parameterActions;

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(*captureTabStateHandlerMock, isSaved(index))
			.WillRepeatedly([=](int index) {
				return true;
			});

	EXPECT_CALL(imageAnnotatorMock, addTabContextMenuActions(testing::_))
			.WillRepeatedly([&](const QList<QAction*> & actions) {
				parameterActions = actions;
			});

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

	// act
	imageAnnotatorMock.tabContextMenuOpened(index);

	// arrange
	QAction *saveContextMenuAction = nullptr;
	for(auto action : parameterActions) {
		if(action->text() == QLatin1Literal("Save")) {
			saveContextMenuAction = action;
		}
	}

	EXPECT_FALSE(saveContextMenuAction->isEnabled());
}

TEST(MultiCaptureHandlerTests, UpdateContextMenuActions_Should_SetSaveActionToEnabled_When_CaptureNotSaved)
{
	// arrange
	int index = 22;
	QList<QAction*> parameterActions;

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(*captureTabStateHandlerMock, isSaved(index))
			.WillRepeatedly([=](int index) {
				return false;
			});

	EXPECT_CALL(imageAnnotatorMock, addTabContextMenuActions(testing::_))
			.WillRepeatedly([&](const QList<QAction*> & actions) {
				parameterActions = actions;
			});

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

	// act
	imageAnnotatorMock.tabContextMenuOpened(index);

	// arrange
	QAction *saveContextMenuAction = nullptr;
	for(auto action : parameterActions) {
		if(action->text() == QLatin1Literal("Save")) {
			saveContextMenuAction = action;
		}
	}

	EXPECT_TRUE(saveContextMenuAction->isEnabled());
}

TEST(MultiCaptureHandlerTests, CopyPath_Should_CopyCurrentTabPathToClipboard)
{
	// arrange
	int index = 22;
	auto parentDir = QString("/foo");
	auto path = parentDir + QString("/bar.png");
	QList<QAction*> parameterActions;

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);
	auto clipboardMock = QSharedPointer<ClipboardMock>(new ClipboardMock);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(*captureTabStateHandlerMock, path(index))
			.WillRepeatedly([=](int index) {
				return path;
			});

	EXPECT_CALL(imageAnnotatorMock, addTabContextMenuActions(testing::_))
			.WillRepeatedly([&](const QList<QAction*> & actions) {
				parameterActions = actions;
			});

	EXPECT_CALL(*clipboardMock, setText(path))
			.Times(testing::Exactly(1));

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			clipboardMock,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

	// act & assert
	multiCaptureHandler.copyPath();
}

TEST(MultiCaptureHandlerTests, OpenDirectory_Should_FetchCurrentTabPathFromTabStateHandler_And_PassTheParentDirectoryOnlyToDesktopService)
{
	// arrange
	int index = 22;
	auto parentDir = QString("/foo");
	auto path = parentDir + QString("/bar.png");
	QList<QAction*> parameterActions;

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);
	auto desktopServiceMock = QSharedPointer<DesktopServiceMock>(new DesktopServiceMock);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(*captureTabStateHandlerMock, path(index))
			.WillRepeatedly([=](int index) {
				return path;
			});

	EXPECT_CALL(imageAnnotatorMock, addTabContextMenuActions(testing::_))
			.WillRepeatedly([&](const QList<QAction*> & actions) {
				parameterActions = actions;
			});

	EXPECT_CALL(*desktopServiceMock, openFile(parentDir))
			.Times(testing::Exactly(1));

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			nullptr,
			desktopServiceMock,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

	// act & assert
	multiCaptureHandler.openDirectory();
}

TEST(MultiCaptureHandlerTests, RemoveImage_Should_NotRemoveTab_When_OperationDidNotDeleteImage)
{
	// arrange
	int index = 22;
	auto parentDir = QString("/foo");
	auto path = parentDir + QString("/bar.png");
	QList<QAction*> parameterActions;

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);
	auto fileServiceMock = QSharedPointer<FileServiceMock>(new FileServiceMock);
	auto messageBoxServiceMock = QSharedPointer<MessageBoxServiceMock>(new MessageBoxServiceMock);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(*captureTabStateHandlerMock, path(index))
			.WillRepeatedly([=](int index) {
				return path;
			});

	EXPECT_CALL(imageAnnotatorMock, removeTab(index))
			.Times(testing::Exactly(0));

	EXPECT_CALL(*messageBoxServiceMock, okCancel(testing::_, testing::_))
			.WillRepeatedly([=](const QString &title, const QString &info) {
				return false;
			});

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			nullptr,
			nullptr,
			fileServiceMock,
			messageBoxServiceMock,
			nullptr,
			nullptr);

	// act & assert
	multiCaptureHandler.removeImage();
}

TEST(MultiCaptureHandlerTests, RemoveImage_Should_RemoveTab_When_OperationDidDeleteImage)
{
	// arrange
	int index = 22;
	auto parentDir = QString("/foo");
	auto path = parentDir + QString("/bar.png");
	QList<QAction*> parameterActions;

	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto captureTabStateHandlerMock = QSharedPointer<CaptureTabStateHandlerMock>(new CaptureTabStateHandlerMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);
	auto fileServiceMock = QSharedPointer<FileServiceMock>(new FileServiceMock);
	auto messageBoxServiceMock = QSharedPointer<MessageBoxServiceMock>(new MessageBoxServiceMock);

	EXPECT_CALL(*captureTabStateHandlerMock, currentTabIndex())
			.WillRepeatedly([=]() {
				return index;
			});

	EXPECT_CALL(*captureTabStateHandlerMock, path(index))
			.WillRepeatedly([=](int index) {
				return path;
			});

	EXPECT_CALL(imageAnnotatorMock, removeTab(index))
			.Times(testing::Exactly(1));

	EXPECT_CALL(*messageBoxServiceMock, okCancel(testing::_, testing::_))
			.WillRepeatedly([=](const QString &title, const QString &info) {
				return true;
			});

	EXPECT_CALL(*fileServiceMock, remove(path))
			.WillRepeatedly([=](const QString &path) {
				return true;
			});

	MultiCaptureHandler multiCaptureHandler(
			&imageAnnotatorMock,
			nullptr,
			captureTabStateHandlerMock,
			configMock,
			nullptr,
			nullptr,
			fileServiceMock,
			messageBoxServiceMock,
			nullptr,
			nullptr);

	// act & assert
	multiCaptureHandler.removeImage();
}

int main(int argc, char **argv) {
	QGuiApplication guiApplication(argc, argv);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
