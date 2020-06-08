#include <bits/stdc++.h>

struct thread
{
  thread(long long arrive_time, long long end_time, int thread_index) : arrive_time(arrive_time), end_time(end_time), thread_index(thread_index)
  {
  }

  long long arrive_time;
  long long end_time;
  int thread_index;
};

struct cmp
{
  bool operator()(const thread a, const thread b)
  {
    if (a.end_time == b.end_time)
      return a.thread_index > b.thread_index;
    return a.end_time > b.end_time;
  }
};

void Solve(std::vector<long long> &vec, int thread_num)
{
  std::priority_queue<thread, std::vector<thread>, cmp> thread_queue;
  std::vector<std::pair<int, long long>> answer;

  for (int i = 0; i < vec.size(); i++)
  {
    if (thread_queue.size() < thread_num)
    {
      thread temp((long long)0, (long long)vec[i], i);
      thread_queue.push(temp);
      answer.push_back(std::make_pair(temp.thread_index, temp.arrive_time));
    }
    else
    {
      thread previous = thread_queue.top();
      thread current(previous.end_time, previous.end_time + vec[i], previous.thread_index);
      thread_queue.pop();
      thread_queue.push(current);
      answer.push_back(std::make_pair(current.thread_index, current.arrive_time));
    }
  }

  // Output answer
  for (int i = 0; i < answer.size(); i++)
    std::cout << answer[i].first << " " << answer[i].second << std::endl;
}
int main()
{
  std::ios_base::sync_with_stdio(false);

  std::vector<long long> vec;
  int thread_num;
  int n;
  std::cin >> thread_num >> n;
  for (int i = 0; i < n; i++)
  {
    long long temp;
    std::cin >> temp;
    vec.push_back(temp);
  }

  Solve(vec, thread_num);
  return 0;
}
