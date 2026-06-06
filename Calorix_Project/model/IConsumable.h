#pragma once
#include <string>

class IConsumable {
public:
    virtual ~IConsumable() = default;

    virtual unsigned getId() const = 0;
    virtual std::string getName() const = 0;
    virtual double getCaloriesPer100g() const = 0;
    virtual double getProteinPer100g() const = 0;
    virtual double getCarbsPer100g() const = 0;
    virtual double getFatPer100g() const = 0;
    virtual double getFiberPer100g() const = 0;
};