#ifndef FPS_GRAPH_H
#define FPS_GRAPH_H
#include <vector>

class FpsGraph 
{

private:
	char title[25]="FPS";
	std::vector<float> fps_log;
	std::vector<float> ms_log;
public:
	FpsGraph();
	void Draw();
	void addFps(float fps);
	void addMiliseconds(float milisecond);
};

#endif // !FPS_GRAPH_H

