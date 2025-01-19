//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#ifndef SLIDETEMPLATE_H
#define SLIDETEMPLATE_H
#include <LeGUILib/GUIElements/Slide.h>


class SlideTemplate : public Slide
{
public:
    SlideTemplate() = default;
    virtual ~SlideTemplate() = default;
    void addElement(const std::string& key, const std::shared_ptr<GUIElement>& value)
    {
        guiElementMap_.insert(std::pair(key,value));
    }
    template <typename T>
    std::shared_ptr<T> getElement(const std::string& key)
    {
        auto element = guiElementMap_[key];
        return std::dynamic_pointer_cast<T>(element);
    }
    virtual void compose() = 0;
private:
    std::unordered_map<std::string,std::shared_ptr<GUIElement>> guiElementMap_;
};



#endif //SLIDETEMPLATE_H
