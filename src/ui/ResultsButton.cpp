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
            SoloFreePlayCoordinator->PresentViewController(CachedViewControllers::topViewController, il2cpp_utils::MakeDelegate<System::Action*>((std::function<void()>) [] { ShowOtherViewControllers(); }), ViewController::AnimationDirection::Vertical, false);
        });
        getLogger().info("Created View Results UIButton.");
        auto rect = reinterpret_cast<UnityEngine::RectTransform *>(resultsButton->get_transform());
        rect->set_anchoredPosition({-17, -27});
        getLogger().info("Set the anchoredPosition of the View Results UIButton.");
        resultsButton->set_interactable(false);
        getLogger().info("Set View Results UIButton to be uninteractable.");
    }
    
    LeaderboardDidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

MAKE_HOOK_MATCH(continueButtonPressed, &ResultsViewController::ContinueButtonPressed, void, ResultsViewController *self) {
    resultsButton->set_interactable(true);
    getLogger().info("Set View Results UIButton to be interactable.");

    continueButtonPressed(self);
}

void TakeMeToResults::HookInstallers::PlatformLeaderboardViewController(Logger &logger) {
    INSTALL_HOOK(logger, LeaderboardDidActivate);
}

void TakeMeToResults::HookInstallers::ContinueButtonPressed(Logger &logger) {
    INSTALL_HOOK(logger, continueButtonPressed);
}