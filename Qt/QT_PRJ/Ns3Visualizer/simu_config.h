#ifndef SIMU_CONFIG_H
#define SIMU_CONFIG_H

#include "node_config.h"
#include "ap_config.h"
#include "JsonHelper.h"
#include "ppdu_adapter.h"
#include "ppdu_timeline_view.h"
#include "ppdu_visual_item.h"
#include "shm.h"
#include "qt_ppdu_reader.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QtGlobal>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QWidget>
#include <QThread>
#include <functional>
#include <qprocess.h>

namespace Ui
{
    class Simu_Config;
}

class Simu_Config : public QWidget
{
    Q_OBJECT

public:
    explicit Simu_Config(QWidget *parent = nullptr);
    ~Simu_Config();
    node_config *node_config_page = new (node_config);
    Ap_config *ap_config_page = new (Ap_config);
    void Write_building_into_config();

    void Draw_the_config_map();

    void update_json(QGraphicsScene *,QJsonObject&);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::Simu_Config *ui;
    JsonHelper *jsonHelper;
    QGraphicsScene *scene;

    QThread* m_ppduThread = nullptr;
    QtPpduReader* m_ppduReader = nullptr;
    PpduTimelineView* m_timelineView = nullptr;
    QProcess *ns3Process = nullptr;
};

class NodeItem : public QGraphicsEllipseItem
{
public:
    std::function<void(int id, double x, double y, double z)> onPositionCommitted;
    NodeItem(const QRectF &buildingRect, double scale,
             QGraphicsItem *parent = nullptr)
        : QGraphicsEllipseItem(parent),
          m_rect(buildingRect),
          m_scale(scale)
    {
        setRect(-4, -4, 8, 8);
        setFlags(ItemIsMovable | ItemSendsGeometryChanges);
        setAcceptHoverEvents(true);
        m_infoItem = new QGraphicsSimpleTextItem(this);
        m_infoItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        m_infoItem->setZValue(100);
        m_infoItem->setVisible(false);

    }

    void finishInit()
    {
        m_initialized = true;
    }

    QGraphicsSimpleTextItem *m_infoItem = nullptr;
    qint8 m_id = -1;
    double x_sim = 0;
    double y_sim = 0;
    double z_sim = 0;
    QString Type = "";

protected:
    bool m_hovered = false;
    bool m_initialized = false;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override
    {
        m_hovered = true;
        update();

        m_infoItem->setText(QString(
                                "Type:%1\nID: %2\nx=%3  y=%4  z=%5")
                                .arg(Type)
                                .arg(m_id)
                                .arg(x_sim, 0, 'f', 2)
                                .arg(y_sim, 0, 'f', 2)
                                .arg(z_sim, 0, 'f', 2));

        m_infoItem->setPos(8, 8); // bias to the center of the node
        m_infoItem->setVisible(true);

        QGraphicsEllipseItem::hoverEnterEvent(event);
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
    {
        m_hovered = false;
        m_infoItem->setVisible(false);
        update();
        QGraphicsEllipseItem::hoverLeaveEvent(event);
    }

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override
    {
        QGraphicsEllipseItem::paint(painter, option, widget);

        if (m_hovered)
        {
            painter->setRenderHint(QPainter::Antialiasing);
            QPen pen(QColor(0, 120, 215));
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->setBrush(Qt::NoBrush);
            painter->drawEllipse(rect().adjusted(-3, -3, 3, 3));
        }
    }

    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value) override
    {
        if (change == ItemPositionChange)
        {
            QPointF p = value.toPointF();
            p.setX(qBound(m_rect.left(), p.x(), m_rect.right()));
            p.setY(qBound(m_rect.top(), p.y(), m_rect.bottom()));
            return p;
        }

        if (change == ItemPositionHasChanged)
        {
            QPointF p = pos();

            x_sim = p.x() / m_scale;
            y_sim = p.y() / m_scale;
            //std::cout << "x_sim: " << x_sim << " y_sim: " << y_sim << std::endl;

        }

        return QGraphicsEllipseItem::itemChange(change, value);
    }

    QRectF boundingRect() const override
    {
        return rect().adjusted(-5, -5, 5, 5);
    }

private:
    QRectF m_rect;
    double m_scale;
};

#endif // SIMU_CONFIG_H
