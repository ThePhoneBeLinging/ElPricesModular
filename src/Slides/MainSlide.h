//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#ifndef MAINSLIDE_H
#define MAINSLIDE_H
#include <ElPricesCollector/ElPricesCollector.h>
#include <ElPricesUsageController/ElPricesUsageController.h>
#include <LeGUILib/GUIElements/ImageElement.h>

#include "BoxChart.h"
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
    std::shared_ptr<BoxChart> boxChart_;

};



#endif //MAINSLIDE_H
