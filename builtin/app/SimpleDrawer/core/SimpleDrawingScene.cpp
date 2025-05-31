#include "SimpleDrawingScene.h"
#include "settings.h"
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>

SimpleDrawingScene::SimpleDrawingScene(QObject* parent)
    : QGraphicsScene(parent)
    , currentColor(DEF_PEN_COLOR)
    , penWidth(DEF_PEN_WIDTH) {
}

void SimpleDrawingScene::setMode(const DrawingMode m) {
	switch (m) {
	case DrawingMode::DrawingMode:
		for (auto& each : itemsStack) {
			each->setFlag(QGraphicsItem::ItemIsMovable, false);
		}
	case DrawingMode::EditMode:
		for (auto& each : itemsStack) {
			each->setFlag(QGraphicsItem::ItemIsMovable, true);
		}
		break;
	}

	mode = m;
}

QImage SimpleDrawingScene::exportImage() {
	QImage image(this->sceneRect().size().toSize(), QImage::Format_ARGB32);
	image.fill(Qt::white);

	QPainter painter(&image);
	this->render(&painter);

	return image;
}

void SimpleDrawingScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		startPos = event->scenePos();
		QPen pen(currentColor, penWidth);
		switch (mode) {
		case DrawingMode::DrawingMode:
			tempItem = create_from_types(pen);
			if (tempItem) {
				tempItem->setFlag(QGraphicsItem::ItemIsMovable, false);
			} else {
				pathItem->setFlag(QGraphicsItem::ItemIsMovable, false);
			}
			break;
		case DrawingMode::EditMode:
			tempItem = itemAt(event->scenePos(), QTransform());
			break;
		}
	}

	QGraphicsScene::mousePressEvent(event);
}

void SimpleDrawingScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	if (event->buttons() & Qt::LeftButton) {
		QPointF currentPos = event->scenePos();
		switch (mode) {
		case DrawingMode::DrawingMode: {
			process_drawing_moving(currentPos);
		} break;
		case DrawingMode::EditMode:
			break;
		}
	}
	QGraphicsScene::mouseMoveEvent(event);
}

void SimpleDrawingScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {

	if (tempItem && event->button() == Qt::LeftButton) {
		switch (mode) {
		case DrawingMode::DrawingMode: {
			if (tempItem) {
				itemsStack.append(tempItem);
				redoStack.clear();
				tempItem = nullptr;
			} else {
				if (pathItem) {
					pathItem->setFlag(QGraphicsItem::ItemIsMovable);
					itemsStack.append(pathItem);
					redoStack.clear();
					pathItem = nullptr;
				}
			}
		} break;
		case DrawingMode::EditMode:
			break;
		}
	}
	QGraphicsScene::mouseReleaseEvent(event);
}

QGraphicsItem* SimpleDrawingScene::create_from_types(QPen& pen) {
	switch (itemType) {
	case SupportItemItem::Line:
		return addLine(QLineF(startPos, startPos), pen);
	case SupportItemItem::Rect:
		return addRect(QRectF(startPos, startPos), pen);
	case SupportItemItem::Ellipse:
		return addEllipse(QRectF(startPos, startPos), pen);
	case SupportItemItem::FreeHand:
		currentPath = QPainterPath(startPos);
		pathItem = addPath(currentPath, pen);
		return nullptr;
	}
	return nullptr;
}

void SimpleDrawingScene::process_drawing_moving(const QPointF& currentPos) {

	if (itemType == SupportItemItem::FreeHand) {
		if (pathItem) {
			currentPath.lineTo(currentPos);
			pathItem->setPath(currentPath);
		}
		return;
	}

	if (!tempItem)
		return;

	switch (itemType) {
	case SupportItemItem::Line: {
		auto lineItem = static_cast<QGraphicsLineItem*>(tempItem);
		lineItem->setLine(QLineF(startPos, currentPos));
		break;
	}
	case SupportItemItem::Rect: {
		auto rectItem = static_cast<QGraphicsRectItem*>(tempItem);
		QRectF newRect(startPos, currentPos);
		rectItem->setRect(newRect.normalized()); // normalized 保证宽高正值
		break;
	}
	case SupportItemItem::Ellipse: {
		auto ellipseItem = static_cast<QGraphicsEllipseItem*>(tempItem);
		QRectF newRect(startPos, currentPos);
		ellipseItem->setRect(newRect.normalized());
		break;
	}
	case SupportItemItem::FreeHand:
		break;
	}
}

void SimpleDrawingScene::undo() {
	if (!itemsStack.isEmpty()) {
		QGraphicsItem* item = itemsStack.takeLast();
		removeItem(item);
		redoStack.append(item);
	}
}

void SimpleDrawingScene::redo() {
	if (!redoStack.isEmpty()) {
		QGraphicsItem* item = redoStack.takeLast();
		addItem(item);
		itemsStack.append(item);
	}
}
