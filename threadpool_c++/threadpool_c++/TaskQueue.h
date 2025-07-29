#pragma once
#include<queue>
#include<pthread.h>
using namespace std;

//��������ṹ��
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

//�������
template <typename T>
class TaskQueue
{
public:
	TaskQueue();
	~TaskQueue();

	//�������
	void addTask(Task<T> &task);
	void addTask(callback f, void* arg);
	//ȡ��һ������
	Task<T> taskTask();
	//��ȡ��ǰ����ĸ���
	inline size_t taskNumber()
	{
		return m_taskQ.size();
	}

private:
	pthread_mutex_t m_mutex;
	queue<Task<T>> m_taskQ;
};

