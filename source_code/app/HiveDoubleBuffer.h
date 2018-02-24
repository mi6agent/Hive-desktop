#ifndef HIVEDOUBLEBUFFER_H
#define HIVEDOUBLEBUFFER_H

#include <list>
#include <iostream>

template <typename T>
class HiveDoubleBuffer final
{
public:
  HiveDoubleBuffer();

  void push_front(T item);
  bool pop_front(T item);

private:
  using Container = std::list<T>;
  Container buffer1;
  Container buffer2;
  bool reading = false;
  bool writing = false;
  bool isFliping = false;

  Container *inbound_buffer = &buffer1;
  Container *outbound_buffer = &buffer2;

  void flip();
};

template<typename T>
HiveDoubleBuffer<T>::HiveDoubleBuffer()
{

}

template<typename T>
void HiveDoubleBuffer<T>::push_front(T item)
{
  while(1)
    {
      if(isFliping)
        {
          //do something is better
          continue;
        }

      writing = true;
      inbound_buffer->push_front(item);
      writing = false;
      break;
    }
}

template<typename T>
bool HiveDoubleBuffer<T>::pop_front(T item)
{
  while(1)
    {
      if(isFliping)
        {
          //do something is better
          continue;
        }
      if(outbound_buffer->empty())
        {
          flip();
          if(outbound_buffer->empty())
            {
              printf("buffer empty \n");
              return false;
            }
        }
      reading = true;
      item = outbound_buffer->front();
      printf("%s\n", item);
//      outbound_buffer->pop_front();
      reading = false;
      break;
    }
  return true;
}

template<typename T>
void HiveDoubleBuffer<T>::flip()
{
  isFliping = true;
  while(1)
    {
      if(writing || reading)
        {
          //do something is better
          continue;
        }
      Container *temp = inbound_buffer;
      inbound_buffer = outbound_buffer;
      outbound_buffer = temp;
      break;
    }
  printf("flipped\n");
  isFliping = false;
}










#endif // HIVEDOUBLEBUFFER_H