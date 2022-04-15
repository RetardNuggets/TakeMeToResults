#pragma once

#include "main.hpp"
#include "Classes/CachedViewControllers.hpp"

namespace TakeMeToResults
{
    namespace HookInstallers
    {
        void ResultsViewController(Logger &logger);
    }
    CachedViewControllers *_CachedViewControllers();
}