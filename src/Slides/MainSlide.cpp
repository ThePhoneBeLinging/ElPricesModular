//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#include "MainSlide.h"
#include <iostream>
#include <fmt/format.h>
#include <LeGUILib/GUIElements/Text.h>

#include "LastLargePriceGroupColumn.h"
#include "PriceGrouper/PriceSorter.h"
#include "Utility/TimeUtil.h"

MainSlide::MainSlide(const std::shared_ptr<ElPricesCollector>& collectorController, const std::shared_ptr<ElPricesUsageController>& usageController) : largePriceGroupColumns_()
{
    for (int i = 0; i < 4; i++)
    {
        if (i == 3)
        {
            largePriceGroupColumns_.push_back(std::make_shared<LastLargePriceGroupColumn>(this));
        }
        else
        {
            largePriceGroupColumns_.push_back(std::make_shared<LargePriceGroupColumn>(this));
        }
        largePriceGroupColumns_.back()->setX(320*i + 10);
        largePriceGroupColumns_.back()->setY(200);
    }
    keepRunning_ = true;
    auto largePriceColumnUpdateFunction = [this, collectorController] () -> void
    {

        std::unique_lock lock(mutex_);
        std::vector<int> prices;
        while (keepRunning_)
        {
            prices.clear();
            auto vector = collectorController->getCurrentAndFuturePrices();
            for (const auto& price : vector)
            {
                if (price != nullptr)
                {
                    prices.push_back(price->getTotalPrice());
                }
            }
            auto response = PriceSorter::findLargePriceGroups(prices);
            for (int i = 0; i < response.size(); i++)
            {
                largePriceGroupColumns_[i]->update(response[i]);
            }
            int delay = TimeUtil::secondsToNextHour();
            condVar_.wait_for(lock,std::chrono::seconds(delay));
        }
    };



    auto clockTextUpdateFunction = [this] () -> void
    {
        std::shared_ptr<Text> text = this->createElement<Text>();
        text->setX(50);
        text->setY(50);
        text->setColor(0,0,0);
        text->setFontSize(60);
        text->setText("TEXT");
        std::unique_lock lock(mutex_);
        while (keepRunning_)
        {
            auto currentTime = TimeUtil::getCurrentTime();
            std::string currentTimeString;
            if (currentTime.tm_hour < 10)
            {
                currentTimeString.append("0");
            }
            currentTimeString.append(std::to_string(currentTime.tm_hour));
            currentTimeString.append(":");
            if (currentTime.tm_min < 10)
            {
                currentTimeString.append("0");
            }
            currentTimeString.append(std::to_string(currentTime.tm_min));
            text->setText(currentTimeString);
            int secondsToWait = TimeUtil::secondsToNextMinute();
            condVar_.wait_for(lock,std::chrono::seconds(secondsToWait));
        }
    };

    auto updateCurrentPrice = [this, collectorController] () -> void
    {
        auto text = this->createElement<Text>();
        text->setX(300);
        text->setY(50);
        text->setColor(0,0,0);
        text->setFontSize(60);
        std::unique_lock lock(mutex_);
        while (keepRunning_)
        {
            double price = collectorController->getCurrentPrice()->getTotalPrice();
            std::string string = fmt::format("{:.2f} Kr",price / 10000);
            text->setText(string);
            int secondsToWait = TimeUtil::secondsToNextHour();
            condVar_.wait_for(lock,std::chrono::seconds(secondsToWait));
        }
    };

    auto currentUsageWattFunction = [this, usageController] () -> void
    {
        auto text = this->createElement<Text>();
        text->setX(550);
        text->setY(50);
        text->setColor(0,0,0);
        text->setFontSize(60);
        std::unique_lock lock(mutex_);
        while (keepRunning_)
        {
            double wattage = usageController->getWattage();
            std::string string = fmt::format("{:.3f} Kw", wattage);
            text->setText(string);
            condVar_.wait_for(lock,std::chrono::seconds(1));
        }
    };

    auto currentKrUsage = [this, collectorController ,usageController] () -> void
    {
        auto text = this->createElement<Text>();
        text->setX(550);
        text->setY(100);
        text->setColor(0,0,0);
        text->setFontSize(60);
        std::unique_lock lock(mutex_);
        while (keepRunning_)
        {
            double wattage = usageController->getWattage();
            double price = collectorController->getCurrentPrice()->getTotalPrice() / 10000;
            std::string string = fmt::format("{:.2f} Kr/Time", wattage * price);
            text->setText(string);
            condVar_.wait_for(lock,std::chrono::seconds(1));
        }
    };
    threads_.emplace_back(largePriceColumnUpdateFunction);
    threads_.emplace_back(clockTextUpdateFunction);
    threads_.emplace_back(updateCurrentPrice);
    threads_.emplace_back(currentUsageWattFunction);
    threads_.emplace_back(currentKrUsage);
}

MainSlide::~MainSlide()
{
    keepRunning_ = false;
    condVar_.notify_all();
    for (auto& thread : threads_)
    {
        thread.join();
    }
}