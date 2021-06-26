#pragma once
#include "iLayer.hpp"
#include <string_view>
#include "event.hpp"
#include "time.hpp"
namespace zx
{
	struct SystemConstructEventData : public EventData
	{
		std::string_view stackKey;
		bool appBlocking = true;
	};
	class iLayerSystem;
	class iSystem : public iLayer
	{
	public:
		inline iSystem(layer_id layer = 0) 
			: iLayer(layer), pm_ParentSystem(nullptr), pm_TimeScale(1.0f) {}

		

		
		[[nodiscard]] inline float timescale() const noexcept { return pm_TimeScale; }
		[[nodiscard]] inline float& timescale() noexcept { return pm_TimeScale; }

		[[nodiscard]] inline std::string_view stackKey() const noexcept { return pm_StackKey; }

		[[nodiscard]] inline iLayerSystem* parent() const noexcept { return pm_ParentSystem; }


		virtual void initialize() {}
		virtual void awake() {}
		virtual void start() {}

		virtual void early_update() {}
		virtual void update() {}
		virtual void late_update() {}

		virtual void pre_render() {}
		virtual void render() {}
		virtual void post_render() {}

		virtual void exit() {}


		Event<SystemConstructEventData> onSystemInit;
		Event<SystemConstructEventData> onSystemDispose;

		inline void ReleaseSystem() noexcept { pm_ApplicationBlocking = false; }

		inline void LocalTimeUpdate(float parentTimeScale) noexcept
		{
			pm_TimeStep = zx::timestep(time::delta().seconds() * pm_TimeScale * parentTimeScale);
		}
		void LayerAdded() override;
		void LayerRemoved() override;
		
	protected:
		[[nodiscard]] inline std::string& stackKey() noexcept { return pm_StackKey; }
	private:
		bool pm_ApplicationBlocking = true;
		std::string pm_StackKey = "";
		float pm_TimeScale;
		zx::timestep pm_TimeStep;
		iLayerSystem* pm_ParentSystem;


		inline void SetParent(iLayerSystem* parent) noexcept
		{
			pm_ParentSystem = parent;
		}
		inline void SystemInitialize()
		{
			initialize();
		}
		inline void SystemStart()
		{
			start();
		}
		inline void SystemAwake()
		{
			awake();
		}
		inline void SystemEarlyUpdate()
		{
			early_update();
		}
		inline void SystemUpdate()
		{
			
			update();
		}
		inline void SystemLateUpdate()
		{
			late_update();
		}
		inline void SystemPreRender()
		{
			pre_render();
		}
		inline void SystemRender()
		{
			render();
		}
		inline void SystemPostRender()
		{
			post_render();
		}
		inline void SystemExit()
		{
			exit();
			
		}


		template<std::derived_from<iSystem> T>
		friend class LayerSystem;
	};

	class iLayerSystem : public iSystem
	{

	public:
		[[nodiscard]] inline float timescale() const noexcept { return pm_TimeScale; }
		[[nodiscard]] inline float& timescale() noexcept { return pm_TimeScale; }

		[[nodiscard]] inline const zx::timestep& deltaTime() const noexcept { return pm_TimeStep; }


		inline void LocalTimeUpdate() noexcept
		{
			pm_TimeStep = zx::timestep(time::delta().seconds() * pm_TimeScale);
		}
		virtual void Remove(iSystem* system) = 0;


	private:
		float pm_TimeScale = 1.0f;
		zx::timestep pm_TimeStep;

	};


	template<std::derived_from<iSystem> T>
	class LayerSystem : public iLayerSystem, public LayerGroup<T>
	{
	protected:
		[[nodiscard]] LayerGroup<T>::set& layerSet() noexcept { return LayerGroup<T>::pm_Layers; }


		void LayerAdded(T* layer) override {
			layer->SetParent(this);
			layer->LayerAdded();
		}
		void LayerRemoved(T* layer) override {
			layer->LayerRemoved();
		}
	public:
		void Remove(iSystem* system) override {
			LayerGroup<T>::Remove(static_cast<T*>(system));
		}
		inline void initialize() override {
			for (auto l : layerSet())
				l->SystemInitialize();
		}
		inline void awake() override {
			for (auto l : layerSet())
				l->SystemAwake();
		}
		inline void start() override {
			for (auto l : layerSet())
				l->SystemStart();
		}
		inline void early_update() override {
			for (auto l : layerSet())
				l->SystemEarlyUpdate();
		}
		inline void update() override {
			for (auto l : layerSet())
			{
				l->LocalTimeUpdate(timescale());
				l->SystemUpdate();
			}
		}
		inline void late_update() override {
			for (auto l : layerSet())
				l->SystemLateUpdate();
		}
		inline void pre_render() override {
			for (auto l : layerSet())
				l->SystemPreRender();
		}
		inline void render() override {
			for (auto l : layerSet())
				l->SystemRender();
		}
		inline void post_render() override {
			for (auto l : layerSet())
				l->SystemPostRender();
		}
		inline void exit() override {
			for (auto l : layerSet())
				l->SystemExit();
		}
	};
}