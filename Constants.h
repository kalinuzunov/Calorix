#pragma once

namespace Constants {
    namespace Global {
        inline const std::string EMPTY_STRING = "";
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
    }

    namespace FoodLimits {
        constexpr double DEFAULT_MACRO_VALUE = 0.0;

    }

}