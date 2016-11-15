#ifndef SCENE_H_
#define SCENE_H_

#include "Data.h"
#include "Generator.h"
#include "SysTool.h"
#include <iostream>
#include <thread>
#include <chrono>


class Scene
{
public:
	~Scene();
	Scene(int, int, int = SysTool::TIME_LOW);

	template<typename... StringType>
	void execute(StringType&&... st)
	{
		while (true)
		{
			char ch = SysTool::getchNonBlocking();
			if (ch == 'q')
			{
				break;
			}
			else if (ch == 'p')
			{
				std::cin.get();
			}
			else if (ch == 'j')
			{
				millisec = (millisec == SysTool::TIME_LOW) ? millisec : millisec - 10;
			}
			else if (ch == 'k')
			{
				millisec = (millisec == SysTool::TIME_HIGH) ? millisec : millisec + 10;
			}
			showScene();
			std::for_each(data.begin(), data.end(), [&](Data & d){ d.refresh(generator, SysTool::COLOR_HEAD, SysTool::COLOR_BODY, SysTool::COLOR_TAIL, SysTool::COLOR_EMPTY, std::forward<StringType>(st)...); });
			std::this_thread::sleep_for(std::chrono::milliseconds(millisec));
		}
	}
private:
	const int COLS;
	Generator generator;
	vector<Char **> scene;
	vector<Data> data;
	int millisec;

	void showScene();
};

#endif