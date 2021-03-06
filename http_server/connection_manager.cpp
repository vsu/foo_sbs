//
// connection_manager.cpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2011 Victor C. Su
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection_manager.hpp"
#include <algorithm>
#include <boost/bind.hpp>

namespace http
{
namespace server
{

void connection_manager::start(connection_ptr c)
{
    connections_.insert(c);
    c->start();
}

void connection_manager::stop(connection_ptr c)
{
    connections_.erase(c);
    c->stop();
}

void connection_manager::stop_all()
{
    std::for_each(connections_.begin(), connections_.end(),
                  boost::bind(&connection::stop, _1));
    connections_.clear();
}

std::set<connection_ptr> connection_manager::get_connections()
{
    return connections_;
}

void connection_manager::send_data_all(void * data, size_t length)
{
    std::set<connection_ptr>::const_iterator c;
    for (c = connections_.begin(); c != connections_.end(); ++c)
    {
        ((connection_ptr)(*c))->send_data(data, length);
    }
}

} // namespace server
} // namespace http