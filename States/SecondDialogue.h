#ifndef SecondDialogue_H
#define SecondDialogue_H

#include "../State.h"
#include <fstream>

class SecondDialogue: public State
{
public:
    SecondDialogue();
    ~SecondDialogue();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    unsigned int currentFrame;
    unsigned int lastFrame;
    unsigned int lineCurrentSize;
    std::fstream currentFile;
    std::string line;
    std::string showingLine;
};

#endif // SecondDialogue_H
