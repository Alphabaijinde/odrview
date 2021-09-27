//
// Created by baijinde on 21-9-17.
//

#ifndef ODRVIEWER_INFOASSEMBLING_H
#define ODRVIEWER_INFOASSEMBLING_H

#include "../views/RoadItem.h"
#include "../views/RoadMapItem.h"
#include "../views/LaneSectionItem.h"

#include "../model/MapInfo.h"
#include "xodr.h"

#include <vector>

#define __INFOASSEMBLE (InfoAssembling::getInstance())

typedef QVector<QPointF> LanePaint;
typedef QVector<LanePaint> LaneSectionPaint;
typedef QVector<LaneSectionPaint> RoadPaint;
typedef QVector<RoadPaint> RoadMapPaint;
typedef QVector<std::shared_ptr<t_road_lanes_laneSection_lr_lane>> SectionLane;
typedef QVector<SectionLane> RoadLane;
typedef QVector<std::pair<std::string, RoadLane> > RoadMapLane;

class InfoAssembling {
private:
    InfoAssembling();
    ~InfoAssembling();

public:
    static InfoAssembling *getInstance()
    {
        static InfoAssembling infoAssembling;
        return &infoAssembling;
    }

    const RoadMapItem* getRoadMapItem() {
        return m_pRoadMapItem;
    }

    void roadMapItemReset();

    void transferRoadMapInfo(const std::vector< std::shared_ptr<t_road> > &vecAllRoad);
    void transferLanesList(const std::vector<std::shared_ptr<t_road>> &vecAllRoad, RoadMapLane &roadMapLane);
    void transferRoad(const std::shared_ptr<t_road> &road, RoadItem *pRoadItem);
    void transferLaneSection(const std::shared_ptr<t_road_lanes_laneSection> &laneSection, LaneSectionItem *pLaneSectionItem, int index);

private:
    QPolygonF getRoadShape(const QVector<LaneSectionPaint> &roadPaint, const std::vector<std::shared_ptr<t_road_lanes_laneSection>> &vecLaneSection);
    QPolygonF getLaneSectionShape(const QVector<LanePaint> &laneSectionPaint);
    QVector<QPointF> fillLaneData(const QVector<QPointF> &qvecOutsideLaneData, const QVector<QPointF> &qvecInsideLaneData);

private:
    RoadMapItem *m_pRoadMapItem;

};


#endif //ODRVIEWER_INFOASSEMBLING_H
