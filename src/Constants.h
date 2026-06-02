#pragma once

namespace Constants {

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
        constexpr unsigned MIN_PASSWORD_LENGTH = 3;
    }
}