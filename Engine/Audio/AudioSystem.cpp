#include "pch.h"
#include "AudioSystem.h"

nc::AudioSystem g_audioSystem;

namespace nc
{
	void AudioSystem::Startup()
	{
		FMOD::System_Create(&m_system);

		void* extradriverdata = nullptr;
		m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	}

	void AudioSystem::Shutdown()
	{
		for (auto& sound : m_sounds)
		{
			sound.second->release();
		}
		m_sounds.clear();

		m_system->close();
		m_system->release();
	}

	void AudioSystem::Update(float dt)
	{
		m_system->update();
	}

	void AudioSystem::AddAudio(const std::string& name, const std::string& filename)
	{
		if (m_sounds.find(name) == m_sounds.end())
		{
			FMOD::Sound* sound{ nullptr };
			m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
			m_sounds[name] = sound;
		}
	}

	void AudioSystem::PlayAudio(const std::string& name, bool loop)
	{
		auto iter = m_sounds.find(name);
		if (iter != m_sounds.end())
		{
			FMOD::Sound* sound = iter->second;
			FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
			sound->setMode(mode);
			FMOD::Channel* channel;
			m_system->playSound(sound, 0, false, &channel);
			// hack
			if (loop)
			{
				m_loopChannel = channel;
			}
		}
	}
	void AudioSystem::StopLoopChannel()
	{
		if (m_loopChannel) m_loopChannel->stop();
	}
}
