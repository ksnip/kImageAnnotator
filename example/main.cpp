/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>

#include <kImageAnnotator/KImageAnnotator.h>

using kImageAnnotator::KImageAnnotator;

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QPixmap pixmap(QSize(500, 500));
	pixmap.fill(QColor(Qt::darkGreen));
	auto kImageAnnotator = new KImageAnnotator();
	kImageAnnotator->addTab(pixmap, QStringLiteral("image1"), QStringLiteral("image1"));
	kImageAnnotator->addTab(pixmap, QStringLiteral("image2"), QStringLiteral("image2"));
	kImageAnnotator->adjustSize();

	QMainWindow mainWindow;
	mainWindow.setCentralWidget(kImageAnnotator);
	auto menuBar = mainWindow.menuBar();
	auto menu = new QMenu(QLatin1Literal("Edit"));
	auto annotationAction = new QAction(QLatin1Literal("Annotation"), &mainWindow);
	auto cropAction = new QAction(QLatin1Literal("Crop"), &mainWindow);
	auto scaleAction = new QAction(QLatin1Literal("Scale"), &mainWindow);
	auto modifyCanvasAction = new QAction(QLatin1Literal("Modify Canvas"), &mainWindow);
	mainWindow.connect(annotationAction, &QAction::triggered, kImageAnnotator, &KImageAnnotator::showAnnotator);
	mainWindow.connect(cropAction, &QAction::triggered, kImageAnnotator, &KImageAnnotator::showCropper);
	mainWindow.connect(scaleAction, &QAction::triggered, kImageAnnotator, &KImageAnnotator::showScaler);
	mainWindow.connect(modifyCanvasAction, &QAction::triggered, kImageAnnotator, &KImageAnnotator::showCanvasModifier);
	menu->addAction(annotationAction);
	menu->addAction(cropAction);
	menu->addAction(scaleAction);
	menu->addAction(modifyCanvasAction);
	menuBar->addMenu(menu);
	mainWindow.show();
	mainWindow.setMinimumSize(kImageAnnotator->sizeHint());

	QPixmap imageItem(QSize(100, 100));
	imageItem.fill(QColor(Qt::yellow));
	kImageAnnotator->insertImageItem(QPointF(100,100), imageItem);

	return app.exec();
}
