#include<iostream>
#include<string>

int main()
{
int arr[] = {2,3,5,9,0,2,3,1,4,1,5,2,6,7,3,9,9,2,1};
int ptr[] = {2,1};
int start_index = -1;
int end_index = -1;

int n = sizeof(arr) / sizeof(arr[0]);
int m = sizeof(ptr) / sizeof(ptr[0]);
int j = 0;
bool found = false;

for (size_t i = 0; i < n; i++)
{
	if (arr[i] == ptr[j])
	{
		j++;
		if (j == m)
		{
			start_index = i - m + 1;
			end_index = i;
			found = true;
			break;
		}
	}
	else
	{
		j = 0;

	}
}

if (found)
	std::cout << "Pattern found from index " << start_index << " to " << end_index << std::endl;
else
	std::cout << "Pattern not found" << std::endl;
}