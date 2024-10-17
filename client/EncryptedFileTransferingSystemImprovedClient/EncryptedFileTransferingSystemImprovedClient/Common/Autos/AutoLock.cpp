#include "AutoLock.hpp"
#include "../Logging/Logger.hpp"

autos::AutoLock::AutoLock(std::shared_ptr<std::mutex> mutex)
    : m_mutex(std::move(mutex))
{
    m_mutex->lock();
}

autos::AutoLock::~AutoLock()
{
    try {
        m_mutex->unlock();
    } catch (const std::exception& ex) {
        LOG_WARNING(ex.what())
    }
}