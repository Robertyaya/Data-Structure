#include <bits/stdc++.h>

struct Request
{
  // Struct constructor
  Request(int arrive_time, int process_time) : arrive_time(arrive_time),
                                               process_time(process_time)
  {
  }

  int arrive_time;
  int process_time;
};

struct Response
{
  Response(bool dropped, int start_time) : dropped(dropped),
                                           start_time(start_time)
  {
  }
  bool dropped;
  int start_time;
};

std::vector<Request> ReadRequest()
{
  std::vector<Request> requests;
  int count;
  std::cin >> count;
  for (int i = 0; i < count; i++)
  {
    int arrive_time, process_time;
    std::cin >> arrive_time >> process_time;
    requests.push_back(Request(arrive_time, process_time));
  }
  return requests;
}

std::vector<Response> ProcessRequests(std::vector<Request> &requests, int buffer_size)
{
  // Boundary case
  std::vector<Response> responses;
  if (buffer_size == 0)
    return responses;

  // Record the time of packet which send to the processor
  std::queue<int> buffer;
  int OutBuffer_time = 0;

  for (int i = 0; i < requests.size(); i++)
  {
    // The buffer have the space, therefore the packet can put in
    if (buffer.size() < buffer_size)
    {
      // Update the OutBuffer_time
      if (OutBuffer_time < requests[i].arrive_time)
        OutBuffer_time = requests[i].arrive_time;

      responses.push_back(Response(false, OutBuffer_time));

      OutBuffer_time += requests[i].process_time;
      buffer.push(OutBuffer_time);
    }
    else // The buffer have no space, we need to check whether can pop out the first packet in buffer or dropped out
    {
      int front_outbufferTime = buffer.front();
      if (front_outbufferTime <= requests[i].arrive_time)
      {
        // Update the OutBuffer_time
        if (OutBuffer_time < requests[i].arrive_time)
          OutBuffer_time = requests[i].arrive_time;

        responses.push_back(Response(false, OutBuffer_time));
        OutBuffer_time += requests[i].process_time;

        buffer.pop();
        buffer.push(OutBuffer_time);
      }
      else
      {
        responses.push_back(Response(true, -1));
      }
    }
  }

  return responses;
}

void PrintResponse(std::vector<Response> &responses)
{
  // Boundary condition
  if (responses.size() == 0)
  {
    std::cout << "" << std::endl;
    return;
  }
  for (int i = 0; i < responses.size(); i++)
  {
    // If response is dropped, print -1 else print its start_time
    std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);

  int buffer_size;
  std::cin >> buffer_size;
  std::vector<Request> requests = ReadRequest();
  std::vector<Response> responses = ProcessRequests(requests, buffer_size);
  PrintResponse(responses);
  return 0;
}
