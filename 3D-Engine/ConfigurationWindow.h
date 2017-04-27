#ifndef CONFIG_WINDOW_H
#define CONFIG_WINDOW_H
#include "FpsGraph.h"
class ConfigurationWindow 
{

private:
	char titleFps[25] = "FPS";
	std::vector<float> fps_log;
	std::vector<float> ms_log;

public:
	void addFps(float fps);
	void addMiliseconds(float milisecond);
	ConfigurationWindow();
	void Draw();
};

#endif // !CONFIG_WINDOW_H

