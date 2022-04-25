#include "TakeMeToResults.hpp"
#include "Classes/CachedViewControllers.hpp"

#include "System/Action.hpp"

#include "UnityEngine/Object.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/RectTransform.hpp"

#include "questui/shared/BeatSaberUI.hpp"

#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/SoloFreePlayFlowCoordinator.hpp"
#include "GlobalNamespace/StandardLevelDetailView.hpp"

using namespace GlobalNamespace;
using namespace HMUI;

void ShowOtherViewControllers()
{
    auto levelSelectFlowCoord = UnityEngine::Object::FindObjectOfType<SoloFreePlayFlowCoordinator *>();
    levelSelectFlowCoord->SetLeftScreenViewController(CachedViewControllers::leftScreenViewController, ViewController::AnimationType::In);
    levelSelectFlowCoord->SetRightScreenViewController(CachedViewControllers::rightScreenViewController, ViewController::AnimationType::In);
    levelSelectFlowCoord->SetTopScreenViewController(CachedViewControllers::topScreenViewController, ViewController::AnimationType::In);
    levelSelectFlowCoord->SetBottomScreenViewController(CachedViewControllers::bottomScreenViewController, ViewController::AnimationType::In);
}

UnityEngine::UI::Button *resultsButton;
MAKE_HOOK_MATCH(LeaderboardDidActivate, &PlatformLeaderboardViewController::DidActivate, void, PlatformLeaderboardViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    if (firstActivation)
    {
        CachedViewControllers::Clear();
        resultsButton = QuestUI::BeatSaberUI::CreateUIButton(self->get_transform(), "View Results", []()
        {
            auto FreePlayCoord = UnityEngine::Object::FindObjectOfType<SoloFreePlayFlowCoordinator *>();
            auto SoloFreePlayCoordinator = FreePlayCoord->YoungestChildFlowCoordinatorOrSelf();
            if(SoloFreePlayCoordinator != CachedViewControllers::correctSelectedLevel) {
            getLogger().info("Trying to present correct level view.");
            SoloFreePlayCoordinator->PresentFlowCoordinator(CachedViewControllers::correctSelectedLevel, NULL, ViewController::AnimationDirection::Horizontal, true, true);
            getLogger().info("Presented correct level view.");
            SoloFreePlayCoordinator = CachedViewControllers::correctSelectedLevel;
            getLogger().info("Set flow coordinator to correct level view.");
            }
            SoloFreePlayCoordinator->PresentViewController(CachedViewControllers::topViewController, il2cpp_utils::MakeDelegate<System::Action*>((std::function<void()>) [] { ShowOtherViewControllers(); }), ViewController::AnimationDirection::Vertical, false);
        });
        getLogger().info("Created View Results UIButton.");
        auto rect = reinterpret_cast<UnityEngine::RectTransform *>(resultsButton->get_transform());
        rect->set_anchoredPosition({-47.3, -27});
        getLogger().info("Set the anchoredPosition of the View Results UIButton.");
        resultsButton->set_interactable(false);
        getLogger().info("Set View Results UIButton to be uninteractable.");
    }
    
    LeaderboardDidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

MAKE_HOOK_MATCH(AllowButtonClicks, &ResultsViewController::DidDeactivate, void, ResultsViewController *self, bool removedFromHierarchy, bool screenSystemDisabling) {
    resultsButton->set_interactable(true);
    getLogger().info("Set View Results UIButton to be interactable.");

    AllowButtonClicks(self, removedFromHierarchy, screenSystemDisabling);
}

void TakeMeToResults::HookInstallers::PlatformLeaderboardViewController(Logger &logger) {
    INSTALL_HOOK(logger, LeaderboardDidActivate);
}

void TakeMeToResults::HookInstallers::ResultsViewController_DidDeactivate(Logger &logger) {
    INSTALL_HOOK(logger, AllowButtonClicks);
}