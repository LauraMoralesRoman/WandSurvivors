#include "utils.hpp"
#include "defs.hpp"
#include <cstdio>
#include <string>
#include <filesystem>
#include <cassert>
#include <iostream>

namespace fs = std::filesystem;

void test_utils::Event::set() {
	std::lock_guard<std::mutex> lock(mtx);
	flag = true;
	cv.notify_all();
}

void test_utils::Event::clear() {
	std::lock_guard<std::mutex> lock(mtx);
	flag = false;
}

void test_utils::Event::wait() {
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [this](){ return flag; });
}

bool test_utils::Event::is_set() const {
	std::lock_guard<std::mutex> lock(mtx);
	return flag;
}

test_utils::FILERAII::~FILERAII() {
	std::fclose(self->file);
}

std::string test_utils::get_filename_from_FILE(FILE *file) {
    int fd = fileno(file);
    if (fd == -1) {
        std::cerr << "Error getting file descriptor" << std::endl;
        return "";
    }

    fs::path symlinkPath = fs::path("/proc/self/fd") / std::to_string(fd);
    try {
        if (fs::exists(symlinkPath) && fs::is_symlink(symlinkPath)) {
            return fs::read_symlink(symlinkPath);
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    }

    return "";
}

const test_utils::FILERAII test_utils::create_tmp_file() {
	FILE* tmp_file = std::tmpfile();
	assert(tmp_file);

	std::string path = get_filename_from_FILE(tmp_file);

	return test_utils::FILERAII {
		.name = path,
		.file = tmp_file,
		.fd = fileno(tmp_file)
	};
}
