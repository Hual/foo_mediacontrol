#pragma once

#include <map>
#include <vector>

typedef std::map<const char*, wchar_t*> track_data_map;
typedef std::vector<Platform::String^> genre_data_vector;

class track_data {
public:
	track_data(metadb_handle_ptr metadb_data);
	~track_data();

	inline track_data_map& get() {
		return m_data;
	}

	inline wchar_t* get(const char* key) {
		return m_data.find(key)->second;
	}

	inline wchar_t* get_title() {
		return get("title");
	}

	inline wchar_t* get_artist() {
		return get("artist");
	}

	inline wchar_t* get_album_artist() {
		return get("album artist");
	}

	inline wchar_t* get_album() {
		return get("album");
	}

	inline wchar_t* get_track_number() {
		return get("track number");
	}

	inline genre_data_vector& get_genres() {
		return m_genres;
	}

	inline album_art_data::ptr& get_album_art() {
		return m_album_art;
	}

private:
	track_data_map m_data = {
		{ "title", empty },
		{ "artist", empty },
		{ "album artist", empty },
		{ "album", empty },
		{ "track number", empty }
	};
	
	genre_data_vector m_genres;
	album_art_data::ptr m_album_art = nullptr;

	static wchar_t* const empty;
	static wchar_t* const genre_separator;
};
