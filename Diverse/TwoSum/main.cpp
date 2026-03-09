
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

 vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        int ind1=-1, ind2=-1;
        
        for(int i = 0; i < nums.size(); i ++)
        {
            int dif = target - nums[i];
            if(m.find(dif) != m.end())
            {
                ind1 = i;
                ind2 = m[dif];
                break;
            }
            m[nums[i]] = i;
        }
        return {ind1, ind2};
 }

int main()
{
     vector<int> v = {2,7,11,15};
     int target = 9;
     vector<int> rez = twoSum(v, target);
     for(int i = 0; i < rez.size(); i ++)
     {
         cout << rez[i] << " ";
     }
     cout << endl;
    return 0;
}