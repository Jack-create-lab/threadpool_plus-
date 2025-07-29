#pragma once
#include<queue>
#include<pthread.h>
using namespace std;

//定义任务结构体
using callback = void(*)(void*);
template <typename T>
struct Task
{
	Task<T>()
	{
		function = nullptr;
		arg = nullptr;
	}
	Task<T>(callback f, void* arg)
	{
		function = f;
		this->arg = (T*)arg;
	}
	callback function;
	T* arg;
};

//任务队列
template <typename T>
class TaskQueue
{
public:
	TaskQueue();
	~TaskQueue();

	//添加任务
	void addTask(Task<T> &task);
	void addTask(callback f, void* arg);
	//取出一个任务
	Task<T> taskTask();
	//获取当前任务的个数
	inline size_t taskNumber()
	{
		return m_taskQ.size();
	}

private:
	pthread_mutex_t m_mutex;
	queue<Task<T>> m_taskQ;
};

