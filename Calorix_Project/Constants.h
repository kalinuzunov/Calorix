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

        constexpr double ACTIVITY_MULTIPLIER_SEDENTARY   = 1.2;
        constexpr double ACTIVITY_MULTIPLIER_LIGHT       = 1.375;
        constexpr double ACTIVITY_MULTIPLIER_MODERATE    = 1.55;
        constexpr double ACTIVITY_MULTIPLIER_ACTIVE      = 1.725;
        constexpr double ACTIVITY_MULTIPLIER_VERY_ACTIVE = 1.9;

        constexpr double ACTIVITY_MULTIPLIERS[] = {
            ACTIVITY_MULTIPLIER_SEDENTARY,
            ACTIVITY_MULTIPLIER_LIGHT,
            ACTIVITY_MULTIPLIER_MODERATE,
            ACTIVITY_MULTIPLIER_ACTIVE,
            ACTIVITY_MULTIPLIER_VERY_ACTIVE
        };

        constexpr double GOAL_MODIFIER_WEIGHT_LOSS = -500.0;
        constexpr double GOAL_MODIFIER_MAINTENANCE = 0.0;
        constexpr double GOAL_MODIFIER_BULKING     = 300.0;
        constexpr double GOAL_MODIFIER_NONE        = 0.0;

        constexpr double GOAL_CALORIE_MODIFIERS[] = {
            GOAL_MODIFIER_WEIGHT_LOSS,
            GOAL_MODIFIER_MAINTENANCE,
            GOAL_MODIFIER_BULKING,
            GOAL_MODIFIER_NONE
        };

        constexpr double MIN_SAFE_CALORIES_MALE = 1500.0;
        constexpr double MIN_SAFE_CALORIES_FEMALE = 1200.0;
        constexpr double MIN_SAFE_CALORIES_OTHER = (MIN_SAFE_CALORIES_MALE + MIN_SAFE_CALORIES_FEMALE) / 2.0;

        constexpr double MIN_SAFE_CALORIES[] = {
            MIN_SAFE_CALORIES_MALE,
            MIN_SAFE_CALORIES_FEMALE,
            MIN_SAFE_CALORIES_OTHER
        };

        namespace MifflinStJeor {
            constexpr double WEIGHT_MULTIPLIER = 10.0;
            constexpr double HEIGHT_MULTIPLIER = 6.25;
            constexpr double AGE_MULTIPLIER = 5.0;

            constexpr double MALE_MODIFIER = 5.0;
            constexpr double FEMALE_MODIFIER = -161.0;
            constexpr double OTHER_MODIFIER = (MALE_MODIFIER + FEMALE_MODIFIER) / 2.0;

            constexpr double MODIFIERS[] = {
                MALE_MODIFIER,
                FEMALE_MODIFIER,
                OTHER_MODIFIER
            };
        }

        namespace HarrisBenedict {
            constexpr double MALE_BASE = 66.5;
            constexpr double FEMALE_BASE = 655.1;
            constexpr double OTHER_BASE = (MALE_BASE + FEMALE_BASE) / 2.0;
            constexpr double BASE[] = {MALE_BASE, FEMALE_BASE, OTHER_BASE};

            constexpr double MALE_WEIGHT_MULT = 13.75;
            constexpr double FEMALE_WEIGHT_MULT = 9.563;
            constexpr double OTHER_WEIGHT_MULT = (MALE_WEIGHT_MULT + FEMALE_WEIGHT_MULT) / 2.0;
            constexpr double WEIGHT_MULT[] = {MALE_WEIGHT_MULT, FEMALE_WEIGHT_MULT, OTHER_WEIGHT_MULT};

            constexpr double MALE_HEIGHT_MULT = 5.003;
            constexpr double FEMALE_HEIGHT_MULT = 1.850;
            constexpr double OTHER_HEIGHT_MULT = (MALE_HEIGHT_MULT + FEMALE_HEIGHT_MULT) / 2.0;
            constexpr double HEIGHT_MULT[] = {MALE_HEIGHT_MULT, FEMALE_HEIGHT_MULT, OTHER_HEIGHT_MULT};

            constexpr double MALE_AGE_MULT = 6.75;
            constexpr double FEMALE_AGE_MULT = 4.676;
            constexpr double OTHER_AGE_MULT = (MALE_AGE_MULT + FEMALE_AGE_MULT) / 2.0;
            constexpr double AGE_MULT[] = {MALE_AGE_MULT, FEMALE_AGE_MULT, OTHER_AGE_MULT};
        }

        namespace WHO {
            constexpr unsigned AGE_YOUNG = 30;
            constexpr unsigned AGE_MIDDLE = 60;

            constexpr double MALE_18_30_MULT = 15.3;
            constexpr double MALE_18_30_BASE = 679.0;
            constexpr double MALE_31_60_MULT = 11.6;
            constexpr double MALE_31_60_BASE = 879.0;
            constexpr double MALE_60_PLUS_MULT = 13.5;
            constexpr double MALE_60_PLUS_BASE = 487.0;

            constexpr double FEMALE_18_30_MULT = 14.7;
            constexpr double FEMALE_18_30_BASE = 496.0;
            constexpr double FEMALE_31_60_MULT = 8.7;
            constexpr double FEMALE_31_60_BASE = 829.0;
            constexpr double FEMALE_60_PLUS_MULT = 10.5;
            constexpr double FEMALE_60_PLUS_BASE = 596.0;
        }
    }

}