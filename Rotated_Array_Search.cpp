#include<iostream>
#include<vector>
using namespace std;

int searchInRotatedArray(vector<int> nums, int target) {
	int n = nums.size();

	// Logic
	int start = 0;
	int end = n - 1;

	while(start <= end) {
		int mid = (start + end) / 2;

		if(nums[mid] == target) {
			return mid;
		}

		// Two cases
		if(nums[start] <= nums[mid]) {
			// Left
			if(target >= nums[start] && target <= nums[mid]) {
				end = mid - 1;
			} else {
				start = mid + 1;
			}
		} else {
			// Right
			if(target >= nums[mid] && target <= nums[end]) {
				start = mid + 1;
			} else {
				end = mid - 1;
			}
		}
	}

	return -1;
}

int main() {
	vector<int> nums{4, 5, 6, 7, 0, 1, 2, 3};
	int target;
	cin >> target;
	cout << searchInRotatedArray(nums, target) << endl;
	return 0;
}
