#pragma once

#include "GlobalNamespace/ResultsViewController.hpp"
#include "HMUI/ViewController.hpp"

using namespace GlobalNamespace;
using namespace HMUI;

class CachedViewControllers
{
    public:
    ViewController *leftScreenViewController;
    ViewController *rightScreenViewController;
    ViewController *topScreenViewController;
    ViewController *bottomScreenViewController;
    ViewController *topViewController;
    CachedViewControllers();
};