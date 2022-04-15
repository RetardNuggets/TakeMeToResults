#include "TakeMeToResults.hpp"

#include "Classes/CachedViewControllers.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"

using namespace GlobalNamespace;

MAKE_HOOK_MATCH(_ResultsViewController, &ResultsViewController::DidActivate, void, ResultsViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    _ResultsViewController(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

CachedViewControllers *_ReturnCachedViewControllers = new CachedViewControllers();
CachedViewControllers *TakeMeToResults::_CachedViewControllers()
{
    return _ReturnCachedViewControllers;
}

void TakeMeToResults::HookInstallers::ResultsViewController(Logger &logger)
{
    INSTALL_HOOK(logger, _ResultsViewController);
}