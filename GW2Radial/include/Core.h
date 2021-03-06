#pragma once

#include <Main.h>
#include <Singleton.h>
#include <Wheel.h>
#include <UnitQuad.h>
#include <CustomWheel.h>

namespace GW2Radial
{

class Core : public Singleton<Core>
{
public:
	static void Init(HMODULE dll);
	static void Shutdown();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	Core() = default;
	~Core();

	void ForceReloadWheels() { forceReloadWheels_ = true; }

	HWND gameWindow() const { return gameWindow_; }
	HMODULE dllModule() const { return dllModule_; }
	WNDPROC baseWndProc() const { return baseWndProc_; }
	uint screenWidth() const { return screenWidth_; }
	uint screenHeight() const { return screenHeight_; }
	const std::unique_ptr<UnitQuad>& quad() const { return quad_; }
	Effect* mainEffect() const { return mainEffect_; }
	ImFont* font() const { return font_; }
	ImFont* fontBlack() const { return fontBlack_; }
	ImFont* fontItalic() const { return fontItalic_; }

	void OnInjectorCreated();

protected:
	void InternalInit();
	void OnFocusLost();
	void OnFocus();
	void OnUpdate();

	void OnDeviceSet(IDirect3DDevice9 *device, D3DPRESENT_PARAMETERS *presentationParameters);
	void OnDeviceUnset();

	void PreCreateDevice(HWND hFocusWindow);
	void PostCreateDevice(IDirect3DDevice9 *device, D3DPRESENT_PARAMETERS *presentationParameters);

	void PreReset();
	void PostReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS *presentationParameters);
	
	void DrawUnder(IDirect3DDevice9* device, bool frameDrawn, bool sceneEnded);
	void DrawOver(IDirect3DDevice9* device, bool frameDrawn, bool sceneEnded);

	HWND gameWindow_ = nullptr;
	HMODULE dllModule_ = nullptr;
	WNDPROC baseWndProc_ = nullptr;

	uint screenWidth_ = 0, screenHeight_ = 0;
	bool firstFrame_ = true;
	bool forceReloadWheels_ = false;
	uint mapId_ = 0;
	std::array<wchar_t, 256> characterName_;
	uint tickSkip_ = 0;
	const uint TickSkipCount = 10;

	std::unique_ptr<UnitQuad> quad_;
	Effect* mainEffect_ = nullptr;

	ImFont *font_ = nullptr, *fontBlack_ = nullptr, *fontItalic_ = nullptr, *fontDraw_ = nullptr;

	std::vector<std::unique_ptr<Wheel>> wheels_;
	std::unique_ptr<CustomWheelsManager> customWheels_;
	
	std::unique_ptr<ConfigurationOption<bool>> firstMessageShown_;
	std::unique_ptr<ConfigurationOption<bool>> ignoreRTSS_;

	ImGuiContext* imguiContext_ = nullptr;
};
}
