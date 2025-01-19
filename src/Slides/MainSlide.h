//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#ifndef MAINSLIDE_H
#define MAINSLIDE_H
#include <ElPricesCollector/ElPricesCollector.h>
#include <ElPricesUsageController/ElPricesUsageController.h>
#include <LeGUILib/GUIElements/ImageElement.h>

#include "Elements/BoxWith3Texts.h"
#include "Elements/BoxWith4Texts.h"
#include "SlideTemplate.h"
#include "Elements/TimeBox.h"


class MainSlide : public Slide
{
public:
    MainSlide();
    void compose(const std::shared_ptr<ElPricesCollector>& collectorController, const std::shared_ptr<ElPricesUsageController>& usageController) const;
private:
    [[nodiscard]] double getUsageInDKKFromInterval(int seconds, const std::shared_ptr<ElPricesCollector>& elPricesCollector_, const std::shared_ptr<ElPricesUsageController>& elPricesUsageController) const;
    std::shared_ptr<ImageElement> background_;
    std::shared_ptr<BoxWith3Texts> topLeftBox_;
    std::shared_ptr<TimeBox> timeBox_;
    std::shared_ptr<BoxWith3Texts> topRigthBox_;
    std::shared_ptr<BoxWith4Texts> bottomLeftBox_;
    std::shared_ptr<BoxWith4Texts> bottomRigthBox_;

};



#endif //MAINSLIDE_H
