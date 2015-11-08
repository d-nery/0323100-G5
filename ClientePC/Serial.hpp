#pragma once

#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <string>

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

namespace IntroEE {
	class Serial {
	private:
		int fd;
		struct termios tty;

	public:
		Serial(std::string dev);
		~Serial();
		int read(std::string& str);
		void write(std::string data);
	};
}
