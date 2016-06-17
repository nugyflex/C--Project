#pragma once
#include "CollisionDetection.h"
#include "gameController.h"
#include "Graphics.h"
#include "levelEditor.h"
class editorLevel : public gameLevel
{
protected:
	levelEditor* LevelEditor;
public:
	void HandleInput() override;
	void Load() override;
	void Update() override;
	void Render() override;
	void Unload() override;
};