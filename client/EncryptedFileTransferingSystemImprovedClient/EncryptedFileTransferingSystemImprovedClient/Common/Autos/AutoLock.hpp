#pragma once
#include <memory>
#include <mutex>

namespace autos {
class AutoLock {
public:
    explicit AutoLock(std::shared_ptr<std::mutex> mutex);

    ~AutoLock();

    AutoLock(const AutoLock&) = delete;

    AutoLock(AutoLock&&) = delete;

    AutoLock& operator=(const AutoLock&) = delete;

    AutoLock& operator=(AutoLock&&) = delete;

private:
    std::shared_ptr<std::mutex> m_mutex;
};
};
