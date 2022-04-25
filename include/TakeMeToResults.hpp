#pragma once

#include "main.hpp"

namespace TakeMeToResults
{
    namespace HookInstallers
    {
        void ResultsViewController_ContinueButtonPressed(Logger &logger);
        void PlatformLeaderboardViewController(Logger &logger);
        void ResultsViewController_DidDeactivate(Logger &logger);
        void LevelSelectionFlowCoordinator(Logger &logger);
    }
}