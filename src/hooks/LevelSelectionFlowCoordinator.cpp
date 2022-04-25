#include "main.hpp"
#include "TakeMeToResults.hpp"
#include "Classes/CachedViewControllers.hpp"

#include "UnityEngine/Object.hpp"

using namespace GlobalNamespace;

MAKE_HOOK_MATCH(CacheDetailsView, &LevelSelectionFlowCoordinator::ActionButtonWasPressed, void, LevelSelectionFlowCoordinator *self) {
    auto correctSelectedLevel = UnityEngine::Object::FindObjectOfType<SoloFreePlayFlowCoordinator *>();
    CachedViewControllers::correctSelectedLevel = correctSelectedLevel;
    CacheDetailsView(self);
}

void TakeMeToResults::HookInstallers::LevelSelectionFlowCoordinator(Logger &logger) {
    INSTALL_HOOK(logger, CacheDetailsView);
}

