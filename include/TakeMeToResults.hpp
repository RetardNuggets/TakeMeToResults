#pragma once

#include "main.hpp"
#include "Classes/CachedViewControllers.hpp"

namespace TakeMeToResults
{
    namespace HookInstallers
    {
        void ResultsViewController(Logger &logger);
        void SinglePlayerLevelSelectionFlowCoordinator(Logger &logger);
    }
    CachedViewControllers *_CachedViewControllers();
}