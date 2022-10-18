#ifndef SHARED_BUFFER
#define SHARED_BUFFER

#include <string>
#include <queue>
#include <condition_variable>

template <class T>
class sharedBuff {
public:
	sharedBuff() = default;
	~sharedBuff() = default;

	void inline push(T t) {
		{
			std::lock_guard<std::mutex> lockBuff(mtx);
			elemBuff.push(t);
		}
		cond.notify_one();
	}

	T inline pull() {
		std::unique_lock<std::mutex> lockBuff(mtx);

		while (elemBuff.empty())
		{
			cond.wait(lockBuff);
		}

		T pulledElem = elemBuff.front();
		elemBuff.pop();
		return pulledElem;
	}
private:
	std::queue<T> elemBuff;
	mutable std::mutex mtx;
	std::condition_variable cond;
};

#endif /* SAFE_QUEUE */