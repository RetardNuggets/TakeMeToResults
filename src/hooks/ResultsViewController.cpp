#include "TakeMeToResults.hpp"

#include "Classes/CachedViewControllers.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"

using namespace GlobalNamespace;

MAKE_HOOK_MATCH(_ResultsViewController, &ResultsViewController::DidActivate, void, ResultsViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    CachedViewControllers::Init();
    getLogger().info("Cached view controllers.");
    _ResultsViewController(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

void TakeMeToResults::HookInstallers::ResultsViewController(Logger &logger)
{
    INSTALL_HOOK(logger, _ResultsViewController);
}