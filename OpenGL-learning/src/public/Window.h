#pragma once

#include <string>

class Window
{
public:
	Window(unsigned int width, unsigned int height, const std::string& title);

	void OnUpdate();
	void ShutDown();
	bool ShouldClose() const;

	void* GetNativeWindow() const { return m_Window; }

private:
	void* m_Window;

};