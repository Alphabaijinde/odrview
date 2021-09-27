//
// Created by baijinde on 21-9-26.
//

#ifndef ODRVIEWER_COMMON_H
#define ODRVIEWER_COMMON_H

enum AllItemZValue
{
    RoadMapItemZValue = 0,
    LaneItemZValue = 1,
    LaneSectionItemZValue,              // 2
    RoadItemZValue,                     // 3
    LinkSignItemZValue,                 // 4
    DrawRoadEndPointsItemZValue,        // 5
    DrawIntersectionItemZValue,         // 6
    JunctionPreviewItemZValue,          // 7
    LaneDirectionItemZValue,            // 8
    RoadPreviewItemZValue,              // 9 使用结束就会删除
    ElementItemZValue,
    JunctionMenuBtnTypeItemZValue,
    ConnectLineItemZValue,
    QPointItemZValue
};

#define STR_RAIL                "rail"
#define STR_RESTRICTED          "restricted"
#define STR_MEDIAN              "median"
#define STR_STOP                "stop"
#define STR_NONE                "none"
#define STR_BORDER              "border"
#define STR_BIKING              "biking"
#define STR_PARKING             "parking"
#define STR_SIDEWALK            "sidewalk"
#define STR_DRIVING             "driving"
#define STR_BIDIRECTIONAL       "bidirectional"
#define STR_EXIT                "exit"
#define STR_OFFRAMP             "offRamp"
#define STR_ONRAMP              "onRamp"
#define STR_ENTRY               "entry"
#define STR_SHOULDER            "shoulder"
#define STR_STANDARD            "standard"
#define STR_SOLID               "solid"
#define STR_BROKEN              "broken"
#define STR_SOLID_SOLID         "solid solid"
#define STR_SOLID_BROKEN        "solid broken"
#define STR_BROKEN_SOLID        "broken solid"
#define STR_BROKEN_BROKEN       "broken broken"
#define STR_DEF_ROAD_JUNCTION   "-1"
#define STR_EMPTY               ""
#define STR_BLUE                "blue"
#define STR_GREEN               "green"
#define STR_RED                 "red"
#define STR_WHITE               "white"
#define STR_YELLOW              "yellow"
#define STR_ORANGE              "orange"
#define LANE_LINE_WIDTHF 0.15

#endif //ODRVIEWER_COMMON_H
