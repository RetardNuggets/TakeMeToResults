#include "TakeMeToResults.hpp"

#include "Classes/CachedViewControllers.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"

using namespace GlobalNamespace;

CachedViewControllers *_ReturnCachedViewControllers;
MAKE_HOOK_MATCH(_ResultsViewController, &ResultsViewController::DidActivate, void, ResultsViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    _ReturnCachedViewControllers = new CachedViewControllers();
    getLogger().info("Created new CachedViewControllers type");
    _ResultsViewController(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    getLogger().info("Called resultviewcontroller");
}

CachedViewControllers *TakeMeToResults::_CachedViewControllers()
    {
        return _ReturnCachedViewControllers;
    }

void TakeMeToResults::HookInstallers::ResultsViewController(Logger &logger)
{
    INSTALL_HOOK(logger, _ResultsViewController);
}