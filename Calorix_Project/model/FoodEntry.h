#pragma once
#include "IConsumable.h"
#include "Date.h"
#include <memory>

class FoodEntry {
private:
    static unsigned nextId;
    unsigned entryId;
    std::shared_ptr<IConsumable> consumableItem;
    double weightGrams;
    Date date;

public:
    FoodEntry(std::shared_ptr<IConsumable> item, double weightGrams, const Date& date);

    FoodEntry(unsigned entryId, std::shared_ptr<IConsumable> item, double weightGrams, const Date& date);

    unsigned getEntryId() const;
    std::shared_ptr<IConsumable> getItem() const;
    double getWeight() const;
    Date getDate() const;

    double getTotalCalories() const;
    double getTotalProtein() const;
    double getTotalCarbs() const;
    double getTotalFat() const;
    double getTotalFiber() const;

    static void updateNextId(unsigned loadedId);
};