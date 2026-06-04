#pragma once
#include <string>

namespace Constants {
    namespace Global {
        inline const std::string EMPTY_STRING = "";
        constexpr unsigned STARTING_ID = 1;
        constexpr unsigned INVALID_ID = 0;
        constexpr double ZERO = 0.0;
    }

    namespace ProfileLimits {
        constexpr unsigned int MIN_AGE = 1;
        constexpr unsigned int MAX_AGE = 150;
        constexpr double MIN_WEIGHT = 0.0;
        constexpr double MIN_HEIGHT = 0.0; 
    }

    namespace ProfileDefaults {
        constexpr double WEIGHT = 70.0;
        constexpr double HEIGHT = 170.0;
        constexpr unsigned int AGE = 18;
    }

    namespace UserLimits {
        constexpr size_t MIN_PASSWORD_LENGTH = 8;
        constexpr unsigned DEFAULT_AGE = 0;
    }

    namespace DateLimits {
        constexpr size_t EXPECTED_STRING_LENGTH = 10;
        constexpr size_t YEAR_START_INDEX = 0;
        constexpr size_t YEAR_LENGTH = 4;
        constexpr size_t MONTH_START_INDEX = 5;
        constexpr size_t MONTH_LENGTH = 2;
        constexpr size_t DAY_START_INDEX = 8;
        constexpr size_t DAY_LENGTH = 2;

        constexpr unsigned FEBRUARY_INDEX = 2;
        constexpr unsigned MAX_MONTHS = 12;

        constexpr unsigned DEFAULT_YEAR = 2000;
        constexpr unsigned DEFAULT_MONTH = 1;
        constexpr unsigned DEFAULT_DAY = 1;

        constexpr unsigned MONTHS_IN_YEAR = 12;
        constexpr unsigned MAX_DAYS_IN_MONTH = 31;
    }

    namespace FoodLimits {
        constexpr double DEFAULT_MACRO_VALUE = 0.0;
        constexpr double BASE_GRAMS_UNIT = 100.0;
    }

    namespace ExerciseLimits {
        constexpr double DEFAULT_CALORIES_VALUE = 0.0;
        constexpr double DEFAULT_DURATION_VALUE = 0.0;
        constexpr double MINUTES_IN_HOUR = 60.0;
    }
    namespace GoalLimits {
        constexpr double DEFAULT_TARGET_VALUE = 0.0;
    }
    namespace HealthFormulas {
        constexpr double CENTIMETERS_IN_METER = 100.0;

        constexpr double BMR_WEIGHT_MULTIPLIER = 10.0;
        constexpr double BMR_HEIGHT_MULTIPLIER = 6.25;
        constexpr double BMR_AGE_MULTIPLIER = 5.0;

        constexpr double ACTIVITY_MULTIPLIER_SEDENTARY   = 1.2;
        constexpr double ACTIVITY_MULTIPLIER_LIGHT       = 1.375;
        constexpr double ACTIVITY_MULTIPLIER_MODERATE    = 1.55;
        constexpr double ACTIVITY_MULTIPLIER_ACTIVE      = 1.725;
        constexpr double ACTIVITY_MULTIPLIER_VERY_ACTIVE = 1.9;
        constexpr double ACTIVITY_MULTIPLIERS[] = {ACTIVITY_MULTIPLIER_SEDENTARY, ACTIVITY_MULTIPLIER_LIGHT, ACTIVITY_MULTIPLIER_MODERATE, ACTIVITY_MULTIPLIER_VERY_ACTIVE, ACTIVITY_MULTIPLIER_VERY_ACTIVE};

        constexpr double GOAL_MODIFIER_WEIGHT_LOSS = -500.0;
        constexpr double GOAL_MODIFIER_MAINTENANCE = 0.0;
        constexpr double GOAL_MODIFIER_BULKING     = 300.0;
        constexpr double GOAL_MODIFIER_NONE        = 0.0;
        constexpr double GOAL_CALORIE_MODIFIERS[] = {GOAL_MODIFIER_WEIGHT_LOSS, GOAL_MODIFIER_MAINTENANCE, GOAL_MODIFIER_BULKING, GOAL_MODIFIER_NONE};

        constexpr double BMR_MALE_MODIFIER = 5.0;
        constexpr double BMR_FEMALE_MODIFIER = -161.0;
        constexpr double BMR_OTHER_MODIFIER = (BMR_MALE_MODIFIER+BMR_FEMALE_MODIFIER)/2;
        constexpr double BMR_MODIFIERS[] = {BMR_MALE_MODIFIER, BMR_FEMALE_MODIFIER,BMR_OTHER_MODIFIER};

        constexpr double MIN_SAFE_CALORIES_MALE = 1500.0;
        constexpr double MIN_SAFE_CALORIES_FEMALE = 1200.0;
        constexpr double MIN_SAFE_CALORIES_OTHER = (MIN_SAFE_CALORIES_MALE + MIN_SAFE_CALORIES_FEMALE) / 2.0;

        constexpr double MIN_SAFE_CALORIES[] = {
            MIN_SAFE_CALORIES_MALE,
            MIN_SAFE_CALORIES_FEMALE,
            MIN_SAFE_CALORIES_OTHER
        };
    }

}