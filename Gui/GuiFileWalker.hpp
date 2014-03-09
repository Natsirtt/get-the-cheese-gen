#ifndef GUIFILEWALKER_HPP
#define GUIFILEWALKER_HPP

#include <vector>
#include <string>
#include "GuiElement.hpp"

class FileWalker : public GuiElement {
public:
	FileWalker(std::string directory, std::string filter);

    void update();
	void draw();
	void postEvent(SDL_Event* e);

	std::string getSelectedFile();

	double getWidth();
	double getHeight();

	void setAction(std::function<void ()> action);

private:
    std::vector<std::string> mFiles;
    int mScrolled;
    int mSelected;
    std::string mDirectory;
    std::string mFilter;
    int mMaxXSize;

    std::function<void ()> mAction;
};

#endif // GUIFILEWALKER_HPP
