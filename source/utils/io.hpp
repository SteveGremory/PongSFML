#pragma once

#include <SFML/Audio.hpp>
#include <filesystem>
#include <string_view>

namespace utils {
inline auto load_sound(sf::SoundBuffer& buffer, const std::string_view path) {
	try {
		std::filesystem::path sound_path(path);
		if (!buffer.loadFromFile(sound_path)) {
			// Handle error - sound file not found
			throw std::filesystem::filesystem_error("Could not open ", path,
													std::error_code());
		}
	} catch (...) {
		throw;
	}
}
} // namespace utils
