//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#include "MainSlide.h"

#include <iostream>
#include <LeGUILib/GUIElements/Text.h>
#include "Elements/BoxWith3Texts.h"
#include "Utility/TimeUtil.h"

MainSlide::MainSlide(const std::shared_ptr<ElPricesCollector>& collectorController, const std::shared_ptr<ElPricesUsageController>& usageController)
{
    boxChart_ = std::make_shared<BoxChart>(this);
    boxChart_->setSpacing(15);
    boxChart_->setBoxWidth(15);
    boxChart_->setX(125);
    boxChart_->setY(650);
    boxChart_->setHeight(250);
    keepRunning_ = true;

    auto updateBoxChartFunction = [this, collectorController] () -> void
    {
        std::unique_lock lock(mutex_);
        while (keepRunning_)
        {
            std::vector<double> values;
            for (const auto& val : collectorController->getCurrentAndFuturePrices())
            {
                values.push_back(static_cast<double>(val->getTotalPrice()) / 10000);

            }
            boxChart_->setPrices(values);
            int secondsToWait = TimeUtil::secondsToNextHour();
            condVar_.wait_for(lock,std::chrono::seconds(secondsToWait));
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
            std::string string = std::format("{:.2f} Kr",price / 10000);
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
            std::string string = std::format("{:.3f} Kw", wattage);
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
            std::string string = std::format("{:.2f} Kr/Time", wattage * price);
            text->setText(string);
            condVar_.wait_for(lock,std::chrono::seconds(1));
        }
    };

    threads_.emplace_back(updateBoxChartFunction);
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