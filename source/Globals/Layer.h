#pragma once

namespace EG
{
	enum Layer
	{
		LayerVisual = 1 << 0,
		LayerCanvas = 1 << 1,
		LayerCamera = 1 << 2
	};

	static unsigned int AllLayerMask()
	{
		return LayerVisual | LayerCanvas | LayerCamera;
	}
}