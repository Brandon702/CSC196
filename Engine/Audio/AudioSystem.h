#pragma once

#include <fmod.hpp>
#include <string>
#include <map>

namespace nc
{
	class AudioSystem
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);

		void AddAudio(const std::string& name, const std::string& filename);
		void PlayAudio(const std::string& name, bool loop = false);

		void StopLoopChannel();
	private:
		FMOD::System* m_system;
		std::map<std::string, FMOD::Sound*> m_sounds;
		FMOD::Channel* m_loopChannel{ nullptr };
	};
}
extern nc::AudioSystem g_audioSystem;