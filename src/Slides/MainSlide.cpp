//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#include "MainSlide.h"
#include <iostream>
#include <fmt/format.h>
#include <LeGUILib/GUIElements/Text.h>

#include "LastLargePriceGroupColumn.h"
#include "PriceGrouper/PriceSorter.h"
#include "Utility/ConfigController.h"
#include "Utility/TimeUtil.h"

MainSlide::MainSlide(const std::shared_ptr<ElPricesCollector>& collectorController, LeGUILib* guiLib) : largePriceGroupColumns_()
{

    closeAppButton_ = this->createElement<RectangleElement>();
    closeAppButton_->setX(0);
    closeAppButton_->setY(0);
    closeAppButton_->setWidth(20);
    closeAppButton_->setHeight(20);
    closeAppButton_->setColor(255,0,0);
    closeAppButton_->setZ(50);
    closeAppButton_->setOnClick([guiLib]() -> void
    {
        guiLib->closeGUI();
    });

    reloadConfigButton_ = this->createElement<RectangleElement>();
    reloadConfigButton_->setX(1260);
    reloadConfigButton_->setY(0);
    reloadConfigButton_->setWidth(20);
    reloadConfigButton_->setHeight(20);
    reloadConfigButton_->setColor(0,0,255);
    reloadConfigButton_->setZ(50);
    reloadConfigButton_->setOnClick([]() -> void
    {
        ConfigController::loadConfig("../../Resources/config.json");
    });

    hourUsageText_ = this->createElement<Text>();
    hourUsageText_->setX(550);
    hourUsageText_->setY(70);
    hourUsageText_->setColor(0,0,0);
    hourUsageText_->setFontSize(60);

    hourKRUsage_ = this->createElement<Text>();
    hourKRUsage_->setX(550);
    hourKRUsage_->setY(120);
    hourKRUsage_->setColor(0,0,0);
    hourKRUsage_->setFontSize(60);

    currentUsageWattageText_ = this->createElement<Text>();
    currentUsageWattageText_->setX(50);
    currentUsageWattageText_->setY(70);
    currentUsageWattageText_->setColor(0,0,0);
    currentUsageWattageText_->setFontSize(60);

    currentKRUsage_ = this->createElement<Text>();
    currentKRUsage_->setX(50);
    currentKRUsage_->setY(120);
    currentKRUsage_->setColor(0,0,0);
    currentKRUsage_->setFontSize(60);

    currentHourFunction_ = [this, collectorController] (int pulsesLastHour, double currentWattage) -> void
    {
        double price = collectorController->getCurrentPrice()->getTotalPrice() / 10000;

        double kwhUsed = static_cast<double>(pulsesLastHour) / 1000;
        std::string hourUsageString = fmt::format("{:.3f} KwH, Denne Time", kwhUsed);
        this->hourUsageText_->setText(hourUsageString);

        std::string hourPriceString = fmt::format("{:.2f} Kr, Denne Time", kwhUsed * price);
        this->hourKRUsage_->setText(hourPriceString);

        std::string currentUsageString = fmt::format("{:.3f} Kw", currentWattage);
        this->currentUsageWattageText_->setText(currentUsageString);

        std::string currentUsageDKKstring = fmt::format("{:.2f} Kr/Time", currentWattage * price);
        this->currentKRUsage_->setText(currentUsageDKKstring);
    };

    usageController_ = std::make_unique<ElPricesUsageController>(currentHourFunction_);


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
        text->setY(10);
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
        text->setY(10);
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

    threads_.emplace_back(largePriceColumnUpdateFunction);
    threads_.emplace_back(clockTextUpdateFunction);
    threads_.emplace_back(updateCurrentPrice);
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