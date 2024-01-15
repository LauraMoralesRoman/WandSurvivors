#pragma once
#include <condition_variable>
#include <string>


namespace test_utils {
	class Event {
	public:
		Event() : flag(false) {}

		void set(); 
		void clear();
		void wait();
		bool is_set() const;

	private:
		mutable std::mutex mtx;
		std::condition_variable cv;
		bool flag;
	};

	std::string get_filename_from_FILE(FILE* file);
	struct FILERAII {
			~FILERAII();

			std::string name;
			FILE* file;
			int fd;
	};

	const FILERAII create_tmp_file();
}
