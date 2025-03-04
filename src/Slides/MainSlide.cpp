//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#include "MainSlide.h"
#include <iostream>
#include <fmt/format.h>
#include <LeGUILib/GUIElements/Text.h>
#include "Elements/BoxWith3Texts.h"
#include "PriceGrouper/PriceSorter.h"
#include "Utility/TimeUtil.h"

MainSlide::MainSlide(const std::shared_ptr<ElPricesCollector>& collectorController, const std::shared_ptr<ElPricesUsageController>& usageController)
{
    for (int i = 0; i < 4; i++)
    {
        largePriceGroupColumns_.push_back(std::make_shared<LargePriceGroupColumn>(this));
        largePriceGroupColumns_[i]->setX(275*i + 50);
        largePriceGroupColumns_[i]->setY(200);
    }

    auto largePriceColumnUpdateFunction = [this] () -> void
    {
        std::vector<int> prices;
        prices.push_back(24000);
        prices.push_back(23500);
        prices.push_back(23400);
        prices.push_back(23200);
        prices.push_back(23700);
        prices.push_back(23700);
        prices.push_back(28300);
        prices.push_back(29600);
        prices.push_back(30700);
        prices.push_back(29200);
        prices.push_back(27500);
        prices.push_back(26400);
        prices.push_back(25800);
        prices.push_back(25700);
        prices.push_back(26000);
        prices.push_back(27300);
        prices.push_back(28200);
        prices.push_back(37300);
        prices.push_back(38000);
        prices.push_back(37800);
        prices.push_back(36400);
        prices.push_back(28000);
        prices.push_back(27500);
        prices.push_back(26700);

        std::unique_lock lock(mutex_);
        while (keepRunning_)
        {
            auto response = PriceSorter::findLargePriceGroups(prices);
            for (int i = 0; i < response.size(); i++)
            {
                largePriceGroupColumns_[i]->update(response[i]);
            }
            int delay = TimeUtil::secondsToNextHour();
            condVar_.wait_for(lock,std::chrono::seconds(delay));
        }
    };

    keepRunning_ = true;

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
            std::string currentTimeString = "";
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
            int secondsToWait = 60 - currentTime.tm_sec;
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