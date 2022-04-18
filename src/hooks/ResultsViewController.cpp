#include "TakeMeToResults.hpp"

#include "Classes/CachedViewControllers.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"

using namespace GlobalNamespace;

MAKE_HOOK_MATCH(CacheViewControllers, &ResultsViewController::ContinueButtonPressed, void, ResultsViewController *self)
{
    CachedViewControllers::Init();
    getLogger().info("Cached view controllers.");
    CacheViewControllers(self);
}

void TakeMeToResults::HookInstallers::ResultsViewController_ContinueButtonPressed(Logger &logger)
{
    INSTALL_HOOK(logger, CacheViewControllers);
}