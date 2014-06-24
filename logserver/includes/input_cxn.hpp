#ifndef INPUT_CXN_HPP
#define INPUT_CXN_HPP

#include <cstdint>

#include <ev++.h>

#include "iobuf.hpp"

namespace input_cxn {

class accept_handler {
public:
	accept_handler(int fd);
	void io_cb(ev::io &watcher, int revents);
	~accept_handler();
private:
	ev::io io;
};

class handler {
private:
	iobuf read_queue;
	size_t to_read;
	uint32_t state;
	ev::io io;

public:
	handler(int fd);
	~handler();
	void io_cb(ev::io &watcher, int revents);
private:
	void suicide(); /* get yourself ready for suspension (e.g., stop loop activity) if safe, just delete self */
	/* could implement move operators, but others are odd */
	handler & operator=(handler other);
	handler(const handler &);
	handler(const handler &&other);
	handler & operator=(handler &&other);
};

};
#endif
