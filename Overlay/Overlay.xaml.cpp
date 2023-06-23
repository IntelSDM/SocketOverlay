﻿//#include "pch.h"
#include "Overlay.xaml.h"
#include <TlHelp32.h>
#include <thread>
#include <string>

using namespace std;

using namespace Cheat;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Graphics::Canvas;

using namespace Microsoft::Graphics::Canvas;
using namespace Microsoft::Graphics::Canvas::Text;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Gaming::XboxGameBar;

using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::UI::ViewManagement;
using namespace Windows::ApplicationModel::Core;

Microsoft::Graphics::Canvas::UI::Xaml::CanvasSwapChainPanel^ CanvasObject;

namespace sdk
{
	float WindowWidth;
	float WindowHeight;
}

Overlay::Overlay()
{
	InitializeComponent();

	// Hide Title Bar
	auto  _coreTitleBar = CoreApplication::GetCurrentView()->TitleBar;
	_coreTitleBar->ExtendViewIntoTitleBar = true;
	auto _TitleBar = ApplicationView::GetForCurrentView()->TitleBar;
	_TitleBar->ButtonBackgroundColor = Colors::Transparent;
	_TitleBar->ButtonInactiveBackgroundColor = Colors::Transparent;
	_TitleBar->ButtonPressedBackgroundColor = Colors::Transparent;
	_TitleBar->ButtonHoverBackgroundColor = Colors::Transparent;
}

//You can just pass the CanvasObject directly into this but I used it in other places also
void RenderingThread()
{
	static auto ds = CanvasObject->SwapChain->CreateDrawingSession(Colors::Transparent);

	ds->Clear(Colors::Transparent);

	/* RENDER*/
	std::string test = std::to_string(sdk::WindowWidth) + "x" + std::to_string(sdk::WindowHeight);
	std::wstring wideText(test.begin(), test.end());
	Platform::String^ text = ref new Platform::String(wideText.c_str());
	ds->DrawText(text, 0, 0, Colors::Red);

	/*END OF RENDERING*/
//	ds->FillRectangle(0,0, sdk::WindowWidth, sdk::WindowHeight,Colors::White);

	ds->Flush();

	CanvasObject->SwapChain->Present();

}


void Overlay::canvasSwapChainPanel_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	canvasSwapChainPanel->SwapChain = ref new CanvasSwapChain(CanvasDevice::GetSharedDevice(), (float)Window::Current->CoreWindow->Bounds.Width, 
		(float)Window::Current->CoreWindow->Bounds.Height, 96);

	CanvasObject = canvasSwapChainPanel;

	//lets use this it is way better for what we want
	sdk::WindowWidth = (float)Window::Current->CoreWindow->Bounds.Width;
	sdk::WindowHeight = (float)Window::Current->CoreWindow->Bounds.Height;

	std::thread RenderThread(RenderingThread);
	RenderThread.detach();

}