//
// Created by baijinde on 7/1/21.
//

#ifndef ODRVIEWER_XODR_H
#define ODRVIEWER_XODR_H

#include "common_func.h"
#include <limits>
#include <cstdint>

typedef t_typevar<double, 0, std::numeric_limits<int>::max()> t_grEqZero;
typedef t_typevar<double, 1, std::numeric_limits<int>::max()> t_grZero;


enum class e_trafficRule : std::uint8_t
{
    RHT,
    LHT
};

enum class e_road_link_elementType : std::uint8_t
{
    ROAD,
    JUNCTION
};

enum class e_contactPoint : std::uint8_t
{
    START,
    END
};

enum class e_elementDir : std::uint8_t
{
    PLUS,
    MINUS
};

enum class t_bool : std::uint8_t
{
    TRUE,
    FALSE
};

enum class e_dataQuality_RawData_Source : std::uint8_t
{
    SENSOR,
    CADASTER,
    CUSTOM
};

enum class e_dataQuality_RawData_PostProcessing : std::uint8_t
{
    RAW,
    CLEANED,
    PROCESSED,
    FUSED
};

enum class e_laneType : std::uint8_t
{
    shoulder,
    border,
    driving,
    stop,
    none,
    restricted,
    parking,
    median,
    biking,
    sidewalk,
    curb,
    exit,
    entry,
    onRamp,
    offRamp,
    connectingRamp,
    bidirectional,
    special1,
    special2,
    special3,
    roadWorks,
    tram,
    rail,
    bus,
    taxi,
    HOV,
    mwyEntry,
    mwyExit
};

enum class e_unitSpeed : std::uint8_t
{
    M_S,
    MPH,
    KM_H
};

enum class e_road_lanes_laneSection_lr_lane_access_rule : std::uint8_t
{
    ALLOW,
    DENY
};

enum class e_accessRestrictionType : std::uint8_t
{
    SIMULATOR,
    AUTONOMOUSTRAFFIC,
    PEDESTRIAN,
    PASSENGERCAR,
    BUS,
    DELIVERY,
    EMERGENCY,
    TAXI,
    THROUGHTRAFFIC,
    TRUCK,
    BICYCLE,
    MOTORCYCLE,
    NONE,
    TRUCKS
};

enum class e_roadMarkType : std::uint8_t
{
    NONE,
    SOLID,
    BROKEN,
    SOLID_SOLID,
    SOLID_BROKEN,
    BROKEN_SOLID,
    BROKEN_BROKEN,
    BOTTS_DOTS,
    GRASS,
    CURB,
    CUSTOM,
    EDGE
};

enum class e_roadMarkWeight : std::uint8_t
{
    standard,
    bold
};

enum class e_roadMarkColor : std::uint8_t
{
    standard,
    blue,
    green,
    red,
    white,
    yellow,
    orange
};

enum class e_road_lanes_laneSection_lcr_lane_roadMark_laneChange : std::uint8_t
{
    increase,
    decrease,
    both,
    none
};

enum class e_roadMarkRule : std::uint8_t
{
    no_passing,
    caution,
    none
};


#endif //ODRVIEWER_XODR_H
