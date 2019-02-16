#include<iostream>
#include<cmath>
#include<list>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
using namespace std;

bool is_prime(uint64_t n)
{
    uint64_t sq = sqrt(n);
    bool result = false;
    for (uint64_t i = 2; i <= sq; i++)
    {
        if (n % i == 0)
	    return result;
	    
    }
    result = true;
    return result;
}
list<uint64_t> get_all_prime_divisors(uint64_t n)
{

   list<uint64_t> div_list;
   for (uint64_t i = 2; i <= n; i++)
   {
       if (is_prime(i) && n % i == 0)
       {
           div_list.push_front(i);
       }
   }
  return div_list;
}
string name_;
string jabberwocky(string s)
{
  name_ = s;
  int name_len = name_.length();
  for (int i = 0; i < name_len; i += 2)
  {
     if (i + 1 < name_len)
     {
         char temp = name_[i];
	 name_[i] = name_[i + 1];
	 name_[i + 1] = temp;
     }
     else
         break;
  }
  
  return name_;
}
uint64_t power(char c, uint64_t sk_)
{
    if (sk_ == 0) 
        return 1;
    if (sk_ % 2 == 0)
	return power(c * c, sk_ / 2);
    return c * power(c * c, sk_ / 2);
}
int main()
{
  list<uint64_t> div_list = get_all_prime_divisors(100000);
  auto it = div_list.begin();
  for (; it != div_list.end();it++)
  {
      cout<<*it<<" ";
  }
  cout<<endl;
  string test = jabberwocky("caitianxung");
  cout<<test<<endl;
  cout<<power(2,5)<<endl;
  char data_[1024*1024];
  string filename = "test.data";
  int fd = open(filename.c_str(), O_RDONLY);
  if (fd == -1)
      perror("open failed");
  ssize_t nread = read(fd, data_, sizeof(data_) - 1);
  data_[nread] = '\0';
  cout<<data_<<endl;
  
  uint64_t sn_ = 5, sk_ = 3;
   int fdout = open("letter", O_WRONLY|O_CREAT, 0666);
  if (fd == -1)
       perror("open letter failed");

  uint64_t i = 0, temp;
  while (data_[i] != '\0')
  {
      temp = power(data_[i], sk_) % sn_;
      ssize_t nwrite =  write(fdout, &temp, sizeof(temp));
      i++;
  }
  close(fdout);
  
  return 0;
}

