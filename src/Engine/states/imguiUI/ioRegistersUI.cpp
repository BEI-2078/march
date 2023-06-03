#include "imguiUI.hpp"

void Engine::imguiUI::ioRegisterUI()
{
	if(ImGui::Begin("inputButtons", nullptr, windowFlags | ImGuiWindowFlags_NoTitleBar))
	{
		inputButtonsUIWidth = this->m_data->size.x - dmaUIWidth * 2 - padding * 4;
		ImGui::SetWindowSize(ImVec2(inputButtonsUIWidth, inputButtonsUIHeight));
		ImGui::SetWindowPos(ImVec2(dmaUIWidth + 2 * padding, this->m_data->size.y - inputButtonsUIHeight - padding));


	} 	
}
