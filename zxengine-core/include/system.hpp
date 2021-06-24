#pragma once
#include "iLayer.hpp"
namespace zx
{

	class iSystem : public iLayer
	{
	public:
		iSystem(layer_id layer = 0) : iLayer(layer) {}
		virtual void initialize(){}
		virtual void awake() {}
		virtual void start() {}

		virtual void early_update() {}
		virtual void update() {}
		virtual void late_update() {}

		virtual void pre_render() {}
		virtual void render() {}
		virtual void post_render() {}

		virtual void exit() {}

	};
	template<std::derived_from<iSystem> T>
	class LayerSystem : public iSystem, public LayerGroup<T>
	{
	protected:
		LayerGroup<T>::set& layerSet() { return LayerGroup<T>::pm_Layers; }
	public:

		void initialize() override
		{
			for (auto l : layerSet())
				l->initialize();
		}
		void awake() override
		{
			for (auto l : layerSet())
				l->awake();
		}
		void start() override 
		{
			for (auto l : layerSet())
				l->start();
		}
		void early_update() override 
		{
			for (auto l : layerSet())
				l->early_update();
		}
		void update() override 
		{
			for (auto l : layerSet())
				l->update();
		}
		void late_update() override 
		{
			for (auto l : layerSet())
				l->late_update();
		}
		void pre_render() override 
		{
			for (auto l : layerSet())
				l->pre_render();
		}
		void render() override 
		{
			for (auto l : layerSet())
				l->render();
		}
		void post_render() override
		{
			for (auto l : layerSet())
				l->post_render();
		}

		void exit() override
		{
			for (auto l : layerSet())
				l->exit();
		}
	};
}