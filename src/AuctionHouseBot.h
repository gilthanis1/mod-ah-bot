/*
 * Copyright (C) 2008-2010 Trinity <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef AUCTION_HOUSE_BOT_H
#define AUCTION_HOUSE_BOT_H

#include "Common.h"
#include "ObjectGuid.h"

struct AuctionEntry;

class Player;

class WorldSession;

#include "ItemTemplate.h"

#define AHB_GREY        0
#define AHB_WHITE       1
#define AHB_GREEN       2
#define AHB_BLUE        3
#define AHB_PURPLE      4
#define AHB_ORANGE      5
#define AHB_YELLOW      6
#define AHB_MAX_QUALITY 6
#define AHB_GREY_TG     0
#define AHB_WHITE_TG    1
#define AHB_GREEN_TG    2
#define AHB_BLUE_TG     3
#define AHB_PURPLE_TG   4
#define AHB_ORANGE_TG   5
#define AHB_YELLOW_TG   6
#define AHB_GREY_I      7
#define AHB_WHITE_I     8
#define AHB_GREEN_I     9
#define AHB_BLUE_I      10
#define AHB_PURPLE_I    11
#define AHB_ORANGE_I    12
#define AHB_YELLOW_I    13

class AHBConfig
{
private:
    uint32 AHID;
    uint32 AHFID;
    uint32 minItems;
    uint32 maxItems;
    uint32 percentGreyTradeGoods;
    uint32 percentWhiteTradeGoods;
    uint32 percentGreenTradeGoods;
    uint32 percentBlueTradeGoods;
    uint32 percentPurpleTradeGoods;
    uint32 percentOrangeTradeGoods;
    uint32 percentYellowTradeGoods;
    uint32 percentGreyItems;
    uint32 percentWhiteItems;
    uint32 percentGreenItems;
    uint32 percentBlueItems;
    uint32 percentPurpleItems;
    uint32 percentOrangeItems;
    uint32 percentYellowItems;
    uint32 minPriceGrey;
    uint32 maxPriceGrey;
    uint32 minBidPriceGrey;
    uint32 maxBidPriceGrey;
    uint32 maxStackGrey;
    uint32 minPriceWhite;
    uint32 maxPriceWhite;
    uint32 minBidPriceWhite;
    uint32 maxBidPriceWhite;
    uint32 maxStackWhite;
    uint32 minPriceGreen;
    uint32 maxPriceGreen;
    uint32 minBidPriceGreen;
    uint32 maxBidPriceGreen;
    uint32 maxStackGreen;
    uint32 minPriceBlue;
    uint32 maxPriceBlue;
    uint32 minBidPriceBlue;
    uint32 maxBidPriceBlue;
    uint32 maxStackBlue;
    uint32 minPricePurple;
    uint32 maxPricePurple;
    uint32 minBidPricePurple;
    uint32 maxBidPricePurple;
    uint32 maxStackPurple;
    uint32 minPriceOrange;
    uint32 maxPriceOrange;
    uint32 minBidPriceOrange;
    uint32 maxBidPriceOrange;
    uint32 maxStackOrange;
    uint32 minPriceYellow;
    uint32 maxPriceYellow;
    uint32 minBidPriceYellow;
    uint32 maxBidPriceYellow;
    uint32 maxStackYellow;

    uint32 buyerPriceGrey;
    uint32 buyerPriceWhite;
    uint32 buyerPriceGreen;
    uint32 buyerPriceBlue;
    uint32 buyerPricePurple;
    uint32 buyerPriceOrange;
    uint32 buyerPriceYellow;
    uint32 buyerBiddingInterval;
    uint32 buyerBidsPerInterval;

    uint32 greytgp;
    uint32 whitetgp;
    uint32 greentgp;
    uint32 bluetgp;
    uint32 purpletgp;
    uint32 orangetgp;
    uint32 yellowtgp;
    uint32 greyip;
    uint32 whiteip;
    uint32 greenip;
    uint32 blueip;
    uint32 purpleip;
    uint32 orangeip;
    uint32 yellowip;

    uint32 greyTGoods;
    uint32 whiteTGoods;
    uint32 greenTGoods;
    uint32 blueTGoods;
    uint32 purpleTGoods;
    uint32 orangeTGoods;
    uint32 yellowTGoods;

    uint32 greyItems;
    uint32 whiteItems;
    uint32 greenItems;
    uint32 blueItems;
    uint32 purpleItems;
    uint32 orangeItems;
    uint32 yellowItems;

public:
    AHBConfig(uint32 ahid)
    {
        AHID = ahid;
        switch (ahid)
        {
            case 2:
                AHFID = 55;
                break;
            case 6:
                AHFID = 29;
                break;
            case 7:
                AHFID = 120;
                break;
            default:
                AHFID = 120;
                break;
        }
    }

    AHBConfig()
    {
    }

    uint32 GetAHID()
    {
        return AHID;
    }

    uint32 GetAHFID()
    {
        return AHFID;
    }

    void SetMinItems(uint32 value)
    {
        minItems = value;
    }

    uint32 GetMinItems()
    {
        if ((minItems == 0) && (maxItems))
            return maxItems;
        else if ((maxItems) && (minItems > maxItems))
            return maxItems;
        else
            return minItems;
    }

    void SetMaxItems(uint32 value)
    {
        maxItems = value;
        // CalculatePercents() needs to be called, but only if
        // SetPercentages() has been called at least once already.
    }

    uint32 GetMaxItems()
    {
        return maxItems;
    }

    void
    SetPercentages(uint32 greytg, uint32 whitetg, uint32 greentg, uint32 bluetg, uint32 purpletg, uint32 orangetg, uint32 yellowtg, uint32 greyi, uint32 whitei,
                   uint32 greeni, uint32 bluei, uint32 purplei, uint32 orangei, uint32 yellowi)
    {
        uint32 totalPercent =
                greytg + whitetg + greentg + bluetg + purpletg + orangetg + yellowtg + greyi + whitei + greeni + bluei + purplei + orangei + yellowi;

        if (totalPercent == 0)
        {
            maxItems = 0;
        }
        else if (totalPercent != 100)
        {
            greytg = 0;
            whitetg = 27;
            greentg = 12;
            bluetg = 10;
            purpletg = 1;
            orangetg = 0;
            yellowtg = 0;
            greyi = 0;
            whitei = 10;
            greeni = 30;
            bluei = 8;
            purplei = 2;
            orangei = 0;
            yellowi = 0;
        }
        percentGreyTradeGoods = greytg;
        percentWhiteTradeGoods = whitetg;
        percentGreenTradeGoods = greentg;
        percentBlueTradeGoods = bluetg;
        percentPurpleTradeGoods = purpletg;
        percentOrangeTradeGoods = orangetg;
        percentYellowTradeGoods = yellowtg;
        percentGreyItems = greyi;
        percentWhiteItems = whitei;
        percentGreenItems = greeni;
        percentBlueItems = bluei;
        percentPurpleItems = purplei;
        percentOrangeItems = orangei;
        percentYellowItems = yellowi;
        CalculatePercents();
    }

    uint32 GetPercentages(uint32 color)
    {
        switch (color)
        {
            case AHB_GREY_TG:
                return percentGreyTradeGoods;
            case AHB_WHITE_TG:
                return percentWhiteTradeGoods;
            case AHB_GREEN_TG:
                return percentGreenTradeGoods;
            case AHB_BLUE_TG:
                return percentBlueTradeGoods;
            case AHB_PURPLE_TG:
                return percentPurpleTradeGoods;
            case AHB_ORANGE_TG:
                return percentOrangeTradeGoods;
            case AHB_YELLOW_TG:
                return percentYellowTradeGoods;
            case AHB_GREY_I:
                return percentGreyItems;
            case AHB_WHITE_I:
                return percentWhiteItems;
            case AHB_GREEN_I:
                return percentGreenItems;
            case AHB_BLUE_I:
                return percentBlueItems;
            case AHB_PURPLE_I:
                return percentPurpleItems;
            case AHB_ORANGE_I:
                return percentOrangeItems;
            case AHB_YELLOW_I:
                return percentYellowItems;
            default:
                return 0;
        }
    }

    void SetMinPrice(uint32 color, uint32 value)
    {
        switch (color)
        {
            case AHB_GREY:
                minPriceGrey = value;
                break;
            case AHB_WHITE:
                minPriceWhite = value;
                break;
            case AHB_GREEN:
                minPriceGreen = value;
                break;
            case AHB_BLUE:
                minPriceBlue = value;
                break;
            case AHB_PURPLE:
                minPricePurple = value;
                break;
            case AHB_ORANGE:
                minPriceOrange = value;
                break;
            case AHB_YELLOW:
                minPriceYellow = value;
                break;
            default:
                break;
        }
    }

    uint32 GetMinPrice(uint32 color)
    {
        switch (color)
        {
            case AHB_GREY:
            {
                if (minPriceGrey == 0)
                    return 100;
                else if (minPriceGrey > maxPriceGrey)
                    return maxPriceGrey;
                else
                    return minPriceGrey;
            }
            case AHB_WHITE:
            {
                if (minPriceWhite == 0)
                    return 150;
                else if (minPriceWhite > maxPriceWhite)
                    return maxPriceWhite;
                else
                    return minPriceWhite;
            }
            case AHB_GREEN:
            {
                if (minPriceGreen == 0)
                    return 200;
                else if (minPriceGreen > maxPriceGreen)
                    return maxPriceGreen;
                else
                    return minPriceGreen;
            }
            case AHB_BLUE:
            {
                if (minPriceBlue == 0)
                    return 250;
                else if (minPriceBlue > maxPriceBlue)
                    return maxPriceBlue;
                else
                    return minPriceBlue;
            }
            case AHB_PURPLE:
            {
                if (minPricePurple == 0)
                    return 300;
                else if (minPricePurple > maxPricePurple)
                    return maxPricePurple;
                else
                    return minPricePurple;
            }
            case AHB_ORANGE:
            {
                if (minPriceOrange == 0)
                    return 400;
                else if (minPriceOrange > maxPriceOrange)
                    return maxPriceOrange;
                else
                    return minPriceOrange;
            }
            case AHB_YELLOW:
            {
                if (minPriceYellow == 0)
                    return 500;
                else if (minPriceYellow > maxPriceYellow)
                    return maxPriceYellow;
                else
                    return minPriceYellow;
            }
            default:
            {
                return 0;
            }
        }
    }

    void SetMaxPrice(uint32 color, uint32 value)
    {
        switch (color)
        {
            case AHB_GREY:
                maxPriceGrey = value;
                break;
            case AHB_WHITE:
                maxPriceWhite = value;
                break;
            case AHB_GREEN:
                maxPriceGreen = value;
                break;
            case AHB_BLUE:
                maxPriceBlue = value;
                break;
            case AHB_PURPLE:
                maxPricePurple = value;
                break;
            case AHB_ORANGE:
                maxPriceOrange = value;
                break;
            case AHB_YELLOW:
                maxPriceYellow = value;
                break;
            default:
                break;
        }
    }

    uint32 GetMaxPrice(uint32 color)
    {
        switch (color)
        {
            case AHB_GREY:
            {
                if (maxPriceGrey == 0)
                    return 150;
                else
                    return maxPriceGrey;
            }
            case AHB_WHITE:
            {
                if (maxPriceWhite == 0)
                    return 250;
                else
                    return maxPriceWhite;
            }
            case AHB_GREEN:
            {
                if (maxPriceGreen == 0)
                    return 300;
                else
                    return maxPriceGreen;
            }
            case AHB_BLUE:
            {
                if (maxPriceBlue == 0)
                    return 350;
                else
                    return maxPriceBlue;
            }
            case AHB_PURPLE:
            {
                if (maxPricePurple == 0)
                    return 450;
                else
                    return maxPricePurple;
            }
            case AHB_ORANGE:
            {
                if (maxPriceOrange == 0)
                    return 550;
                else
                    return maxPriceOrange;
            }
            case AHB_YELLOW:
            {
                if (maxPriceYellow == 0)
                    return 650;
                else
                    return maxPriceYellow;
            }
            default:
            {
                return 0;
            }
        }
    }

    void SetMinBidPrice(uint32 color, uint32 value)
    {
        switch (color)
        {
            case AHB_GREY:
                minBidPriceGrey = value;
                break;
            case AHB_WHITE:
                minBidPriceWhite = value;
                break;
            case AHB_GREEN:
                minBidPriceGreen = value;
                break;
            case AHB_BLUE:
                minBidPriceBlue = value;
                break;
            case AHB_PURPLE:
                minBidPricePurple = value;
                break;
            case AHB_ORANGE:
                minBidPriceOrange = value;
                break;
            case AHB_YELLOW:
                minBidPriceYellow = value;
                break;
            default:
                break;
        }
    }

    uint32 GetMinBidPrice(uint32 color)
    {
        switch (color)
        {
            case AHB_GREY:
            {
                if (minBidPriceGrey > 100)
                    return 100;
                else
                    return minBidPriceGrey;
            }
            case AHB_WHITE:
            {
                if (minBidPriceWhite > 100)
                    return 100;
                else
                    return minBidPriceWhite;
            }
            case AHB_GREEN:
            {
                if (minBidPriceGreen > 100)
                    return 100;
                else
                    return minBidPriceGreen;
            }
            case AHB_BLUE:
            {
                if (minBidPriceBlue > 100)
                    return 100;
                else
                    return minBidPriceBlue;
            }
            case AHB_PURPLE:
            {
                if (minBidPricePurple > 100)
                    return 100;
                else
                    return minBidPricePurple;
            }
            case AHB_ORANGE:
            {
                if (minBidPriceOrange > 100)
                    return 100;
                else
                    return minBidPriceOrange;
            }
            case AHB_YELLOW:
            {
                if (minBidPriceYellow > 100)
                    return 100;
                else
                    return minBidPriceYellow;
            }
            default:
            {
                return 0;
            }
        }
    }

    void SetMaxBidPrice(uint32 color, uint32 value)
    {
        switch (color)
        {
            case AHB_GREY:
                maxBidPriceGrey = value;
                break;
            case AHB_WHITE:
                maxBidPriceWhite = value;
                break;
            case AHB_GREEN:
                maxBidPriceGreen = value;
                break;
            case AHB_BLUE:
                maxBidPriceBlue = value;
                break;
            case AHB_PURPLE:
                maxBidPricePurple = value;
                break;
            case AHB_ORANGE:
                maxBidPriceOrange = value;
                break;
            case AHB_YELLOW:
                maxBidPriceYellow = value;
                break;
            default:
                break;
        }
    }

    uint32 GetMaxBidPrice(uint32 color)
    {
        switch (color)
        {
            case AHB_GREY:
            {
                if (maxBidPriceGrey > 100)
                    return 100;
                else
                    return maxBidPriceGrey;
            }
            case AHB_WHITE:
            {
                if (maxBidPriceWhite > 100)
                    return 100;
                else
                    return maxBidPriceWhite;
            }
            case AHB_GREEN:
            {
                if (maxBidPriceGreen > 100)
                    return 100;
                else
                    return maxBidPriceGreen;
            }
            case AHB_BLUE:
            {
                if (maxBidPriceBlue > 100)
                    return 100;
                else
                    return maxBidPriceBlue;
            }
            case AHB_PURPLE:
            {
                if (maxBidPricePurple > 100)
                    return 100;
                else
                    return maxBidPricePurple;
            }
            case AHB_ORANGE:
            {
                if (maxBidPriceOrange > 100)
                    return 100;
                else
                    return maxBidPriceOrange;
            }
            case AHB_YELLOW:
            {
                if (maxBidPriceYellow > 100)
                    return 100;
                else
                    return maxBidPriceYellow;
            }
            default:
            {
                return 0;
            }
        }
    }

    void SetMaxStack(uint32 color, uint32 value)
    {
        switch (color)
        {
            case AHB_GREY:
                maxStackGrey = value;
                break;
            case AHB_WHITE:
                maxStackWhite = value;
                break;
            case AHB_GREEN:
                maxStackGreen = value;
                break;
            case AHB_BLUE:
                maxStackBlue = value;
                break;
            case AHB_PURPLE:
                maxStackPurple = value;
                break;
            case AHB_ORANGE:
                maxStackOrange = value;
                break;
            case AHB_YELLOW:
                maxStackYellow = value;
                break;
            default:
                break;
        }
    }

    uint32 GetMaxStack(uint32 color)
    {
        switch (color)
        {
            case AHB_GREY:
            {
                return maxStackGrey;
            }
            case AHB_WHITE:
            {
                return maxStackWhite;
            }
            case AHB_GREEN:
            {
                return maxStackGreen;
            }
            case AHB_BLUE:
            {
                return maxStackBlue;
            }
            case AHB_PURPLE:
            {
                return maxStackPurple;
            }
            case AHB_ORANGE:
            {
                return maxStackOrange;
            }
            case AHB_YELLOW:
            {
                return maxStackYellow;
            }
            default:
            {
                return 0;
            }
        }
    }

    void SetBuyerPrice(uint32 color, uint32 value)
    {
        switch (color)
        {
            case AHB_GREY:
                buyerPriceGrey = value;
                break;
            case AHB_WHITE:
                buyerPriceWhite = value;
                break;
            case AHB_GREEN:
                buyerPriceGreen = value;
                break;
            case AHB_BLUE:
                buyerPriceBlue = value;
                break;
            case AHB_PURPLE:
                buyerPricePurple = value;
                break;
            case AHB_ORANGE:
                buyerPriceOrange = value;
                break;
            case AHB_YELLOW:
                buyerPriceYellow = value;
                break;
            default:
                break;
        }
    }

    uint32 GetBuyerPrice(uint32 color)
    {
        switch (color)
        {
            case AHB_GREY:
                return buyerPriceGrey;
            case AHB_WHITE:
                return buyerPriceWhite;
            case AHB_GREEN:
                return buyerPriceGreen;
            case AHB_BLUE:
                return buyerPriceBlue;
            case AHB_PURPLE:
                return buyerPricePurple;
            case AHB_ORANGE:
                return buyerPriceOrange;
            case AHB_YELLOW:
                return buyerPriceYellow;
            default:
                return 0;
        }
    }

    void SetBiddingInterval(uint32 value)
    {
        buyerBiddingInterval = value;
    }

    uint32 GetBiddingInterval()
    {
        return buyerBiddingInterval;
    }

    void CalculatePercents()
    {
        greytgp = (uint32) (((double) percentGreyTradeGoods / 100.0) * maxItems);
        whitetgp = (uint32) (((double) percentWhiteTradeGoods / 100.0) * maxItems);
        greentgp = (uint32) (((double) percentGreenTradeGoods / 100.0) * maxItems);
        bluetgp = (uint32) (((double) percentBlueTradeGoods / 100.0) * maxItems);
        purpletgp = (uint32) (((double) percentPurpleTradeGoods / 100.0) * maxItems);
        orangetgp = (uint32) (((double) percentOrangeTradeGoods / 100.0) * maxItems);
        yellowtgp = (uint32) (((double) percentYellowTradeGoods / 100.0) * maxItems);
        greyip = (uint32) (((double) percentGreyItems / 100.0) * maxItems);
        whiteip = (uint32) (((double) percentWhiteItems / 100.0) * maxItems);
        greenip = (uint32) (((double) percentGreenItems / 100.0) * maxItems);
        blueip = (uint32) (((double) percentBlueItems / 100.0) * maxItems);
        purpleip = (uint32) (((double) percentPurpleItems / 100.0) * maxItems);
        orangeip = (uint32) (((double) percentOrangeItems / 100.0) * maxItems);
        yellowip = (uint32) (((double) percentYellowItems / 100.0) * maxItems);
        uint32 total = greytgp + whitetgp + greentgp + bluetgp + purpletgp + orangetgp + yellowtgp + greyip + whiteip + greenip + blueip + purpleip + orangeip +
                       yellowip;
        int32 diff = (maxItems - total);
        if (diff < 0)
        {
            if ((whiteip - diff) > 0)
                whiteip -= diff;
            else if ((greenip - diff) > 0)
                greenip -= diff;
        }
    }

    uint32 GetPercents(uint32 color)
    {
        switch (color)
        {
            case AHB_GREY_TG:
                return greytgp;
            case AHB_WHITE_TG:
                return whitetgp;
            case AHB_GREEN_TG:
                return greentgp;
            case AHB_BLUE_TG:
                return bluetgp;
            case AHB_PURPLE_TG:
                return purpletgp;
            case AHB_ORANGE_TG:
                return orangetgp;
            case AHB_YELLOW_TG:
                return yellowtgp;
            case AHB_GREY_I:
                return greyip;
            case AHB_WHITE_I:
                return whiteip;
            case AHB_GREEN_I:
                return greenip;
            case AHB_BLUE_I:
                return blueip;
            case AHB_PURPLE_I:
                return purpleip;
            case AHB_ORANGE_I:
                return orangeip;
            case AHB_YELLOW_I:
                return yellowip;
            default:
                return 0;
        }
    }

    void DecItemCounts(uint32 Class, uint32 Quality)
    {
        switch (Class)
        {
            case ITEM_CLASS_TRADE_GOODS:
                DecItemCounts(Quality);
                break;
            default:
                DecItemCounts(Quality + 7);
                break;
        }
    }

    void DecItemCounts(uint32 color)
    {
        switch (color)
        {
            case AHB_GREY_TG:
                --greyTGoods;
                break;
            case AHB_WHITE_TG:
                --whiteTGoods;
                break;
            case AHB_GREEN_TG:
                --greenTGoods;
                break;
            case AHB_BLUE_TG:
                --blueTGoods;
                break;
            case AHB_PURPLE_TG:
                --purpleTGoods;
                break;
            case AHB_ORANGE_TG:
                --orangeTGoods;
                break;
            case AHB_YELLOW_TG:
                --yellowTGoods;
                break;
            case AHB_GREY_I:
                --greyItems;
                break;
            case AHB_WHITE_I:
                --whiteItems;
                break;
            case AHB_GREEN_I:
                --greenItems;
                break;
            case AHB_BLUE_I:
                --blueItems;
                break;
            case AHB_PURPLE_I:
                --purpleItems;
                break;
            case AHB_ORANGE_I:
                --orangeItems;
                break;
            case AHB_YELLOW_I:
                --yellowItems;
                break;
            default:
                break;
        }
    }

    void IncItemCounts(uint32 Class, uint32 Quality)
    {
        switch (Class)
        {
            case ITEM_CLASS_TRADE_GOODS:
                IncItemCounts(Quality);
                break;
            default:
                IncItemCounts(Quality + 7);
                break;
        }
    }

    void IncItemCounts(uint32 color)
    {
        switch (color)
        {
            case AHB_GREY_TG:
                ++greyTGoods;
                break;
            case AHB_WHITE_TG:
                ++whiteTGoods;
                break;
            case AHB_GREEN_TG:
                ++greenTGoods;
                break;
            case AHB_BLUE_TG:
                ++blueTGoods;
                break;
            case AHB_PURPLE_TG:
                ++purpleTGoods;
                break;
            case AHB_ORANGE_TG:
                ++orangeTGoods;
                break;
            case AHB_YELLOW_TG:
                ++yellowTGoods;
                break;
            case AHB_GREY_I:
                ++greyItems;
                break;
            case AHB_WHITE_I:
                ++whiteItems;
                break;
            case AHB_GREEN_I:
                ++greenItems;
                break;
            case AHB_BLUE_I:
                ++blueItems;
                break;
            case AHB_PURPLE_I:
                ++purpleItems;
                break;
            case AHB_ORANGE_I:
                ++orangeItems;
                break;
            case AHB_YELLOW_I:
                ++yellowItems;
                break;
            default:
                break;
        }
    }

    void ResetItemCounts()
    {
        greyTGoods = 0;
        whiteTGoods = 0;
        greenTGoods = 0;
        blueTGoods = 0;
        purpleTGoods = 0;
        orangeTGoods = 0;
        yellowTGoods = 0;

        greyItems = 0;
        whiteItems = 0;
        greenItems = 0;
        blueItems = 0;
        purpleItems = 0;
        orangeItems = 0;
        yellowItems = 0;
    }

    uint32 GetItemCounts(uint32 color)
    {
        switch (color)
        {
            case AHB_GREY_TG:
                return greyTGoods;
            case AHB_WHITE_TG:
                return whiteTGoods;
            case AHB_GREEN_TG:
                return greenTGoods;
            case AHB_BLUE_TG:
                return blueTGoods;
            case AHB_PURPLE_TG:
                return purpleTGoods;
            case AHB_ORANGE_TG:
                return orangeTGoods;
            case AHB_YELLOW_TG:
                return yellowTGoods;
            case AHB_GREY_I:
                return greyItems;
            case AHB_WHITE_I:
                return whiteItems;
            case AHB_GREEN_I:
                return greenItems;
            case AHB_BLUE_I:
                return blueItems;
            case AHB_PURPLE_I:
                return purpleItems;
            case AHB_ORANGE_I:
                return orangeItems;
            case AHB_YELLOW_I:
                return yellowItems;
            default:
                return 0;
        }
    }

    void SetBidsPerInterval(uint32 value)
    {
        buyerBidsPerInterval = value;
    }

    uint32 GetBidsPerInterval()
    {
        return buyerBidsPerInterval;
    }

    ~AHBConfig()
    {
    }
};

class AuctionHouseBot
{
private:

    bool debug_Out;
    bool debug_Out_Filters;

    bool AHBSeller;
    bool AHBBuyer;
    bool UseBuyPriceForBuyer;
    bool UseBuyPriceForSeller;

    uint32 AHBplayerAccount;
    ObjectGuid::LowType AHBplayerGUID;
    uint32 ItemsPerCycle;

    //Begin Filters

    bool Vendor_Items;
    bool Loot_Items;
    bool Other_Items;
    bool Vendor_TGs;
    bool Loot_TGs;
    bool Other_TGs;

    bool No_Bind;
    bool Bind_When_Picked_Up;
    bool Bind_When_Equipped;
    bool Bind_When_Use;
    bool Bind_Quest_Item;

    bool DisablePermEnchant;
    bool DisableConjured;
    bool DisableGems;
    bool DisableMoney;
    bool DisableMoneyLoot;
    bool DisableLootable;
    bool DisableKeys;
    bool DisableDuration;
    bool DisableBOP_Or_Quest_NoReqLevel;
    bool DisablePets;
    bool DisableMounts;

    bool DisableWarriorItems;
    bool DisablePaladinItems;
    bool DisableHunterItems;
    bool DisableRogueItems;
    bool DisablePriestItems;
    bool DisableDKItems;
    bool DisableShamanItems;
    bool DisableMageItems;
    bool DisableWarlockItems;
    bool DisableUnusedClassItems;
    bool DisableDruidItems;

    uint32 DisableItemsBelowLevel;
    uint32 DisableItemsAboveLevel;
    uint32 DisableTGsBelowLevel;
    uint32 DisableTGsAboveLevel;
    uint32 DisableItemsBelowGUID;
    uint32 DisableItemsAboveGUID;
    uint32 DisableTGsBelowGUID;
    uint32 DisableTGsAboveGUID;
    uint32 DisableItemsBelowReqLevel;
    uint32 DisableItemsAboveReqLevel;
    uint32 DisableTGsBelowReqLevel;
    uint32 DisableTGsAboveReqLevel;
    uint32 DisableItemsBelowReqSkillRank;
    uint32 DisableItemsAboveReqSkillRank;
    uint32 DisableTGsBelowReqSkillRank;
    uint32 DisableTGsAboveReqSkillRank;

    std::set<uint32> DisableItemStore;

    //End Filters

    AHBConfig AllianceConfig;
    AHBConfig HordeConfig;
    AHBConfig NeutralConfig;

    time_t _lastrun_a;
    time_t _lastrun_h;
    time_t _lastrun_n;

    inline uint32 minValue(uint32 a, uint32 b)
    { return a <= b ? a : b; };

    void addNewAuctions(Player* AHBplayer, AHBConfig* config);

    void addNewAuctionBuyerBotBid(Player* AHBplayer, AHBConfig* config, WorldSession* session);

    static uint32 getPrice(const ItemTemplate* item, bool useBuyPrice = false);
    static uint32 getCustomScaling(const ItemTemplate* item);

    AuctionHouseBot();

public:
    static AuctionHouseBot* instance()
    {
        static AuctionHouseBot instance;
        return &instance;
    }

    ~AuctionHouseBot();

    void Update();

    void Initialize();

    void InitializeConfiguration();

    void LoadValues(AHBConfig*);

    void DecrementItemCounts(AuctionEntry* ah, uint32 itemEntry);

    void IncrementItemCounts(AuctionEntry* ah);

    void Commands(uint32, uint32, uint32, char*);

    ObjectGuid::LowType GetAHBplayerGUID()
    { return AHBplayerGUID; };

    uint32 getMaxStackCount(AHBConfig* config, const Item* item, const ItemTemplate* prototype);
};

#define auctionbot AuctionHouseBot::instance()

#endif
