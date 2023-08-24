//#include "pch.h"
#include "pch.h"
#include "Overlay.xaml.h"
#include <TlHelp32.h>
#include <thread>
#include <string>
#include "Graphics.h"
#include "Input.h"
#include "Sockets.h"
#include "RectangleJson.h"
using namespace Cheat;
using namespace Platform;


Microsoft::Graphics::Canvas::UI::Xaml::CanvasSwapChainPanel^ CanvasObject;
float WindowWidth;
float WindowHeight;
CanvasDrawingSession^ SwapChain;


Overlay::Overlay()
{
	InitializeComponent();

	// Hide Title Bar
	auto  coretitlebar = CoreApplication::GetCurrentView()->TitleBar;
	coretitlebar->ExtendViewIntoTitleBar = true;
	auto titlebar = ApplicationView::GetForCurrentView()->TitleBar;
	titlebar->ButtonBackgroundColor = Colors::Transparent;
	titlebar->ButtonInactiveBackgroundColor = Colors::Transparent;
	titlebar->ButtonPressedBackgroundColor = Colors::Transparent;
	titlebar->ButtonHoverBackgroundColor = Colors::Transparent;
}

std::list<RectangleJson> RectangleList = { RectangleJson(0,0,100,100), };
//You can just pass the CanvasObject directly into this but I used it in other places also
void RenderingThread()
{
	SwapChain = CanvasObject->SwapChain->CreateDrawingSession(Colors::Transparent);
	int i = 0;
	while (true) 
	{
		i++;
		SwapChain->Clear(Colors::Transparent);
		/* RENDER*/
		if (&TCPClient)
		{
		std::string test = std::to_string(i) + "x" + std::to_string(TCPClient->RectangleList.size());
		std::wstring widetext(test.begin(), test.end());
		Platform::String^ text = ref new Platform::String(widetext.c_str());
	
		SwapChain->DrawText(text, 0, 0, Colors::Red);
		TCPClient->DrawingHandler();
		}
		
		/*END OF RENDERING*/

		SwapChain->Flush();
	
		CanvasObject->SwapChain->Present();
		
	
	}
}


void Overlay::canvasSwapChainPanel_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	canvasSwapChainPanel->SwapChain = ref new CanvasSwapChain(CanvasDevice::GetSharedDevice(), (float)Window::Current->CoreWindow->Bounds.Width, 
		(float)Window::Current->CoreWindow->Bounds.Height, 96);

	CanvasObject = canvasSwapChainPanel;

	//lets use this it is way better for what we want
	WindowWidth = (float)Window::Current->CoreWindow->Bounds.Width;
	WindowHeight = (float)Window::Current->CoreWindow->Bounds.Height;
	CreateSockets();

	std::thread renderthread(RenderingThread);
	renderthread.detach();
}
