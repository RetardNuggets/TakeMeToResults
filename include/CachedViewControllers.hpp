#pragma once

#include "HMUI/ViewController.hpp"

namespace CachedViewControllers
{
    extern HMUI::ViewController *leftScreenViewController;
    extern HMUI::ViewController *rightScreenViewController;
    extern HMUI::ViewController *topScreenViewController;
    extern HMUI::ViewController *bottomScreenViewController;
    extern HMUI::ViewController *topViewController;
    void GetViewControllers();
    void ShowViewControllers();
    void Clear();
};