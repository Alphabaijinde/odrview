//
// Created by baijinde on 21-9-17.
//

#include "InfoAssembling.h"
#include "../util/ComputeParameter.h"

#include <QDebug>
#include <QVector>

InfoAssembling::InfoAssembling()
{
    m_pRoadMapItem = new RoadMapItem();
}

InfoAssembling::~InfoAssembling()
{
    qDebug() << "~InfoAssembling";
}

void InfoAssembling::roadMapItemReset()
{
    if(m_pRoadMapItem != nullptr)
    {
        delete m_pRoadMapItem;
        m_pRoadMapItem = new RoadMapItem();
    }
}

void InfoAssembling::transferRoadMapInfo(const std::vector<std::shared_ptr<t_road>> &vecAllRoad)
{
    RoadMapPoint roadMapPoint;
    RoadMapPaint roadMapPaint;
    RoadMapLane roadMapLane;
    __MAPDATA->getRoadSurfaceContourPoint(vecAllRoad, roadMapPoint);     // 所有点

    __MAPDATA->getRoadLaneSectionPoint(roadMapPoint, roadMapPaint);      // 车道段的点

    QVector<QVector<QVector<std::pair<QVector<QVector<QPointF> >, int> > > > roadMapLanePaint;
    __MAPDATA->getRoadGeometryPoint(roadMapPoint, roadMapLanePaint);     // 绘制车道

    std::map<std::string, std::map<int, std::map<int, std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int>>>>>>> allRoadMarkPoint;
    __MAPDATA->getAllRoadMarkPoint(allRoadMarkPoint);

    transferLanesList(vecAllRoad, roadMapLane);

    // 绘制车道
    for (int i = 0; i < roadMapLanePaint.size(); ++i)
    {
        auto eachRoadPaint = roadMapPaint[i]; // 绘制车道的信息
        std::map<int, std::map<int, std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int>>>>>> eachRoadRoadMarkPaint = allRoadMarkPoint[vecAllRoad.at(i)->id]; // 绘制车道线的信息

        // 每一个道路
        RoadItem *pRoadItem = new RoadItem();
        transferRoad(vecAllRoad.at(i), pRoadItem);    // 道路信息装入RoadItem
        pRoadItem->setZValue(QString(pRoadItem->getRoadId().c_str()).toInt());

        QVector<QVector<std::pair<QVector<QVector<QPointF> >, int> > > roadPoint = roadMapLanePaint[i];
        RoadLane roadLane = roadMapLane[i].second;    // 道路数一致，所以共用下标
        pRoadItem->setPolygonPoint(getRoadShape(roadMapPaint[i], vecAllRoad.at(i)->m_lanes->m_laneSections));

        for (int j = 0; j < roadPoint.size(); ++j)
        {
            auto eachLaneSectionPaint = eachRoadPaint[j];
            std::map<int, std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int>>>>> eachLaneSectionRoadMarkPaint = eachRoadRoadMarkPaint[j];

            // 每一个车道段
            LaneSectionItem *pLaneSectionItem = new LaneSectionItem(vecAllRoad.at(i)->id);
            transferLaneSection(vecAllRoad.at(i)->m_lanes->m_laneSections.at(j), pLaneSectionItem, j);

            QVector<std::pair<QVector<QVector<QPointF> >, int> > laneSectionPoint = roadPoint[j];
            SectionLane sectionLane = roadLane[j];

            pLaneSectionItem->setPolygonPoint(getLaneSectionShape(roadMapPaint[i][j]));

            int startLaneIndex = 0;
            if(!sectionLane.empty())
            {
               if(nullptr != dynamic_cast<t_road_lanes_laneSection_left_lane *>(sectionLane[0].get()))
               {
                   startLaneIndex = dynamic_cast<t_road_lanes_laneSection_left_lane *>(sectionLane[0].get())->id;
               }
               else if(nullptr != dynamic_cast<t_road_lanes_laneSection_center_lane *>(sectionLane[0].get()))
               {
                   startLaneIndex = dynamic_cast<t_road_lanes_laneSection_center_lane *>(sectionLane[0].get())->id;
               }
               else if(nullptr != dynamic_cast<t_road_lanes_laneSection_right_lane *>(sectionLane[0].get()))
               {
                   startLaneIndex = dynamic_cast<t_road_lanes_laneSection_right_lane *>(sectionLane[0].get())->id;
               }
            }

            for (int k = 0; k < laneSectionPoint.size(); ++k)
            {
                // 每一个几何元素
                QVector<QVector<QPointF> > qvecGeometry = laneSectionPoint[k].first;
                // 几何元素信息 一个车道段要同时传输全部几何元素
                int iIndexGeometry = laneSectionPoint[k].second;
                std::shared_ptr<t_road_planView_geometry> geometry = vecAllRoad.at(i)->m_planView->m_geometrys[iIndexGeometry];
                std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int>>>> geometryRoadMarkPaint = eachLaneSectionRoadMarkPaint[iIndexGeometry];

                for (int n = 0; n < sectionLane.size(); ++n)
                {
                    int iLaneId = 0;
                    if(nullptr != dynamic_cast<t_road_lanes_laneSection_left_lane *>(sectionLane[n].get()))
                    {
                        iLaneId = dynamic_cast<t_road_lanes_laneSection_left_lane *>(sectionLane[n].get())->id;
                    }
                    else if(nullptr != dynamic_cast<t_road_lanes_laneSection_center_lane *>(sectionLane[n].get()))
                    {
                        iLaneId = dynamic_cast<t_road_lanes_laneSection_center_lane *>(sectionLane[n].get())->id;
                    }
                    else if(nullptr != dynamic_cast<t_road_lanes_laneSection_right_lane *>(sectionLane[n].get()))
                    {
                        iLaneId = dynamic_cast<t_road_lanes_laneSection_right_lane *>(sectionLane[n].get())->id;
                    }

                    std::string strLaneId = std::to_string(iLaneId);

                    // 绘制道路标线
                    if(!sectionLane[n]->m_roadMarks.empty())
                    {
                        std::map<std::string, QVector<std::pair<QPointF, int>>> laneRoadMarkPaint = geometryRoadMarkPaint[strLaneId];

                        for(auto eachcolRoadMark : laneRoadMarkPaint)
                        {
                            QVector<QPointF> eachRoadMarkPoints; // 每个roadmark的点
                            for(int num = 0; num < eachcolRoadMark.second.size(); ++num)
                            {
                                if(eachcolRoadMark.second[num].second < 0)
                                {
                                    continue;
                                }

                                if(
                                        ((num+1) < eachcolRoadMark.second.size()) &&
                                        (eachcolRoadMark.second[num].second != eachcolRoadMark.second[num+1].second)
                                        )
                                {
                                    eachRoadMarkPoints.append(eachcolRoadMark.second[num].first);

                                    // 当前roadmark的点是最后一个
                                    Painting painting;
                                    painting.polygonF = eachRoadMarkPoints;
                                    painting.qstrColor = enum2str<e_roadMarkColor>(sectionLane[n]->m_roadMarks[eachcolRoadMark.second[num].second]->color);
                                    painting.qstrStyle = enum2str<e_roadMarkType>(sectionLane[n]->m_roadMarks[eachcolRoadMark.second[num].second]->type);
                                    painting.width = sectionLane[n]->m_roadMarks[eachcolRoadMark.second[num].second]->width._val;
                                    pLaneSectionItem->appendLaneLine(strLaneId, painting);

                                    eachRoadMarkPoints.clear();
                                }
                                else
                                {
                                    eachRoadMarkPoints.append(eachcolRoadMark.second[num].first);

                                    // 车道的最后一个点
                                    if((num+1) == eachcolRoadMark.second.size())
                                    {
                                        Painting painting;
                                        painting.polygonF = eachRoadMarkPoints;
                                        painting.qstrColor = enum2str<e_roadMarkColor>(sectionLane[n]->m_roadMarks[eachcolRoadMark.second[num].second]->color);
                                        painting.qstrStyle = enum2str<e_roadMarkType>(sectionLane[n]->m_roadMarks[eachcolRoadMark.second[num].second]->type);
                                        painting.width = sectionLane[n]->m_roadMarks[eachcolRoadMark.second[num].second]->width._val;
                                        pLaneSectionItem->appendLaneLine(strLaneId, painting);

                                        eachRoadMarkPoints.clear();
                                    }
                                }
                            }

                        }
                    }

                    // 绘制道路（lanesection层道路的点）
                    {
                        QPolygonF polygonF;
                        Painting painting;
                        if(n < startLaneIndex)
                        {
                            //左车道
                            polygonF = fillLaneData(roadMapPaint[i][j][n], roadMapPaint[i][j][n+1]);
                        }
                        else if(n > startLaneIndex)
                        {
                            //右车道
                            polygonF = fillLaneData(roadMapPaint[i][j][n], roadMapPaint[i][j][n-1]);
                        }
                        else
                        {
                            //0车道
                            continue;
                        }

                        painting.polygonF = polygonF;
                        painting.qstrColor = enum2str<e_laneType>(sectionLane[n]->type);
                        pLaneSectionItem->appendFilling(roadMapLane[i].first, painting);
                        pLaneSectionItem->setLanePolygonPoint(strLaneId, polygonF);
                    }

                    // 显示状态栏信息（geometry层道路的点）
                    QPolygonF laneFilling;
                    if(n < startLaneIndex)
                    {
                        //左车道
                        laneFilling = fillLaneData(qvecGeometry[n], qvecGeometry[n+1]);
                    }
                    else if(n > startLaneIndex)
                    {
                        //右车道】
                        laneFilling = fillLaneData(qvecGeometry[n], qvecGeometry[n-1]);
                    }
                    else
                    {
                        //LaneID等于0的情况，没有车道
                        continue;
                    }

                    if(n != startLaneIndex)
                    {
                        pLaneSectionItem->appendLanePolygon(laneFilling, vecAllRoad.at(i)->id, vecAllRoad.at(i)->m_lanes->m_laneSections.at(j) , geometry, strLaneId);
                    }
                }
            }

            pRoadItem->addToGroup(pLaneSectionItem);
            pRoadItem->appendLaneSectionItem(vecAllRoad.at(i)->m_lanes->m_laneSections.at(j)->s, pLaneSectionItem);
            QObject::connect(pLaneSectionItem, &LaneSectionItem::sigCurPosInfo, m_pRoadMapItem, &RoadMapItem::onMap);
        }

        m_pRoadMapItem->addToGroup(pRoadItem);
        m_pRoadMapItem->appendRoadItem(pRoadItem);
    }
}

void InfoAssembling::transferLanesList(const std::vector<std::shared_ptr<t_road>> &vecAllRoad, RoadMapLane &roadMapLane)
{
    for(auto eachRoad: vecAllRoad)
    {
        RoadLane roadLane;

        for(auto eachlaneSection: eachRoad->m_lanes->m_laneSections)
        {
            SectionLane sectionLane;

            if(eachlaneSection->m_left)
            {
                for(auto eachLane: eachlaneSection->m_left->m_lanes)
                {
                    sectionLane.append(std::shared_ptr<t_road_lanes_laneSection_lr_lane>(eachLane));
                }
            }

            if(eachlaneSection->m_center)
            {
                for(auto eachLane: eachlaneSection->m_center->m_lanes)
                {
                    sectionLane.append(std::shared_ptr<t_road_lanes_laneSection_lr_lane>(eachLane));
                }
            }

            if(eachlaneSection->m_right)
            {
                for(auto eachLane: eachlaneSection->m_right->m_lanes)
                {
                    sectionLane.append(std::shared_ptr<t_road_lanes_laneSection_lr_lane>(eachLane));
                }
            }

            roadLane.append(sectionLane);
        }

        roadMapLane.append(std::make_pair(eachRoad->id, roadLane));
    }
}

void InfoAssembling::transferRoad(const std::shared_ptr<t_road> &road, RoadItem *pRoadItem)
{
    if(nullptr != pRoadItem)
    {
        pRoadItem->setRoad(road);
    }
}


void InfoAssembling::transferLaneSection(const std::shared_ptr<t_road_lanes_laneSection> &laneSection, LaneSectionItem *pLaneSectionItem, int index)
{
    if(nullptr != pLaneSectionItem)
    {
        pLaneSectionItem->setLaneSection(laneSection, index);
    }
}

QPolygonF InfoAssembling::getRoadShape(const QVector<LaneSectionPaint> &roadPaint, const std::vector<std::shared_ptr<t_road_lanes_laneSection>> &vecLaneSection)
{
    QPolygonF polygon;
    QPolygonF polygonEnd;

    QMap<double, std::pair<int, int>> eachSMaxLaneSize;
    // 获取相同soffset左车道最多右车道最多的laneSection的iIndex
    for(int i = 0; i < vecLaneSection.size(); ++i)
    {
       auto iter = eachSMaxLaneSize.find(vecLaneSection[i]->s._val);
       if(iter != eachSMaxLaneSize.end())
       {
           if( vecLaneSection[i]->m_left->m_lanes.size() > vecLaneSection[iter.value().first]->m_left->m_lanes.size())
           {
               iter.value().first = i;
           }

           if(vecLaneSection[i]->m_right->m_lanes.size() > vecLaneSection[iter.value().second]->m_right->m_lanes.size())
           {
               iter.value().second = i;
           }
       }
       else
       {
           eachSMaxLaneSize.insert(vecLaneSection[i]->s._val, std::make_pair(i, i));
       }
    }

    for(auto eachS : eachSMaxLaneSize)
    {
        if(roadPaint[eachS.first].empty() || roadPaint[eachS.second].empty())
        {
            continue;
        }

        polygon.append(roadPaint[eachS.first].at(0));
        polygonEnd.append(roadPaint[eachS.second].at(roadPaint[eachS.second].size() - 1));
    }

    polygon = fillLaneData(polygon, polygonEnd);
    return polygon;
}

QPolygonF InfoAssembling::getLaneSectionShape(const QVector<LanePaint> &laneSectionPaint)
{
    QPolygonF polygon;
    QPolygonF polygonEnd;

    if(!laneSectionPaint.empty())
    {
        polygon.append(laneSectionPaint.at(0));
        polygonEnd.append(laneSectionPaint.at(laneSectionPaint.size() - 1));
    }

    polygon = fillLaneData(polygon, polygonEnd);
    return polygon;
}

//车道填充数据的定义
QVector<QPointF> InfoAssembling::fillLaneData(const QVector<QPointF> &qvecOutsideLaneData, const QVector<QPointF> &qvecInsideLaneData)
{
    QVector<QPointF> qvecLaneFillingData;
    for(int i = 0; i < qvecOutsideLaneData.size(); ++i)
    {
        qvecLaneFillingData.push_back(qvecOutsideLaneData[i]);
    }

    for(int i = qvecInsideLaneData.size() - 1; i >= 0; --i)
    {
        qvecLaneFillingData.push_back(qvecInsideLaneData[i]);
    }

    return qvecLaneFillingData;
}
