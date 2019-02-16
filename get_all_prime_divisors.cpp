#include<iostream>
#include<list>
#include<math.h>
bool is_prime(uint64_t n)
{
    bool result = false;
    uint64_t sq_num = sqrt(n);
    //std::cout<<"sq_num "<<sq_num;

    for (int i = 2; i < sq_num; i++)
    {   
//	    std::cout<<"i = "<<i;
	if (n % i == 0)
	    return result;
    
    }
  //  std::cout<<std::endl;
    result = true;
    return result;
 }

std::list<uint64_t> get_all_prime_divisors(uint64_t n)
{
    std::list<uint64_t> div_list;
    for (uint64_t i = 2; i <= n; i++)
    {
	 if (is_prime(i) )
         { 
	    std::cout<<i<<" ";
            //div_list.push_front(i);
         }
    }
}

int main()
{
	std::list<uint64_t> temp = get_all_prime_divisors(100);
	/* std::list<uint64_t>::iterator i;
	for (i = temp.begin(); i != temp.end(); i++)
	{
	    printf("%ld ", *i);

	}*/
return 0;
}
