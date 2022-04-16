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
#include "HMUI/TitleViewController.hpp"

#include "GlobalNamespace/SoloFreePlayFlowCoordinator.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"

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
MAKE_HOOK_MATCH(levelSelectDidActivate, &SoloFreePlayFlowCoordinator::SinglePlayerLevelSelectionFlowCoordinatorDidActivate, void, SoloFreePlayFlowCoordinator *self, bool firstActivation, bool addedToHierarchy)
{
    if (firstActivation)
    {
        CachedViewControllers::Clear();
        auto SelectionViewController = UnityEngine::Object::FindObjectOfType<TitleViewController *>();
        resultsButton = QuestUI::BeatSaberUI::CreateUIButton(SelectionViewController->get_transform(), "View Results", []()
        {
            auto FreePlayCoord = UnityEngine::Object::FindObjectOfType<SoloFreePlayFlowCoordinator *>();
            auto SoloFreePlayCoordinator = FreePlayCoord->YoungestChildFlowCoordinatorOrSelf();
            SoloFreePlayCoordinator->PresentViewController(CachedViewControllers::topViewController, il2cpp_utils::MakeDelegate<System::Action*>((std::function<void()>) [] { ShowOtherViewControllers(); }), ViewController::AnimationDirection::Vertical, false);
        });
        getLogger().info("Created View Results UIButton.");
        auto rect = reinterpret_cast<UnityEngine::RectTransform *>(resultsButton->get_transform());
        rect->set_anchoredPosition({30, -3.5});
        getLogger().info("Set anchoredPosition for View Results UIButton.");
        resultsButton->set_interactable(false);
        getLogger().info("Set View Results UIButton to be uninteractable.");
    }
    
    levelSelectDidActivate(self, firstActivation, addedToHierarchy);
}

MAKE_HOOK_MATCH(continueButtonPressed, &ResultsViewController::ContinueButtonPressed, void, ResultsViewController *self) {
    resultsButton->set_interactable(true);
    getLogger().info("Set View Results UIButton to be interactable.");

    continueButtonPressed(self);
}

void TakeMeToResults::HookInstallers::SinglePlayerLevelSelectionFlowCoordinator(Logger &logger) {
    INSTALL_HOOK(logger, levelSelectDidActivate);
}

void TakeMeToResults::HookInstallers::ContinueButtonPressed(Logger &logger) {
    INSTALL_HOOK(logger, continueButtonPressed);
}