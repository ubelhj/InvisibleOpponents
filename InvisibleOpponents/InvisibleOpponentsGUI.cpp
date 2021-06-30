#include "pch.h"
#include "InvisibleOpponents.h"

std::string InvisibleOpponents::GetPluginName() {
	return "Free Flight";
}

void InvisibleOpponents::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void InvisibleOpponents::RenderSettings() {
	CVarWrapper enableCvar = cvarManager->getCvar("invisible_opponents_enabled");

	if (!enableCvar) {
		return;
	}

	bool enabled = enableCvar.getBoolValue();

	if (ImGui::Checkbox("Enable plugin", &enabled)) {
		enableCvar.setValue(enabled);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Toggle having invisible opponents");
	}

	ImGui::TextUnformatted("Makes the other team invisible");

	ImGui::NewLine();

	ImGui::TextUnformatted("Controls for spectators only");

	CVarWrapper blueInvisibleCvar = cvarManager->getCvar("invisible_opponents_enable_blue");

	if (!blueInvisibleCvar) {
		return;
	}

	bool blueInvisibleEnable = blueInvisibleCvar.getBoolValue();

	if (ImGui::Checkbox("Make blue invisible", &blueInvisibleEnable)) {
		blueInvisibleCvar.setValue(blueInvisibleEnable);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("If checked, blue is invisible");
	}

	CVarWrapper orangeInvisibleCvar = cvarManager->getCvar("invisible_opponents_enable_orange");

	if (!orangeInvisibleCvar) {
		return;
	}

	bool orangeInvisibleEnable = orangeInvisibleCvar.getBoolValue();

	if (ImGui::Checkbox("Make orange invisible", &orangeInvisibleEnable)) {
		orangeInvisibleCvar.setValue(orangeInvisibleEnable);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("If checked, orange is invisible");
	}

	ImGui::Separator();

	ImGui::TextUnformatted("Plugin commissioned by Frowzy and Striped");
	ImGui::TextUnformatted("youtube.com/c/frowzySquirrel/");
	ImGui::TextUnformatted("youtube.com/c/striped/");
	ImGui::TextUnformatted("Plugin made by JerryTheBee#1117 - DM me on discord for custom plugin commissions!");
}

/*
// Do ImGui rendering here
void InvisibleOpponents::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
}

// Name of the menu that is used to toggle the window.
std::string InvisibleOpponents::GetMenuName()
{
	return "InvisibleOpponents";
}

// Title to give the menu
std::string InvisibleOpponents::GetMenuTitle()
{
	return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void InvisibleOpponents::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool InvisibleOpponents::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool InvisibleOpponents::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void InvisibleOpponents::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void InvisibleOpponents::OnClose()
{
	isWindowOpen_ = false;
}
*/
